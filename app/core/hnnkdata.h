// HnnkData.h
#ifndef HNNKDATA_H
#define HNNKDATA_H

#include <QString>
#include <QDateTime>

class HnnkData {
public:
    HnnkData() = default;
    HnnkData(qint64 id, qint64 mid, const QString& account, const QDateTime& addTime,
             const QDateTime& startTime, const QDateTime& endTime, float eeg, float eog,
             float bodyMovement, float medValue, float minValue, float maxValue,
             float avgValue, const QString& event);

    // Getters
    qint64 getId() const;
    qint64 getMid() const;
    QString getAccount() const;
    QDateTime getAddTime() const;
    QDateTime getStartTime() const;
    QDateTime getEndTime() const;
    float getEeg() const;
    float getEog() const;
    float getBodyMovement() const;
    float getMedValue() const;
    float getMinValue() const;
    float getMaxValue() const;
    float getAvgValue() const;
    QString getEvent() const;

    // Setters
    void setId(qint64 id);
    void setMid(qint64 mid);
    void setAccount(const QString& account);
    void setAddTime(const QDateTime& time);
    void setStartTime(const QDateTime& time);
    void setEndTime(const QDateTime& time);
    void setEeg(float value);
    void setEog(float value);
    void setBodyMovement(float value);
    void setMedValue(float value);
    void setMinValue(float value);
    void setMaxValue(float value);
    void setAvgValue(float value);
    void setEvent(const QString& event);

private:
    qint64 m_id{0};
    qint64 m_mid{0};
    QString m_account;
    QDateTime m_addTime;
    QDateTime m_startTime;
    QDateTime m_endTime;
    float m_eeg{0};
    float m_eog{0};
    float m_bodyMovement{0};
    float m_medValue{0};
    float m_minValue{0};
    float m_maxValue{0};
    float m_avgValue{0};
    QString m_event;
};

#endif // HNNKDATA_H
