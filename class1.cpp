#define GLEW_STATIC
/**
 * �ڰ���GLFW��ͷ�ļ�֮ǰ������GLEW��ͷ�ļ���
 * �ڰ���glew.hͷ�ļ�ʱ���������OpenGL��Ҫ��ͷ�ļ�������GL/gl.h����
 * ��������Ҫ�ڰ�������������OpenGL��ͷ�ļ�֮ǰ�Ȱ���GLEW��
 */
//GLEW
#include <GL\glew.h>
#include <GL\glut.h>
//GLFW
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <cmath>
#include "LearnGL\Shaders.h"

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
	// �����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	// GLEW�ڹ���OpenGL�ĺ���ָ��ʱ�����ʹ���ִ����ļ���
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
	Shader ourShader("E:/Workspaces/OpenGL/LearnOpenGL/LearnGL/LearnGL/Shaders/Class2/class2.vs",
		"E:/Workspaces/OpenGL/LearnOpenGL/LearnGL/LearnGL/Shaders/Class2/class2.fs");

	//setup vertex buffer
	GLfloat vertices[] = {
		// Positions        
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		0.0f,  0.5f, 0.0f   // Top 
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0); // Unbind VAO

	// GAME LOOP
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();//����¼�����

		glClearColor(0.2f, 0.3f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		// Update the uniform color
		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLint vertexColorLocation = glGetUniformLocation(ourShader.Program, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// Draw the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);//flush ����
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

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