#include <SFML/Graphics.hpp>
#include<string>

#include"sfml_text.h"

using namespace sf;

int levelNumber = 1;
int mapQuant = 7;
bool isEscape = false;
bool isMenu = 1;
bool isClicked = false;
bool gameRunning = false;
bool inGame = true;
bool isLoaded = false;
bool isSingle;
int lang = 0;

bool enableMusic = true;
bool enableSound = true;
bool Hardcore = false;

Text levNum("", font, 100);
Text levSelect("", font, 150);
Text back("", font, 100);
Text arrLeft("<", font1, 150);
Text arrRight(">", font1, 150);
///Text play("", font, 150);

Txt play("Играть", 400, 250, 150);
Text exitstr("", font, 150);
Text help("", font, 150);
Text settings("",font,150);

Text language("", font, 100);
Text lg("", font, 100);
Text help2("", font, 100);
Text play1("", font, 100);
Text single("",font, 150);
Text multi("",font,150);
Text hardcore_str("",font,100);
Text h_yes("",font,100);
Text h_no("",font,100);

Text plr1("", font, 70);
Text plr1_Control_1("", font, 70);
Text plr1_Control_2("", font, 70);
Text plr1_Control_3("", font, 70);
Text plr1_Control_4("", font, 70);
Text plr2("", font, 70);
Text plr2_Control_1("", font, 70);
Text plr2_Control_2("", font, 70);
Text plr2_Control_3("", font, 70);
Text plr2_Control_4("", font, 70);

Text continu("", font, 100);
Text exit_to_menu("",font, 100);

Txt musSetting("Музыка: Да", 200,200, 100);
Txt soundSetting("Звук: Да", 200, 300, 100);
Txt newBack("Назад", 100, 850, 100);


std::vector<std::string>mapName =
{
    "Руины", "Штаб", "Кустовый ад", "Прорыв", "Коробейники", "Tonke", "Развалины"
};

void loadMenuResources(int lang)
{
    font1.loadFromFile("fonts/STENCIL.ttf");

    levNum.setPosition(270,475);
    levSelect.setPosition(40,150);
    back.setPosition(100,850);
    arrLeft.setPosition(100,450); ///425
    arrRight.setPosition(1025,450);  ///700
    hardcore_str.setPosition(100,650);
    h_yes.setPosition(500,650);
    h_no.setPosition(500,650);

    exitstr.setPosition(400,700);///550
    settings.setPosition(280,550);
    help.setPosition(300,400);
    language.setPosition(300,400);
    lg.setPosition(600,400);
    help2.setPosition(390,150);
    play1.setPosition(850,850);

    continu.setPosition(350,350);
    exit_to_menu.setPosition(425,500);

    single.setPosition(270,300);
    multi.setPosition(150,500);

    plr1.setPosition(70,140);
    plr1_Control_1.setPosition(70,200);
    plr1_Control_2.setPosition(70,260);
    plr1_Control_3.setPosition(70,320);
    plr1_Control_4.setPosition(70,380);

    plr2.setPosition(70,480);
    plr2_Control_1.setPosition(70,540);
    plr2_Control_2.setPosition(70,600);
    plr2_Control_3.setPosition(70,660);
    plr2_Control_4.setPosition(70,720);



    font.loadFromFile("fonts/dsarmy.ttf");
    levNum.setString(std::to_string(levelNumber) + " " + mapName[levelNumber-1]);
    levNum.setFillColor(Color::Black);
    levSelect.setString("Выберите уровень");
    levSelect.setFillColor(Color::Black);
    back.setString("Назад");

    exitstr.setString("Выход");
    settings.setString("Настройки");
    help.setString("Помошь");
    help2.setString("Помощь");

    language.setString("Язык: ");
    lg.setString("русский");

    play1.setString("играть");
    continu.setString("продолжить");
    exit_to_menu.setString("в меню");

    single.setString("Одиночная");
    multi.setString("Один на один");
    hardcore_str.setString("Хардкор: ");
    h_yes.setString("Да");
    h_no.setString("Нет");

    plr1.setString("Игрок 1 / Одиночная");
    plr1_Control_1.setString("Движение - WASD, Огонь - Пробел");
    plr1_Control_2.setString("Установить пушку - F");
    plr1_Control_3.setString("Заложить мину - E");
    plr1_Control_4.setString("Вызвать артиллерию - Q");

    plr2.setString("Игрок 2");
    plr2_Control_1.setString("Движение - стрелки, Огонь - Num3");
    plr2_Control_2.setString("Установить пушку - Num4");
    plr2_Control_3.setString("Заложить мину - Num1");
    plr2_Control_4.setString("Вызвать артиллерию - Num5");

    language.setPosition(300,400);
    lg.setPosition(600,400);
    help.setPosition(350,400);
    help2.setPosition(440,150);
    levSelect.setPosition(40,150);
    exit_to_menu.setPosition(425,500);
}

