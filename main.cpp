#include<iostream>
using namespace std;

bool Check(char x, char y, char z)
{
    if(x == y & x == z & x != ' ')
    {
        return true;
    }
    return false;
}

int checkWinner(char board[3][3])
{
    //  2: Player winner (X)
    //  -2: AI winner    (O)
    //  0: Tie case      (X = O)
    //  1: No winner

    // Check Rows
    for(int i = 0; i < 3; i++)
    {
        if(Check(board[i][0], board[i][1], board[i][2]))
        {
            return board[i][0] == 'X' ? 2 : -2;
        }
    }

    // Check Cols
    for(int i = 0; i < 3; i++)
    {
        if(Check(board[0][i], board[1][i], board[2][i]))
        {
            return board[0][i] == 'X' ? 2 : -2;
        }
    }

    // Check Diameter 1
    if(Check(board[0][0], board[1][1], board[2][2]))
    {
        return board[0][0] == 'X' ? 2 : -2;
    }

    // Check Diameter 2
    if(Check(board[2][0], board[1][1], board[0][2]))
    {
        return board[2][0] == 'X' ? 2 : -2;
    }

    // Check Tie Case
    bool tie = true;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == ' ')
            {
                tie = false;
            }
        }
    }
    if(tie)
        return 0;

    // Continue Playing
    return 1;
}

void drowBoard(char board[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cout << "| " << board[i][j] << " |";
        }
        cout << "\n -------------- \n";
    }
}

int miniMax(char board[3][3], int depth, bool Maximiz, bool firstTime)
{
    int result = checkWinner(board);
    if(depth == 0 | result != 1)
    {
        return result;
    }

    if(Maximiz)
    {
        int finalScore = -3;
        int valueI,valueJ;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    int score = miniMax(board, depth - 1, false, false);
                    board[i][j] = ' ';
                    if(score > finalScore)
                    {
                        finalScore = score;
                        valueI = i;
                        valueJ = j;
                    }
                }
            }
        }
        if(firstTime)
        {
            board[valueI][valueJ] = 'O';
        }
        return finalScore;
    }
    else
    {
        int finalScore = 300;
        int valueI,valueJ;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    int score = miniMax(board, depth - 1, true, false);
                    board[i][j] = ' ';
                    if(score < finalScore)
                    {
                        finalScore = score;
                        valueI = i;
                        valueJ = j;
                    }
                }
            }
        }
        if(firstTime)
        {
            board[valueI][valueJ] = 'O';
        }
        return finalScore;
    }
}

int main()
{
    char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    int x, y;
    bool winner = false;
    char player = 'X';
    while(!winner)
    {
        cout<<"Enter Index : ";
        cin >> x >> y;
        if(board[x][y] == ' ')
        {
            board[x][y] = player;
            //player == 'X' ? player = 'O' : player = 'X';
            int result =  miniMax(board, 100, false,true);
            //int result = checkWinner(board);
            drowBoard(board);
            cout << "result: " << result << "\n";
            winner = (checkWinner(board) != 1);
        }
        else
        {
            cout << "The Field is Not Empty \n";
        }
    }

    int result = checkWinner(board);
    if(result == 0)
    {
        cout << "Tie \n";
    }
    else
    {
        if(result == 2)
            cout<< " X Player Wins"<<endl;
        else if(result == -2)
            cout<< " O Player Wins"<<endl;
    }
    return 0;
}
