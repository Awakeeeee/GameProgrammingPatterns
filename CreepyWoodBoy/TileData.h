#pragma once
#include "Simple2D.h"

//��Ԫģʽ: ����tile�ɹ��õ����ݵķ�װ��
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