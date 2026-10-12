// ---------------------------------------------------------------------------
// M1 第 1 步：构建系统自检
//
// 这个文件此刻唯一的作用是证明工具链成立：
//   cmake 找得到 Qt6 → 编译器编得过 → 链接器连得上 Qt6Widgets → 产出 .exe
//
// 真正的界面代码在 M4 才开始写，那时会新增 src/ui/*.cpp，
// 并在这里挂上主窗口。现在这里不放任何业务逻辑。
// ---------------------------------------------------------------------------

#include <QApplication>
#include <QLabel>
#include <QString>
#include <Qt>
#include <QtGlobal>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QLabel label(QStringLiteral(
        "工具链自检通过\n\n"
        "Qt 版本：%1\n"
        "编译器：%2\n\n"
        "能看到这个窗口，说明 Qt Widgets 可以正常编译并运行。")
        .arg(QStringLiteral(QT_VERSION_STR),
             QStringLiteral(__VERSION__)));

    label.setWindowTitle(QStringLiteral("Trainticket —— M1 第 1 步"));
    label.setAlignment(Qt::AlignCenter);
    label.resize(460, 180);
    label.show();

    return app.exec();
}
