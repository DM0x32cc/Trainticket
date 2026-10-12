#pragma once

#include <QString>

/// 三种角色
enum class Role {
    Admin,      // 管理员
    Seller,     // 售票员
    Passenger   // 乘客
};

/// 一个账号。
/// 管理员与售票员使用短账号（admin / seller）；乘客用身份证号作为账号。
struct User {
    QString account;                        // 账号
    QString password;                       // 密码（课程设计按明文保存）
    QString name;                           // 姓名（乘客用）
    Role    role = Role::Passenger;         // 角色
};
