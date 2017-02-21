#ifndef MINESWEEPERVIEW
#define MINESWEEPERVIEW

class MinesweeperView
{
private:

   
  public:
  void PromptPlayer()
  {
      printf("Select a tile in format: row,col,action\n");
      printf("Actions:\n");
      printf("S - Select\n");
      printf("F - Flag\n");
  }
  void GetPlayerInput(int& row, int& col, char& act)
  {
      scanf("%d,%d,%c",&row,&col,&act);
  }

  void DisplayGameOver(const MinesweeperModel &game)
  {
      printf("\n\n--- GAME OVER ---\n you've hit a mine!\n");
      DrawBoard(game,true);
  }
  void DisplayGameWon(const MinesweeperModel &game)
  {
      printf("\n\n--- YOU WIN! ---\n");
      DrawBoard(game,true);
  }


    void DrawBoard(const MinesweeperModel &game,bool showMines=false)
    {
        char display;
        int rows, cols;
        int val;
        game.GetDimensions(rows,cols);

        printf("\n\n");
        if(!showMines)
            printf("Mines remaining:%d\n",game.GetMineCount());

        for (int r = 0; r < rows; r++)
        {
           
            if(r==0)
            {
                printf("   ");
                for(int c=0;c<cols;c++)
                    printf("%2d ",c);
            
            printf("\n");
            }
             printf("%2d ",r);

            for (int c = 0; c < cols; c++)
            {
               
                //printf("%2d ", game.Board[r][c]);
                 val =game.GetTileAt(r,c);
                switch(val)
                {
                    case UNKOWN:
                        display='X';
                        break;
                    case MINE:
                        display=showMines?'!':'X';
                        break;
                    case FLAG_CORRECT:
                    case FLAG_INCORRECT:
                        display='F';
                        break;
                    case CLEAR:
                        display=' ';
                        break;
                    case MINE_TRIPPED:
                        display='!';
                        break;
                    default:
                        display=val+'0';
                        break;

                }


                printf("%2c ",display);
            }
            printf("\n");
        }
        fflush(stdout);
    }
};

#endif