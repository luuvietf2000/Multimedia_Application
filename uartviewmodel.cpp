#include "uartviewmodel.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

UartViewModel::UartViewModel(QObject *parent)
    : QObject{parent}
{
    uart = new Uart();
    uart->moveToThread(&workUart);
    connect(uart, &Uart::dataReady, this, &UartViewModel::readyRead);
    workUart.start();
    setPower(0);
    setSpeed(0);
}

UartViewModel::~UartViewModel()
{
    uart->deleteLater();
    workUart.quit();
    workUart.wait();
}

void UartViewModel::readyRead(QByteArray byteArray)
{
    QJsonDocument json = QJsonDocument::fromJson(byteArray);
    int speed = json["speed"].toInt();
    setSpeed(speed);
    int power = json["power"].toInt();
    setPower(power);

}

int UartViewModel::speed() const
{
    return m_speed;
}

void UartViewModel::setSpeed(int newSpeed)
{
    if (m_speed == newSpeed)
        return;
    m_speed = newSpeed;
    qDebug() << m_speed;
    emit speedChanged();
}

int UartViewModel::power() const
{
    return m_power;
}

void UartViewModel::setPower(int newPower)
{
    if (m_power == newPower)
        return;
    m_power = newPower;
    emit powerChanged();
}
