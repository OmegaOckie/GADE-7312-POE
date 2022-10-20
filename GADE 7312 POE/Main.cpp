#include"libs.h"
void framebuffer_resize_callback(GLFWwindow* window, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}
int main()
{

	//INIT GLFW
	glfwInit();

	//CREATE WINDOW
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);/*
	glViewport(0, 0, framebufferWidth, framebufferHeight);*/

	glfwMakeContextCurrent(window);

	//INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)

	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	//MAIN  LOOP
	while (!glfwWindowShouldClose(window))
	{
		//UPDATE INPUT
		glfwPollEvents();
		
		//UPDATE


		//DRAW

		//CLEAR
		glClearColor(0.6f, 0.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//DRAW

		//END DRAW
		glfwSwapBuffers(window);
		glFlush();
	}

	//END OF PROGRAM
	return 0;
}