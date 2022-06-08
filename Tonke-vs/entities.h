#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Explosion{
public:
    int x,y;
    float frame;
    Image image;
    Texture texture;
    Sprite sprite;

    Explosion(int X, int Y)
    {
        x = X; y = Y; frame = 0;
        image.loadFromFile("image/Explosion.png");
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(350,0,50,50));
    }

    void update(){
        sprite.setTextureRect(IntRect(int(frame)*50,0,50,50));
        frame+=0.1;
        sprite.setPosition(x,y);
    }

    FloatRect getRect(){
		return FloatRect(x, y, 50, 50);
	}
};

class Entity{
public:
    float x,y,w,h,dx,dy,speed,frame,damage,reloadTime;
    float health;
    bool life,shoot, isDead;
    enum stateObject {down,left,up,right};
    stateObject state;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    String name;

    Entity(Image &image, float X, float Y, int W, int H, String Name){
        x = X; y = Y; w = W; h = H; name = Name;
        speed = 0; health = 100; dx = 0; dy = 0; frame = 120;
        life = true; shoot = false; isDead = false;
        state = down;
        image.createMaskFromColor(Color::White);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(w/2, h/2);}

    FloatRect getRect(){
		return FloatRect(x, y, w, h);
	}

	void setDirection(int Angle){
        state = stateObject(int(Angle/90));
    }
    };

class Player1 :public Entity{
public:
    int gunsNumber, HE_amount;
    bool gunPlace, gunPressed, hasMine, minePlace, moveLock, hasArty, useArty, qPressed, highExplosiveShell;
    Sprite isMine;
    Sprite isArty;
    Player1(Image &image, float X, float Y, float W, float H, String Name) :Entity(image, X, Y, W, H, Name)
    {
        if(name == "Player1")  sprite.setTextureRect(IntRect(1,1,w,h));
        speed = 3;
        damage = 55;
        gunsNumber = 0;
        reloadTime = 120;
        gunPlace = false;
        minePlace = false;
        hasMine = true;
        moveLock = false;
        hasArty = false;
        useArty = false;
        qPressed = false;
        highExplosiveShell = false;
        HE_amount = 0;
        isMine.setTexture(texture);
        isMine.setTextureRect(IntRect(602,2,46,46));
        isMine.setPosition(152,2);
        isArty.setTexture(texture);
        isArty.setTextureRect(IntRect(652,2,46,46));
        isArty.setPosition(202,2);
    }

    void control(){
        if(life && !moveLock){
            if(Keyboard::isKeyPressed(Keyboard::D)) {
                state = right;
                dx = speed; dy = 0;///speed = 3;
                sprite.setRotation(-90);
            }

            if(Keyboard::isKeyPressed(Keyboard::A)) {
                state = left;
                dx = -speed; dy = 0;///speed = -3;
                sprite.setRotation(90);
            }

            if(Keyboard::isKeyPressed(Keyboard::W)){
                state = up;
                dy = -speed; dx = 0;///speed = -3;
                sprite.setRotation(180);
            }

            if(Keyboard::isKeyPressed(Keyboard::S)){
                state = down;
                dy = speed; dx = 0;///speed = 3;
                sprite.setRotation(0);
            }

            if(Keyboard::isKeyPressed(Keyboard::Space) && frame>reloadTime){
                    shoot = true; frame = 0;
                    if (highExplosiveShell) HE_amount--;
                    }
            if(Keyboard::isKeyPressed(Keyboard::F) && gunsNumber>0 && !gunPressed){gunsNumber--; gunPlace = true; gunPressed = true;}
            if(Keyboard::isKeyPressed(Keyboard::E) && hasMine){hasMine = false; minePlace = true;}
            if(Keyboard::isKeyPressed(Keyboard::Q) && hasArty && !qPressed){useArty = true;}
        }

    }

    void update()
    {
        control();
        /*switch(state){
        case right: dx = speed; dy = 0; break;
        case left: dx = speed; dy = 0; break;
        case up: dy = speed; dx = 0; break;
        case down: dy = speed; dx = 0; break;}*/

        if(Keyboard::isKeyPressed(Keyboard::Q)) qPressed = true;
        if(!Keyboard::isKeyPressed(Keyboard::Q)) qPressed = false;
        if(!Keyboard::isKeyPressed(Keyboard::F)) gunPressed = false;

        highExplosiveShell = hasHESh();
        if(highExplosiveShell) reloadTime = 240;
        else reloadTime = 120;

        x += dx;
        checkCollision(dx,0);
        y += dy;
        checkCollision(0,dy);

        if(health<=0) {
                life = false;
                sprite.setTextureRect(IntRect(301,1,48,48));
        }
        if(health>100) health = 100;
        dx = 0; dy = 0;///speed = 0;
        frame++;
        sprite.setPosition(x+w/2,y+h/2);
    }