void menu(RenderWindow & window){
    Texture mtex1,mbackground;
    mtex1.loadFromFile("image/menu/title.png");
    mbackground.loadFromFile("image/menu/background.png");

    Sprite menuBg(mbackground);
    Sprite menuTitle(mtex1);

    bool isArrow = false;
    bool levelChanged = false;
    isMenu = true;
    int menuNum = -1;
    int menuState = 0;
    levelNumber = 1;
    levNum.setString(std::to_string(levelNumber) + " " + mapName[levelNumber-1]);

    menuBg.setPosition(0,0);
    menuTitle.setPosition(350,0);

    if(!isLoaded) {loadMenuResources(lang); isLoaded = true;}

    while(isMenu && window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {window.close(); inGame = false;}
        }

        menuNum = -1;
        window.clear();
        window.draw(menuBg);
        window.draw(menuTitle);
        if(!Mouse::isButtonPressed(Mouse::Left)) isClicked = false;
        if(!Keyboard::isKeyPressed(Keyboard::Escape)) isEscape = false;

        if(menuState==0){ /// Menu
            play.setFillColor(Color::Black);
            help.setFillColor(Color::Black);
            exitstr.setFillColor(Color::Black);
            settings.setFillColor(Color::Black);

            if(play.getRect().contains(Mouse::getPosition(window))){play.setFillColor(Color::Red); menuNum = 1; }
            if(IntRect(225,450,700,100).contains(Mouse::getPosition(window))){help.setFillColor(Color::Red); menuNum = 2; }
            if(IntRect(280,600,650,100).contains(Mouse::getPosition(window))){settings.setFillColor(Color::Red); menuNum = 3; }
            if(IntRect(400,750,325,100).contains(Mouse::getPosition(window))){exitstr.setFillColor(Color::Red); menuNum = 4; }

            if(Keyboard::isKeyPressed(Keyboard::Escape) && !isEscape) {window.close(); isMenu=false; inGame = false;}
            if(Mouse::isButtonPressed(Mouse::Left) && isClicked == false)
            {
                isClicked = true;
                if(menuNum==1) {menuState = 1;}
                if(menuNum==2) {menuState = 3;}
                if(menuNum == 3) {menuState = 4;}
                if(menuNum==4) {window.close(); isMenu=false; inGame=false;}
            }
            play.draw(window);
            window.draw(help);
            window.draw(exitstr);
            window.draw(settings);
        }

        if(menuState==1){ /// Mode selection
            single.setFillColor(Color::Black);
            multi.setFillColor(Color::Black);
            back.setFillColor(Color::Black);

            if(Keyboard::isKeyPressed(Keyboard::Escape) && !isEscape){menuState = 0; isEscape = true;}
            if(IntRect(270,350,650,100).contains(Mouse::getPosition(window))){single.setFillColor(Color::Red); menuNum = 1; }
            if(IntRect(150,550,900,100).contains(Mouse::getPosition(window))){multi.setFillColor(Color::Red); menuNum = 2; }
            if(IntRect(100,875,250,80).contains(Mouse::getPosition(window))){back.setFillColor(Color::Red); menuNum = 0; }

            if(Mouse::isButtonPressed(Mouse::Left) && !isClicked){
                isClicked = true;
                if(menuNum==1) {menuState = 2; isSingle = true;}
                if(menuNum==2) {menuState = 2; isSingle = false;}
                if(menuNum==0) {menuState = 0;}
            }

            window.draw(single);
            window.draw(multi);
            window.draw(back);
        }

        if(menuState==2){ /// Level selection
            levelChanged = false;
            if(!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)) isArrow = false;

            arrLeft.setFillColor(Color::Black);
            arrRight.setFillColor(Color::Black);
            back.setFillColor(Color::Black);
            play1.setFillColor(Color::Black);
            hardcore_str.setFillColor(Color::Black);
            h_yes.setFillColor(Color::Black);
            h_no.setFillColor(Color::Black);

            if(IntRect(75,500,90,110).contains(Mouse::getPosition(window)) && levelNumber>1){arrLeft.setFillColor(Color::Red); menuNum = 3; }
            if(IntRect(1000,500,90,110).contains(Mouse::getPosition(window)) && levelNumber<mapQuant){arrRight.setFillColor(Color::Red); menuNum = 4; }
            if(IntRect(100,875,250,80).contains(Mouse::getPosition(window))){back.setFillColor(Color::Red); menuNum = 0; }
            if(IntRect(850,875,250,80).contains(Mouse::getPosition(window))){play1.setFillColor(Color::Red); menuNum = 5;}
            if(IntRect(100,675,550,80).contains(Mouse::getPosition(window))){
                    hardcore_str.setFillColor(Color::Red);
                    h_yes.setFillColor(Color::Red);
                    h_no.setFillColor(Color::Red);
                    menuNum = 6;}

            if(Keyboard::isKeyPressed(Keyboard::Escape)){menuState = 1; isEscape = true;}
            if(Keyboard::isKeyPressed(Keyboard::Left) && levelNumber>1 && !isArrow){levelNumber--; levelChanged = true; isArrow = true;}
            if(Keyboard::isKeyPressed(Keyboard::Right) && levelNumber<mapQuant && !isArrow){levelNumber++; levelChanged = true; isArrow = true;}
            if(Keyboard::isKeyPressed(Keyboard::Space)) isMenu = false;
            if(Mouse::isButtonPressed(Mouse::Left) && !isClicked)
            {
                isClicked = true;
                if(menuNum==3) {levelNumber--; levelChanged = true;}
                if(menuNum==4) {levelNumber++; levelChanged = true;}
                if(menuNum==5) isMenu = false;
                if(menuNum==0){menuState=1;}
                if(menuNum==6){Hardcore = !Hardcore;}
            }

            if(levelChanged) levNum.setString(std::to_string(levelNumber) + " " + mapName[levelNumber-1]);
            window.draw(levSelect);
            window.draw(arrLeft);
            window.draw(arrRight);
            window.draw(back);
            window.draw(levNum);
            window.draw(play1);
            window.draw(hardcore_str);
            if(Hardcore) window.draw(h_yes);
            else window.draw(h_no);
        }

        if(menuState == 3){ /// Help
            RectangleShape rect(Vector2f(1100, 750));
            rect.setPosition(50,130);
            rect.setFillColor(Color(140,140,140));

            back.setFillColor(Color::Black);
            plr1_Control_1.setFillColor(Color::Black);
            plr1_Control_2.setFillColor(Color::Black);
            plr1_Control_3.setFillColor(Color::Black);
            plr1_Control_4.setFillColor(Color::Black);
            plr1.setFillColor(Color::Black);
            plr2_Control_1.setFillColor(Color::Black);
            plr2_Control_2.setFillColor(Color::Black);
            plr2_Control_3.setFillColor(Color::Black);
            plr2_Control_4.setFillColor(Color::Black);
            plr2.setFillColor(Color::Black);

            if(IntRect(100,875,250,80).contains(Mouse::getPosition(window))){back.setFillColor(Color::Red); menuNum = 0; }

            if(Keyboard::isKeyPressed(Keyboard::Escape)){menuState = 0; isEscape = true;}
            if(Mouse::isButtonPressed(Mouse::Left) && !isClicked)
            {
                isClicked = true;
                if(menuNum==0){menuState=0;}
            }

            window.draw(rect);
            window.draw(back);
            window.draw(plr1);
            window.draw(plr1_Control_1);
            window.draw(plr1_Control_2);
            window.draw(plr1_Control_3);
            window.draw(plr1_Control_4);
            window.draw(plr2);
            window.draw(plr2_Control_1);
            window.draw(plr2_Control_2);
            window.draw(plr2_Control_3);
            window.draw(plr2_Control_4);
        }

        if(menuState == 4){ /// Settings
            musSetting.setFillColor(Color::Black);
            soundSetting.setFillColor(Color::Black);
            newBack.setFillColor(Color::Black);

            if(newBack.getRect().contains(Mouse::getPosition(window))) {newBack.setFillColor(Color::Red); menuNum = 0;}
            if(musSetting.getRect().contains(Mouse::getPosition(window))) {musSetting.setFillColor(Color::Red); menuNum = 1;}
            if(soundSetting.getRect().contains(Mouse::getPosition(window))) {soundSetting.setFillColor(Color::Red); menuNum = 2;}

            if(Mouse::isButtonPressed(Mouse::Left) & !isClicked){
                isClicked = true;
                if(menuNum == 0){menuState = 0;}
                if(menuNum == 1){
                    enableMusic = !enableMusic;
                    if(enableMusic == false) {musSetting.setString("Музыка: Нет"); march.stop();}
                    else {musSetting.setString("Музыка: Да"); march.play();}
                }
                if(menuNum == 2){
                    enableSound = !enableSound;
                    if(!enableSound) {soundSetting.setString("Звук: Нет");}
                    else soundSetting.setString("Звук: Да");
                }
            }

            newBack.draw(window);
            musSetting.draw(window);
            soundSetting.draw(window);
        }

        window.display();
    }
}


