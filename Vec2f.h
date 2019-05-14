#pragma once

#include "OpenGL.h"

#ifndef _VEC2F_
#define _VEC2F_

struct Vec2f {
	Vec2f() : x(0), y(0) { }
	Vec2f(float _x, float _y) : x(_x), y(_y) { }
	bool operator == (const Vec2f& v) {
		return x == v.x && y == v.y;
	}
	float x, y;
};

static Vec2f GetOGL_Pos(int x, int y) {
	
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
 
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	
	return Vec2f((float)posX, (float)posY);
}

#endif