#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QList>

// 用户结构体
struct User {
    qint64 id{0};                // 主键
    QString account;             // 账号
    qint64 uid{0};               // 用户唯一ID
    QString password;
    QString nickname;
    QString headImgUrl;
    bool savePassword{false};
    bool localRegister{false};
    QDateTime addTime;
};

struct HNNKData {
    qint64 id{0};
    qint64 mid{0};
    QString account;
    QDateTime addTime;
    QDateTime startTime;
    QDateTime endTime;
    float eeg{0};
    float eog{0};
    float bodyMovementValue{0};
    float medValue{0};
    float minValue{0};
    float maxValue{0};
    float avgValue{0};
    QString event;
};

class DatabaseManager : public QObject {
    Q_OBJECT
private:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager() override;
public:
    // 单例设计模式
    static DatabaseManager& instance();

    void closeDatabase();
    bool openDatabase();

    QString getDatabasePath() const;
    void setDatabasePath(const QString& path);


    // 初始化数据库并创建必要表，返回是否成功
    bool initializeUserDatabase();                  // 初始化 user_info.db
    bool initializeHnnkDatabase();              // 初始化 hnnk_info.db

    /**
     * 插入用户记录
     * @param user 要插入的用户数据
     * @return 成功返回新记录ID，否则返回-1，可通过lastError()获取详细错误信息
     */
    qint64 insertUser(const User &user);

    // 检查账号是否已存在
    bool userExists(const QString &account) const;

    // 获取所有用户
    QList<User> getAllUsers() const;

    // 最近一次操作的错误
    QSqlError lastError() const;

    // 按 account 查询单个用户；不存在时返回 id<0
    User getUserByAccount(const QString &account) const;

    // 更新某 account 的 savePassword 标志
    bool updateSavePassword(const QString &account, bool save);

    qint64 insertHnnkData(const HNNKData &data);                              // 插入 HNNK 数据
    QList<HNNKData> getHnnkDataByAccount(const QString &account) const;      // 根据 account 获取所有记录
    QList<HNNKData> getRecentHnnkDataByAccount(const QString &account, int n) const; // 获取最近 N 条记录




private:
    static const QString UserConnectionName;
    static const QString HnnkConnectionName;
    QSqlDatabase m_db;
    QSqlDatabase m_hnnkDb;
    QSqlError m_lastError;

    //文件存放路径
    QString dbPath;

    bool createUserTables();
    bool createHnnkTables();       // 创建 db_data 表
    void logError(const QSqlError &err, const QString &context) const;

};

#endif // DATABASEMANAGER_H
