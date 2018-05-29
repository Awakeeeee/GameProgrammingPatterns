#include <iostream>
#include "Simple2D.h"
#include <string>
#include <windows.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
Simple2D::Image* img_gh = Simple2D::CreateImage("..\\Asset\\ghost.png");
Simple2D::Image* img_de = Simple2D::CreateImage("..\\Asset\\demon.png");
Simple2D::Image* img_so = Simple2D::CreateImage("..\\Asset\\sorcerer.png");

class Monster
{
public:
	Monster() = default;
	Monster(Simple2D::Image* img, int hp) :img(img), hp(hp) {};
	~Monster() { img = NULL; }
	Simple2D::Image* getImg() { return img; }
	float getScale() { return scale; }
	int getHp() { return hp; }
	void takeDamage() { hp--; }
protected:
	Simple2D::Image* img;
	int hp;
	float scale;
};

typedef Monster* (*callback)();

class Spawner
{
public:
	Spawner() = default;
	Spawner(callback m) :c(m) {};
	Monster* spawn() { return c(); }
private:
	callback c;
};

class Ghost : public Monster
{
public:
	Ghost(Simple2D::Image* img, int hp, float scale) :Monster(img, hp) { this->scale = scale; };
};

class Demon : public Monster
{
public:
	Demon(Simple2D::Image* img, int hp, float scale) :Monster(img, hp) { this->scale = scale; };
};

class Sorcerer : public Monster
{
public:
	Sorcerer(Simple2D::Image* img, int hp, float scale) :Monster(img, hp) { this->scale = scale; };
};

//Function pointers as prototype
Monster* spawnGhost()
{
	int ranX = 20 + (rand() % 21);
	int ranY = 10 + (rand() % 11);
	return new Ghost(img_gh, 1, 0.25F);
}
Monster* spawnDemon()
{
	return new Demon(img_de, 2, 0.5F);
}
Monster* spawnSorcerer()
{
	return new Sorcerer(img_so, 3, 0.5F);
}

template<class T>
class Tile
{
public:
	int x; //in pixel
	int y;
	T* obj_on_tile;
	Tile(int x, int y) :x(x), y(y), obj_on_tile(NULL) {};
};

class Player
{
public:
	const std::string PLAYER_MODEL_PATH = "..\\Asset\\cross.png";
	Player() = default;
	Player(int start_px, int start_py, int boundary_x, int boundary_y) :px(start_px), py(start_py), bx(boundary_x), by(boundary_y)
	{
		model = Simple2D::CreateImage(PLAYER_MODEL_PATH);
	}
	void Update()
	{
		Simple2D::DrawImage(model, px, py, 0.0F, 0.5F);
	}
	void Move(int newx, int newy)
	{
		if (newx < 32)
			newx = 32;
		else if (newx > bx - 32)
			newx = bx - 32;
		if (newy < 32)
			newy = 32;
		else if (newy > by - 32)
			newy = by - 32;
		px = newx;
		py = newy;
	}
	float currentX() { return (float)px; }
	float currentY() { return (float)py; }

private:
	int px;
	int py;
	int bx;
	int by;
	Simple2D::Image* model;
};

#define CreateWindow CreateWindow
int main()
{
	Simple2D::Window* window = Simple2D::CreateWindow("Destroy the Prototypes", SCREEN_WIDTH, SCREEN_HEIGHT);

	//a map
	Tile<Monster>* map[20][10];
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			int px = 32 + x * 64;
			int py = 32 + y * 64;
			Tile<Monster>* tile = new Tile<Monster>(px, py);
			map[x][y] = tile;
		}
	}

	//a player
	Player player = Player(32, 32, SCREEN_WIDTH, SCREEN_HEIGHT);

	//一个Spawner class, 通过设置参数, 生产不同的Monster
	//这就是原型模式吗, 就这么简单吗?
	Spawner gh_sp = Spawner(spawnGhost);
	Spawner de_sp = Spawner(spawnDemon);
	Spawner so_sp = Spawner(spawnSorcerer);
	float spawn_interval = 1;
	float count = 0;
	float last_frame_time = 0;

	while (!Simple2D::ShouldWindowClose(window))
	{
		//always execute
		Simple2D::RefreshWindowBuffer(window);

		for (int x = 0; x < 20; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				Tile<Monster>* t = map[x][y];
				if(t->obj_on_tile != NULL)
					Simple2D::DrawImage(t->obj_on_tile->getImg(), t->x, t->y, 0.0F, t->obj_on_tile->getScale());
			}
		}
		player.Update();

		count += Simple2D::GetGameTime() - last_frame_time;
		last_frame_time = Simple2D::GetGameTime();

		if (Simple2D::IsKeyPressed(Simple2D::KeyCode::KEY_UP_ARROW))
			player.Move(player.currentX(), player.currentY() + 64);
		else if (Simple2D::IsKeyPressed(Simple2D::KeyCode::KEY_DOWN_ARROW))
			player.Move(player.currentX(), player.currentY() - 64);
		else if (Simple2D::IsKeyPressed(Simple2D::KeyCode::KEY_LEFT_ARROW))
			player.Move(player.currentX() - 64, player.currentY());
		else if (Simple2D::IsKeyPressed(Simple2D::KeyCode::KEY_RIGHT_ARROW))
			player.Move(player.currentX() + 64, player.currentY());

		if (Simple2D::IsKeyPressed(Simple2D::KeyCode::KEY_SPACE))
		{
			int coordx = (int)(player.currentX() / SCREEN_WIDTH * 20);
			int coordy = (int)(player.currentY() / SCREEN_HEIGHT * 10);
			Monster* target = map[coordx][coordy]->obj_on_tile;
			if (target != NULL)
			{
				target->takeDamage();
				cout << "attack monster!" << endl;
				if (target->getHp() <= 0)
				{
					map[coordx][coordy]->obj_on_tile = NULL;
					delete target;
				}
			}
			else
			{
				cout << "failed attack!" << endl;
			}
		}

		//execute by time interval
		if (count < spawn_interval)
			continue;

		count = 0;
		int ranX = (rand() % 20);
		int ranY = (rand() % 10);
		int ran_type = rand() % 3;

		if (map[ranX][ranY]->obj_on_tile != NULL)
			continue;
		switch (ran_type)
		{
		case 0:
			map[ranX][ranY]->obj_on_tile = gh_sp.spawn();
			break;
		case 1:
			map[ranX][ranY]->obj_on_tile = de_sp.spawn();
			break;
		case 2:
			map[ranX][ranY]->obj_on_tile = so_sp.spawn();
			break;
		default:
			break;
		}
	}

	return 0;
}