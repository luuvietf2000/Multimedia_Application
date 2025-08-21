#include "carowinchecker.h"
#include "caroviewmodel.h"

CaroWinChecker::CaroWinChecker(QObject *parent)
    : QObject{parent}
{}

void CaroWinChecker::setEdge(const int &size)
{
    edge = size;
    createBoard();
}

bool CaroWinChecker::setPixel(const int &x, const int &y, int &value)
{
    int line = 7;
    bool result = false;
    board[x][y].value = value;
    for(int i = 0; i < line + 1; i++){
        int cx = x + dx[i];
        int cy = y + dy[i];
        bool position_valid = checkPointValid(cx, cy);
        if(position_valid){
            if(board[x][y].value == board[cx][cy].value){
                updateLine(x, y, cx, cy, line, i);
                point endLine = board[x][y].EndLinePoint[i];
                updateLine(endLine.x, endLine.y, x, y, line, line - i);
                qDebug() << "range" << calculatorRange(x, y, endLine.x, endLine.y);
            }
        }
    }
    for(int i = 0; i < (line + 1) / 2; i++){
        int x1 = x + dx[i];
        int y1 = y + dy[i];
        int x2 = x + dx[line - i];
        int y2 = y + dy[line - i];
        bool positionLineOneValid = checkPointValid(x1, y1);
        bool positionLineTwoValid = checkPointValid(x2, y2);
        if(positionLineOneValid && positionLineTwoValid){
            bool byValue = (board[x][y].value == board[x1][y1].value) && (board[x][y].value == board[x2][y2].value);
            if(byValue){
                int cx1 = board[x1][y1].EndLinePoint[i].x;
                int cy1 = board[x1][y1].EndLinePoint[i].y;
                int cx2 = board[x2][y2].EndLinePoint[line - i].x;
                int cy2 = board[x2][y2].EndLinePoint[line - i].y;
                updateLine(cx2, cy2, cx1, cy1, line, i);
                updateLine(cx1, cy1, cx2, cy2, line, line - i);

                //int range =  abs(cx1, cx2) + (cy1 == cy2 || cx1 == cx2 ? 0 : abs(cy1, cy2));
                qDebug() << "range" << calculatorRange(cx1, cy1, cx2, cy2);
                // check winner
            }
        }
    }
    return result;
}

int CaroWinChecker::calculatorRange(const int &x1, const int &y1, const int &x2, const int &y2)
{
    int range =  abs(x1, x2) + (y1 == y2 || x1 == x2 ? 0 : abs(y1, y2));
    return range + 1;
}

void CaroWinChecker::updateLine(const int &x1, const int &y1, const int &x2, const int &y2, int &line, const int &index)
{
    board[x1][y1].EndLinePoint[index] = board[x2][y2].EndLinePoint[index];
}

bool CaroWinChecker::checkPointValid(const int &x, const int &y)
{
    return x > -1 && y> -1 && x < edge && y < edge;
}

void CaroWinChecker::createBoard()
{
    QVector<QVector<pointCaro>> newBoard;
    for(int y = 0; y < edge; y++){
        QVector<pointCaro> new_row;
        for(int x = 0; x < edge; x++)
            new_row.append(pointCaro(y, x, CaroViewModel::NotExist));
        newBoard.append(new_row);
    }
    board = newBoard;
}

int CaroWinChecker::abs(const int &x, const int &y)
{
    return x > y ? x - y : y - x;
}

