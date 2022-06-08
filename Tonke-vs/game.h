#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"entities.h"
#include"lifebar.h"
#include"crate.h"

const float pi = 4*atan(1);

void GameMulti(RenderWindow & game)
{
    gameRunning = true;

    int plr1_score = 0;
    int plr2_score = 0;
    bool player1_won = false;
    bool player2_won = false;

    Text score1("", font,60);
    score1.setFillColor(Color::Black);
    score1.setPosition(10,-15);

    Text score2("", font,60);
    score2.setFillColor(Color::Black);
    score2.setPosition(1160,930);

    Text gunsAmount1("0", font,60);
    gunsAmount1.setFillColor(Color::Red);
    gunsAmount1.setPosition(60,-15);

    Text HEshells1("0",font,60);
    HEshells1.setFillColor(Color(250,250,0));
    HEshells1.setPosition(110,-15);

    Text HEshells2("0",font,60);
    HEshells2.setFillColor(Color(250,250,0));
    HEshells2.setPosition(1060,930);

    Text gunsAmount2("0", font,60);
    gunsAmount2.setFillColor(Color::Red);
    gunsAmount2.setPosition(1110,930);

    Text victory1("Игрок 1 выиграл!",font,150);
    victory1.setPosition(50,350);
    victory1.setFillColor(Color::Black);

    Text victory2("Игрок 2 выиграл!",font,150);
    victory2.setPosition(50,350);
    victory2.setFillColor(Color::Black);

    Text vicUnder("R - играть снова", font, 80);
    vicUnder.setPosition(300,550);
    vicUnder.setFillColor(Color::Black);


    /// Importing entities textures
    Image entities;
    entities.loadFromFile("image/Entities.png");

    if(enableMusic) mapmus[levelNumber-1].play();
B:  loadMap(levelNumber, false);
    player1_won = false;
    player2_won = false;

    Player1 plr1(entities,100,100,48,48,"Player1");
    Player2 plr2(entities,1050,850,48,48,"Player2");

    lifeBar lifebar2(plr2.x, plr2.y, plr2.health);
    reloadBar rBar2(plr2.x, plr2.y, plr2.reloadTime);
    lifeBar lifebar1(plr1.x, plr1.y, plr1.health);
    reloadBar rBar1(plr1.x, plr1.y, plr1.reloadTime);

    if(Hardcore){
        plr1.health = 1;
        plr2.health = 1;
    }


    gunsAmount1.setString(std::to_string(plr1.gunsNumber));
    gunsAmount2.setString(std::to_string(plr2.gunsNumber));

    /// Guns list
    std::vector<Gun*> guns;
    std::vector<Gun*>::iterator it;

    for(int i = 0; i<numberOfGuns; i++){
        int x = gunPosition[i][0]; int y = gunPosition[i][1];
        int a = gunPosition[i][2]; int b = gunPosition[i][3];
        int rot = gunPosition[i][4];
        guns.push_back(new Gun(entities,x,y,a,b,"Gun",rot));}

    /// Bullet list
    std::vector<Shell*> shells;
    std::vector<Shell*>::iterator i;

    std::vector<Explosion*> explosions;
    std::vector<Explosion*>::iterator e;

    /// Crate list
    std::vector<Crate*> crates;
    std::vector<Crate*>::iterator c;

    /// Mines list
    std::vector<Mine*> mines;
    std::vector<Mine*>::iterator m;

    /// Arty list
    std::vector<Arty*> artillery;
    std::vector<Arty*>::iterator art;

    while(game.isOpen() & gameRunning)
    {
        sf::Event event;
        while(game.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {game.close(); inGame = false;}
        }
        /// Menu/Reset button
        if(!Keyboard::isKeyPressed(Keyboard::Escape)) isEscape = false;
        if(Keyboard::isKeyPressed(Keyboard::Escape) && !isEscape) {isEscape = true; inGameMenu(game);}/*game.close();*/
        if(Keyboard::isKeyPressed(Keyboard::R)) goto B;

        /// Crate spawn
        if(crateSpawn()) crates.push_back(new Crate(entities));

        /// Calling arty
        if(plr1.useArty){
            plr1.moveLock = true;
            plr1.useArty = false;
            artillery.push_back(new Arty(entities,plr1.x,plr1.y,1));
        }
        if(plr2.useArty){
            plr2.moveLock = true;
            plr2.useArty = false;
            artillery.push_back(new Arty(entities,plr2.x,plr2.y,2));
        }

        /// Player mine spawn
        if(plr1.minePlace) {
            plr1.minePlace = false;
            mines.push_back(new Mine(entities,int(plr1.x+25)/50*50,int(plr1.y+25)/50*50));
        }
        if(plr2.minePlace) {
            plr2.minePlace = false;
            mines.push_back(new Mine(entities,int(plr2.x+25)/50*50,int(plr2.y+25)/50*50));
        }

        /// Player gun spawn
        if(plr1.gunPlace){
            plr1.gunPlace = false;
            gunsAmount1.setString(std::to_string(plr1.gunsNumber));
            guns.push_back(new Gun(entities,plr1.x,plr1.y,50,50,"Plr1",plr1.sprite.getRotation()));
        }
        if(plr2.gunPlace){
            plr2.gunPlace = false;
            gunsAmount2.setString(std::to_string(plr2.gunsNumber));
            guns.push_back(new Gun(entities,plr2.x,plr2.y,50,50,"Plr2",plr2.sprite.getRotation()));
        }

        /// Bullet spawn
        if (plr1.shoot){
                plr1.shoot = false;
                shells.push_back(new Shell(entities, plr1.x+25-26*sin(pi/180*plr1.sprite.getRotation()), plr1.y+25+26*cos(pi/180*plr1.sprite.getRotation()),
                                           3, 3, "Tank1_shell", plr1.state, plr1.damage, plr1.highExplosiveShell));
                if(enableSound){
                    shot.stop();
                    shot.setPlayingOffset(sf::seconds(43.5));
                    shot.play();
                }}
        if (plr2.shoot){
                plr2.shoot = false;
                shells.push_back(new Shell(entities, plr2.x+25-26*sin(pi/180*plr2.sprite.getRotation()), plr2.y+25+26*cos(pi/180*plr2.sprite.getRotation()),
                                         3, 3, "Tank1_shell", plr2.state, plr2.damage, plr2.highExplosiveShell));
                if(enableSound){
                    shot.stop();
                    shot.setPlayingOffset(sf::seconds(43.5));
                    shot.play();
                }}
        for(it = guns.begin(); it!=guns.end();){
            Gun*a = *it;
            if (a->shoot){
                a->shoot = false;
                shells.push_back(new Shell(entities, a->x+25-26*sin(pi/180*a->sprite.getRotation()), a->y+25+26*cos(pi/180*a->sprite.getRotation()),
                                           3, 3, "Gun_shell", a->state, a->damage, false));
                if(enableSound){
                    shot.stop();
                    shot.setPlayingOffset(sf::seconds(43.5));
                    shot.play();
                }}
            it++;
        }
        /// Updating "alive" and deleting "dead" bullets
        for(i = shells.begin(); i!=shells.end();){
            Shell* b = *i;
			b->update();
			if (b->getRect().intersects(plr1.getRect())){plr1.health -= b->damage; b->life=false;}
			if (b->getRect().intersects(plr2.getRect())){plr2.health -= b->damage; b->life=false;}
			for(it = guns.begin(); it!=guns.end();){
                Gun*a = *it;
                if (b->getRect().intersects(a->getRect()) && a->life){a->health = 0; b->life=false;}
                it++;
			}
			for(c = crates.begin(); c != crates.end();){
                Crate*t = *c;
                if (b->getRect().intersects(t->getRect()) ){
                        t->exist = false; b->life=false;
                        explosions.push_back(new Explosion(t->x,t->y));}
                c++;
            }
			if (b->life == false)	{ i = shells.erase(i); delete b; }
			else i++;
        }

        ///Explosion
        if(!plr2.life && !plr2.isDead){
            explosions.push_back(new Explosion(plr2.x,plr2.y));
            if(enableSound){
                explosion.stop();
                explosion.setPlayingOffset(sf::seconds(0.5));explosion.play(); plr2.isDead = true;
            }}

        if(!plr1.life && !plr1.isDead){
            explosions.push_back(new Explosion(plr1.x,plr1.y));
            if(enableSound){
                explosion.stop();
                explosion.setPlayingOffset(sf::seconds(0.5));explosion.play(); plr1.isDead = true;
            }}

        for(e = explosions.begin(); e!=explosions.end();){
            Explosion* a = *e;
            a->update();
			if(a->frame>7) {e = explosions.erase(e); delete a;}
			else e++;
        }

        ///Update
        plr1.update();
        plr2.update();

        if(!Hardcore){
            lifebar1.update(plr1.x,plr1.y,plr1.health);
            rBar1.update(plr1.x,plr1.y,plr1.frame,plr1.reloadTime);
            lifebar2.update(plr2.x,plr2.y,plr2.health);
            rBar2.update(plr2.x,plr2.y,plr2.frame,plr2.reloadTime);
        }


        /// /// Guns
        for(it = guns.begin(); it!=guns.end();){
            Gun* a = *it;
            if (a->getRect().intersects(plr1.getRect()) && !a->p1){a->health = 0;}
			if (a->getRect().intersects(plr2.getRect()) && !a->p2){a->health = 0;}
            if(!a->p1) a->checkEnemy(plr1.x,plr1.y,plr1.life);
            if(!a->p2) a->checkEnemy(plr2.x,plr2.y,plr2.life);
			a->update();
			it++;
        }
        /// /// Crates
        for(c = crates.begin(); c != crates.end();){
            Crate*t = *c;
            if (t->getRect().intersects(plr1.getRect())){
                switch(t->type){
                case 0: plr1.health+=30; break;
                case 1: plr1.gunsNumber++; gunsAmount1.setString(std::to_string(plr1.gunsNumber)); break;
                case 2: plr1.hasMine = true; break;
                case 3: plr1.hasArty = true; break;
                case 4: plr1.HE_amount += 5; break;}
                t->exist = false;
            }
            if (t->getRect().intersects(plr2.getRect())){
                switch(t->type){
                case 0: plr2.health+=30; break;
                case 1: plr2.gunsNumber++; gunsAmount2.setString(std::to_string(plr2.gunsNumber)); break;
                case 2: plr2.hasMine = true; break;
                case 3: plr2.hasArty = true;
                case 4: plr2.HE_amount += 5; break;}
                t->exist = false;
            }
            t->update();
            if (!t->exist) {c = crates.erase(c); delete t;}
            else c++;
		}
        /// /// Mines
		for(m = mines.begin(); m != mines.end();){
            Mine*t = *m;
            t->update();
            if (t->getRect().intersects(plr1.getRect()) && t->isArmed){
                    plr1.health-=t->damage;
                    explosions.push_back(new Explosion(t->x,t->y));
                    t->exist = false;}
            else if (t->getRect().intersects(plr2.getRect()) && t->isArmed){
                    plr2.health-=t->damage;
                    explosions.push_back(new Explosion(t->x,t->y));
                    t->exist = false;}
            m++;
        }
        /// /// Explosives
		/*for(ex = explosives.begin(); ex!=explosives.end();){
            Explosives* b = *ex;
            b->update();
            if(b->exploded) {
                tnt.stop();
                tnt.setPlayingOffset(sf::seconds(0.5));
                tnt.play();

                if(b->getRect().intersects(plr1.getRect())) plr1.health-=3*b->damage;
                if(b->getRect().intersects(plr2.getRect())) plr2.health-=3*b->damage;
                for(int i = -1; i<2; i++)
                for(int j = -1; j<2; j++){
                    explosions.push_back(new Explosion(b->x+i*50,b->y+j*50));
                    e = explosions.end()-1;
                    Explosion *exp = *e;
                    if(exp->getRect().intersects(plr1.getRect())) plr1.health-=b->damage;
                    if(exp->getRect().intersects(plr2.getRect())) plr2.health-=b->damage;
                    for(it = guns.begin(); it!=guns.end();){
                        Gun* a = *it;
                        if (a->getRect().intersects(exp->getRect())){a->health = 0;}
                        it++;
                    }
                    if(TileMap[int(b->y)/50+j][int(b->x)/50+i] == '4')
                        tileHealth[int(b->y)/50+j][int(b->x)/50+i] = -1;
                    if(TileMapBush[int(b->y)/50+j][int(b->x)/50+i] == '1')
                        TileMapBush[int(b->y)/50+j][int(b->x)/50+i] = '0';
                }
                ex = explosives.erase(ex);
                delete b;}
            else ex++;
        }*/
        /// /// Artillery
        for(art = artillery.begin(); art!= artillery.end();){
            Arty *a = *art;
            a->update();
            if(a->status==1 && !a->isLaunched){
                if(a->player==1){plr1.moveLock = false; plr1.frame=110; plr1.hasArty = false;}
                if(a->player==2){plr2.moveLock = false; plr2.frame=110; plr2.hasArty = false;}
                a->isLaunched = true;
            }
            if(a->status==1 && a->fire){
                if(enableSound) artStrike();
                if(a->fire_y>=0 && a->fire_y<1000){
                    explosions.push_back(new Explosion(a->fire_x,a->fire_y));
                    e = explosions.end()-1;
                    Explosion *exp = *e;
                    if(exp->getRect().intersects(plr1.getRect())) plr1.health-=a->damage;
                    if(exp->getRect().intersects(plr2.getRect())) plr2.health-=a->damage;
                    for(it = guns.begin(); it!=guns.end();){
                        Gun* a = *it;
                        if (a->getRect().intersects(exp->getRect())){a->health = 0;}
                        it++;
                    }
                    for(m = mines.begin(); m!=mines.end();){
                        Mine*k = *m;
                        if (k->getRect().intersects(exp->getRect())){k->exist = false;}
                        m++;
                    }
                    int j = a->fire_x/50;
                    int i = a->fire_y/50;
                    if(TileMap[i][j] == '4' && tileHealth[i][j] > -1)
                            tileHealth[i][j]--;
                    if(TileMapBush[i][j] == '1')
                        TileMapBush[i][j] = '0';

                    for(c = crates.begin(); c != crates.end();){
                        Crate*t = *c;
                        if(t->getRect().intersects(exp->getRect())){t->exist = false;}
                        if (!t->exist) {c = crates.erase(c); delete t;}
                        else c++;
                    }
                }
            }
            else if(a->status==2 && a->player==1) {
                plr1.moveLock = false;
                art = artillery.erase(art); delete a;}
            else if(a->status==2 && a->player==2) {
                plr2.moveLock = false;
                art = artillery.erase(art); delete a;}
            else if(a->status==3) {art = artillery.erase(art); delete a;}
            else art++;
        }

        ///Drawing
        game.clear();
        /// /// Ground and walls
        for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
		    s_map.setTextureRect(IntRect(100, 0, 50, 50));
            s_map.setPosition(j * 50, i * 50);
			game.draw(s_map);
		    if (TileMap[i][j] == '3')  s_map.setTextureRect(IntRect(100, 0, 50, 50));
		    if (TileMap[i][j] == '4')  s_map.setTextureRect(IntRect(300-50*tileHealth[i][j], 0, 50, 50));
		    if (TileMap[i][j] == '2')  s_map.setTextureRect(IntRect(50, 0, 50, 50));

			s_map.setPosition(j * 50, i * 50);
			game.draw(s_map);
		}
        /// /// Bullets
		for(i = shells.begin(); i!=shells.end();){
            Shell* b = *i;
            game.draw(b->sprite);
            i++;
        }
        /// /// Mines
        for(m = mines.begin(); m!=mines.end();){
            Mine* b = *m;
            if(!b->exist){m = mines.erase(m); delete b;}
            else{game.draw(b->sprite); m++;}
        }
        /// /// Artillery aim
        for(art = artillery.begin(); art!= artillery.end();){
            Arty *a = *art;
            if(a->status==0) game.draw(a->aim);
            art++;
        }
        /// /// Entities
		for(it = guns.begin(); it!=guns.end();){
            Gun* a = *it;
			game.draw(a->sprite);
			it++;
        }
        game.draw(plr1.sprite);
        if(plr1.life &!Hardcore){
                game.draw(lifebar1.black);
                game.draw(lifebar1.bar);
                game.draw(rBar1.black);
                game.draw(rBar1.bar);}
        if(plr1.hasMine) game.draw(plr1.isMine);
        if(plr1.hasArty) game.draw(plr1.isArty);

        game.draw(plr2.sprite);
        if(plr2.life & !Hardcore){
                game.draw(lifebar2.black);
                game.draw(lifebar2.bar);
                game.draw(rBar2.black);
                game.draw(rBar2.bar);}
        if(plr2.hasMine) game.draw(plr2.isMine);
        if(plr2.hasArty) game.draw(plr2.isArty);

        /// /// Explosions
        for(e = explosions.begin(); e!=explosions.end();){
            Explosion* a = *e;
            game.draw(a->sprite);
			e++;
        }
        /// /// Crates
		for(c = crates.begin(); c != crates.end();){
            Crate*t = *c;
            game.draw(t->sprite);
            c++;
		}
        /// /// Bushes
        for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMapBush[i][j] == '1')  {
			s_map.setTextureRect(IntRect(0, 0, 50, 50));
            s_map.setPosition(j * 50, i * 50);
			game.draw(s_map);
			}
		}
		/// /// Text
		if(!plr1.life && !player1_won){
            if(!player2_won && !player1_won) plr2_score++;
            player2_won = true;
            game.draw(victory2);
            game.draw(vicUnder);
        }

        if(!plr2.life && !player2_won){
            if(!player1_won && !player2_won) plr1_score++;
            player1_won = true;
            game.draw(victory1);
            game.draw(vicUnder);
        }

        score1.setString(std::to_string(plr1_score));
        score2.setString(std::to_string(plr2_score));
        HEshells1.setString(std::to_string(plr1.HE_amount));
        HEshells2.setString(std::to_string(plr2.HE_amount));
        game.draw(score1);
        game.draw(score2);
        game.draw(gunsAmount1);
        game.draw(gunsAmount2);
        game.draw(HEshells1);
        game.draw(HEshells2);

        /// Display
        game.display();
    }

    mapmus[levelNumber-1].stop();
}



