#ifndef MINESWEEPERCONTROLLER_H
#define MINESWEEPERCONTROLLER_H

class MinesweeperController
{
  private:
    MinesweeperModel &Model;
    MinesweeperView &View;

  public:
    MinesweeperController(MinesweeperModel &m, MinesweeperView &v) : Model(m), View(v)
    {
        Model.GenerateMines();
    }

    void Run()
    {
        int row, col;
        char action;
        GameStatus play = GAME_PLAYING;
        while (play==GAME_PLAYING)
        {
            UpdateView();
            View.PromptPlayer();
            View.GetPlayerInput(row, col, action);
            play = SelectTile(row, col, action);     
        }
        if(play==GAME_WON)
        {
            View.DisplayGameWon(Model);
        }
        else
        {
            View.DisplayGameOver(Model);
        }
    }

    void UpdateView()
    {
        View.DrawBoard(Model);
    }

    GameStatus SelectTile(int row, int col, char act)
    {
        return Model.SelectTile(row,col,act);
       
    }
};

#endif