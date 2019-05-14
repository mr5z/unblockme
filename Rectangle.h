#pragma once
#include "Settings.h"
enum Block_Size
{
	BS_HORIZONTAL_FULL,
	BS_HORIZONTAL_HALF,
	BS_VERTICAL_FULL,
	BS_VERTICAL_HALF
};

enum Side
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	UNKNOWN
};

typedef unsigned int Texture;
typedef unsigned char ubyte;

struct ColorRGB {
	ColorRGB() { }
	ColorRGB(ubyte _R, ubyte _G, ubyte _B): R(_R), G(_G), B(_B) { }
	ubyte R;
	ubyte G;
	ubyte B;
};

class Rectangle
{
public:

	Rectangle() { }
	Rectangle(float x, float y, Block_Size sizeType);
			  
	void Draw();
	void BoundCheck(float clipSpace);	
	
	static bool Collide(const Rectangle& a, const Rectangle& b);
	static Side GetSideHit(const Rectangle& a, const Rectangle& b);
	
	static void ChangeType(Rectangle& r, int type)
	{
		r.sizeType = Block_Size(type);
		switch (r.sizeType)
		{
		case BS_HORIZONTAL_FULL:	
			r.width 	= H_FULL_WIDTH;
			r.height 	= H_FULL_HEIGHT;
			break;
		case BS_HORIZONTAL_HALF:	
			r.width 	= H_HALF_WIDTH;
			r.height 	= H_HALF_HEIGHT;
			break;
		case BS_VERTICAL_FULL:
			r.width 	= V_FULL_WIDTH;
			r.height 	= V_FULL_HEIGHT;
			break;
		case BS_VERTICAL_HALF:
			r.width 	= V_HALF_WIDTH;
			r.height 	= V_HALF_HEIGHT;
			break;
		}
	}
	
							  
public:
	
	inline void SetType(Block_Size sizeType) {
		this->sizeType = sizeType;
	}
	
	inline void SetX(float x) {
		this->x = x;
	}
	
	inline void SetY(float y) {
		this->y = y;
	}
	
	inline bool InRangeX(float X) const {
		return X >= Left() && X <= Right();
	}
	
	inline bool InRangeY(float Y) const {
		return Y >= Bottom() && Y <= Top();
	}
	
	inline float Hover(float X, float Y) const {
		return  InRangeX(X) && InRangeY(Y);
	}
	
	inline float GetWidth() const {
		return width;
	}
	
	inline float GetHeight() const {
		return height;
	}
	
	inline float Left() const {
		return x;
	}
	
	inline float Right() const {
		return x + width;
	}
	
	inline float Top() const {
		return y;
	}
	
	inline float Bottom() const {
		return y - height;
	}
	
	inline float CenterX() const {
		return x + width * 0.5;
	}
	
	inline float CenterY() const {
		return y - height * 0.5;
	}
	
	
	inline bool IsTypeHorizontal() const {
		return (sizeType == BS_HORIZONTAL_FULL ||
				sizeType == BS_HORIZONTAL_HALF);
	}
		
	inline bool IsTypeVertical() const {
		return (sizeType == BS_VERTICAL_FULL ||
				sizeType == BS_VERTICAL_HALF);
	}
	
	
	static Texture texture_H;
	static Texture texture_V;
	bool grab;
	Side sideHit;
	
private:

	
	float x, y;
	float width, height;
	ColorRGB color;
	Block_Size sizeType;
	
};