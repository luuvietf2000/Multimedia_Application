#include "caro_viewmodel.h"
#include <QRandomGenerator>

CaroViewModel::CaroViewModel(QObject *parent)
    : QObject{parent}
{
    computer = new CaroComputer();
    setMaxLine(21);
    setBoardDefault();
    m_turn = turnOne;
    setPlayerWinner(NoneTurn);
    m_modeGame = NoneMode;
    computer->setBoard(m_board);
}

CaroViewModel::~CaroViewModel()
{
    delete computer;
}

void CaroViewModel::setPixelBoard(const int &x, const int &y)
{
    int value = getPixel();
    m_board[x][y] = value;
    if(m_modeGame == playerVSComputer)
        computer->setPixel(x, y);
    point start, end;
    bool isWin = check.setPixel(x, y, value, start, end);
    if(isWin)
        setWinner(m_turn, start, end);
    setTurn(!m_turn);
    emit boardChanged();
    requestComputerAction();
}

QVariantList CaroViewModel::board() const
{
    QVariantList map;
    for(int i = 0; i < maxLine(); i++){
        QVariantList variant_list;
        for(int j = 0; j < maxLine(); j++)
            variant_list.append(m_board[i][j]);
        QVariant variant(variant_list);
        map.append(variant);
    }
    return map;
}

int CaroViewModel::maxLine() const
{
    return m_maxLine;
}

void CaroViewModel::setMaxLine(int newMaxLine)
{
    if (m_maxLine == newMaxLine)
        return;
    m_maxLine = newMaxLine;
    computer->setNumbleCell(m_maxLine);
    emit maxLineChanged();
}

void CaroViewModel::setBoardDefault()
{
    QVector<QVector<int>> new_board;
    for(int x = 0; x < maxLine(); x++){
        QVector<int> new_row;
        for(int y = 0; y < maxLine(); y++)
            new_row.push_back(NotExist);
        new_board.append(new_row);
    }
    m_board = new_board;
    check.setEdge(m_maxLine);
    emit boardChanged();
}

void CaroViewModel::requestRetry()
{
    setTurn(turnOne);
    setPlayerWinner(NoneTurn);
    setBoardDefault();
    check.createBoard();
    computer->requestRetry();
    requestComputerAction();
}

QVariantList CaroViewModel::setInfoPlayer()
{
    QVariantList result;
    bool numble[] = {false, false};
    int indexComputer = QRandomGenerator::global()->bounded(2);
    switch (m_modeGame){
        case playerVsPlayer:
            for(int numble = 1; numble < 3; numble++){
                QVariant player = createInfoPlayer(numble, false);
                result.append(player);
            }
            break;
        case playerVSComputer:
            numble[indexComputer] = true;
            for(int index = 1; index < 3; index++){
                QVariant player = createInfoPlayer(index, numble[index - 1]);
                result.append(player);
            }
            break;
        default:
            for(int i = 0; i < 2; i++){
                QVariantMap player;
                player["name"] = "";
                player["source"] = "";
                result.append(player);
            }
            break;
    }
    return result;
}

QVariant CaroViewModel::createInfoPlayer(const int &player, const bool &isComputer)
{
    QVariantMap map;
    QString name_default = "Player " + QString::number(player);
    map["name"] = isComputer ? name_computer : name_default;
    map["source"] = isComputer ? "qrc:/image/bot.png" : "qrc:/image/user.png";
    QVariant variant(map);
    return variant;
}

int CaroViewModel::turn() const
{
    return m_turn;
}

void CaroViewModel::setTurn(int newTurn)
{
    if (m_turn == newTurn)
        return;
    m_turn = newTurn;
    emit turnChanged();
}

int CaroViewModel::modeGame() const
{
    return m_modeGame;
}

void CaroViewModel::setModeGame(int newModeGame)
{
    if (m_modeGame == newModeGame)
        return;
    m_modeGame = newModeGame;
    setPlayer(setInfoPlayer());
    requestComputerAction();
    emit modeGameChanged();
}

QVariantList CaroViewModel::player() const
{
    return m_player;
}

void CaroViewModel::setPlayer(const QVariantList &newPlayer)
{
    if (m_player == newPlayer)
        return;
    m_player = newPlayer;
    emit playerChanged();
}

int CaroViewModel::getPixel()
{
    int value = m_turn == turnOne ? X : O;
    return value;
}

QVariantList CaroViewModel::pointLineWinner() const
{
    return m_pointLineWinner;
}

void CaroViewModel::setPointLineWinner(const QVariantList &newPointLineWinner)
{
    if (m_pointLineWinner == newPointLineWinner)
        return;
    m_pointLineWinner = newPointLineWinner;
    emit pointLineWinnerChanged();
}

int CaroViewModel::playerWinner() const
{
    return m_playerWinner;
}

void CaroViewModel::setPlayerWinner(int newPlayerWinner)
{
    if (m_playerWinner == newPlayerWinner)
        return;
    m_playerWinner = newPlayerWinner;
    emit playerWinnerChanged();
}

void CaroViewModel::requestComputerAction()
{
    if(m_modeGame == playerVsPlayer || m_player[m_turn].toMap()["name"] != name_computer)
        return;
    point _point = computer->requestComputerMove(m_turn == turnOne ? X : O);
    setPixelBoard(_point.x, _point.y);
}

void CaroViewModel::setWinner(int &_turn, point &start, point &end)
{
    setPlayerWinner(_turn);
    QVariantList list;
    QVariantMap map;
    map["x"] = start.x;
    map["y"] = start.y;
    QVariant variant(map);
    list.append(map);
    map["x"] = end.x;
    map["y"] = end.y;
    variant = QVariant(map);
    list.append(variant);
    setPointLineWinner(list);
    emit boardChanged();
}
