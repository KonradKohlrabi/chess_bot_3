#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <cctype>
#include <raylib.h>
#include <cstring>

using namespace std;

void printBoard(char board[8][8])
{
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << "[" << board[i][j] << "]";
        }
        cout << endl;
    }
}

array<int, 5> inputToMove(string input)
{
    array<int, 5> move = {input[1] - '0' - 1, input[0] - 'a', input[3] - '0' - 1, input[2] - 'a', 0};
    return move;
}

void movePiece(array<int, 5> move, char board[8][8])
{
    char piece = board[move[0]][move[1]];
    if (move[4] == 0)
    {
        board[move[0]][move[1]] = ' ';
        board[move[2]][move[3]] = piece;
    }
    else
    {
        char promotionsLower[4] = {'q', 'r', 'n', 'b'};
        char promotionsUpper[4] = {'Q', 'R', 'N', 'B'};
        board[move[0]][move[1]] = ' ';
        if (move[4] == 5)
        {
            if (islower(piece))
            {
                board[0][4] = ' ';
                board[0][7] = ' ';
                board[0][5] = 'r';
                board[0][6] = 'k';
            }
            else
            {
                board[7][4] = ' ';
                board[7][7] = ' ';
                board[7][5] = 'R';
                board[7][6] = 'K';
            }
        }
        else if (move[4] == 6)
        {
            if (islower(piece))
            {
                board[0][4] = ' ';
                board[0][0] = ' ';
                board[0][3] = 'r';
                board[0][2] = 'k';
            }
            else
            {
                board[7][4] = ' ';
                board[7][0] = ' ';
                board[7][3] = 'R';
                board[7][2] = 'K';
            }
        }
        else if (islower(piece))
        {
            board[move[2]][move[3]] = promotionsLower[move[4] - 1];
        }
        else if (isupper(piece))
        {
            board[move[2]][move[3]] = promotionsUpper[move[4] - 1];
        }
    }
}

