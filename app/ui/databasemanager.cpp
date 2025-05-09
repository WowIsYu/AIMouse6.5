#include "DatabaseManager.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

const QString DatabaseManager::UserConnectionName = "UserInfoConnection";
const QString DatabaseManager::HnnkConnectionName = "HnnkInfoConnection";

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    // 初始化用户数据库连接
    if (QSqlDatabase::contains(UserConnectionName)) {
        m_db = QSqlDatabase::database(UserConnectionName);
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE", UserConnectionName);
    }

    // 初始化医疗数据库连接
    if (QSqlDatabase::contains(HnnkConnectionName)) {
        m_hnnkDb = QSqlDatabase::database(HnnkConnectionName);
    } else {
        m_hnnkDb = QSqlDatabase::addDatabase("QSQLITE", HnnkConnectionName);
    }
}

DatabaseManager::~DatabaseManager() {
    if (m_db.isOpen()) m_db.close();
    if (m_hnnkDb.isOpen()) m_hnnkDb.close();
}


bool DatabaseManager::initializeUserDatabase() {
    //设置数据库保存路径
    QString baseDir = QDir::cleanPath(QCoreApplication::applicationDirPath() + "/data");
    if (!QDir().mkpath(baseDir)) {
        qWarning() << "Failed to create directory:" << baseDir;
        return false;
    }
    //设置数据表名
    QString dbPath = baseDir + "/user_info.db";
    m_db.setDatabaseName(dbPath);
    qDebug() << "Database path:" << dbPath;
    //开启数据库
    if (!m_db.open()) {
        logError(m_db.lastError(), "open database");
        return false;
    }
    return createUserTables();
}

bool DatabaseManager::initializeHnnkDatabase()
{
    //设置数据库保存路径
    QString baseDir = QDir::cleanPath(QCoreApplication::applicationDirPath() + "/data");
    if (!QDir().mkpath(baseDir)) {
        qWarning() << "Failed to create directory:" << baseDir;
        return false;
    }
    //设置数据表名
    QString dbPath = baseDir + "/hnnk_info.db";
    m_hnnkDb.setDatabaseName(dbPath);
    qDebug() << "Database path:" << dbPath;
    //开启数据库
    if (!m_hnnkDb.open()) {
        logError(m_hnnkDb.lastError(), "open database");
        return false;
    }
    return createHnnkTables();
}

bool DatabaseManager::createHnnkTables() {
    QSqlQuery query(m_hnnkDb);
    bool ok = query.exec(
        "CREATE TABLE IF NOT EXISTS hnnk_data ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "mid INTEGER NOT NULL,"
        "account TEXT NOT NULL,"
        "addtime TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "start_time TIMESTAMP,"
        "end_time TIMESTAMP,"
        "eeg FLOAT DEFAULT 0,"
        "eog FLOAT DEFAULT 0,"
        "body_movement_value FLOAT DEFAULT 0,"
        "med_value FLOAT DEFAULT 0,"
        "min_value FLOAT DEFAULT 0,"
        "max_value FLOAT DEFAULT 0,"
        "avg_value FLOAT DEFAULT 0,"
        "event TEXT)"
        );
    if (!ok) {
        logError(query.lastError(), "create hnnk_data");
    }
    return ok;
}


bool DatabaseManager::createUserTables() {
    QSqlQuery query(m_db);
    bool ok = query.exec(
        "CREATE TABLE IF NOT EXISTS tb_user ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "account TEXT NOT NULL UNIQUE,"
        "uid INTEGER,"
        "password TEXT,"
        "nickname TEXT,"
        "headImgUrl TEXT,"
        "save_passwd INTEGER DEFAULT 0,"
        "local_register INTEGER DEFAULT 0,"
        "addtime TIMESTAMP DEFAULT CURRENT_TIMESTAMP)"
        );
    if (!ok) {
        logError(query.lastError(), "create tb_user");
        return false;
    }
    ok = query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx_account ON tb_user(account)");
    if (!ok) {
        logError(query.lastError(), "create index");
    }
    return ok;
}

