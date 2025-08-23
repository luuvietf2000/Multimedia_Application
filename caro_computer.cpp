#include "caro_computer.h"
#include "caro_winchecker.h"
#include "caro_viewmodel.h"

CaroComputer::CaroComputer(QObject *parent)
    : QObject{parent}
{}

void CaroComputer::setPointerBoard(QVector<QVector<pointCaro> > &board)
{
    boardPointer = &board;
}

void CaroComputer::setNumbleCell(const int &cell)
{
    numbleCell = cell;
}

void CaroComputer::getLineParent(const int &x, const int &y, const int &value, const int &index, QString &line)
{
    const int count = 4;
    bool startRival = false;
    CaroWinChecker win_checker;
    for(int index = 0; index < count; index++){
        int cx = x + dx[index];
        int cy = y + dy[index];
        bool pointValid = win_checker.checkPointValid(cx, cy);
        bool isSameValue = (*boardPointer)[cx][cy].value == value || (*boardPointer)[cx][cy].value == CaroViewModel::NotExist;
        if(pointValid && (isSameValue || startRival)){
            if(startRival && !isSameValue)
                return;
            int range = win_checker.calculatorRange(cx, cy, (*boardPointer)[cx][cy].EndLinePoint[index].x, (*boardPointer)[cx][cy].EndLinePoint[index].y);
            QString content = "";
            for(int i = 0; i < range && index + i < count; i++){
                content += QString(charValue[(*boardPointer)[cx][cy].value]);
            }
            line += content;
        }
        else if(pointValid && index == 0){
            line += QString(charValue[(*boardPointer)[x][y].value]);
            startRival = true;
        }
        else
            return;
    }
}

void CaroComputer::extractParent(const int &x, const int &y, const int &value, const int &index, QString &line)
{
    const int numbleLine = 7;
    QString prefixLine;
    getLineParent(x, y, value, index, prefixLine);
    QString afterLine;
    getLineParent(x, y, value, numbleLine - index, afterLine);
    line = prefixLine + charValue[value] + afterLine;
}