void GameSingle(RenderWindow & game)
{
    int gunCount;
    gameRunning = true;
    Text gunsLeft("",font,60);
    gunsLeft.setPosition(650,-15);
    gunsLeft.setFillColor(Color::Black);
    Text victory("Победа!",font,200);
    victory.setPosition(300,350);
    victory.setFillColor(Color::Black);
    Text defeat("Поражение!",font,200);
    defeat.setPosition(140,350);
    defeat.setFillColor(Color::Black);
    Text defUnder("R - попробовать снова", font, 80);
    defUnder.setPosition(200,550);
    defUnder.setFillColor(Color::Black);
    Text vicUnder1("N - следующий уровень", font, 80);
    vicUnder1.setPosition(200,550);
    vicUnder1.setFillColor(Color::Black);
    Text vicUnder2("R - сыграть заново", font, 80);
    vicUnder2.setPosition(200,650);
    vicUnder2.setFillColor(Color::Black);

    /// Importing entities textures
    Image entities;
    entities.loadFromFile("image/Entities.png");

A:  if(levelNumber>1) mapmus[levelNumber-2].stop();
    if(enableMusic) mapmus[levelNumber-1].play();
B:  loadMap(levelNumber, true);
    Player1 plr1(entities,100,100,48,48,"Player1");

    lifeBar lifebar(plr1.x, plr1.y, plr1.health);
    reloadBar rBar1(plr1.x, plr1.y, plr1.reloadTime);
    if(Hardcore) plr1.health = 1;


    std::vector<Gun*> guns;
    std::vector<Gun*>::iterator it;

    for(int i = 0; i<numberOfGuns; i++){
        int x = gunPosition[i][0]; int y = gunPosition[i][1];
        int a = gunPosition[i][2]; int b = gunPosition[i][3];
        int rot = gunPosition[i][4];
        guns.push_back(new Gun(entities,x,y,a,b,"Gun",rot));}

    gunCount = guns.size();
    gunsLeft.setString("Орудий осталось: " + std::to_string(gunCount));

    /// Bullet list
    std::vector<Shell*> shells;
    std::vector<Shell*>::iterator i;

    std::vector<Explosion*> explosions;
    std::vector<Explosion*>::iterator e;

    /// Crate list
    std::vector<Crate*> crates;
    std::vector<Crate*>::iterator c;

    /// In-game
    while(game.isOpen() & gameRunning)
    {
        sf::Event event;
        while(game.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {game.close(); inGame = false;}
        }
        if(!Keyboard::isKeyPressed(Keyboard::Escape)) isEscape = false;

        /// Menu/Reset/Next level button
        if(Keyboard::isKeyPressed(Keyboard::Escape) && !isEscape) {isEscape = true; inGameMenu(game);} ///In-game menu
        if(Keyboard::isKeyPressed(Keyboard::R)) goto B; /// Reset
        if(Keyboard::isKeyPressed(Keyboard::N) && gunCount == 0 && levelNumber < mapQuant) {levelNumber++; goto A;} /// Next level

        /// Guns count string update
        gunsLeft.setString("Орудий осталось: " + std::to_string(gunCount));

        /// Bullet spawn
        if (plr1.shoot){
                plr1.shoot = false;
                shells.push_back(new Shell(entities, plr1.x+25-26*sin(pi/180*plr1.sprite.getRotation()), plr1.y+25+26*cos(pi/180*plr1.sprite.getRotation()),
                                           3, 3, "Tank1_shell", plr1.state, plr1.damage, plr1.highExplosiveShell));
                if(enableSound){
                    shot.stop();
                    shot.setPlayingOffset(sf::seconds(43.5));
                    shot.play();
                }}
        for(it = guns.begin(); it!=guns.end();){
            Gun*a = *it;
            if (a->shoot){
                a->shoot = false;
                shells.push_back(new Shell(entities, a->x+25-26*sin(pi/180*a->sprite.getRotation()), a->y+25+26*cos(pi/180*a->sprite.getRotation()), 3, 3, "Gun_shell", a->state, a->damage, false));
                if(enableSound){
                    shot.stop();
                    shot.setPlayingOffset(sf::seconds(43.5));
                    shot.play();
                }}
            it++;
        }

        /// Crate spawn
        if(crateSpawn(true) & !Hardcore) crates.push_back(new Crate(entities, true));


        /// Updating "alive" and deleting "dead" bullets
        for(i = shells.begin(); i!=shells.end();){
            Shell* b = *i;
			b->update();
			if (b->getRect().intersects(plr1.getRect())){plr1.health -= b->damage; b->life=false;}
			for(it = guns.begin(); it!=guns.end();){
                Gun*a = *it;
                if (b->getRect().intersects(a->getRect()) && a->life){a->health = 0; b->life=false;}
                it++;
			}
			for(c = crates.begin(); c != crates.end();){
                Crate*t = *c;
                if (b->getRect().intersects(t->getRect()) ){
                        t->exist = false; b->life=false;
                        explosions.push_back(new Explosion(t->x,t->y));}
                c++;
            }
			if (b->life == false)	{ i = shells.erase(i); delete b; }
			else i++;
        }

        ///Explosion
        if(plr1.life==false && plr1.isDead==false){
            if(enableSound){
                explosions.push_back(new Explosion(plr1.x,plr1.y));
                explosion.stop();
                explosion.setPlayingOffset(sf::seconds(0.5));explosion.play(); plr1.isDead = true;}
            }

        for(e = explosions.begin(); e!=explosions.end();){
            Explosion* a = *e;
            a->update();
			if(a->frame>7) {e = explosions.erase(e); delete a;}
			else e++;
        }

        ///Update
        gunCount = 0;
        plr1.update();
        if(!Hardcore){
            lifebar.update(plr1.x,plr1.y,plr1.health);
            rBar1.update(plr1.x,plr1.y,plr1.frame,plr1.reloadTime);
        }

        for(it = guns.begin(); it!=guns.end();){
            Gun* a = *it;
            if (a->getRect().intersects(plr1.getRect())){a->health = 0;}
            if (a->life==true) gunCount++;
            a->checkEnemy(plr1.x,plr1.y,plr1.life);
			a->update();
			it++;
        }

        for(c = crates.begin(); c != crates.end();){
            Crate*t = *c;
            if (t->getRect().intersects(plr1.getRect())){
                switch(t->type){
                case 0: plr1.health+=30; break;
                case 1: plr1.hasArty = true; break;}
                t->exist = false;
            }
            t->update();
            if (!t->exist) {c = crates.erase(c); delete t;}
            else c++;
		}

        ///Drawing
        game.clear();
        /// /// Ground and walls
        for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
		    s_map.setTextureRect(IntRect(100, 0, 50, 50));
            s_map.setPosition(j * 50, i * 50);
			game.draw(s_map);
		    if (TileMap[i][j] == '3')  s_map.setTextureRect(IntRect(100, 0, 50, 50));
		    if (TileMap[i][j] == '4')  s_map.setTextureRect(IntRect(300-50*tileHealth[i][j], 0, 50, 50));
		    if (TileMap[i][j] == '2')  s_map.setTextureRect(IntRect(50, 0, 50, 50));
		    if (TileMap[i][j] == 'w')  s_map.setTextureRect(IntRect(350, 0, 50, 50));
		    if (TileMap[i][j] == 'h')  s_map.setTextureRect(IntRect(400, 0, 50, 50));

			s_map.setPosition(j * 50, i * 50);
			game.draw(s_map);
		}
        /// /// Bullets
        for(auto i: shells){
            game.draw(i->sprite);
        }

        /// /// Entities
		for(auto i: guns){
			game.draw(i->sprite);
        }
        game.draw(plr1.sprite);
        if(plr1.life & !Hardcore){
                game.draw(lifebar.black);
                game.draw(lifebar.bar);
                game.draw(rBar1.black);
                game.draw(rBar1.bar);}

        /// /// Crates
		for(auto i: crates){
            game.draw(i->sprite);
		}

        /// /// Explosions
        for(e = explosions.begin(); e!=explosions.end();){
            Explosion* a = *e;
            game.draw(a->sprite);
			e++;
        }
        /// /// Bushes
        for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMapBush[i][j] == '1')  {
			s_map.setTextureRect(IntRect(0, 0, 50, 50));
            s_map.setPosition(j * 50, i * 50);
			game.draw(s_map);
			}
		}
        /// /// Text
		game.draw(gunsLeft);
		if(gunCount==0){ game.draw(victory); game.draw(vicUnder2);}
		if(gunCount==0 && levelNumber < mapQuant) game.draw(vicUnder1);
		if(plr1.life == false) {game.draw(defeat); game.draw(defUnder);}

        /// Display
        game.display();
    }

    mapmus[levelNumber-1].stop();
}