vector<array<int, 5>> getAllMoves(char board[8][8], bool isWhitesTurn)
{
    vector<array<int, 5>> moves;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char piece = board[i][j];

            if (piece == 'p' && i + 1 <= 7)
            {
                if (board[i + 1][j] == ' ')
                {

                    if (i + 2 <= 7 && i == 1 && board[i + 2][j] == ' ')
                    {
                        moves.push_back(array<int, 5>{i, j, i + 2, j, 0});
                    }
                    if (i == 6 && board[7][j] == ' ')
                    {
                        moves.push_back(array<int, 5>{i, j, i + 1, j, 1});
                        moves.push_back(array<int, 5>{i, j, i + 1, j, 2});
                        moves.push_back(array<int, 5>{i, j, i + 1, j, 3});
                        moves.push_back(array<int, 5>{i, j, i + 1, j, 4});
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, i + 1, j, 0}); // letzte Zahl zusatzcode 0 = kein zusatz, 1 = dame, 2 = turm, 3 = springer, 4 = läufer, 5 = kurze rochade, 6 = lange rochade
                    }
                }
                if (j + 1 <= 7 && isupper(board[i + 1][j + 1]) && i != 6)
                {
                    moves.push_back(array<int, 5>{i, j, i + 1, j + 1, 0});
                }
                if (j - 1 >= 0 && isupper(board[i + 1][j - 1]) && i != 6)
                {
                    moves.push_back(array<int, 5>{i, j, i + 1, j - 1, 0});
                }
                if (i == 6 && j + 1 <= 7 && board[7][j + 1] != ' ' && isupper(board[7][j + 1]))
                {
                    moves.push_back(array<int, 5>{i, j, i + 1, j + 1, 1});
                    moves.push_back(array<int, 5>{i, j, i + 1, j + 1, 2});
                    moves.push_back(array<int, 5>{i, j, i + 1, j + 1, 3});
                    moves.push_back(array<int, 5>{i, j, i + 1, j + 1, 4});
                }
                if (i == 6 && j - 1 >= 0 && board[7][j - 1] != ' ' && isupper(board[7][j - 1]))
                {
                    moves.push_back(array<int, 5>{i, j, i + 1, j - 1, 1});
                    moves.push_back(array<int, 5>{i, j, i + 1, j - 1, 2});
                    moves.push_back(array<int, 5>{i, j, i + 1, j - 1, 3});
                    moves.push_back(array<int, 5>{i, j, i + 1, j - 1, 4});
                }
            }
            else if (piece == 'P' && i - 1 >= 0)
            {
                if (board[i - 1][j] == ' ')
                {
                    if (i - 2 >= 0 && i == 6 && board[i - 2][j] == ' ')
                    {
                        moves.push_back(array<int, 5>{i, j, i - 2, j, 0});
                    }
                    if (i == 1 && board[0][j] == ' ')
                    {
                        moves.push_back(array<int, 5>{i, j, i - 1, j, 1});
                        moves.push_back(array<int, 5>{i, j, i - 1, j, 2});
                        moves.push_back(array<int, 5>{i, j, i - 1, j, 3});
                        moves.push_back(array<int, 5>{i, j, i - 1, j, 4});
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, i - 1, j, 0});
                    }
                }
                if (j + 1 <= 7 && islower(board[i - 1][j + 1]) && i != 1)
                {
                    moves.push_back(array<int, 5>{i, j, i - 1, j + 1, 0});
                }
                if (j - 1 >= 0 && islower(board[i - 1][j - 1]) && i != 1)
                {
                    moves.push_back(array<int, 5>{i, j, i - 1, j - 1, 0});
                }
                if (i == 1 && j + 1 <= 7 && board[0][j + 1] != ' ' && islower(board[0][j + 1]))
                {
                    moves.push_back(array<int, 5>{i, j, i - 1, j + 1, 1});
                    moves.push_back(array<int, 5>{i, j, i - 1, j + 1, 2});
                    moves.push_back(array<int, 5>{i, j, i - 1, j + 1, 3});
                    moves.push_back(array<int, 5>{i, j, i - 1, j + 1, 4});
                }
                if (i == 1 && j - 1 >= 0 && board[0][j - 1] != ' ' && islower(board[0][j - 1]))
                {
                    moves.push_back(array<int, 5>{i, j, i - 1, j - 1, 1});
                    moves.push_back(array<int, 5>{i, j, i - 1, j - 1, 2});
                    moves.push_back(array<int, 5>{i, j, i - 1, j - 1, 3});
                    moves.push_back(array<int, 5>{i, j, i - 1, j - 1, 4});
                }
            }
            else if (piece == 'n' || piece == 'N')
            {
                int possibleKnightSquares[8][2] = {{i + 2, j + 1}, {i + 2, j - 1}, {i - 2, j + 1}, {i - 2, j - 1}, {i + 1, j - 2}, {i - 1, j + 2}, {i + 1, j + 2}, {i - 1, j - 2}};
                for (int k = 0; k < 8; k++)
                {
                    int x = possibleKnightSquares[k][0];
                    int y = possibleKnightSquares[k][1];
                    if (x <= 7 && x >= 0 && y <= 7 && y >= 0 && (board[x][y] == ' ' || islower(board[x][y]) != islower(board[i][j])))
                    {
                        moves.push_back(array<int, 5>{i, j, x, y, 0});
                    }
                }
            }
            else if (piece == 'k' || piece == 'K')
            {
                int possibleKingSquares[8][2] = {{i, j + 1}, {i, j - 1}, {i + 1, j}, {i - 1, j}, {i + 1, j + 1}, {i + 1, j - 1}, {i - 1, j + 1}, {i - 1, j - 1}};
                for (int k = 0; k < 8; k++)
                {
                    int x = possibleKingSquares[k][0];
                    int y = possibleKingSquares[k][1];
                    if (x <= 7 && x >= 0 && y <= 7 && y >= 0 && (islower(board[x][y]) != islower(board[i][j]) || board[x][y] == ' '))
                    {
                        moves.push_back(array<int, 5>{i, j, x, y, 0});
                    }
                }
                if (piece == 'K' && board[7][4] == 'K')
                {
                    if (board[7][7] == 'R' && board[7][6] == ' ' && board[7][5] == ' ')
                    {
                        moves.push_back(array<int, 5>{i, j, 7, 6, 5});
                    }
                    if (board[7][0] == 'R' && board[7][1] == ' ' && board[7][2] == ' ' && board[7][3] == ' ')
                    {
                        moves.push_back(array<int, 5>{i, j, 7, 2, 6});
                    }
                }
                else if (piece == 'k' && board[0][4] == 'k')
                {
                    if (board[0][7] == 'r' && board[0][6] == ' ' && board[0][5] == ' ')
                    {
                        moves.push_back(array<int, 5>{i, j, 0, 6, 5});
                    }
                    if (board[0][0] == 'r' && board[7][1] == ' ' && board[7][2] == ' ' && board[7][3] == ' ')
                    {
                        moves.push_back(array<int, 5>{i, j, 0, 2, 6});
                    }
                }
            }
            else if (piece == 'r' || piece == 'R')
            {
                int k = i + 1;
                bool running = true;
                while (k <= 7 && running)
                {
                    if (board[k][j] != ' ')
                    {
                        running = false;
                        if (islower(board[k][j]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, k, j, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, k, j, 0});
                        k++;
                    }
                }

                k = i - 1;
                running = true;
                while (k >= 0 && running)
                {
                    if (board[k][j] != ' ')
                    {
                        running = false;
                        if (islower(board[k][j]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, k, j, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, k, j, 0});
                        k--;
                    }
                }

                k = j + 1;
                running = true;
                while (k <= 7 && running)
                {
                    if (board[i][k] != ' ')
                    {
                        running = false;
                        if (islower(board[i][k]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, i, k, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, i, k, 0});
                        k++;
                    }
                }

                k = j - 1;
                running = true;
                while (k >= 0 && running)
                {
                    if (board[i][k] != ' ')
                    {
                        running = false;
                        if (islower(board[i][k]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, i, k, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, i, k, 0});
                        k--;
                    }
                }
            }
            else if (piece == 'q' || piece == 'Q')
            {
                int k = i + 1;
                bool running = true;
                while (k <= 7 && running)
                {
                    if (board[k][j] != ' ')
                    {
                        running = false;
                        if (islower(board[k][j]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, k, j, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, k, j, 0});
                        k++;
                    }
                }

                k = i - 1;
                running = true;
                while (k >= 0 && running)
                {
                    if (board[k][j] != ' ')
                    {
                        running = false;
                        if (islower(board[k][j]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, k, j, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, k, j, 0});
                        k--;
                    }
                }

                k = j + 1;
                running = true;
                while (k <= 7 && running)
                {
                    if (board[i][k] != ' ')
                    {
                        running = false;
                        if (islower(board[i][k]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, i, k, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, i, k, 0});
                        k++;
                    }
                }

                k = j - 1;
                running = true;
                while (k >= 0 && running)
                {
                    if (board[i][k] != ' ')
                    {
                        running = false;
                        if (islower(board[i][k]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, i, k, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, i, k, 0});
                        k--;
                    }
                }

                int x = i + 1;
                int y = j + 1;
                running = true;
                while (x <= 7 && y <= 7 && running)
                {
                    if (board[x][y] != ' ')
                    {
                        running = false;
                        if (islower(board[x][y]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, x, y, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, x, y, 0});
                        x++;
                        y++;
                    }
                }

                x = i + 1;
                y = j - 1;
                running = true;
                while (x <= 7 && y >= 0 && running)
                {
                    if (board[x][y] != ' ')
                    {
                        running = false;
                        if (islower(board[x][y]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, x, y, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, x, y, 0});
                        x++;
                        y--;
                    }
                }

                x = i - 1;
                y = j + 1;
                running = true;
                while (x >= 0 && y <= 7 && running)
                {
                    if (board[x][y] != ' ')
                    {
                        running = false;
                        if (islower(board[x][y]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, x, y, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, x, y, 0});
                        x--;
                        y++;
                    }
                }

                x = i - 1;
                y = j - 1;
                running = true;
                while (x >= 0 && y >= 0 && running)
                {
                    if (board[x][y] != ' ')
                    {
                        running = false;
                        if (islower(board[x][y]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, x, y, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, x, y, 0});
                        x--;
                        y--;
                    }
                }
            }
            else if (piece == 'b' || piece == 'B')
            {
                bool running = true;
                int x = i + 1;
                int y = j + 1;
                while (x <= 7 && y <= 7 && running)
                {
                    if (board[x][y] != ' ')
                    {
                        running = false;
                        if (islower(board[x][y]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, x, y, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, x, y, 0});
                        x++;
                        y++;
                    }
                }

                x = i + 1;
                y = j - 1;
                running = true;
                while (x <= 7 && y >= 0 && running)
                {
                    if (board[x][y] != ' ')
                    {
                        running = false;
                        if (islower(board[x][y]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, x, y, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, x, y, 0});
                        x++;
                        y--;
                    }
                }

                x = i - 1;
                y = j + 1;
                running = true;
                while (x >= 0 && y <= 7 && running)
                {
                    if (board[x][y] != ' ')
                    {
                        running = false;
                        if (islower(board[x][y]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, x, y, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, x, y, 0});
                        x--;
                        y++;
                    }
                }

                x = i - 1;
                y = j - 1;
                running = true;
                while (x >= 0 && y >= 0 && running)
                {
                    if (board[x][y] != ' ')
                    {
                        running = false;
                        if (islower(board[x][y]) != islower(board[i][j]))
                        {
                            moves.push_back(array<int, 5>{i, j, x, y, 0});
                        }
                    }
                    else
                    {
                        moves.push_back(array<int, 5>{i, j, x, y, 0});
                        x--;
                        y--;
                    }
                }
            }

            for (int i = (int)moves.size() - 1; i >= 0; i--)
            {
                if ((islower(board[moves[i][0]][moves[i][1]]) && !isWhitesTurn) || (isupper(board[moves[i][0]][moves[i][1]]) && isWhitesTurn))
                {
                    moves.erase(moves.begin() + i);
                }
            }
        }
    }

    return moves;
}

