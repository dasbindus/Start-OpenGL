#define GLEW_STATIC
/**
 * 在包含GLFW的头文件之前包含了GLEW的头文件。
 * 在包含glew.h头文件时会引入许多OpenGL必要的头文件（例如GL/gl.h），
 * 所以你需要在包含其它依赖于OpenGL的头文件之前先包含GLEW。
 */
//GLEW
#include <GL\glew.h>
#include <GL\glut.h>
//GLFW
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <cmath>
#include "LearnGL\Shaders.h"
#include <SOIL.h>

//pre define
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	//======================== Init ================================
	glfwInit();
	//GL3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnGL", NULL, NULL);
	if (window == NULL)
	{
		printf("Fail to create window.\n");
		glfwTerminate();
		return -1;
	}
	// 将我们窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	// GLEW在管理OpenGL的函数指针时更多地使用现代化的技术
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW!\n");
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);

	printf("GLFW config: XXX\n");

	//====================== main GL logic =========================
	//setup viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	//Class1
	//Shader ourShader("E://Workspaces//OpenGL//LearnOpenGL//LearnGL//LearnGL//Shaders//Class1//class1.vs",
	//	"E://Workspaces//OpenGL//LearnOpenGL//LearnGL//LearnGL//Shaders//Class1//class1.fs");
	//Class2
	//Shader ourShader("E:/Workspaces/OpenGL/LearnOpenGL/LearnGL/LearnGL/Shaders/Class2/class2.vs",
	//	"E:/Workspaces/OpenGL/LearnOpenGL/LearnGL/LearnGL/Shaders/Class2/class2.fs");
	//Class3
	Shader ourShader("E:/Workspaces/OpenGL/LearnOpenGL/LearnGL/LearnGL/Shaders/Class3/class3.vs",
		"E:/Workspaces/OpenGL/LearnOpenGL/LearnGL/LearnGL/Shaders/Class3/class3.frag");

	//setup vertex buffer
	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	//------- create and load texute -------
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//set texture params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//Load texture
	int texWidth, texHeight;
	unsigned char* image = SOIL_load_image("E:/Workspaces/OpenGL/LearnOpenGL/LearnGL/LearnGL/Texture/wall.jpg",
		&texWidth, &texHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	// GAME LOOP
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();//检查事件触发

		glClearColor(0.2f, 0.3f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		//bind texture
		glBindTexture(GL_TEXTURE_2D, texture);

		// Draw the triangle
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);//flush 送显
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//====================== Terminate GLFW =========================
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	printf("key: %d\n", key);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}