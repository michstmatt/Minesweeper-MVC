#include "MinesweeperModel.h"

#include "MinesweeperView.h"
#include "MinesweeperController.h"
#include <cstdlib>

int main(int argc, char** argv)
{
    MinesweeperModel game(5);
    MinesweeperView view;
    MinesweeperController controller(game, view);
    
    controller.Run();
    

    return 0;
}