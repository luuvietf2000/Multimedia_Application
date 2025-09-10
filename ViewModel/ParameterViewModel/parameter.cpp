#include "parameter.h"

Parameter::Parameter(QObject *parent)
    : QObject{parent}
{
}


int Parameter::height() const
{
    return _height;
}

void Parameter::setHeight(const int &newHeightSize)
{
    if(newHeightSize == _height)
        return;
    _height = newHeightSize;
    emit heightChanged();
}

int Parameter::width() const
{
    return _width;
}

void Parameter::setWidth(const int &newWidthSize)
{
    if(newWidthSize == _width)
        return;
    _width = newWidthSize;

    emit widthChanged();
}