vector<array<int, 5>> getAllowedMoves(char board[8][8], bool isWhitesTurn)
{
    vector<array<int, 5>> moves = getAllMoves(board, isWhitesTurn);
    char tmp_board[8][8];

    int kingX;
    int kingY;

    for (int i = (int)moves.size() - 1; i >= 0; i--)
    {
        memcpy(tmp_board, board, sizeof(tmp_board));
        movePiece(moves[i], tmp_board);

        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                if ((tmp_board[x][y] == 'k' && isWhitesTurn) || (tmp_board[x][y] == 'K' && !isWhitesTurn))
                {
                    kingX = x;
                    kingY = y;
                }
            }
        }

        vector<array<int, 5>> tmp_moves = getAllMoves(tmp_board, !isWhitesTurn);
        for (int j = 0; j < tmp_moves.size(); j++)
        {
            if (tmp_moves[j][2] == kingX && tmp_moves[j][3] == kingY) // King is Capturable
            {
                moves.erase(moves.begin() + i);
                break;
            }
        }
    }
    return moves;
}

bool isAllowedMove(array<int, 5> move, char board[8][8], bool isWhitesTurn)
{
    bool isAllowedMove = false;
    vector<array<int, 5>> allowedMoves = getAllMoves(board, isWhitesTurn);
    for (int i = 0; i < allowedMoves.size(); i++)
    {
        if (move == allowedMoves[i])
        {
            isAllowedMove = true;
        }
        cout << allowedMoves[i][0];
        cout << allowedMoves[i][1];
        cout << allowedMoves[i][2];
        cout << allowedMoves[i][3];
        cout << allowedMoves[i][4];
        cout << endl;
    }
    return isAllowedMove;
}

