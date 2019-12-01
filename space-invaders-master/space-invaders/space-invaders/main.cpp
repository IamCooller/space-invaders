#include "spaceInvadersGame.h"
#include "spaceInvadersScreens.h"
#pragma comment(lib, "user32.lib")
float randomCooldownTest(float min, float max)
{
    return ((max - min)*((float)rand() / RAND_MAX)) + min;
}

void main() {
    Screen* logo = new Logo();
    logo->show();
    delete logo;

    Menu* menu = new Menu();
    menu->show();
    int players = menu->getSelected() + 1;
    delete menu;
    
    SpaceInvaders* game = new SpaceInvaders(players);

    game->setupSystem();
    game->initialize();
    
    while (game->frame());

    Screen* end = new GameOver(game->getPlayer1(), game->getPlayer2());
    end->show();
    delete end;
    
    game->shutdown();
    delete game;
}
