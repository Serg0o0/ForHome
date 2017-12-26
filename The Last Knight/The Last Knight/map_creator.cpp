#include "map_creator.h"

char TileMap[HEIGHT_MAP][HEIGHT_MAP];

void randomMapGenerate() //������� ��� �������� ����� 
{ 
	int randomnumber;
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < HEIGHT_MAP; j++)
		{
			randomnumber = rand() % 100 ;
			if ((randomnumber >=0) && (randomnumber<50))
			{
				TileMap[i][j] = '0';
			}
			if ((randomnumber >=50) && (randomnumber<75))
			{
				TileMap[i][j] = '1';
			}
			if ((randomnumber >=75) && (randomnumber<98))
			{
				TileMap[i][j] = '2';
			}
			if ((randomnumber >=98) && (randomnumber<100))
			{
				TileMap[i][j] = '3';
			}
		}
}

void update_map(int n)
{
	int randomnumber;
	char AddTileMap[HEIGHT_MAP][HEIGHT_MAP];

	// ����� ������ �� 1 ������
	if (n == 1) 
	{
		for (int i = 0;i < HEIGHT_MAP;i++)
			for (int j = 1;j < HEIGHT_MAP;j++)
			{
				AddTileMap[i][j] = TileMap[i][j-1];//����������� ����� �� ������� ������ �� 1 ������
			}
		
		for(int i = 0;i < HEIGHT_MAP;i++)//���������� ����� ����� �����
		{
			randomnumber = rand() % 100 ;
			if ((randomnumber >=0) && (randomnumber<50))
			{
				AddTileMap[i][0] = '0';
			}
			if ((randomnumber >=50) && (randomnumber<75))
			{
				AddTileMap[i][0] = '1';
			}
			if ((randomnumber >=75) && (randomnumber<98))
			{
				AddTileMap[i][0] = '2';
			}
			if ((randomnumber >=98) && (randomnumber<100))
			{
				AddTileMap[i][0] = '3';
			}
		}
	}

	// ����� ����� �� 1 ������
	if (n == 2) 
	{
		for (int i = 0;i < HEIGHT_MAP;i++)
			for (int j = 0;j < (HEIGHT_MAP - 1);j++)
			{
				AddTileMap[i][j] = TileMap[i][j+1];//����������� ����� �� ������� ����� �� 1 ������
			}
		
		for(int i = 0;i < HEIGHT_MAP;i++)//���������� ������ ����� �����
		{
			randomnumber = rand() % 100 ;
			if ((randomnumber >=0) && (randomnumber<50))
			{
				AddTileMap[i][HEIGHT_MAP - 1] = '0';
			}
			if ((randomnumber >=50) && (randomnumber<75))
			{
				AddTileMap[i][HEIGHT_MAP - 1] = '1';
			}
			if ((randomnumber >=75) && (randomnumber<98))
			{
				AddTileMap[i][HEIGHT_MAP - 1] = '2';
			}
			if ((randomnumber >=98) && (randomnumber<100))
			{
				AddTileMap[i][HEIGHT_MAP - 1] = '3';
			}
		}
	}

	// ����� ����� �� 1 ������
	if (n == 3) 
	{
		for (int i = 0;i < (HEIGHT_MAP - 1);i++)
			for (int j = 0;j < HEIGHT_MAP;j++)
			{
				AddTileMap[i][j] = TileMap[i+1][j];//����������� ����� �� ������� ����� �� 1 ������
			}
		
		for(int j = 0;j < HEIGHT_MAP;j++)//���������� ������ ����� �����
		{
			randomnumber = rand() % 100 ;
			if ((randomnumber >=0) && (randomnumber<50))
			{
				AddTileMap[HEIGHT_MAP - 1][j] = '0';
			}
			if ((randomnumber >=50) && (randomnumber<75))
			{
				AddTileMap[HEIGHT_MAP - 1][j] = '1';
			}
			if ((randomnumber >=75) && (randomnumber<98))
			{
				AddTileMap[HEIGHT_MAP - 1][j] = '2';
			}
			if ((randomnumber >=98) && (randomnumber<100))
			{
				AddTileMap[HEIGHT_MAP - 1][j] = '3';
			}
		}
	}

	// ����� ���� �� 1 ������
	if (n == 4) 
	{
		for (int i = 1;i < HEIGHT_MAP;i++)
			for (int j = 0;j < HEIGHT_MAP;j++)
			{
				AddTileMap[i][j] = TileMap[i-1][j];//����������� ����� �� ������� ���� �� 1 ������
			}
		
		for(int j = 0;j < HEIGHT_MAP;j++)//���������� ������� ����� �����
		{
			randomnumber = rand() % 100 ;
			if ((randomnumber >=0) && (randomnumber<50))
			{
				AddTileMap[0][j] = '0';
			}
			if ((randomnumber >=50) && (randomnumber<75))
			{
				AddTileMap[0][j] = '1';
			}
			if ((randomnumber >=75) && (randomnumber<98))
			{
				AddTileMap[0][j] = '2';
			}
			if ((randomnumber >=98) && (randomnumber<100))
			{
				AddTileMap[0][j] = '3';
			}
		}
	}

	for (int i = 0;i < HEIGHT_MAP;i++)
			for (int j = 0;j < HEIGHT_MAP;j++)
			{
				TileMap[i][j] = AddTileMap[i][j];
			}
}