class Solution {
public:
    bool row[9][10], col[9][10], square[9][10];

    bool dfs(int cell, vector<vector<char>>& board)
    {
        if (cell == 81) return true;

        int i = cell / 9, j = cell % 9;

        // This cell was written
        if (board[i][j] != '.') {
            return (dfs(cell + 1, board));
        }

        // was not writen
        for (int k = 1; k <= 9; k++)
        {
            if (!row[i][k] && !col[j][k] && !square[(i / 3) * 3 + j / 3][k])
            {
                board[i][j] = '0' + k;
                row[i][k] = col[j][k] = square[(i / 3) * 3 + j / 3][k] = true;
                if (dfs(cell + 1, board)) return true;
                board[i][j] = '.';
                row[i][k] = col[j][k] = square[(i / 3) * 3 + j / 3][k] = false;
            }
        }

        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    int k = board[i][j] - '0';
                    row[i][k] = col[j][k] = square[(i / 3) * 3 + j / 3][k] = true;
                }
            }
        }
        dfs(0, board);
    }
};
