#pragma once
#include "Block.h"
class WideBlock :public Block
{
public:
	WideBlock(const Vec2& pos_in, int supposed_width, const char* path1, const char* path2, int hits_in, int* number_in)
		:
		Block(pos_in, supposed_width, path1, path2, hits_in)
	{
		number = number_in;
		*number += 1;
	}
	~WideBlock()
	{
		*number -= 1;
	}

private:
	int* number;


};