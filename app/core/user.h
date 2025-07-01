// User.h
#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

class User {
public:
    User() = default;
    User(qint64 id, const QString& account, qint64 uid, const QString& password,
         const QString& nickname, const QString& headImgUrl, bool savePassword,
         bool localRegister, const QDateTime& addTime);

    // Getters
    qint64 getId() const;
    QString getAccount() const;
    qint64 getUid() const;
    QString getPassword() const;
    QString getNickname() const;
    QString getHeadImgUrl() const;
    bool getSavePassword() const;
    bool getLocalRegister() const;
    QDateTime getAddTime() const;

    // Setters
    void setId(qint64 id);
    void setAccount(const QString& account);
    void setUid(qint64 uid);
    void setPassword(const QString& password);
    void setNickname(const QString& nickname);
    void setHeadImgUrl(const QString& headImgUrl);
    void setSavePassword(bool save);
    void setLocalRegister(bool local);
    void setAddTime(const QDateTime& time);

private:
    qint64 m_id{0};
    QString m_account;
    qint64 m_uid{0};
    QString m_password;
    QString m_nickname;
    QString m_headImgUrl;
    bool m_savePassword{false};
    bool m_localRegister{false};
    QDateTime m_addTime;
};

#endif // USER_H
