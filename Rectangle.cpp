#include "Rectangle.h"
#include "Settings.h"
#include "OpenGL.h"

#include <cmath>

static float texCoord[] = {
	0, 1,
	1, 1,
	0, 0,
	1, 0
};

Texture Rectangle::texture_H;
Texture Rectangle::texture_V;

Rectangle::Rectangle(float x, float y, Block_Size sizeType)
	:
	x(x),
	y(y),
	sizeType(sizeType),
	grab(false),
	sideHit(UNKNOWN),
	color(ColorRGB(255, 255, 255))
{

	switch (sizeType)
	{
	case BS_HORIZONTAL_FULL:	
		width 	= H_FULL_WIDTH;
		height 	= H_FULL_HEIGHT;
		break;
	case BS_HORIZONTAL_HALF:	
		width 	= H_HALF_WIDTH;
		height 	= H_HALF_HEIGHT;
		break;
	case BS_VERTICAL_FULL:
		width 	= V_FULL_WIDTH;
		height 	= V_FULL_HEIGHT;
		break;
	case BS_VERTICAL_HALF:
		width 	= V_HALF_WIDTH;
		height 	= V_HALF_HEIGHT;
		break;
	}
}

void Rectangle::Draw()
{
	const float vertices[] = {
		x, y,
		x + width, y,
		x, y - height,
		x + width, y - height,
	};
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
	
	if 		(IsTypeHorizontal()) glBindTexture(GL_TEXTURE_2D, texture_H);
	else /* (IsTypeVertical())*/ glBindTexture(GL_TEXTURE_2D, texture_V);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}

void Rectangle::BoundCheck(float clipSpace) {

	if (Left() < -clipSpace) {
		SetX(-clipSpace);
	}		
	else if (Right() > clipSpace) {
		SetX(clipSpace - GetWidth());
	}	
	else if (Top() > clipSpace) {
		SetY(clipSpace);
	}
	else if (Bottom() < -clipSpace) {
		SetY(-clipSpace + GetHeight());
	}
	
}

bool Rectangle::Collide(const Rectangle& a, const Rectangle& b) {
	
	if (a.IsTypeVertical()) {
	
		if (b.InRangeX(a.Left()) || b.InRangeX(a.Right()))
			if (a.Top() >= b.Bottom() && a.Bottom() <= b.Top())
				return true;
	
	} else {
	
		if (b.InRangeY(a.Top()) || b.InRangeY(a.Bottom())) 
			if (a.Left() <= b.Right() && a.Right() >= b.Left())
				return true;
	}
	
	return false;
	
}

Side Rectangle::GetSideHit(const Rectangle& a, const Rectangle& b) {

	float var1, var2;
	
	if (a.IsTypeHorizontal()) {
		var1 = a.Left() - b.Right();
		var2 = a.Right() - b.Left();
		if (std::abs(var1) > std::abs(var2))
			return RIGHT;
		else
			return LEFT;	
	} else {
		var1 = a.Bottom() - b.Top();
		var2 = a.Top() - b.Bottom();
		if (std::abs(var1) > std::abs(var2))
			return UP;
		else
			return DOWN;
	}
	
	return UNKNOWN;
}	
