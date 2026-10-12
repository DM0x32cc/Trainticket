#pragma once

#include <QString>

/// 全部业务函数的统一返回值。
///
/// 约定：
///   ok == true   → message 为空
///   ok == false  → message 是给用户看的原因，可直接丢进 QMessageBox
///
/// 用法：
///   return { true,  {} };                            // 成功
///   return { false, QStringLiteral("余票不足") };     // 失败
struct Result {
    bool    ok = false;
    QString message;
};