    bool hasHESh(){
        if(HE_amount == 0) return false;
        else return true;
    }

    void checkCollision(float Dx, float Dy)
	{
        for(int i = y/50; i<(y+h)/50; i++)
        for(int j = x/50; j<(x+w)/50; j++){
            if((TileMap[i][j] == '4' && tileHealth[i][j]>-1) | TileMap[i][j] == '2' | TileMap[i][j] == 'w')
            {
                if(Dy>0){y = i*50 - h; dy = 0;}
                if(Dy<0){y = i*50 + 50; dy = 0;}
                if(Dx>0){x = j*50 - w; dx = 0;}
                if(Dx<0){x = j*50 + 50; dx = 0;}
            }
        }
	}

    float getCoordX() {return x;}
    float getCoordY() {return y;}
    };

class Player2 :public Entity{
public:
    int gunsNumber,HE_amount;
    bool gunPlace, gunPressed, hasMine, minePlace, moveLock, hasArty, useArty, qPressed, highExplosiveShell;
    Sprite isMine;
    Sprite isArty;
    Player2(Image &image, float X, float Y, float W, float H, String Name) :Entity(image, X, Y, W, H, Name)
    {
        if(name == "Player2") sprite.setTextureRect(IntRect(51,1,w,h));
        speed = 3;
        damage = 55;
        gunsNumber = 0;
        HE_amount = 0;
        reloadTime = 120;
        gunPlace = false;
        minePlace = false;
        hasMine = true;
        moveLock = false;
        hasArty = false;
        useArty = false;
        qPressed = false;
        highExplosiveShell = false;
        isMine.setTexture(texture);
        isMine.setTextureRect(IntRect(602,2,46,46));
        isMine.setPosition(1000,952);
        isArty.setTexture(texture);
        isArty.setTextureRect(IntRect(652,2,46,46));
        isArty.setPosition(950,952);
    }

    void control(){
        if(life && !moveLock){
            if(Keyboard::isKeyPressed(Keyboard::Right)) {
                state = right;
                dx = speed; dy = 0; ///speed = 3;
                sprite.setRotation(-90);
            }

            if(Keyboard::isKeyPressed(Keyboard::Left)) {
                state = left;
                dx = -speed; dy = 0; ///speed = -3;
                sprite.setRotation(90);
            }

            if(Keyboard::isKeyPressed(Keyboard::Up)){
                state = up;
                dy = -speed; dx = 0; ///speed = -3;
                sprite.setRotation(180);
            }

            if(Keyboard::isKeyPressed(Keyboard::Down)){
                state = down;
                dy = speed; dx = 0;///speed = 3;
                sprite.setRotation(0);
            }

            if((Keyboard::isKeyPressed(Keyboard::PageDown) | Keyboard::isKeyPressed(Keyboard::Numpad3)) && frame>reloadTime){
                shoot = true; frame = 0;
                if(highExplosiveShell) HE_amount--;
            }
            if(Keyboard::isKeyPressed(Keyboard::Numpad4) && gunsNumber>0 && !gunPressed){gunsNumber--; gunPlace = true; gunPressed = true;}
            if((Keyboard::isKeyPressed(Keyboard::Numpad1) | Keyboard::isKeyPressed(Keyboard::End)) && hasMine){hasMine = false; minePlace = true;}
            if(Keyboard::isKeyPressed(Keyboard::Numpad5) && hasArty && !qPressed){useArty = true;}
        }

    }

    void update()
    {
        control();
        /*switch(state){
        case right: dx = speed; dy = 0; break;
        case left: dx = speed; dy = 0; break;
        case up: dy = speed; dx = 0; break;
        case down: dy = speed; dx = 0; break;}*/

        if(Keyboard::isKeyPressed(Keyboard::Numpad5)) qPressed = true;
        if(!Keyboard::isKeyPressed(Keyboard::Numpad5)) qPressed = false;
        if(!Keyboard::isKeyPressed(Keyboard::L)) gunPressed = false;

        highExplosiveShell = hasHESh();
        if(highExplosiveShell) reloadTime = 240;
        else reloadTime = 120;

        x += dx;
        checkCollision(dx,0);
        y += dy;
        checkCollision(0,dy);

        if(health<=0) {
                life = false;
                sprite.setTextureRect(IntRect(351,1,48,48));
        }
        if(health>100) health = 100;
        dx = 0; dy = 0; ///speed = 0;
        frame++;
        sprite.setPosition(x+w/2,y+h/2);
    }

