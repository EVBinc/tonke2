#include <SFML/Audio.hpp>

sf::SoundBuffer shotBuffer;
sf::Sound shot;

sf::SoundBuffer expBuffer;
sf::Sound explosion;

sf::SoundBuffer G_expBuffer;
sf::Sound G_explosion;

sf::SoundBuffer hitBuffer;
sf::Sound wall_hit;

sf::SoundBuffer destructionBuffer;
sf::Sound wall_destruction;

sf::SoundBuffer tntBuffer;
sf::Sound tnt;

sf::SoundBuffer artyBuffer;
sf::Sound artilleryFire[3];

sf::Music march;
sf::Music mapmus[50];

void setSound()
{
    shotBuffer.loadFromFile("sound/shot.ogg");
    shot.setBuffer(shotBuffer);

    expBuffer.loadFromFile("sound/explosion.ogg");
    explosion.setBuffer(expBuffer);

    G_expBuffer.loadFromFile("sound/gun_explosion.ogg");
    G_explosion.setBuffer(G_expBuffer);

    hitBuffer.loadFromFile("sound/wall_hit.ogg");
    wall_hit.setBuffer(hitBuffer);

    destructionBuffer.loadFromFile("sound/wall_destruction.ogg");
    wall_destruction.setBuffer(destructionBuffer);

    tntBuffer.loadFromFile("sound/tnt.ogg");
    tnt.setBuffer(tntBuffer);

    artyBuffer.loadFromFile("sound/arty.ogg");
    artilleryFire[0].setBuffer(artyBuffer);
    artilleryFire[0].setVolume(40);
    artilleryFire[1].setBuffer(artyBuffer);
    artilleryFire[1].setVolume(40);
    artilleryFire[2].setBuffer(artyBuffer);
    artilleryFire[2].setVolume(40);

    march.openFromFile("music/march_2.ogg");
    mapmus[0].openFromFile("music/black.ogg");
    mapmus[0].setVolume(30);
    mapmus[0].setLoop(true);
    mapmus[1].openFromFile("music/billie.ogg");
    mapmus[1].setVolume(30);
    mapmus[1].setLoop(true);
    mapmus[2].openFromFile("music/ghost.ogg");
    mapmus[2].setVolume(40);
    mapmus[2].setLoop(true);
    mapmus[3].openFromFile("music/panzer.ogg");
    mapmus[3].setVolume(40);
    mapmus[3].setLoop(true);
    mapmus[4].openFromFile("music/tetris.ogg");
    mapmus[4].setVolume(30);
    mapmus[4].setLoop(true);
    mapmus[5].openFromFile("music/hell.ogg");
    mapmus[5].setVolume(100);
    mapmus[5].setLoop(true);
    mapmus[6].openFromFile("music/bells.ogg");
    mapmus[6].setVolume(100);
    mapmus[6].setLoop(true);
}

int soundTimer = 0;
int soundInterval = 1;

void artStrike(){
    soundTimer+=1;
    if(soundTimer%soundInterval==0){
        artilleryFire[soundTimer/soundInterval-1].stop();
        artilleryFire[soundTimer/soundInterval-1].setPlayingOffset(sf::seconds(1.7));
        artilleryFire[soundTimer/soundInterval-1].play();
    }
    if(soundTimer==3*soundInterval) soundTimer = 0;
}
