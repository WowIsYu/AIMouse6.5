// User.cpp
#include "User.h"

User::User(qint64 id, const QString& account, qint64 uid, const QString& password,
           const QString& nickname, const QString& headImgUrl, bool savePassword,
           bool localRegister, const QDateTime& addTime)
    : m_id(id), m_account(account), m_uid(uid), m_password(password),
    m_nickname(nickname), m_headImgUrl(headImgUrl), m_savePassword(savePassword),
    m_localRegister(localRegister), m_addTime(addTime) {}

// Getters implementation
qint64 User::getId() const { return m_id; }
QString User::getAccount() const { return m_account; }
qint64 User::getUid() const { return m_uid; }
QString User::getPassword() const { return m_password; }
QString User::getNickname() const { return m_nickname; }
QString User::getHeadImgUrl() const { return m_headImgUrl; }
bool User::getSavePassword() const { return m_savePassword; }
bool User::getLocalRegister() const { return m_localRegister; }
QDateTime User::getAddTime() const { return m_addTime; }

// Setters implementation
void User::setId(qint64 id) { m_id = id; }
void User::setAccount(const QString& account) { m_account = account; }
void User::setUid(qint64 uid) { m_uid = uid; }
void User::setPassword(const QString& password) { m_password = password; }
void User::setNickname(const QString& nickname) { m_nickname = nickname; }
void User::setHeadImgUrl(const QString& headImgUrl) { m_headImgUrl = headImgUrl; }
void User::setSavePassword(bool save) { m_savePassword = save; }
void User::setLocalRegister(bool local) { m_localRegister = local; }
void User::setAddTime(const QDateTime& time) { m_addTime = time; }