int evaluateForWhite(char board[8][8])
{
    // Weights
    unordered_map<char, int> pieceValues = {
        {'p', 1},
        {'b', 3},
        {'n', 3},
        {'r', 5},
        {'q', 9},
        {'k', 0},
        {'P', -1},
        {'B', -3},
        {'N', -3},
        {'R', -5},
        {'Q', -9},
        {'K', 0}};

    int eval = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != ' ')
            {
                eval += pieceValues[board[i][j]];
            }
        }
    }

    return eval;
}

int isGameOver(char board[8][8], bool isWhitesTurn)
{
    if (getAllowedMoves(board, isWhitesTurn).size() == 0)
    {
        int kingX;
        int kingY;

        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                if ((board[x][y] == 'k' && isWhitesTurn) || (board[x][y] == 'K' && !isWhitesTurn))
                {
                    kingX = x;
                    kingY = y;
                }
            }
        }

        for (const auto &move : getAllowedMoves(board, !isWhitesTurn))
        {
            if (move[2] == kingX && move[3] == kingY)
            {
                return 2;
            }
        }
        return 1;
    }

    return 0; // 0 = kein ende, 1 = unentschieden, 2 = matt
}

int minimax(char board[8][8], int depth, bool isWhitesTurn, int alpha, int beta) // alpha beta pruining
{
    if (depth == 0 || isGameOver(board, isWhitesTurn) == 1)
    {
        return evaluateForWhite(board);
    }
    else if (isGameOver(board, isWhitesTurn) == 2)
    {
        if (isWhitesTurn)
        {
            return -100000;
        }
        else
        {
            return 100000;
        }
    }
    else if (isWhitesTurn)
    {
        int maxEval = -1000000;

        vector<array<int, 5>> moves = getAllowedMoves(board, isWhitesTurn);
        for (int i = 0; i < moves.size(); i++)
        {
            char tmp_board[8][8];
            memcpy(tmp_board, board, sizeof(tmp_board));
            movePiece(moves[i], tmp_board);

            int eval = minimax(tmp_board, depth - 1, false, alpha, beta);

            maxEval = max(eval, maxEval);

            alpha = max(alpha, maxEval);

            if (alpha >= beta)
            {
                break;
            }
        }

        return maxEval;
    }
    else
    {
        int minEval = 1000000;

        vector<array<int, 5>> moves = getAllowedMoves(board, isWhitesTurn);
        for (int i = 0; i < moves.size(); i++)
        {
            char tmp_board[8][8];
            memcpy(tmp_board, board, sizeof(tmp_board));
            movePiece(moves[i], tmp_board);

            int eval = minimax(tmp_board, depth - 1, true, alpha, beta);

            minEval = min(eval, minEval);

            beta = min(beta, minEval);

            if (alpha >= beta)
            {
                break;
            }
        }

        return minEval;
    }
}

