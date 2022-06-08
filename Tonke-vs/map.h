#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include<vector>
#include<fstream>
#include<iostream>

const int HEIGHT_MAP = 20;//размер карты высота
const int WIDTH_MAP = 24;//размер карты ширина
int numberOfGuns;
sf::Image map_image;
sf::Texture map;
sf::Sprite s_map;
std::vector<std::string> TileMap(HEIGHT_MAP);
std::vector<std::string> TileMapBush(HEIGHT_MAP);
std::vector<std::vector<int>> tileHealth(HEIGHT_MAP);
std::vector<std::vector<int>> gunPosition;
std::vector<std::vector<int>> clearTiles;



///3 - ground
///4 - brick wall
///2 - concrete wall
///1 - bush

void setMapTexture(){
    map_image.loadFromFile("image/Map.png");
	map_image.createMaskFromColor(sf::Color::White);
	map.loadFromImage(map_image);
	s_map.setTexture(map);
}

void setMapHealth()
{
    for (int i = 0; i < HEIGHT_MAP; i++){
        tileHealth[i].resize(WIDTH_MAP);
		for (int j = 0; j < WIDTH_MAP; j++)
		{
		    if (TileMap[i][j] == '4')  tileHealth[i][int(j)]=3;
		}
    }
}

void findClearTiles()
{
    std::vector<int> coord;
    for(int i = 1; i<HEIGHT_MAP; i++)
    for(int j = 1; j<WIDTH_MAP; j++)
        if(TileMap[i][j]=='3' && TileMapBush[i][j]=='0'){
            coord.clear();
            coord.push_back(j);
            coord.push_back(i);
            clearTiles.push_back(coord);
            ///std::cout << coord[0] << " " << coord[1] << std::endl;
        }
}

void MapClear()
{
    for(int i = 0; i<HEIGHT_MAP; i++){
        TileMap[i].clear();
        TileMapBush[i].clear();
    }
    clearTiles.clear();
}

void loadMap(int mapNumber, bool isSingle)
{
    MapClear();
    gunPosition.clear();
    std::ifstream fin;
    std::string mapNum = std::to_string(mapNumber);
    if(isSingle) fin.open("maps/single/map_" + mapNum + ".tmx");
    else fin.open("maps/multi/map_" + mapNum + ".tmx");
    if(!fin) std::cout << "Map_load: Read error";

    std::ofstream fout;
	fout.open("maps/map.txt");
	while(!fin.eof())
    {
        std::string str;
        getline(fin,str);
        while(!fin.eof() && str.length() != 0 && str[1] != ',') getline(fin,str);
        fout << str << std::endl;
    }
    ///std::cout << "Converting successful" << std::endl;
    fout.close();
    fin.close();
    fin.open("maps/map.txt");

    char ch;
    for(int i = 0; i<HEIGHT_MAP; i++)
    for(int j=0; j<WIDTH_MAP*2+1;j++)
    {
        ch = fin.get();
        if(ch==',') continue;
        TileMap[i]+=std::to_string(int(ch)-48);
        if(i==HEIGHT_MAP-1 && j==WIDTH_MAP*2-1) break;
    }

    for(int i = 0; i<HEIGHT_MAP; i++)
    for(int j=0; j<WIDTH_MAP*2+1;j++)
    {
        if(i==HEIGHT_MAP-1 && j==WIDTH_MAP*2-1) break;
        int a;
        ch = fin.get();
        if(ch==',' | ch=='0' | ch=='\n') continue;
        a = int(ch)-48;
        if(a<9){
            ch = fin.get();
            a = a + int(ch) - 48;
        }
        if(a<13) gunPosition.push_back({j*25,i*50,50,50,90*(a-9)});
    }


    for(int i = 0; i<HEIGHT_MAP; i++)
    for(int j=0; j<WIDTH_MAP*2+1;j++)
    {
        ch = fin.get();
        if(ch==','| ch=='\n') continue;
        TileMapBush[i]+=std::to_string(int(ch)-48);
    }

    numberOfGuns = gunPosition.size();
    setMapTexture();
    setMapHealth();
    findClearTiles();
    fin.close();
}

