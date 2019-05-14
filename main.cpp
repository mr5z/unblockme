#define GLFW_DLL

#include <cstdlib>
#include <iostream>
#include <ctime>

#include <vector>
#include <stdio.h>
#include <GL/glfw.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

#include "Rectangle.h"
#include "Vec2f.h"
#include "SOIL.h"

static struct Mouse {
	bool leftClick;
	int state;
	Vec2f pos;
	static Vec2f posClick;

} mouse;

Vec2f Mouse::posClick;

const int NUMBER_OF_BLOCKS = 25;
const float DISTANCE = 0.01f;
float diff = 0;
int selectedBlock = 0;

int blockCollided = -1;

static int windowWidth = 600;
static int windowHeight = 600;

std::vector< Rectangle > blocks;

float positionX = -1 + DISTANCE;

float randFloat(float min, float max) {
	return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

void Read()
{
	std::ifstream file;
	std::string mystr;
	std::stringstream sstr;
	file.open("C:\\Users\\Mark\\Desktop\\test.txt", std::ios::in | std::ios::binary);
	float number;
	while(file >> mystr)
	{
	std::stringstream(mystr) >> number;
	std::cout << "mystr is " << mystr << ", number is " << number << std::endl;
	}
}

void Write()
{
	std::ofstream fout("filename.txt");
	fout << "Hello";
	fout << 5;
	fout << std::endl;
	fout << "end";
	fout.close();
}

void Initialize()
{

	Rectangle::texture_V = SOIL_load_OGL_texture
	(
		"C:\\unblockmeclone\\Files\\Images\\v_block.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_DDS_LOAD_DIRECT |
		SOIL_FLAG_INVERT_Y |
		SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	printf("error code: %s\n", SOIL_last_result());
	
	Rectangle::texture_H = SOIL_load_OGL_texture
	(
		"C:\\unblockmeclone\\Files\\Images\\h_block.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_DDS_LOAD_DIRECT |
		SOIL_FLAG_INVERT_Y
		//SOIL_FLAG_COMPRESS_TO_DXT
	);
	
	printf("error code: %s\n", SOIL_last_result());

	srand((unsigned int)time(NULL));
	
}

void GLFWCALL Render(void*)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	for (int i = 0;i < blocks.size(); ++i) {
		if (i == 0) glColor3ub(200, 0, 0); else glColor3ub(255, 255, 255);
		blocks[i].Draw();	
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void GLFWCALL PollEvents(void*)
{
	static int currObj = -1;
	int index;
	if (currObj != -1) index = currObj;
	else index = 0;

	for (int i = index;i < blocks.size(); ++i)
	{
	
		Rectangle& a = blocks[i];
	
		if (mouse.state == GLFW_PRESS)
		{
			
			//look for any block to grab
			if (mouse.leftClick && !blocks[selectedBlock].grab &&
				a.Hover(mouse.pos.x, mouse.pos.y))
			{
				//prevent grabbing another block
				if (i != selectedBlock) {
					selectedBlock = i;
				}
				
				a.grab = true;
			
				if (a.IsTypeHorizontal()) {
					diff = mouse.pos.x - a.Left();
				} else {
					diff = mouse.pos.y - a.Top();
				}
			}
			
			float mposX = std::abs(Mouse::posClick.x - mouse.pos.x);
			float mposY = std::abs(Mouse::posClick.y - mouse.pos.y);

			if ((std::abs(mposX) > 0.5f || std::abs(mposY) > 0.5f) &&
				(Mouse::posClick.x != 0 && Mouse::posClick.y != 0)) {
				return;
			}
			
			if (a.grab)
			{	
				if (glfwGetKey(GLFW_KEY_F4))
				{
					static int type = 0;
					type = (type + 1) % 4;
					Rectangle::ChangeType(a, type);
				}
				currObj = i;
				
				Side mouseDir(UNKNOWN);
					
				if (a.IsTypeVertical()) {
					if (mouse.pos.y > Mouse::posClick.y) {
						mouseDir = UP;
					} else if (mouse.pos.y < Mouse::posClick.y) {
						mouseDir = DOWN;
					}
				} else {
					if (mouse.pos.x < Mouse::posClick.x) {
						mouseDir = LEFT;
					} else if (mouse.pos.x > Mouse::posClick.x) {
						mouseDir = RIGHT;
					}
				}
				
				if (a.sideHit == UP && mouseDir == DOWN)
					a.sideHit = UNKNOWN;
				else if (a.sideHit == DOWN && mouseDir == UP)
					a.sideHit = UNKNOWN;
				else if (a.sideHit == LEFT && mouseDir == RIGHT)
					a.sideHit = UNKNOWN;
				else if (a.sideHit == RIGHT && mouseDir == LEFT)
					a.sideHit = UNKNOWN;

				if 		(a.sideHit == UP && mouseDir == UP) return;
				else if (a.sideHit == DOWN && mouseDir == DOWN) return;
				else if (a.sideHit == LEFT && mouseDir == LEFT) return;
				else if (a.sideHit == RIGHT && mouseDir == RIGHT) return;
				
				if (a.IsTypeHorizontal()) {
					a.SetX(mouse.pos.x - diff);
				} else {
					a.SetY(mouse.pos.y - diff);
				}
				
				for (int j = 0;j < blocks.size(); ++j)
				{
					//skip for any self-checking
					if (i == j) continue;
					
					Rectangle& b = blocks[j];
						
					if (Rectangle::Collide(a, b)) {

						a.sideHit = Rectangle::GetSideHit(a, b);
						
						switch(a.sideHit)
						{
						case UP: 	a.SetY(b.Bottom() - DISTANCE);				printf("UP\n");
						break;
						case DOWN: 	a.SetY(b.Top() + a.GetHeight() + DISTANCE);	printf("DOWN\n");
						break;
						case LEFT: 	a.SetX(b.Right() + DISTANCE);				printf("LEFT\n");
						break;
						case RIGHT: a.SetX(b.Left() - a.GetWidth() - DISTANCE);	printf("RIGHT\n");
						break;
						}
						
					}
					
				}
		
			}
			
		} else {
			currObj = -1;
			a.grab = false;
			a.sideHit = UNKNOWN;
		}
		
		//check for bound collision
		a.BoundCheck(1.f - DISTANCE);
		
		//get the mouse position on click
		Mouse::posClick = mouse.pos;
		
	}
}	

void GLFWCALL Resize(int w, int h)
{
	glViewport(0, 0, windowWidth = w, windowHeight = h);
	gluOrtho2D(0, windowWidth, windowHeight, 0);
}

void GLFWCALL Keyboard(int key, int state)
{
	if (state == GLFW_RELEASE) return;
	static int $ = 1;
	float y = 1 - DISTANCE;
	int type = std::rand() % 4;
	
	switch (key)
	{
	case 32:
		system("cls");
		break;
	case GLFW_KEY_F1:
		if (blocks.size() == 0) {
			positionX = -1 + DISTANCE;
			type = std::rand() % 2;
			y = 0.1;
		}
		blocks.push_back(Rectangle(positionX, y, Block_Size(type)));
		break;
	case GLFW_KEY_F2:
		if (!blocks.empty()) blocks.pop_back();
		break;
	case GLFW_KEY_F3:
		Write();
		break;
	case GLFW_KEY_F5:
		$++;
		if ($ == 12) $ = 1;
		positionX = -0.2 * $ - DISTANCE;
		printf("positionX = %f\n", positionX);
		break;
	}
}

void GLFWCALL MouseClick(int button, int state)
{
	mouse.leftClick = (button == GLFW_MOUSE_BUTTON_LEFT);
	mouse.state = state;
}

void GLFWCALL MousePos(int X, int Y)
{
	mouse.pos = GetOGL_Pos(X, Y);
}

int main()
{
	printf("posclick(%f, %f)\n", Mouse::posClick.x, Mouse::posClick.y);
	if(!glfwInit()) {
		printf("Cannot initialize GLFW");
		return -1;
	}

  
	if(!glfwOpenWindow(windowWidth, windowHeight, 3, 3, 3, 0, 0, 0, GLFW_WINDOW)) {
		printf("Cannot create window");
		glfwTerminate();
		return -1;
	}
	
	glfwSetWindowPos(1366 >> 1, 0);
	
	Initialize();
	
	glClearColor(1, 1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	
	glfwDisable(GLFW_KEY_REPEAT);
	glfwDisable(GLFW_STICKY_KEYS);
	
	glfwSetKeyCallback(Keyboard);
	glfwSetMouseButtonCallback(MouseClick);
	glfwSetMousePosCallback(MousePos);
	glfwSetWindowSizeCallback(Resize);
                  
	while(!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED)) {
	
		PollEvents(NULL);
		
		Render(NULL);

		glfwSwapBuffers();
	
		glfwWaitEvents();

	}

	glfwTerminate();

	return 0;

}