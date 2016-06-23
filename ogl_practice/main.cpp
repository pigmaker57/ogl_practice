//Привет
#include <iostream>
#include <cmath>
#include <GLFW/glfw3.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

const int LEVEL_SIZE_X = 5;
const int LEVEL_SIZE_Z = 5;
const double LEVEL_TILE_SIZE = 2;

struct ObjPos {
	double x;
	double y;
	double z;
	double angle;

	double fSpeed;
	double rSpeed;

} ppos {0, 1, 0, 0, 0, 0};


void error_callback(int error, const char* description)
{
	cout << "Error: " << description << endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
	{
		switch(key)
		{
			case GLFW_KEY_UP:
				ppos.fSpeed = 1;
				break;

			case GLFW_KEY_DOWN:
				ppos.fSpeed = -1;
				break;

			case GLFW_KEY_LEFT:
				ppos.rSpeed = -1;
				break;

			case GLFW_KEY_RIGHT:
				ppos.rSpeed = 1;
				break;
		}
	}
	else if(action == GLFW_RELEASE)
	{
		switch (key)
		{
			case GLFW_KEY_UP:
				if(ppos.fSpeed > 0) ppos.fSpeed = 0;
				break;

			case GLFW_KEY_DOWN:
				if (ppos.fSpeed < 0) ppos.fSpeed = 0;
				break;

			case GLFW_KEY_LEFT:
				if (ppos.rSpeed < 0) ppos.rSpeed = 0;
				break;

			case GLFW_KEY_RIGHT:
				if(ppos.rSpeed > 0) ppos.rSpeed = 0;
				break;
		}
	}
}

void updateObj(ObjPos *pos, double deltaFrameTime)
{
	if(pos->fSpeed != 0)
	{
		pos->x += sin(pos->angle) * deltaFrameTime * pos->fSpeed;
		pos->z -= cos(pos->angle) * deltaFrameTime * pos->fSpeed;
	}

	if (pos->rSpeed != 0)
	{
		pos->angle += deltaFrameTime * pos->rSpeed;
	}
}

//рисование квадратика пола
void drawFloorTile(double x, double z, double xSize, double zSize)
{
	glPushMatrix();
	glTranslated(x, 0, -z);
	glBegin(GL_QUADS);
	glVertex3d(0, 0, -zSize);
	glVertex3d(0, 0, 0);
	glVertex3d(xSize, 0, 0);
	glVertex3d(xSize, 0, -zSize);
	glEnd();
	glPopMatrix();
}

void drawLevelFloor(int floor[LEVEL_SIZE_X][LEVEL_SIZE_Z])
{

}

int main(void)
{
	int levelFloor[LEVEL_SIZE_X][LEVEL_SIZE_Z] = {
		{ 0, 0, 0, 1, 1},
		{ 0, 0, 1, 1, 0 },
		{ 0, 1, 1, 0, 0 },
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 }
	};

	const int WINDOW_WIDTH = 640, WINDOW_HEIGHT = 480;
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	/* Инициализация либы */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Test", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	double lastFrameTime = 0;

	/*Включаем отсечение изнаночных граней*/
	//glEnable(GL_CULL_FACE);

	/*Включаем буфер глубины*/
	glEnable(GL_DEPTH_TEST);

	/* Цикл, пока юзер не закроет окно */
	while (!glfwWindowShouldClose(window))
	{
		double deltaFrameTime = glfwGetTime() - lastFrameTime;
		lastFrameTime = glfwGetTime();

		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Настройка перспективной проекции
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-0.2f, 0.2f, -0.2f, 0.2f, 0.2f, 100.f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/*Установка позиции камеры*/
		glRotated(ppos.angle * 180 / M_PI, 0, 1, 0);
		glTranslated(-ppos.x, -ppos.y, -ppos.z);

		/*рисование пола*/
		/*glColor3d(1, 0, 0);
		drawFloorTile(-2, -2, 1, 6);
		glColor3d(1, 0, 1);
		drawFloorTile(-1, -2, 6, 1);
		glColor3d(0, 1, 0);
		drawFloorTile(-1, -1, 4, 4);
		*/
		drawLevelFloor(levelFloor);

		/*стремный треугольничек*/
		glTranslated(0, -0.5, 0);
		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3d(-0.6, 0, 0);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3d(0.6, 0, 0);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3d(0, 1, 0);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();

		updateObj(&ppos, deltaFrameTime);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}