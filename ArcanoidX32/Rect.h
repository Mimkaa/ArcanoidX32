#pragma once
#include "Vec2.h"
#include <vector>
class Rect {

public:

	Rect() = default;
	Rect(const Vec2& vec_in, int v_width, int v_height)
	{
		pos = vec_in;
		width = v_width;
		height = v_height;
		CreateNormals(); 
		CreateSides();
		
	}
	Vec2 center() const
	{
		return pos + Vec2{ float(width / 2),float(height / 2)};
	}

	void set_position(Vec2 pos_in) {
		pos = pos_in;
		UpdateSides();
	}

	virtual ~Rect() = default;
	bool contains(Vec2 vec) {
		return (vec.x > pos.x && vec.y > pos.y && vec.x < pos.x + this->width && vec.y < pos.y + this->height);
	}

	bool collide_rect(const Rect& rect) {
		return(pos.x < rect.pos.x + rect.width && pos.x + this->width > rect.pos.x && pos.y < rect.pos.y + rect.height && pos.y + this->height > rect.pos.y);
	}

	void CreateNormals()
	{
		Vec2 top = Vec2(float(width),0.0f).Normalize();
		normals.push_back(Vec2(top.y, -top.x));
		Vec2 right = Vec2(0.0f,float(height)).Normalize();
		normals.push_back(Vec2(right.y, -right.x));
		Vec2 bottom = Vec2(-float(width), 0.0f).Normalize();
		normals.push_back(Vec2(bottom.y, -bottom.x));
		Vec2 left = Vec2(0.0f, -float(height)).Normalize();
		normals.push_back(Vec2(left.y, -left.x));
	}
	
	void CreateSides()
	{
		p.push_back(center() - Vec2((float)width / 2, (float)height / 2));
		p.push_back(center() - Vec2(-(float)width / 2, (float)height / 2));
		p.push_back(center() + Vec2((float)width / 2, (float)height / 2));
		p.push_back(center() + Vec2(-(float)width / 2, (float)height / 2));
	}
	void UpdateSides()
	{
		p[0] = center() - Vec2((float)width / 2, (float)height / 2);
		p[1] = center() - Vec2(-(float)width / 2, (float)height / 2);
		p[2] = center() + Vec2((float)width / 2, (float)height / 2);
		p[3] = center() + Vec2(-(float)width / 2, (float)height / 2);
	}

public:
	Vec2 pos;
	int width;
	int height;
	std::vector<Vec2> normals;
	std::vector<Vec2> p ;
};

