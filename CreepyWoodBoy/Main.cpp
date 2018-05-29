#include "Simple2D.h"
#include "TileData.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 640;
	Simple2D::Window* window = Simple2D::CreateWindow("Creepy Wood Boy", SCREEN_WIDTH, SCREEN_HEIGHT);

	//��Ԫģʽ:���������ʵ������
	Simple2D::Image* grassTexture = Simple2D::CreateImage("..\\Asset\\grass.png");
	Simple2D::Image* stoneTexture = Simple2D::CreateImage("..\\Asset\\stone.png");
	Simple2D::Image* waterTexture = Simple2D::CreateImage("..\\Asset\\water.png");
	TileData grass = TileData(1, false, grassTexture);
	TileData stone = TileData(2, false, stoneTexture);
	TileData water = TileData(3, true, waterTexture);
	TileData* map[20][10];



	while (!Simple2D::ShouldWindowClose(window))
	{
		Simple2D::RefreshWindowBuffer(window);
		//draw map
		for (int x = 0; x < 20; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				if (y >= 8)
					map[x][y] = &water;
				else
				{
					map[x][y] = &grass;
				}
				//��Ԫģʽ:�������ݻ���ʱ,���ݵ���һ��ָ��,����������ֻ��һ��,����TileData��ʵ��,����ȥ������ʵ������
				Simple2D::DrawImage(map[x][y]->getTexture(), 32 + 64 * x, 32 + 64 * y, 0.0F, 0.25);
			}
		}


	}

	//Simple2D::DestroyImage(grassTexture);
	//Simple2D::DestroyImage(waterTexture);
	//Simple2D::DestroyImage(stoneTexture);
	Simple2D::DestroyWindow(window);

	system("PAUSE");
	return 0;
}