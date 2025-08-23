#ifndef UART_VIEWMODEL_H
#define UART_VIEWMODEL_H

#include <QObject>
#include "uart.h"
#include <QThread>

class UartViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
    Q_PROPERTY(int power READ power WRITE setPower NOTIFY powerChanged FINAL)
public:
    explicit UartViewModel(QObject *parent = nullptr);
    ~UartViewModel();
    int speed() const;
    void setSpeed(int newSpeed);
    int power() const;
    void setPower(int newPower);

private:
    QThread workUart;
    Uart *uart;
    void send(QByteArray &byteArray);
    int m_speed;
    int m_power;

signals:
    void speedChanged();
    void powerChanged();

public slots:
    void readyRead(QByteArray byteArray);
};

#endif // UART_VIEWMODEL_H
