/* 
    By : yzx
    Time : 2024/8/28 上午 2:27:10
*/
#include "mainwindow.h"

#include <QApplication>
#include "src/getip.h"
#include <qdebug.h>
#include <qlabel.h>
#include <qboxlayout.h>
#include <qscreen.h>
// 思路:相当于显示桌面歌词,但显示的不是歌词,而是IP
//  https://github.com/opennessgames/DesktopIP/
class DesktopIP : public QWidget
{
public:
    DesktopIP(QWidget *parent = nullptr) : QWidget(parent)
    {
        // 设置窗口标志以保持在最上层
        setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);

        // 创建一个标签以显示IP地址(歌词)
        QLabel *label = new QLabel(QString("平头网吧<br>" + getWIFIIP()), this);
        label->setStyleSheet("background-color: rgba(0, 0, 0, 0.5); color: white; font-size: 20px; padding: 10px;");

        // 设置文字居中对齐
        label->setAlignment(Qt::AlignCenter);

        // 设置布局
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(label);
        setLayout(layout);

        // 将窗口居中显示在屏幕上
        QScreen *screen = QGuiApplication::primaryScreen();
        if (screen) {
            QRect screenGeometry = screen->geometry();
            int screenWidth = screenGeometry.width();
            int screenHeight = screenGeometry.height();
            int widgetWidth = 300; // 窗口宽度
            int widgetHeight = 100; // 窗口高度
            setGeometry((screenWidth - widgetWidth) / 2, (screenHeight - widgetHeight) / 2, widgetWidth, widgetHeight);
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DesktopIP ip;
    ip.show();
    return a.exec();
}
