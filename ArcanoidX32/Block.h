#pragma once
#include "Vec2.h"
#include "Settings.h"
#include "Rect.h"
class Block
{
public:
	Block(const Vec2& pos_in, int supposed_width, const char* path1, const char* path2, int hits_in)
	{
		pos = pos_in;
		pristine = createSprite(path1);
		damaged = createSprite(path2);
		getSpriteSize(pristine, width, height);
		float ratio = supposed_width / (float)width;
		width = int((float)width * ratio);
		height = int((float)height * ratio);
		setSpriteSize(pristine, width, height);
		setSpriteSize(damaged, width, height);

		rect = { pos, width, height };
		destroyed = false;
		hits = hits_in;
		hits_prime = hits;
		collided = false;
	};
	virtual void Update()
	{
		if (hits <= 0)
		{
			destroyed = true;

		}
	}
	void GetHits(const Rect& rect_in)
	{
		if (rect.collide_rect(rect_in))
		{
			hits -= 1;
		}
		if (hits <= 0)
		{
			destroyed = true;

		}
	}

	virtual void Draw()
	{
		if (hits <= hits_prime / 2) {
			drawSprite(damaged, pos.x, pos.y);
			
		}
		else
		{
			drawSprite(pristine, pos.x, pos.y);
		}
	}
	virtual ~Block()
	{
		destroySprite(pristine);
		destroySprite(damaged);
	}
	int getHeight() const
	{
		return height;
	}
	int getWidht() const
	{
		return width;
	}
	Vec2 getPos() const
	{
		return pos;
	}

	
public:
	Vec2 pos;
	int hits_prime;
	Rect rect;
	bool destroyed;
	int hits;
	bool collided;
	Sprite* pristine;
	Sprite* damaged;
	int width;
	int height;
};