int findBestMove(char board[8][8], bool isWhitesTurn)
{
    const int depth = 4;

    vector<array<int, 5>> moves = getAllowedMoves(board, isWhitesTurn);

    int bestMove = 0;
    int value;

    if (isWhitesTurn)
    {
        int maxEval = -1000000;
        for (int i = 0; i < moves.size(); i++)
        {
            char tmp_board[8][8];
            memcpy(tmp_board, board, sizeof(tmp_board));
            movePiece(moves[i], tmp_board);

            value = minimax(tmp_board, depth - 1, false, -1000000, 1000000);

            if (value > maxEval)
            {
                bestMove = i;
                maxEval = value;
            }
        }
    }
    else
    {
        int minEval = 1000000;
        for (int i = 0; i < moves.size(); i++)
        {
            char tmp_board[8][8];
            memcpy(tmp_board, board, sizeof(tmp_board));
            movePiece(moves[i], tmp_board);

            value = minimax(tmp_board, depth - 1, true, -1000000, 1000000);

            if (value < minEval)
            {
                bestMove = i;
                minEval = value;
            }
        }
    }

    return bestMove;
}

int main()
{
    InitWindow(800, 800, "Egon Engine");
    SetTargetFPS(60);

    unordered_map<char, int> pieceMap = {{'p', 0},
                                         {'b', 1},
                                         {'n', 2},
                                         {'r', 3},
                                         {'q', 4},
                                         {'k', 5},
                                         {'P', 6},
                                         {'B', 7},
                                         {'N', 8},
                                         {'R', 9},
                                         {'Q', 10},
                                         {'K', 11}};

    char board[8][8] = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, // lower = white, upper = black
                        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

    bool running = true;

    Texture2D pieces[12];

    Color brownTile = {137, 81, 42, 255};
    Color clickPointColor = GREEN;
    Color lastMoveColor = {0, 220, 0, 150};

    vector<array<int, 2>> clickPoints = {};

    Vector2 mouse;
    int selectedPieceX;
    int selectedPieceY;

    bool isWhitesTurn = true;
    array<int, 5> lastMove;

    for (int i = 0; i < 12; i++)
    {
        pieces[i] = LoadTexture(("sprites/" + to_string(i) + ".png").c_str());
    }

    while (running)
    {
        bool moved = false;

        // Handle Clicks
        mouse = GetMousePosition();
        vector<array<int, 5>> allowedMoves = getAllowedMoves(board, isWhitesTurn);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (clickPoints.size() == 0)
            {
                for (int i = 0; i < allowedMoves.size(); i++)
                {
                    if (allowedMoves[i][1] == (int)(mouse.x / 100) && allowedMoves[i][0] == 7 - (int)(mouse.y / 100))
                    {
                        clickPoints.push_back({allowedMoves[i][3], allowedMoves[i][2]});
                        selectedPieceX = allowedMoves[i][0];
                        selectedPieceY = allowedMoves[i][1];
                    }
                }
            }
            else
            {
                int x = (int)mouse.x / 100;
                int y = 7 - (int)mouse.y / 100;
                for (int i = 0; i < clickPoints.size(); i++)
                {
                    if (clickPoints[i][0] == x && clickPoints[i][1] == y)
                    {
                        for (auto move : allowedMoves)
                        {
                            if (move[0] == selectedPieceX && move[1] == selectedPieceY && move[3] == x && move[2] == y)
                            {
                                movePiece(move, board);
                                lastMove = move;
                            }
                        }
                        // movePiece({selectedPieceX, selectedPieceY, clickPoints[i][1], clickPoints[i][0], 0}, board);
                        isWhitesTurn = !isWhitesTurn;
                        moved = true;
                    }
                }
                clickPoints = {};
                if (!moved)
                {
                    vector<array<int, 5>> allowedMoves = getAllowedMoves(board, isWhitesTurn);
                    for (int i = 0; i < allowedMoves.size(); i++)
                    {
                        if (allowedMoves[i][1] == (int)(mouse.x / 100) && allowedMoves[i][0] == 7 - (int)(mouse.y / 100))
                        {
                            clickPoints.push_back({allowedMoves[i][3], allowedMoves[i][2]});
                            selectedPieceX = allowedMoves[i][0];
                            selectedPieceY = allowedMoves[i][1];
                        }
                    }
                }
            }
        }

        // Draw Screen
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if ((i + j) % 2 == 1)
                {
                    DrawRectangle(j * 100, i * 100, 100, 100, brownTile);
                }
                if (lastMove[0] == 7 - i && lastMove[1] == j || lastMove[2] == 7 - i && lastMove[3] == j)
                {
                    DrawRectangle(j * 100, i * 100, 100, 100, lastMoveColor);
                }
            }
        }

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] != ' ')
                {
                    DrawTextureEx(
                        pieces[pieceMap[board[i][j]]],
                        {(float)j * 100, (float)(7 - i) * 100},
                        0.0f,
                        100.0f / 128.0f,
                        WHITE);
                }
            }
        }

        for (int i = 0; i < clickPoints.size(); i++)
        {
            DrawCircle(clickPoints[i][0] * 100 + 50, (7 - clickPoints[i][1]) * 100 + 50, 10, clickPointColor);
        }

        EndDrawing();

        running = !WindowShouldClose();

        int gameState = isGameOver(board, isWhitesTurn);
        if (gameState == 1)
        {
            cout << "Das Spiel endet Unentschieden";
            running = false;
        }
        else if (gameState == 2 && isWhitesTurn)
        {
            cout << "Schachmatt, schwarz ist der Sieger!";
            running = false;
        }
        else if (gameState == 2 && !isWhitesTurn)
        {
            cout << "Schachmatt, weiss ist der Sieger!";
            running = false;
        }
        else if (moved) // Bot
        {
            vector<array<int, 5>> allowedMoves = getAllowedMoves(board, isWhitesTurn);
            int bestMove = findBestMove(board, isWhitesTurn);
            movePiece(allowedMoves[bestMove], board);
            lastMove = allowedMoves[bestMove];
            isWhitesTurn = !isWhitesTurn;
        }

        gameState = isGameOver(board, isWhitesTurn);
        if (gameState == 1)
        {
            cout << "Das Spiel endet Unentschieden";
            running = false;
        }
        else if (gameState == 2 && isWhitesTurn)
        {
            cout << "Schachmatt, schwarz ist der Sieger!";
            running = false;
        }
        else if (gameState == 2 && !isWhitesTurn)
        {
            cout << "Schachmatt, weiss ist der Sieger!";
            running = false;
        }
    }
    CloseWindow();
    return 0;
}
