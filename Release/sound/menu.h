#include <SFML/Graphics.hpp>
#include<string>

using namespace sf;

int levelNumber = 1;
int mapQuant = 6;
bool isEscape = false;

Font font, font1;

void menu(RenderWindow & window){
    Texture mtex1,mbackground;
    mtex1.loadFromFile("image/menu/title.png");
    mbackground.loadFromFile("image/menu/background.png");

    Sprite menuBg(mbackground);
    Sprite menuTitle(mtex1);

    bool isMenu = 1;
    bool isClicked = false;
    bool isArrow = false;
    int menuNum = -1;
    int menuState = 0;
    int lang = 0;
    menuBg.setPosition(0,0);
    menuTitle.setPosition(350,0);

    font1.loadFromFile("fonts/STENCIL.ttf");

    Text levNum("", font1, 150);
        levNum.setColor(Color::Black);
        levNum.setString("1");
        levNum.setPosition(550,450);
    Text levSelect("", font, 150);
        levSelect.setColor(Color::Black);
        levSelect.setPosition(40,150);
    Text back("", font, 100);
        back.setColor(Color::Black);
        back.setPosition(100,850);
    Text arrLeft("", font1, 150);
        arrLeft.setColor(Color::Black);
        arrLeft.setString("<");
        arrLeft.setPosition(425,450);
    Text arrRight("", font1, 150);
        arrRight.setColor(Color::Black);
        arrRight.setString(">");
        arrRight.setPosition(700,450);
    Text play("", font, 150);
        play.setColor(Color::Black);
        play.setPosition(400,250);
    Text exit("", font, 150);
        exit.setColor(Color::Black);
        exit.setPosition(400,550);
    Text settings("", font, 150);
        settings.setColor(Color::Black);
        settings.setPosition(300,400);
    Text language("", font, 100);
        language.setColor(Color::Black);
        language.setPosition(300,400);
    Text lg("", font, 100);
        lg.setColor(Color::Black);
        lg.setPosition(600,400);
    Text settings2("", font, 100);
        settings2.setColor(Color::Black);
        settings2.setPosition(390,150);
    Text play1("", font, 100);
        play1.setColor(Color::Black);
        play1.setPosition(850,850);

    font.loadFromFile("fonts/dsarmy.ttf");
    levSelect.setString("Выберите уровень");
    back.setString("Назад");
    play.setString("Играть");
    exit.setString("Выход");
    settings.setString("Настройки");
    settings2.setString("Настройки");
    language.setString("Язык: ");
    lg.setString("русский");
    play1.setString("играть");

    while(isMenu)
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }

        menuNum = -1;
        window.clear();
        window.draw(menuBg);
        window.draw(menuTitle);
        if(!Mouse::isButtonPressed(Mouse::Left)) isClicked = false;
        if(!Keyboard::isKeyPressed(Keyboard::Escape)) isEscape = false;

        if(menuState==0){
            play.setColor(Color::Black);
            settings.setColor(Color::Black);
            exit.setColor(Color::Black);

            if(IntRect(400,300,350,100).contains(Mouse::getPosition(window))){play.setColor(Color::Red); menuNum = 1; }
            if(IntRect(225,450,700,100).contains(Mouse::getPosition(window))){settings.setColor(Color::Red); menuNum = 2; }
            if(IntRect(400,600,325,100).contains(Mouse::getPosition(window))){exit.setColor(Color::Red); menuNum = 3; }

            if(Keyboard::isKeyPressed(Keyboard::Escape) && !isEscape) {window.close(); isMenu=false;}
            if(Mouse::isButtonPressed(Mouse::Left) && isClicked == false)
            {
                isClicked = true;
                if(menuNum==1) {menuState = 1;}
                if(menuNum==2) {menuState = 2;}
                if(menuNum==3) {window.close(); isMenu=false;}
            }
            window.draw(play);
            window.draw(settings);
            window.draw(exit);
        }

        if(menuState==1){
            if(!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)) isArrow = false;

            arrLeft.setColor(Color::Black);
            arrRight.setColor(Color::Black);
            back.setColor(Color::Black);
            play1.setColor(Color::Black);

            if(IntRect(400,500,90,110).contains(Mouse::getPosition(window)) && levelNumber>1){arrLeft.setColor(Color::Red); menuNum = 3; }
            if(IntRect(700,500,90,110).contains(Mouse::getPosition(window)) && levelNumber<mapQuant){arrRight.setColor(Color::Red); menuNum = 4; }
            if(IntRect(100,875,250,80).contains(Mouse::getPosition(window))){back.setColor(Color::Red); menuNum = 0; }
            if(IntRect(850,875,250,80).contains(Mouse::getPosition(window))){play1.setColor(Color::Red); menuNum = 5;}

            if(Keyboard::isKeyPressed(Keyboard::Escape)){menuState = 0; isEscape = true;}
            if(Keyboard::isKeyPressed(Keyboard::Left) && levelNumber>1 && !isArrow){levelNumber--; levNum.setString(std::to_string(levelNumber)); isArrow = true;}
            if(Keyboard::isKeyPressed(Keyboard::Right) && levelNumber<mapQuant-1 && !isArrow){levelNumber++; levNum.setString(std::to_string(levelNumber)); isArrow = true;}
            if(Keyboard::isKeyPressed(Keyboard::Space)) isMenu = false;
            if(Mouse::isButtonPressed(Mouse::Left) && !isClicked)
            {
                isClicked = true;
                if(menuNum==3) {levelNumber--; levNum.setString(std::to_string(levelNumber));}
                if(menuNum==4) {levelNumber++; levNum.setString(std::to_string(levelNumber));}
                if(menuNum==5) isMenu = false;
                if(menuNum==0){menuState=0;}
            }

            window.draw(levSelect);
            window.draw(arrLeft);
            window.draw(arrRight);
            window.draw(back);
            window.draw(levNum);
            window.draw(play1);
        }

        if(menuState==2){
            lg.setColor(Color::Black);
            language.setColor(Color::Black);
            back.setColor(Color::Black);

            if(IntRect(100,875,250,80).contains(Mouse::getPosition(window))){back.setColor(Color::Red); menuNum = 0; }
            if(IntRect(100,425,1025,80).contains(Mouse::getPosition(window))){language.setColor(Color::Red); lg.setColor(Color::Red); menuNum = 1; }

            if(Keyboard::isKeyPressed(Keyboard::Escape)){menuState = 0; isEscape = true;}
            if(Mouse::isButtonPressed(Mouse::Left) && !isClicked)
            {
                isClicked = true;
                if(menuNum==0){menuState=0;}
                if(menuNum==1){
                    if(lang==1){
                        lang = 0;
                        font.loadFromFile("fonts/dsarmy.ttf");
                        levSelect.setString("Выберите уровень");
                        back.setString("Назад");
                        play.setString("Играть");
                        exit.setString("Выход");
                        settings.setString("Настройки");
                        settings2.setString("Настройки");
                        language.setString("Язык: ");
                        lg.setString("русский");
                        play1.setString("играть");
                        language.setPosition(300,400);
                        lg.setPosition(600,400);
                        settings.setPosition(300,400);
                        settings2.setPosition(390,150);
                        levSelect.setPosition(40,150);
                    }
                    else{
                        lang = 1;
                        font.loadFromFile("fonts/STENCIL.ttf");
                        levSelect.setString("Select level");
                        back.setString("Back");
                        play.setString("Play");
                        exit.setString("Exit");
                        settings.setString("Settings");
                        settings2.setString("Settings");
                        language.setString("Language: ");
                        lg.setString("english");
                        play1.setString("Play");
                        language.setPosition(100,400);
                        lg.setPosition(700,400);
                        settings.setPosition(240,400);
                        settings2.setPosition(360,150);
                        levSelect.setPosition(100,150);
                    }
                }
            }
            window.draw(lg);
            window.draw(language);
            window.draw(settings2);
            window.draw(back);
        }

        window.display();
    }
}


void inGameMenu(RenderWindow & window){
    Texture bckg_tex;
    bckg_tex.loadFromFile("image/menu/inGameBckg.png");
    Sprite bckg(bckg_tex);
    bckg.setPosition(320,200);

    bool isMenu = true;


    while(isMenu){
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }

        if(!Keyboard::isKeyPressed(Keyboard::Escape)) isEscape = false;
        if(Keyboard::isKeyPressed(Keyboard::Escape) && !isEscape) {isMenu = false; isEscape = true;}

        window.draw(bckg);
        window.display();
    }
}
