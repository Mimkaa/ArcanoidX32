#pragma once
#include "Vec2.h"
#include "Settings.h"
#include "Rect.h"
#include <string>
class Ability
{
public:
	Ability(const Vec2& pos_in, float supposed_width, int type_in, float  speed_in)
	{
		speed = speed_in;
		pos = pos_in;
		vel = Vec2(0.0f, 1.0f) * speed_in;
		type = type_in;
		if (type == 0)
		{
			sprite = createSprite("data\\59-Breakout-Tiles.png");
		}
		else if (type==1)
		{
			sprite = createSprite("data\\60-Breakout-Tiles.png");
		}
		getSpriteSize(sprite, width, height);
		float ratio = supposed_width / (float)width;
		width = int((float)width * ratio);
		height = int((float)height * ratio);
		setSpriteSize(sprite, width, height);
	
		rect = { pos, width, height };
	}

	void Update()
	{
		pos += vel;
		rect.set_position(pos);
	}
	virtual void Draw()
	{
		drawSprite(sprite, pos.x, pos.y);
	}
	virtual ~Ability()
	{
		destroySprite(sprite);
	};
public:
	float speed;
	Rect rect;
	Vec2 pos;
	Vec2 vel;
	int type;
	Sprite* sprite;
	int width;
	int height;
};