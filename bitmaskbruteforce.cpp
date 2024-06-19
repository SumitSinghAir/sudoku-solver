#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const int BoardSize = 9;
const int CellSize = 3;

int board[BoardSize][BoardSize];
int takenRow[BoardSize];
int takenCol[BoardSize];
int takenGrid[CellSize][CellSize];

int ans = 0;

int makemove(int ch, int row, int col)
{
    board[row][col] = ch;
    // x xor by 1 flips the value of x
    takenRow[row] ^= (1 << ch);
    takenCol[col] ^= (1 << ch);
    takenGrid[row / CellSize][col / CellSize] ^= (1 << ch);
}

int revertmove(int ch, int row, int col)
{
    board[row][col] = 0;
    // x xor by 1 flips the value of x
    takenRow[row] ^= (1 << ch);
    takenCol[col] ^= (1 << ch);
    takenGrid[row / CellSize][col / CellSize] ^= (1 << ch);
}

int getChoices(int row, int col)
{
    int taken = (takenRow[row] | takenCol[col] | takenGrid[row / CellSize][col / CellSize]);
    int notTaken = ((1 << BoardSize + 1) - 1) ^ taken; // simple ~taken will not work as it is 32 bit so it will have preceding ones in beginning
    // int notTaken = (~taken)&((1 << BoardSize + 1) - 1); //this will also work
    if (notTaken & 1)
        notTaken ^= 1; // bit at 0th position is not useful for bitmask, make it 0
    return notTaken;
}

void rec(int row, int col)
{
    // base case
    if (col == BoardSize)
    {
        rec(row + 1, 0);
        return;
    }
    if (row == BoardSize)
    {
        ans++;
        cout << "Answer no.: " << ans << endl;
        for (int i = 0; i < BoardSize; i++)
        {
            for (int j = 0; j < BoardSize; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        return;
    }

    // recursive case
    // cout << "HEHE " << endl;
    if (board[row][col] == 0)
    {
        // we need to fill

        int chmask = getChoices(row, col);
        for (int ch = 1; ch <= BoardSize; ch++)
        {
            if (chmask & (1 << ch))
            {
                makemove(ch, row, col);
                rec(row, col + 1);
                revertmove(ch, row, col);
            }
        }
    }
    else
    {
        // assuming that solution exists; i.e. prefilled values do not collide
        rec(row, col + 1);
    }
}

void solve()
{
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            int ch;
            cin >> ch;
            makemove(ch, i, j);
        }
    }
    rec(0, 0);
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin>>t;
    while (t--)
        solve();
}