#ifndef MINESWEEPERMODEL_H
#define MINESWEEPERMODEL_H

#include <stdlib.h>
#include <stdio.h>



enum Cell
{
    CLEAR=0,
    UNKOWN=-1,
    MINE=-2,
    FLAG_CORRECT=-3,
    FLAG_INCORRECT=-4,
    MINE_TRIPPED=-5
};

enum GameStatus
{ 
    GAME_PLAYING=0,
    GAME_WON=1,
    GAME_OVER=2
};





class MinesweeperModel
{
  private:
    int **Board;
    int Size;
    int MineCount;
    int FlagCorrectCount,FlagIncorrectCount;

  public:
    MinesweeperModel(int size) : Size(size)
    {
        Board = new int *[Size];
        FlagCorrectCount=FlagIncorrectCount=0;

        for (int row = 0; row < Size; row++)
        {
            Board[row] = new int[Size];
            for (int col = 0; col < Size; col++)
            {
                Board[row][col] = UNKOWN;
            }
        }
    }

    ~MinesweeperModel()
    {
        for (int i = 0; i < Size; i++)
            delete[] Board[i];
        delete[] Board;
    }

    void GetDimensions(int& rows, int& cols) const
    {
        rows=Size;cols=Size;
    }

    int GetTileAt(int row, int col) const
    {
        return Board[row][col];
    }

    int GetMineCount() const
    {
        return (MineCount-FlagCorrectCount-FlagIncorrectCount);
    }

    bool GameComplete()const
    {
        return (MineCount==FlagCorrectCount) &&(FlagIncorrectCount==0);
    }








    void GenerateMines()
    {
        srand(Size);
        MineCount = Size;

        int row, col;

        for (int i = 0; i < Size; i++)
        {
            while (Board[row = rand() % Size][col = rand() % Size] == MINE)
                ;
            Board[row][col] = MINE; //set flag
        }
    }

    bool GetTileCount(int row, int col)
    {
        int mineCount = 0;
        int flagCount = 0;

        // printf("Checking cell %2d,%2d\n", row, col); fflush(stdout);

        if (row < 0 || row >= Size || col < 0 || col >= Size)
        {
            return true;
        }

        // iterate through all neighboring cells and count up the Mines
        for (int r = row - 1; r <= row + 1; r++)
        {
            for (int c = col - 1; c <= col + 1; c++)
            {
                if (!((r == row) && (c == col)) && (c >= 0) && (c < Size) && (r >= 0) && (r < Size))
                {
                    // printf("\tChecking cell %2d,%2d ", r, c);
                    if (Board[r][c] == MINE)
                    {
                        //  printf("Mine found!");
                        mineCount++;
                    }
                    if (Board[r][c] == FLAG_CORRECT)
                    {
                        flagCount++;
                        mineCount++;
                    }
                    if (Board[r][c] == FLAG_INCORRECT)
                    {
                        flagCount++;
                        mineCount--;
                    }
                    
                }
            }
        }
        
        if (flagCount > mineCount)
        {
            return false;
        }
        Board[row][col] = mineCount;


        // if the count of mines are 0 then we should check all neighboring cells
        if (mineCount == 0 || mineCount == flagCount)
        {
            for (int r = row - 1; r <= row + 1; r++)
            {
                for (int c = col - 1; c <= col + 1; c++)
                {
                    if (!((r == row) && (c == col)) && (c >= 0) && (c < Size) && (r >= 0) && (r < Size))
                    {
                        if (Board[r][c] == UNKOWN)
                            GetTileCount(r, c);
                    }
                }
            }
        }
        return true;
    }

    void SetFlag(int row, int col)
    {
 
        if(Board[row][col]>UNKOWN)
        {

        }
        else if (Board[row][col]==FLAG_CORRECT)
        {
            //remove flag, set back to mine
            Board[row][col]=MINE;
            FlagCorrectCount--;
        }
        else if (Board[row][col]==FLAG_INCORRECT)
        {
            //remove flag, set back to UNKOWN
            Board[row][col]=UNKOWN;
            FlagIncorrectCount--;
        }
        else if (Board[row][col] == MINE)
        {
            Board[row][col] = FLAG_CORRECT;
            FlagCorrectCount++;
        }
        else 
        {
            Board[row][col] = FLAG_INCORRECT;
            FlagIncorrectCount++;
        }
    }

    GameStatus SelectTile(int row, int col, char act)
    {
        int &cell = Board[row][col];
        if (act == 'F'||act=='f')
        {
            SetFlag(row, col);
            if(GameComplete())
            {
                return GAME_WON;
            }

        }
        else
        {
            if (cell == MINE)
            {
                cell = CLEAR;
                //game over
                cell = MINE_TRIPPED;
                return GAME_OVER;
            }
            else
            {
                if( ! GetTileCount(row, col))
                {
                    return GAME_OVER;
                }
                 
            }
        }
        return GAME_PLAYING;
    }
};

#endif