#pragma once
#include "Vec2.h"
#include "Settings.h"
#include <cstdlib>
#include "CommonMath.h"
#include "iostream"
#include <cmath>
#include "Rect.h"
#include <algorithm>
class Ball
{
public:
	Ball(const Vec2& pos_in, float scale_in, float speed, const char* path)
	{
		pos = pos_in;
		scale = scale_in;
		sp = speed;
		
		vel = Vec2(0, -1 *sp);
		sprite = createSprite(path);
		// resize the sprite
		getSpriteSize(sprite, width, height);
		width = int((float)width * scale);
		height = int((float)height * scale);
		setSpriteSize(sprite, width, height);
		topleft = pos - Vec2(float(width) / 2, float(height) / 2);
		rect = { topleft, width, height };
		FellDown = false;
	
	};
	void Update(float dt)
	{
		topleft = pos - Vec2(float(width) / 2, float(height) / 2);
		rect.set_position(topleft);
		pos += vel * dt;
		BounceEdges();

		

	}
	void RandomRot(float startAng, float endAng)
	{
		const float range = endAng - startAng;
		const float rand_val = (float)rand() / (float)RAND_MAX;
		const float angle = startAng + (range * rand_val);
	
		const Vec2 xHead = { 1.0f,0.0f };
		const Vec2 yHead = { 0.0f,1.0f };
		// rotation (clockwise)
		const Vec2 rotX = xHead * cos(angle) - yHead * sin(angle);
		const Vec2 rotY = yHead * cos(angle) + xHead * sin(angle);
		
		vel = rotX * vel.x + rotY * vel.y;

	}

	
	bool BounceObjects(Rect& rect_in)
	{
		if (rect.collide_rect(rect_in))
		{
			
			Rect* poly1 = &rect_in;
			Rect* poly2 = &rect;

			for (int shape = 0; shape < 2; shape++)
			{
				if (shape == 1)
				{
					poly1 = &rect;
					poly2 = &rect_in;
				}

				// Check diagonals of this polygon...
				for (int p = 0; p < poly1->p.size(); p++)
				{
					Vec2 line_r1s = poly1->center();
					Vec2 line_r1e = poly1->p[p];

					Vec2 displacement = { 0.0f,0.0f };

					// ...against edges of this polygon
					for (int q = 0; q < poly2->p.size(); q++)
					{
						Vec2 line_r2s = poly2->p[q];
						Vec2 line_r2e = poly2->p[(q + 1) % poly2->p.size()];

						// Standard "off the shelf" line segment intersection
						float h = (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r1e.y) - (line_r1s.x - line_r1e.x) * (line_r2e.y - line_r2s.y);
						float t1 = ((line_r2s.y - line_r2e.y) * (line_r1s.x - line_r2s.x) + (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r2s.y)) / h;
						float t2 = ((line_r1s.y - line_r1e.y) * (line_r1s.x - line_r2s.x) + (line_r1e.x - line_r1s.x) * (line_r1s.y - line_r2s.y)) / h;

						if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
						{
							displacement.x += (1.0f - t1) * (line_r1e.x - line_r1s.x);
							displacement.y += (1.0f - t1) * (line_r1e.y - line_r1s.y);
						}
					}

					pos.x -= displacement.x * (shape == 0 ? -1 : +1);
					pos.y -= displacement.y * (shape == 0 ? -1 : +1);
					
					// displacement must not be 0
					/*std::cout << displacement.x << " " << displacement.y << std::endl;
					if (abs(displacement.x) >0.0001 || abs(displacement.y) > 0.0001)
					{
						vel = -(displacement.GetNormalized()) * sp;
					}*/
					
				}
			}
			Vec2 rectifyVec = rect.center() - rect_in.center();
			vel = (rectifyVec.GetNormalized()) * sp;
			RandomRot(-PI / 50, PI / 50);
			return true;
		}
		return false;
	}

	

	void BounceEdges()
	{
		if (pos.x > SCREEN_WIDTH)
		{
			pos.x = SCREEN_WIDTH - width/2;
			vel.x *= -1;
			RandomRot(-PI / 50, PI / 50);
		}
		else if (pos.x < 0)
		{
			pos.x = width / 2;
			vel.x *= -1;
			RandomRot(-PI / 50, PI / 50);
		}
		else if (pos.y > SCREEN_HEIGHT)
		{
			/*pos.y = SCREEN_HEIGHT - height / 2;
			vel.y *= -1;
			RandomRot(-PI / 50, PI / 50);*/
			FellDown = true;
		}
		else if (pos.y < 0)
		{
			pos.y = height / 2;
			vel.y *= -1;
			RandomRot(-PI / 50, PI / 50);
		}
	}
	void Draw()
	{
		drawSprite(sprite, topleft.x, topleft.y);
	}

	~Ball()
	{
		destroySprite(sprite);
	}
	void DebugRect(const char* path)
	{
		Sprite* debug = createSprite(path);
		setSpriteSize(debug, rect.width, rect.height);
		drawSprite(debug, rect.pos.x, rect.pos.y);
		destroySprite(debug);
	}

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

	void SetVel(const Vec2& vel_in)
	{
		vel = vel_in;
	}
	float GetSpeed() const
	{
		return sp;
	}
	float GetFellDown()const
	{
		return FellDown;
	}
private:
	int width;
	int height;
	Vec2 pos;
	Vec2 topleft;
	Vec2 vel;
	Sprite* sprite;
	float sp;
	float scale;
	bool FellDown;
public:
	Rect rect;


};

