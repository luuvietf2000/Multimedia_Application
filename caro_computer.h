#ifndef CARO_COMPUTER_H
#define CARO_COMPUTER_H

#include <QObject>
#include <QVector>
#include <caro_winchecker.h>

class CaroComputer : public QObject
{
    Q_OBJECT
public:
    explicit CaroComputer(QObject *parent = nullptr);
    void setPointerBoard(QVector<QVector<pointCaro>> &board);
    void setNumbleCell(const int &cell);
    void getLineParent(const int &x, const int &y, const int &value, const int &index, QString &line);
    void extractParent(const int &x, const int &y, const int &value, const int &index, QString &line);
signals:
private:
    QVector<QVector<pointCaro>> *boardPointer;
    int numbleCell;
    inline static char charValue[] = {'.', 'X', 'O'};
    inline static int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    inline static int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
};

#endif // CARO_COMPUTER_H
