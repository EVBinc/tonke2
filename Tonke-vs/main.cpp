#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include<sstream>
#include<vector>
#include<list>
#include<cmath>

#include"map.h"
#include"sound.h"
#include"menu.h"
#include"game.h"

using namespace sf;

int main()
{
    /// Importing sound
    setSound();

    /// Making window & menu init
    RenderWindow game(sf::VideoMode(1200, 1000), "Tonke 2.0"/*+mapName[n-1]*/ /*, Style::Fullscreen*/);
    game.setFramerateLimit(60);

    levelNumber = 3;

M:  if(enableMusic) march.play();
    menu(game);
    march.stop();

    if(inGame && isSingle)GameSingle(game);
    if(inGame && !isSingle)GameMulti(game);
    if(inGame)goto M;

    return 0;
}
