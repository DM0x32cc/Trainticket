#pragma once

#include <QDate>
#include <QDateTime>
#include <QString>

/// 一张票。
///
/// (idCard, trainNo, travelDate) 三者共同决定"哪一张票"：
/// 同一张身份证、同一车次、同一乘车日期，只允许购买一张（实名制限购）。
struct Ticket {
    QString   idCard;       // 身份证号
    QString   name;         // 姓名
    QString   trainNo;      // 车次号
    QDate     travelDate;   // 乘车日期  ← 即"运营日"
    QDateTime sellTime;     // 售票时间
};
