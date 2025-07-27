#ifndef PARAMETER_H
#define PARAMETER_H

#include <QObject>
#include <QGuiApplication>
class Parameter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged FINAL)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged FINAL)

public:
    explicit Parameter(QObject *parent = nullptr);
    int height() const;
    void setHeight(const int &newHeightSize);
    int width() const;
    void setWidth(const int &newWidthSize);

private:
    int _height;
    int _width;
    void clear();
signals:
    void heightChanged();
    void widthChanged();
    void activePopupWarning(const QString &title, const QString &sourceImageTitle, const QString &description, const QString &sourceButtonAccept);
};

#endif // PARAMETER_H
