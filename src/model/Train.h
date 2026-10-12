#pragma once

#include <QDate>
#include <QMap>
#include <QString>
#include <QTime>

/// 一个车次 —— 即"每天开行"的列车模板。
///
/// 注意这里【没有】日期字段，也【没有】余票字段：
///   · 日期是运行时的查询维度，记在 Ticket::travelDate 里；
///   · 余票 = capacity − soldByDate[date]，由 TrainManager 计算。
struct Train {
    QString         trainNo;        // 车次号        G1113
    QTime           departTime;     // 发车时间      07:25（每天都是这个点）
    QString         startStation;   // 起点站        南京南
    QString         endStation;     // 终点站        广州南
    double          hours   = 0.0;  // 行车时间      7（小时）
    int             capacity = 0;   // 额定载量      600
    double          price   = 0.0;  // 票价          553.5（自选拓展字段）

    /// 各乘车日期的已售票数：key = 乘车日期，value = 该日已售张数
    QMap<QDate, int> soldByDate;
};