qint64 DatabaseManager::insertUser(const User &user) {
    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO tb_user (account, uid, password, nickname, headImgUrl, save_passwd, local_register, addtime)"
        " VALUES (:account, :uid, :password, :nickname, :headImgUrl, :save_passwd, :local_register, :addtime)"
        );
    query.bindValue(":account", user.account);
    query.bindValue(":uid", user.uid);
    query.bindValue(":password", user.password);
    query.bindValue(":nickname", user.nickname);
    query.bindValue(":headImgUrl", user.headImgUrl);
    query.bindValue(":save_passwd", user.savePassword);
    query.bindValue(":local_register", user.localRegister);
    query.bindValue(":addtime", user.addTime.isValid() ? user.addTime : QDateTime::currentDateTime());

    if (!query.exec()) {
        m_lastError = query.lastError();
        logError(m_lastError, "insertUser");
        return -1;
    }
    return query.lastInsertId().toLongLong();
}

bool DatabaseManager::userExists(const QString &account) const {
    QSqlQuery query(m_db);
    query.prepare("SELECT COUNT(1) FROM tb_user WHERE account = :account");
    query.bindValue(":account", account);
    if (!query.exec() || !query.next()) {
        const_cast<DatabaseManager*>(this)->m_lastError = query.lastError();
        logError(m_lastError, "userExists");
        return false;
    }
    return query.value(0).toInt() > 0;
}

QList<User> DatabaseManager::getAllUsers() const {
    QList<User> users;
    QSqlQuery query(m_db);
    if (!query.exec("SELECT * FROM tb_user")) {
        const_cast<DatabaseManager*>(this)->m_lastError = query.lastError();
        logError(m_lastError, "getAllUsers");
        return users;
    }
    while (query.next()) {
        User u;
        u.id = query.value("id").toLongLong();
        u.account = query.value("account").toString();
        u.uid = query.value("uid").toLongLong();
        u.password = query.value("password").toString();
        u.nickname = query.value("nickname").toString();
        u.headImgUrl = query.value("headImgUrl").toString();
        u.savePassword = query.value("save_passwd").toBool();
        u.localRegister = query.value("local_register").toBool();
        u.addTime = query.value("addtime").toDateTime();
        users.append(u);
    }
    return users;
}

QSqlError DatabaseManager::lastError() const {
    return m_lastError;
}

void DatabaseManager::logError(const QSqlError &err, const QString &context) const {
    qWarning() << "[DatabaseManager]" << context << "error:" << err.text();
}

// 查询单个用户
User DatabaseManager::getUserByAccount(const QString &account) const {
    QSqlQuery q(m_db);
    q.prepare("SELECT * FROM tb_user WHERE account=:acct");
    q.bindValue(":acct", account);
    if (!q.exec() || !q.next()) {
        const_cast<DatabaseManager*>(this)->m_lastError = q.lastError();
        return User{};               // id == 0，视为未找到
    }
    User u;
    u.id             = q.value("id").toLongLong();
    u.account        = q.value("account").toString();
    u.uid            = q.value("uid").toLongLong();
    u.password       = q.value("password").toString();
    u.nickname       = q.value("nickname").toString();
    u.headImgUrl     = q.value("headImgUrl").toString();
    u.savePassword   = q.value("save_passwd").toBool();
    u.localRegister  = q.value("local_register").toBool();
    u.addTime        = q.value("addtime").toDateTime();
    return u;
}

// 更新 save_passwd 字段
bool DatabaseManager::updateSavePassword(const QString &account, bool save) {
    QSqlQuery q(m_db);
    q.prepare("UPDATE tb_user SET save_passwd=:s WHERE account=:acct");
    q.bindValue(":s", save);
    q.bindValue(":acct", account);
    bool ok = q.exec();
    if (!ok) {
        const_cast<DatabaseManager*>(this)->m_lastError = q.lastError();
        logError(q.lastError(), "updateSavePassword");
    }
    return ok;
}

