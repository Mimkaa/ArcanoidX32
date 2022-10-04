#pragma once
#include "Block.h"
class TansparentBlock :public Block
{
public:
	TansparentBlock(const Vec2& pos_in, int supposed_width, const char* path1, const char* path2, const char* path3, const char* path4, int hits_in)
		:
		Block(pos_in, supposed_width, path1, path2, hits_in)
		

	{
		solid = false;
		transparent = createSprite(path3);
		transparentDam = createSprite(path4);
		setSpriteSize(transparent, width, height);
		setSpriteSize(transparentDam, width, height);
		
	}
	
	void Update()
	{
		if (hits <= 0)
		{
			destroyed = true;

		}
		// change states
		if (!solid)
		{
			int now = getTickCount();
			if (now - timer > 3000)
			{
				timer = now;
				solid = true;

			}
		}
		else
		{
			int now = getTickCount();
			if (now - timer > 10000)
			{
				timer = now;
				solid = false;

			}

		}
		// move rect
		if (solid)
		{
			rect = { getPos(), getWidht(),getHeight()};
		}
		else
		{
			rect = { Vec2{ -(float)getWidht(), -(float)getHeight()},getWidht(), getHeight()};
		}
	}
	void Draw()
	{
		if (solid)
		{


			if (hits <= hits_prime / 2) {
				drawSprite(damaged, pos.x, pos.y);

			}
			else
			{
				drawSprite(pristine, pos.x, pos.y);
			}
		}
		else
		{
			if (hits <= hits_prime / 2) {
				drawSprite(transparentDam, pos.x, pos.y);

			}
			else
			{
				drawSprite(transparent, pos.x, pos.y);
			}
		}
	}
	~TansparentBlock()
	{
		// there must not be a memory leak as other sprites are deleted in the parent class
		//(first is called the destructor of the child`s class and then of the parent`s class)
		destroySprite(transparent);
		destroySprite(transparentDam);
	}
private:
	int timer = getTickCount();
	bool solid;
	Sprite* transparent;
	Sprite* transparentDam;
};
