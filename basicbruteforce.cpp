#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const int BoardSize = 4;
const int CellSize = 2;

int board[BoardSize][BoardSize];

bool check(int ch, int row, int col)
{
    // check in row
    for (int c = 0; c < BoardSize; c++)
    {
        if (c != col && board[row][c] == ch)
            return false;
    }

    // check in col
    for (int r = 0; r < BoardSize; r++)
    {
        if (r != row && board[r][col] == ch)
            return false;
    }

    // check in square
    int str = (row / CellSize) * CellSize;
    int stc = (col / CellSize) * CellSize;
    for (int dx = 0; dx < CellSize; dx++)
    {
        for (int dy = 0; dy < CellSize; dy++)
        {
            if (str + dx == row && stc + dy == col)
                continue;

            if (ch == board[str + dx][stc + dy])
                return false;
        }
    }
    return true;
}

int ans = 0;

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
        for (int ch = 1; ch <= BoardSize; ch++)
        {
            if (check(ch, row, col))
            {
                board[row][col] = ch;
                rec(row, col + 1);
                board[row][col] = 0;
            }
        }
    }
    else
    {
        if (check(board[row][col], row, col))
        {
            // pre-filled solution does not collide; solution exists
            rec(row, col + 1);
        }
    }
}

void solve()
{
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            cin >> board[i][j];
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