    void checkCollision(float Dx, float Dy)
	{
        for(int i = y/50; i<(y+h)/50; i++)
        for(int j = x/50; j<(x+w)/50; j++){
            if((TileMap[i][j] == '4' && tileHealth[i][j]>-1) | TileMap[i][j] == '2' | TileMap[i][j] == 'w')
            {
                if(Dy>0){y = i*50 - h; dy = 0;}
                if(Dy<0){y = i*50 + 50; dy = 0;}
                if(Dx>0){x = j*50 - w; dx = 0;}
                if(Dx<0){x = j*50 + 50; dx = 0;}
            }
        }
	}
	bool hasHESh(){
        if(HE_amount == 0) return false;
        else return true;
    }

    float getCoordX() {return x;}
    float getCoordY() {return y;}
    };

class Gun: public Entity{
public:
    bool p1,p2;
    bool enemyInRange = false;
    Gun(Image &image, float X, float Y, float W, float H, String Name, int Angle) :Entity(image, X, Y, W, H, Name)
    {
        if(name == "Gun"){
            sprite.setTextureRect(IntRect(100,0,w,h));
            sprite.setRotation(Angle);
            setDirection(sprite.getRotation());
            damage = 55;
            p1 = false;
            p2 = false;
        }
        if(name == "Plr1"){
            sprite.setTextureRect(IntRect(150,0,w,h));
            sprite.setRotation(Angle);
            setDirection(sprite.getRotation());
            damage = 55;
            p1 = true;
            p2 = false;
        }
        if(name == "Plr2"){
            sprite.setTextureRect(IntRect(200,0,w,h));
            sprite.setRotation(Angle);
            setDirection(sprite.getRotation());
            damage = 55;
            p1 = false;
            p2 = true;
        }
    }

    void update(){
        frame++;
        if(frame>120 && life && enemyInRange){shoot = true; frame = 0;}
        if(!life) sprite.setTextureRect(IntRect(400,0,50,50));
        if(health==0) {
            life = false;
            if(!isDead & enableSound){G_explosion.stop();
                G_explosion.setPlayingOffset(sf::seconds(3.5));
                G_explosion.play();
                isDead = true;}}

        enemyInRange = false;
        sprite.setPosition(x+w/2,y+h/2);
    }

    void checkEnemy(float ex, float ey, bool alive){
        if(alive){
        switch(state)
        {
            case up: if(abs(ex-x)<25 && ey<y && y-ey<300) enemyInRange = true; break;
            case down: if(abs(ex-x)<25 && ey>y && ey-y<300) enemyInRange = true; break;
            case left: if(abs(ey-y)<25 && ex<x && x-ex<300) enemyInRange = true; break;
            case right: if(abs(ey-y)<25 && ex>x && ex-x<300) enemyInRange = true; break;
        }}
    }
};

class Shell :public Entity{
public:
    float flDamage;
    bool highExplosiveShell = false;
    Shell(Image &image, float X, float Y, float W, float H, String Name, stateObject dir, int dmg, bool HE) :Entity(image, X, Y, W, H, Name)
    {
        sprite.setTextureRect(IntRect(275,15,3,22));
        sprite.setOrigin(1,11);
        speed = 10;
        state = dir;
        flDamage = dmg;
        damage = 26;
        highExplosiveShell = HE;
        if(HE) flDamage*=1.5;
    }

    void update(){
        switch(state){
        case up: sprite.setRotation(180); y-=speed; break;
        case down: sprite.setRotation(0); y+=speed; break;
        case left: sprite.setRotation(90); x-=speed; break;
        case right: sprite.setRotation(270); x+=speed; break;
        }
        checkCollision();
        sprite.setPosition(x, y);
        flDamage-=0.3;
        if(damage>25) damage=int(flDamage);
    }
    void checkCollision(){
        for(int i = y/50; i<(y+h)/50; i++)
        for(int j = x/50; j<(x+w)/50; j++){
            if(((TileMap[i][j] == '4') && (tileHealth[i][j]>0)) | TileMap[i][j] == '2')
            {
                life = false;
                if(TileMap[i][j] == '4') {
                    if(highExplosiveShell) tileHealth[i][j]=-1;
                    else tileHealth[i][j]--;
                    if(enableSound){
                        wall_hit.stop();
                        wall_hit.setPlayingOffset(sf::seconds(0.75));
                        wall_hit.play();
                    }
                }
            }}}
};
