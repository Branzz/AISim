#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <windows.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include "Simulation.h"

GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS
	 0.0f,  0.0f,                          1.0f,     0.9f, 0.1f, 0.1f,		// Lower left corner
	 0.5f, -0.8f * float(sqrt(3)) * 1 / 3, 0.0f,     0.1f, 0.9f, 0.1f,		// Lower right corner
	 0.1f,	0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     0.1f, 0.1f, 0.9f,		// Upper corner
	-0.25f,	0.8f * float(sqrt(3)) * 1 / 6, 0.0f,     0.1f, 0.9f, 0.1f,		// Inner left
	 0.2f,	0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.1f, 0.1f,		// Inner right
	 0.1f, -0.8f * float(sqrt(3)) * 1 / 3, 0.0f,     0.1f, 0.1f, 0.9f		// Inner down
};
GLuint indices[] = {
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
};

unsigned int fitnessCalculator(Creature* creature) {
	return creature->getEastDist();
}

int main() {

	init();

	const unsigned int WIDTH = 500, HEIGHT = 500;

	GLFWwindow* window = createWindow(WIDTH, HEIGHT);

	if (window == NULL)
		return EXIT_FAILURE;

	Simulation* simulation = new Simulation(5, 10, 50, WIDTH, HEIGHT, 10, 50, 2, *fitnessCalculator);
	simulation->run();

	// TODO convert creature float pos's to openGL vertices

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*) 0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//glVertex2i(5, 5);

	while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.3f, 0.3f, 0.3f);
        glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
        glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void init() {
	srand((unsigned int)time(0));

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* createWindow(const unsigned int width, const unsigned int height) {
	GLFWwindow* window = glfwCreateWindow(width, height, "Triangle Neural Sim", NULL, NULL);
	if (window == NULL) {
		std::cout << "Could not create window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);
	return window;
}