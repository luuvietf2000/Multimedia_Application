#include "uart.h"
#include <QSerialPortInfo>
#include <QDebug>

Uart::Uart(QObject *parent)
    : QObject{parent}
{
    port = new QSerialPort();
    port->setPortName(namePort);
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    connect(port, &QSerialPort::readyRead, this, &Uart::readyRead);
    if (port->open(QIODevice::ReadWrite)){
        qDebug() << "open finish";
    } else
        qDebug() << "fail";
}

Uart::~Uart()
{
    port->close();
    port->deleteLater();
}

void Uart::sendPort(QByteArray &byteArray)
{
    port->write(byteArray);
}

void Uart::readyRead()
{
    QByteArray byteArray = port->readAll();
    emit dataReady(byteArray);
}
