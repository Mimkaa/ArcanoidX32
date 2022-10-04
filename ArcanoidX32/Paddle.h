#pragma once
#include "Vec2.h"
#include "Settings.h"
#include "Rect.h"
//#include "Framework.h"
class Paddle
{
public:
	Paddle(const Vec2& pos_in, float scale_in, float speed, const char* path)
	{
		pos = pos_in;
		scale = scale_in;
		sp = speed;
		sprite = createSprite(path);
		// resize the sprite
		getSpriteSize(sprite, width, height);
		width = int((float)width * scale);
		height = int((float)height * scale);
		setSpriteSize(sprite, width, height);
		topleft = pos - Vec2(float(width) / 2, float(height) / 2);
		moving_left = false;
		moving_right = false;
		rect = { topleft, width, height };
	};
	
	void AdjustSize(float factor)
	{
		int newWidth = int((float)width * factor);
		int newHeight = int((float)height * factor);
		setSpriteSize(sprite, newWidth, newHeight);
		rect.width = newWidth;
		rect.height = newHeight;
		width = newWidth;
		height = newHeight;
	}

	void Update()
	{
		topleft = pos - Vec2(float(width) / 2, float(height) / 2);
		rect.set_position(topleft);
		// moving
		if (moving_left)
		{
			Move(Vec2{ -1.0f,0.0f } * sp);
		}
		if (moving_right)
		{
			Move(Vec2{ 1.0f,0.0f } *sp);
		}
		Constrain();
	}

	void Draw()
	{
		drawSprite(sprite, topleft.x, topleft.y);
	};
	void Move(const Vec2 & move_dir)
	{
		pos += move_dir * sp;

	};
	void DebugRect(const char* path)
	{
		Sprite* debug = createSprite(path);
		setSpriteSize(debug, rect.width, rect.height);
		drawSprite(debug, rect.pos.x, rect.pos.y);
		destroySprite(debug);
	}

	void Constrain()
	{
		if (pos.x - width/2 < 0)
		{
			pos.x = width / 2;
		}
		else if (pos.x + width/2 > SCREEN_WIDTH)
		{
			pos.x = SCREEN_WIDTH - width/2;
		}
	};
	~Paddle()
	{
		destroySprite(sprite);
	};
	Vec2 getPos() const
	{
		return pos;
	}
	int getHeight() const
	{
		return height;
	}
private:
	Vec2 pos;
	Vec2 topleft;
	Sprite* sprite;
	float scale;
	int width;
	int height;
	float sp;

public:
	bool moving_left;
	bool moving_right;
	Rect rect;
};

