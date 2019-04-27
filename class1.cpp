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

//pre define
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;


int main()
{
	glfwInit();
	//GL3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnGL", 0, 0);
	if (window == 0)
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

	//setup viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	//GAME LOOP
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();//����¼�����

		glClearColor(0.2f, 0.3f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);//flush ����
	}

	// Terminate GLFW
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	printf("key: %d\n", key);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}