void inGameMenu(RenderWindow & window){
    Texture bckg_tex;
    bckg_tex.loadFromFile("image/menu/inGameBckg.png");
    Sprite bckg(bckg_tex);
    bckg.setPosition(320,200);

    isMenu = true;

    while(isMenu && window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {window.close(); inGame = false;}
        }
        continu.setFillColor(Color::Black);
        exit_to_menu.setFillColor(Color::Black);

        int menuNum;

        if(!Keyboard::isKeyPressed(Keyboard::Escape)) isEscape = false;
        if(!Mouse::isButtonPressed(Mouse::Left)) isClicked = false;
        if(Keyboard::isKeyPressed(Keyboard::Escape) && !isEscape) {isMenu = false; isEscape = true;}

        if(IntRect(350,375,510,75).contains(Mouse::getPosition(window))){continu.setFillColor(Color::Red); menuNum = 1; }
        if(IntRect(425,525,325,75).contains(Mouse::getPosition(window))){exit_to_menu.setFillColor(Color::Red); menuNum = 2; }

        if(Mouse::isButtonPressed(Mouse::Left) && isClicked == false)
        {
            isClicked = true;
            if(menuNum==1) {isMenu = false; isClicked = true;}
            if(menuNum==2) {gameRunning = false; isMenu = false;}
        }

        window.draw(bckg);
        window.draw(continu);
        window.draw(exit_to_menu);
        window.display();
    }
}

