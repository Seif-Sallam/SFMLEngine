#include "PCH.h"
#include "../headers/Game.h"
int main()
{
    freopen("outputlog.txt", "w", stdout);
    Game game;
    game.Run();
    return 0;
}