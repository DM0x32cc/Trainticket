# ===========================================================================
# 模拟火车票售票系统 —— 顶层构建脚本
#
# 目标环境：Windows 10/11 x64 + Qt 6.10.2 + MinGW 13.1 64-bit + CMake
#
# 手动构建（在项目根目录执行；构建目录不要放在源码目录里面）：
#   cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
#   cmake --build build -j
# ===========================================================================

# --- (1) CMake 版本区间 ----------------------------------------------------
# 下限 = 本工程用到的语法所需的最低版本
# 上限 = 实测过的最高版本，决定启用到哪一版为止的 CMake 策略
# 将来跑在更新的 CMake 上不会报错，只是策略停在 3.31。
cmake_minimum_required(VERSION 3.21...3.31)

# --- (2) 工程声明 ----------------------------------------------------------
project(Trainticket
    VERSION     1.0
    DESCRIPTION "模拟火车票售票系统"
    LANGUAGES   CXX)

# --- (3) 语言标准 ----------------------------------------------------------
# 这里用 CMAKE_CXX_STANDARD，而不是 target_compile_features(tgt cxx_std_17)。
# 两者语义不同：cxx_std_17 是"至少 C++17"，编译器默认标准更高时它不加任何
# 标志；CMAKE_CXX_STANDARD 是"就是 C++17"，固定加 -std=gnu++17。
#
# 实测本机 GCC 15 的默认标准恰好也是 C++17（__cplusplus = 201703L），
# 所以此刻两种写法产物相同。差别在将来换编译器时才显现：本工程的要求是
# "锁死在 C++17"，让本机与 Windows MinGW 编出同一个标准。
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- (4) 找 Qt -------------------------------------------------------------
# 带上版本号 6.10：万一装的是别的版本，会在这里立刻报错，
# 而不是编译到一半才冒出一堆看不懂的错误。
find_package(Qt6 6.10 REQUIRED COMPONENTS Core Widgets)

# --- (5) Qt 的工程初始化 ---------------------------------------------------
# 实测等价于 set(CMAKE_AUTOMOC ON) + set(CMAKE_AUTOUIC ON)，
# 另外还处理 Windows 下 exe 的输出目录、非 Windows 下的 RPATH 等。
#
# 【坑】它不打开 AUTORCC。M6 加 .qrc 资源文件时别指望它自动生效，
#      要用 Qt 6 推荐的 qt_add_resources()。
qt_standard_project_setup()

# ===========================================================================
# (6) 逻辑层静态库：模型 + 业务逻辑
#
# 架构铁律 2：本层只允许依赖 QtCore。这里只链 Qt6::Core，
# 一旦误 include 了 QtWidgets 的头文件，编译期就会失败。
# ===========================================================================
add_library(trainticket_core STATIC
    src/core/AppClock.cpp
)

# PUBLIC = 这条要求既用于编译本库，也传递给所有链接本库的目标。
# 于是 Trainticket 自动获得 src/ 作为头文件搜索路径，
# 写 #include "core/AppClock.h" 时不必再补路径。
#
# $<BUILD_INTERFACE:...> 表示这条路径只在"从源码构建"的场景下有效。
# 本工程目前不做 install，去掉生成器表达式照样能跑；这样写是为了将来
# 真要做 install/export 时不用回头改，也是现代 CMake 的规范写法。
target_include_directories(trainticket_core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(trainticket_core PUBLIC Qt6::Core)

# ===========================================================================
# (7) 主程序
#
# M1 第 1 步：只验证工具链 —— 能配置、能编译、能链接、能生成可执行文件。
# 界面代码（src/ui/*.cpp）到 M4 再逐个加进下面的源文件列表。
#
# 这里刻意不加 WIN32_EXECUTABLE：加了它，Windows 上程序就不再附带控制台，
# 调试期的打印全都看不见。等 M6 收尾时再加。
# ===========================================================================
add_executable(Trainticket
    src/main.cpp
)

# PRIVATE = Trainticket 需要这两个库，但别人不该因为链接 Trainticket
# 而"继承"到它们（可执行文件本来也不会被别人链接）。
# 注意：trainticket_core 自己的 PUBLIC 要求（src/ 头文件路径、Qt6::Core）
# 仍然会传到 Trainticket 身上 —— PRIVATE/PUBLIC 控制的是"要不要继续往下传"，
# 不是"自己用不用"。
target_link_libraries(Trainticket PRIVATE trainticket_core Qt6::Widgets)
