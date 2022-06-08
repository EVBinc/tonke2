using namespace sf;

class lifeBar
{
public:
    Texture lifebar;
    Sprite black,bar;

    lifeBar(int X, int Y, int H)
    {
        lifebar.loadFromFile("image/bars.png");
        black.setTexture(lifebar);
        black.setTextureRect(IntRect(0,0,50,4));
        bar.setTexture(lifebar);
        bar.setTextureRect(IntRect(0,4,H/2,4));
        bar.setColor(Color::Green);

        black.setPosition(X,Y-10);
        bar.setPosition(X,Y-10);
    }

    void update(int X, int Y, int H){
        bar.setTextureRect(IntRect(0,4,H/2,4));
        if(H>=60) bar.setColor(Color::Green);
        if(H<60) bar.setColor(Color::Yellow);
        if(H<40) bar.setColor(Color::Red);
        if(H<=0) bar.setTextureRect(IntRect(0,0,0,0));

        black.setPosition(X,Y-10);
        bar.setPosition(X,Y-10);
    }
};

class reloadBar{
    public:
    Texture rBar;
    Sprite black,bar;

    reloadBar(int X, int Y, int R)
    {
        rBar.loadFromFile("image/bars.png");
        black.setTexture(rBar);
        black.setTextureRect(IntRect(0,0,50,4));
        bar.setTexture(rBar);
        bar.setTextureRect(IntRect(0,8,50,4));
        bar.setColor(Color(150,150,150));

        black.setPosition(X,Y-12);
        bar.setPosition(X,Y-12);
    }

    void update(int X, int Y, int H, int R){
        if(H<=R)bar.setTextureRect(IntRect(0,4,float(H)/R*50,4));
        else bar.setTextureRect(IntRect(0,4,50,4));
        black.setPosition(X,Y-7);
        bar.setPosition(X,Y-7);
    }
};
