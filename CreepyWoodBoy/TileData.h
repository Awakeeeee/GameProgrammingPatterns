#pragma once
#include "Simple2D.h"

//享元模式: 所有tile可共用的数据的封装类
class TileData
{
public:
	TileData(int cost, bool isBlock, Simple2D::Image* texture) :cost(cost), isBlock(isBlock), texture(texture)
	{}
	int getCost() const
	{
		return cost;
	}
	bool getBlockInfo() const
	{
		return isBlock;
	}
	Simple2D::Image* getTexture() const
	{
		return texture;
	}

private:
	int cost;
	bool isBlock;
	Simple2D::Image* texture;
};