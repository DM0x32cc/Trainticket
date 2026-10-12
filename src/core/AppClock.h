#pragma once

#include <QDateTime>

/// 全系统唯一的"当前时间"入口。
///
/// 【强制约定】业务代码中禁止直接调用 QDateTime::currentDateTime()，
/// 一律走 AppClock::now()。
///
/// 原因：答辩演示时需要把"现在"调到任意时刻，
/// 用来展示"此车已发出""距发车不足 30 分钟不能退票"等场景。
class AppClock {
public:
    /// 当前时间（真实系统时间；若已设定模拟时间则返回模拟时间）
    static QDateTime now();

    /// 设定模拟时间
    static void setMock(const QDateTime& dt);

    /// 恢复真实系统时间
    static void clearMock();

    /// 当前是否处于模拟状态
    static bool isMocked();

private:
    static bool      s_mocked;
    static QDateTime s_mock;
};
