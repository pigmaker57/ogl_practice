//Привет
#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;



void error_callback(int error, const char* description)
{
	cout << "Error: " << description << endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}


int main(void)
{
	const int WINDOW_WIDTH = 640, WINDOW_HEIGHT = 480;
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	/* Initialize the library */
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

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		double deltaFrameTime = glfwGetTime() - lastFrameTime;
		lastFrameTime = glfwGetTime();

		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		//set projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-0.2f, 0.2f, -0.2f, 0.2f, 0.2f, 100.f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

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
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}