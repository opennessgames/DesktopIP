/* 
    By : yzx
    Time : 2024/8/28 上午 12:23:00
*/
#include <QtNetwork/qnetworkinterface.h>
#include <QtNetwork/qnetworkinterface.h>
//#include <QHostAddress>

QString getWIFIIP() {
    // 定义一个列表，用于存储所有符合条件的IP地址
    QList<QHostAddress> ipList;

    // 遍历所有网络接口
    foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
        // 检查接口是否处于活动状态且正在运行
        if (interface.flags() & QNetworkInterface::IsUp &&
            interface.flags() & QNetworkInterface::IsRunning) {

            // 遍历接口的所有地址条目
            foreach (const QNetworkAddressEntry &entry, interface.addressEntries()) {
                // 仅处理IPv4协议的地址，并排除127.x.x.x（回环地址）
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol &&
                    !entry.ip().toString().startsWith("127.")) {
                    // 将符合条件的IP地址添加到列表中
                    ipList.append(entry.ip());
                }
            }
        }
    }

    // 如果列表不为空，返回列表中的第一个IP地址
    if (!ipList.isEmpty()) {
        return ipList.first().toString(); // 返回找到的第一个IP地址
    }

    // 如果没有找到合适的IP地址，则返回"没有IP地址"的提示
    return QString("No IP Address");
}


