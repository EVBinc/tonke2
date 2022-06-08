#include <SFML/Graphics.hpp>

using namespace sf;

Font font, font1;

class Txt{
    /// Подстроено под STENCIL
public:
    Text text;
    int length;

    textstr(String str, int X, int Y, int Scale, Color color = Color::Black){
        text.setString(str);
        length = str.getSize();
        text.setFont(font);
        text.setPosition(X,Y);
        text.setCharacterSize(Scale);
    }

    void setFillColor(Color color){
        text.setFillColor(color);
    }

    IntRect getRect(){
        return IntRect(text.getPosition().x, text.getPosition().y + text.getCharacterSize()*0.3, text.getCharacterSize()*length*0.6, text.getCharacterSize()*0.8);
    }

    void draw(RenderWindow &window){
        window.draw(text);
    }
};
