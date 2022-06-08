#include <random>
#include <ctime>
#include <iostream>

using namespace sf;

int crateTimer = 10*60;
int crateTrigger = 10;
int crateLife = 10*60;

class Crate{
public:
    int x,y,timer;
    enum types{repair,gun,mine,arty,HEShell};
    types type;
    bool exist;

    Texture texture;
    Sprite sprite;

    void setCrate()
    {
        srand(time(0));
        int n;
        n = rand()%clearTiles.size();
        sprite.setPosition(clearTiles[n][0]*50+2,clearTiles[n][1]*50+2);
        x = clearTiles[n][0]*50+2;
        y = clearTiles[n][1]*50+2;
        ///std::cout << n;
    }

    Crate(Image &image, bool isSingle = false)
    {
        srand(time(0));
        int T = rand()%5;
        switch(T){
            case 0: type = repair; break;
            case 1: type = gun; break;
            case 2: type = mine; break;
            case 3: type = arty; break;
            case 4: type = HEShell; break;}
        if(isSingle) type = repair;
        exist = true;
        timer = crateLife;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        switch(type){
            case repair: sprite.setTextureRect(IntRect(502,2,46,46)); break;
            case gun: sprite.setTextureRect(IntRect(552,2,46,46)); break;
            case mine: sprite.setTextureRect(IntRect(602,2,46,46)); break;
            case arty: sprite.setTextureRect(IntRect(652,2,46,46)); break;
            case HEShell: sprite.setTextureRect(IntRect(802,2,46,46)); break;
        }
        setCrate();
    }

    void update()
    {
        timer--;
        if(timer==0) exist = false;
    }

    FloatRect getRect(){
		return FloatRect(x, y, 48, 48);
	}
};

bool crateSpawn(bool isSingle = false){
    crateTimer++;
    if(crateTimer>crateTrigger*60*(1+isSingle)){
        crateTimer = 0;
        return true;
    }
    return false;
}


class Explosives{
public:
    int x,y,timer,damage;
    bool exploded, dealDamage;
    Texture texture;
    Sprite sprite;
    Text countdown;

    Explosives(Image &image, int X, int Y){
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(702,2,46,46));
        exploded = false;
        damage = 20;
        timer = 180;
        x = X; y = Y;
        sprite.setPosition(x+2,y+2);
        countdown.setFont(font);
        countdown.setCharacterSize(50);
        countdown.setString(std::to_string(int(timer/60)));
        countdown.setPosition(x+16,y-11);
        countdown.setFillColor(Color::Black);
    }

    void update(){
        timer--;
        if(timer==0) exploded = true;
        countdown.setString(std::to_string(int(timer/60)+1));
    }

    FloatRect getRect(){
		return FloatRect(x, y, 50, 50);
	}
};

class Arty{
public:
    int fire_x,fire_y,x,y,player,time,damage,firePeriod,fireTime;
    enum statusClass {aiming,firing,cancel,cease};
    bool fire, qPressed, numPressed, isMove, isLaunched;
    statusClass status;
    Texture texture;
    Sprite aim;

    Arty(Image &image, int X, int Y, int P)
    {
        status = aiming;
        fire = false;
        qPressed = true;
        numPressed = true;
        isMove = false;
        isLaunched = false;
        time = 0;
        fireTime = 500;
        firePeriod = 15;
        damage = 40;
        texture.loadFromImage(image);
        aim.setTexture(texture);
        aim.setTextureRect(IntRect(750,0,50,50));
        x = X/50*50; y = Y/50*50; player = P;
        aim.setPosition(x,y);
    }

    void control1(){
        if(Keyboard::isKeyPressed(Keyboard::W) && !isMove) {y-=50; isMove = true;}
        if(Keyboard::isKeyPressed(Keyboard::S) && !isMove) {y+=50; isMove = true;}
        if(Keyboard::isKeyPressed(Keyboard::A) && !isMove) {x-=50; isMove = true;}
        if(Keyboard::isKeyPressed(Keyboard::D) && !isMove) {x+=50; isMove = true;}
        if(Keyboard::isKeyPressed(Keyboard::Space)) {status = firing; time = 0;}
        if(Keyboard::isKeyPressed(Keyboard::Q) && !qPressed) status = cancel;
    }
    void control2(){
        if(Keyboard::isKeyPressed(Keyboard::Up) && !isMove) {y-=50; isMove = true;}
        if(Keyboard::isKeyPressed(Keyboard::Down) && !isMove) {y+=50; isMove = true;}
        if(Keyboard::isKeyPressed(Keyboard::Left) && !isMove) {x-=50; isMove = true;}
        if(Keyboard::isKeyPressed(Keyboard::Right) && !isMove) {x+=50; isMove = true;}
        if(Keyboard::isKeyPressed(Keyboard::Numpad3)) {status = firing; time = 0;}
        if(Keyboard::isKeyPressed(Keyboard::Numpad5) && !numPressed) status = cancel;
    }

    void update(){
        if(!Keyboard::isKeyPressed(Keyboard::Q)) qPressed = false;
        if(!Keyboard::isKeyPressed(Keyboard::Numpad5)) numPressed = false;
        if(status==firing){
            time++;
            if(time<=fireTime) {
                if(time%firePeriod==0){
                    fire_x = x-50*(2-rand()%5);
                    fire_y = y-50*(2-rand()%5);
                    fire = true;}
                else fire = false;
            }
            else status = cease;
        }
        if(status==aiming){
            if(isMove)time++;
            if(time>5){isMove = false; time = 0;}
            if(player == 1) control1();
            if(player == 2) control2();
            aim.setPosition(x,y);
        }
    }

};

class Mine{
public:
    int x,y,damage,armTimer;
    Texture texture;
    Sprite sprite;
    bool isArmed, exist;

    Mine(Image &image, int X, int Y){
        x = X; y = Y;
        armTimer = 90;
        damage = 60;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(850,0,50,50));
        sprite.setPosition(x,y);
        isArmed = false;
        exist = true;
        }

    void update(){
        armTimer--;
        if(armTimer<=0) isArmed = true;}

    FloatRect getRect(){
		return FloatRect(x, y, 50, 50);
	}
};
