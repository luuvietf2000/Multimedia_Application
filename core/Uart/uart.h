#ifndef UART_H
#define UART_H

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
class Uart : public QObject
{
    Q_OBJECT
public:
    explicit Uart(QObject *parent = nullptr);
    ~Uart();
    void sendPort(QByteArray &byteArray);
private:
    void readyRead();
    QSerialPort *port;
    const QString namePort = "COM3";
signals:
    void dataReady(QByteArray byteArray);
};

#endif // UART_H