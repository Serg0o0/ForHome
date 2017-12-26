#include <SFML/Graphics.hpp>
#include <iostream>
#include "Hero.h"
#include "globals.h"
#include "map_creator.h"
#include "grant.h"
#include <list>
#include <sstream>
#include "tower_with_archer.h"
#include "arrow.h"

using namespace sf;
using namespace std; 

extern char TileMap[HeightMap][HeightMap];

int main()
{
	Hero hero;
	Clock clock;
	Clock clock2;
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;//�������� ������� �����, ����������������.

	Font font;
	font.loadFromFile("zealot.ttf");
	Text text_hp("", font, 20);
	text_hp.setColor(Color::Green);
	Text text_score("", font, 20);
	text_score.setColor(Color::Green);

	std::list<Entity*> enemy;
	std::list<Entity*>::iterator ItEnemy;

	std::list<Arrow*> arrow;
	std::list<Arrow*>::iterator ItArrow;

	Image MapImage;
	MapImage.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(MapImage);//�������� �������� ���������
	Sprite SpriteMap;//������ ������ ��� �����
	SpriteMap.setTexture(map);//�������� �������� ��������

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(size, size, desktop.bitsPerPixel), "The Last Knight");

	RandomMapGenerate();

	while (window.isOpen())  //���� ���� �������
	{
		static float n = 0;
		int x = -50, y = -50;
		float dx1 = 0, dy1 = 0;
		float MapSpeed = 10*hero.GetSpeed();
		static float x1 = 0, y1 = 0;
		Gstate status = hero.GetState();

		float time = clock.getElapsedTime().asMicroseconds();
		float AttackTime = clock2.getElapsedTime().asMilliseconds();
		if (hero.GetLife()) gameTime = gameTimeClock.getElapsedTime().asSeconds();
			//������� ����� � �������� ��� ������, ���� ��� �����. 

		clock.restart();
		time = time / 800;
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		
		if ((int)n == 0) 
		{
			if ((hero.GetState() == attack) && (hero.GetLife()) && (AttackTime >= delay / 3))
			{
				clock2.restart();
				n += 0.01*time;
			}
			else
			{
				switch (status)// ������������ ��������� ����� � ����������� �� ��������
				{
					case north:
					{	
						dx1 = 0;
						dy1 = MapSpeed;
						break;
					}
					case west:
					{	
						dx1 = MapSpeed;
						dy1 = 0;
						break;
					}
					case east:
					{	
						dx1 = -MapSpeed;
						dy1 = 0;
						break;
					}
					case south:
					{	
						dx1 = 0;
						dy1 = -MapSpeed;
						break;
					}
					case NorthWest:
					{	
						dx1 = MapSpeed;
						dy1 = MapSpeed;
						break;
					}
					case NorthEast:
					{	
						dx1 = -MapSpeed;
						dy1 = MapSpeed;
						break;
					}
					case SouthWest:
					{	
						dx1 = MapSpeed;
						dy1 = -MapSpeed;
						break;
					}
					case SouthEast:
					{	
						dx1 = -MapSpeed;
						dy1 = -MapSpeed;
						break;
					}
					default:
					{	
						dx1 = 0;
						dy1 = 0;
						break;
					}
				}
			}
		}

		x1 += dx1;
		y1 += dy1;

		for (int i = 0; i < HeightMap; i++) // ����������� �����
		{
			for (int j = 0; j < HeightMap; j++)
			{
				if (TileMap[i][j] == '0') SpriteMap.setTextureRect(IntRect(0, 25, SizeImgMap, SizeImgMap));
				if (TileMap[i][j] == '1') SpriteMap.setTextureRect(IntRect(75, 50, SizeImgMap, SizeImgMap));
				if (TileMap[i][j] == '2') SpriteMap.setTextureRect(IntRect(175, 25, SizeImgMap, SizeImgMap));
				if (TileMap[i][j] == '3') SpriteMap.setTextureRect(IntRect(175, 225, SizeImgMap, SizeImgMap));
				if (TileMap[i][j] == 'g')//���������� ���� � ���� ���� �� �����������
				{
					TileMap[i][j] = '0';//��������� ������ � ������� �������� ���, ����� ��� ������ ����� �� ����������
					SpriteMap.setTextureRect(IntRect(0, 25, SizeImgMap, SizeImgMap));
					enemy.push_back(new Grant(x, y));
				}
				if (TileMap[i][j] == 't')//���������� ���� � ���� ���� �� �����������
				{
					TileMap[i][j] = '0';//��������� ������ � ������� ��������� �����, ����� ��� ������ ����� �� ����������
					SpriteMap.setTextureRect(IntRect(0, 25, SizeImgMap, SizeImgMap));
					enemy.push_back(new TowerArch(x, y));
				}

				SpriteMap.setPosition((int)(x + x1), (int)(y + y1));
				window.draw(SpriteMap);
				x += 25;
			}
			x = -50;
			y += 25;
		}	

		// ��������: ���������� �� ����� �� ������ �� ����� ���� ����������
		if (((int) x1) == SizeImgMap)
		{
			UpdateMap(1);
			x1 = 0;
		}
		if (((int) x1) == -SizeImgMap)
		{
			UpdateMap(2);
			x1 = 0;
		}
		if (((int) y1) == -SizeImgMap)
		{
			UpdateMap(3);
			y1 = 0;
		}
		if (((int) y1) == SizeImgMap)
		{
			UpdateMap(4);
			y1 = 0;
		}

		if (n > 0)//�������� ����� �� �����
		{
			n += 0.01*time;
			if ((int)n == 4 ) 
			{
				for (ItEnemy = enemy.begin();ItEnemy != enemy.end(); ItEnemy++) 
				{
					if (hero.RadiusDamage((*ItEnemy)->GetPosX(), (*ItEnemy)->GetPosY()) == true)
					{
						(*ItEnemy)->SetHp(hero.GetDamage());
						hero.SetScore(20);
					}
				}
			}
		}

		//������� �����
		for (ItEnemy = enemy.begin();ItEnemy != enemy.end(); ItEnemy++) 
		{
			if ((*ItEnemy)->GetType() == tow)
			{
				if (((*ItEnemy)->GetLife()) && (*ItEnemy)->ShootDelay())
				{
					arrow.push_back(new Arrow((*ItEnemy)->GetPosX(), (*ItEnemy)->GetPosY()));
				}
			}
		}
		

		//��������� ������� �����, ���� ����� ���������
		for (ItArrow = arrow.begin();ItArrow != arrow.end();ItArrow++)
		{
			(*ItArrow)->ChangePos(dx1,dy1);
		}

		//��������� ��������� ������ ������������ ������, ���� ����� ��������
		for (ItEnemy = enemy.begin();ItEnemy != enemy.end(); ItEnemy++) 
		{
			(*ItEnemy)->ChangePos(dx1,dy1);
		}

		//��������� �����
		for (ItArrow = arrow.begin();ItArrow != arrow.end();ItArrow++)
		{
			(*ItArrow)->update(time,0);
		}

		//��������� ��������� ����� � ������
		for (ItArrow = arrow.begin();ItArrow != arrow.end();ItArrow++)
		{
			if (hero.GetRect().intersects((*ItArrow)->GetRect()))
				{
					hero.SetHp((*ItArrow)->GetDamage());
					(*ItArrow)->SetLife(false);
				}
		}

		//��������� ������
		for (ItEnemy = enemy.begin();ItEnemy != enemy.end(); ItEnemy++)
		{
			if (((*ItEnemy)->GetState() == attack) && ((*ItEnemy)->GetLife()) && (*ItEnemy)->ShootDelay()) // ������ �����
			{
				(*ItEnemy)->SetN(time);
			}

			if ((*ItEnemy)->GetN() > 0)// ���� ����� ������
			{
				if (((int)((*ItEnemy)->GetN()) == 4 ) && ((*ItEnemy)->RadiusDamage(0,0))) hero.SetHp((*ItEnemy)->GetDamage());
				(*ItEnemy)->SetN(time);
			}
			(*ItEnemy)->update(time, (*ItEnemy)->GetN());
		}

		//�������� ������, ���� ��� ����� �� ������� �����, � ��� ���� ������
		for (ItEnemy = enemy.begin();ItEnemy != enemy.end();) 
		{
			if ((((*ItEnemy)->GetPosX() < -50) || ((*ItEnemy)->GetPosY() < -50) || ((*ItEnemy)->GetPosX() > 850) || ((*ItEnemy)->GetPosY() > 850)) && ((*ItEnemy)->GetLife() == false))
				{
					ItEnemy = enemy.erase(ItEnemy); 
				}
			else  ItEnemy++;
		}

		//�������� �����, ���� ��� ������ � ����� ��� ������� �� ������� �����
		for (ItArrow = arrow.begin();ItArrow != arrow.end();)
		{
			if (((*ItArrow)->GetPosX() < -50) || ((*ItArrow)->GetPosY() < -50) || ((*ItArrow)->GetPosX() > 850) || ((*ItArrow)->GetPosY() > 850) || ((*ItArrow)->GetLife() == false))
			{
				ItArrow = arrow.erase(ItArrow);
			}
			else ItArrow++;
		}

		//����� �� ����� ������
		for (ItEnemy = enemy.begin();ItEnemy != enemy.end(); ItEnemy++)
		{
			window.draw((*ItEnemy)->GetImage());
		}

		//����� �� ����� ���� 
		for (ItArrow = arrow.begin();ItArrow != arrow.end();ItArrow++)
		{
			window.draw((*ItArrow)->GetImage());
		}

		hero.SetStay();
		//��������� �����
		hero.update(time, n);
		window.draw(hero.GetImage());
		if (n > 4) n = 0;

		//����� ����� � ������ �� �����
		std::ostringstream playerHPString;
		std::ostringstream playerScoreString;
		playerHPString << hero.GetHp();
		playerScoreString << hero.GetScore();
		text_hp.setString("Health: " + playerHPString.str());
		text_hp.setPosition(600, 0);
		text_score.setString("Score: " + playerScoreString.str());
		text_score.setPosition(10, 0);
		window.draw(text_hp);
		window.draw(text_score);


		window.display(); //���������� ������ �� ������
		window.clear(); //������� �����
		
	}

	for (ItEnemy = enemy.begin(); ItEnemy != enemy.end();)
	{
		ItEnemy = enemy.erase(ItEnemy);
	}

	for (ItArrow = arrow.begin(); ItArrow != arrow.end();)
	{
		ItArrow = arrow.erase(ItArrow);
	}
	return 0;
}