qint64 DatabaseManager::insertHnnkData(const HNNKData &data) {
    QSqlQuery query(m_hnnkDb);
    query.prepare(
        "INSERT INTO hnnk_data (mid, account, addtime, start_time, end_time, eeg, eog, body_movement_value, med_value, min_value, max_value, avg_value, event) "
        "VALUES (:mid, :account, :addtime, :start_time, :end_time, :eeg, :eog, :body, :med, :min, :max, :avg, :event)"
        );
    query.bindValue(":mid", data.mid);
    query.bindValue(":account", data.account);
    query.bindValue(":addtime", data.addTime.isValid() ? data.addTime : QDateTime::currentDateTime());
    query.bindValue(":start_time", data.startTime);
    query.bindValue(":end_time", data.endTime);
    query.bindValue(":eeg", data.eeg);
    query.bindValue(":eog", data.eog);
    query.bindValue(":body", data.bodyMovementValue);
    query.bindValue(":med", data.medValue);
    query.bindValue(":min", data.minValue);
    query.bindValue(":max", data.maxValue);
    query.bindValue(":avg", data.avgValue);
    query.bindValue(":event", data.event);

    if (!query.exec()) {
        m_lastError = query.lastError();
        logError(m_lastError, "insertHnnkData");
        return -1;
    }
    return query.lastInsertId().toLongLong();
}


QList<HNNKData> DatabaseManager::getHnnkDataByAccount(const QString &account) const {
    QList<HNNKData> list;
    QSqlQuery query(m_hnnkDb);
    query.prepare("SELECT * FROM hnnk_data WHERE account = :account ORDER BY addtime DESC");
    query.bindValue(":account", account);
    if (!query.exec()) {
        const_cast<DatabaseManager*>(this)->m_lastError = query.lastError();
        logError(m_lastError, "getHnnkDataByAccount");
        return list;
    }
    while (query.next()) {
        HNNKData d;
        d.id = query.value("id").toLongLong();
        d.mid = query.value("mid").toLongLong();
        d.account = query.value("account").toString();
        d.addTime = query.value("addtime").toDateTime();
        d.startTime = query.value("start_time").toDateTime();
        d.endTime = query.value("end_time").toDateTime();
        d.eeg = query.value("eeg").toFloat();
        d.eog = query.value("eog").toFloat();
        d.bodyMovementValue = query.value("body_movement_value").toFloat();
        d.medValue = query.value("med_value").toFloat();
        d.minValue = query.value("min_value").toFloat();
        d.maxValue = query.value("max_value").toFloat();
        d.avgValue = query.value("avg_value").toFloat();
        d.event = query.value("event").toString();
        list.append(d);
    }
    return list;
}


QList<HNNKData> DatabaseManager::getRecentHnnkDataByAccount(const QString &account, int n) const {
    QList<HNNKData> list;
    QSqlQuery query(m_hnnkDb);
    query.prepare("SELECT * FROM hnnk_data WHERE account = :account ORDER BY addtime DESC LIMIT :limit");
    query.bindValue(":account", account);
    query.bindValue(":limit", n);
    if (!query.exec()) {
        const_cast<DatabaseManager*>(this)->m_lastError = query.lastError();
        logError(m_lastError, "getRecentHnnkDataByAccount");
        return list;
    }
    while (query.next()) {
        HNNKData d;
        d.id = query.value("id").toLongLong();
        d.mid = query.value("mid").toLongLong();
        d.account = query.value("account").toString();
        d.addTime = query.value("addtime").toDateTime();
        d.startTime = query.value("start_time").toDateTime();
        d.endTime = query.value("end_time").toDateTime();
        d.eeg = query.value("eeg").toFloat();
        d.eog = query.value("eog").toFloat();
        d.bodyMovementValue = query.value("body_movement_value").toFloat();
        d.medValue = query.value("med_value").toFloat();
        d.minValue = query.value("min_value").toFloat();
        d.maxValue = query.value("max_value").toFloat();
        d.avgValue = query.value("avg_value").toFloat();
        d.event = query.value("event").toString();
        list.append(d);
    }
    return list;
}

