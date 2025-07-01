// HnnkData.cpp
#include "HnnkData.h"

HnnkData::HnnkData(qint64 id, qint64 mid, const QString& account, const QDateTime& addTime,
                   const QDateTime& startTime, const QDateTime& endTime, float eeg, float eog,
                   float bodyMovement, float medValue, float minValue, float maxValue,
                   float avgValue, const QString& event)
    : m_id(id), m_mid(mid), m_account(account), m_addTime(addTime),
    m_startTime(startTime), m_endTime(endTime), m_eeg(eeg), m_eog(eog),
    m_bodyMovement(bodyMovement), m_medValue(medValue), m_minValue(minValue),
    m_maxValue(maxValue), m_avgValue(avgValue), m_event(event) {}

// Getters implementation
qint64 HnnkData::getId() const { return m_id; }
qint64 HnnkData::getMid() const { return m_mid; }
QString HnnkData::getAccount() const { return m_account; }
QDateTime HnnkData::getAddTime() const { return m_addTime; }
QDateTime HnnkData::getStartTime() const { return m_startTime; }
QDateTime HnnkData::getEndTime() const { return m_endTime; }
float HnnkData::getEeg() const { return m_eeg; }
float HnnkData::getEog() const { return m_eog; }
float HnnkData::getBodyMovement() const { return m_bodyMovement; }
float HnnkData::getMedValue() const { return m_medValue; }
float HnnkData::getMinValue() const { return m_minValue; }
float HnnkData::getMaxValue() const { return m_maxValue; }
float HnnkData::getAvgValue() const { return m_avgValue; }
QString HnnkData::getEvent() const { return m_event; }

// Setters implementation
void HnnkData::setId(qint64 id) { m_id = id; }
void HnnkData::setMid(qint64 mid) { m_mid = mid; }
void HnnkData::setAccount(const QString& account) { m_account = account; }
void HnnkData::setAddTime(const QDateTime& time) { m_addTime = time; }
void HnnkData::setStartTime(const QDateTime& time) { m_startTime = time; }
void HnnkData::setEndTime(const QDateTime& time) { m_endTime = time; }
void HnnkData::setEeg(float value) { m_eeg = value; }
void HnnkData::setEog(float value) { m_eog = value; }
void HnnkData::setBodyMovement(float value) { m_bodyMovement = value; }
void HnnkData::setMedValue(float value) { m_medValue = value; }
void HnnkData::setMinValue(float value) { m_minValue = value; }
void HnnkData::setMaxValue(float value) { m_maxValue = value; }
void HnnkData::setAvgValue(float value) { m_avgValue = value; }
void HnnkData::setEvent(const QString& event) { m_event = event; }
