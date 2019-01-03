//#include <iostream>
//
//#define GLEW_STATIC
//
//#include "glew/glew.h"
//#include "glfw/glfw3.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);		//����OpenGL�ӿڴ�С
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {		// ���Esc���Ƿ���
//		glfwSetWindowShouldClose(window, true);						// ���ô��ڹر�
//	}
//}
//
//int OpenGLSrc()
//{
//	// ��ʼ��glfw����
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		//ָ��OpenGL�����汾��
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);		//ָ��OpenGL���Ӱ汾��
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//ʹ��OpenGL�ĺ���ģʽ
//
//	GLFWwindow* window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL);		//��������;
//	if (window == NULL) {
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();		//�����������ֹ����;
//		return -1;
//	}
//	glfwMakeContextCurrent(window);		//�����ڵ������Ļ�������λ��ǰ���̵߳������Ļ���;
//
//	// ��ʼ��
//	if (glewInit() != GLEW_OK) {
//		std::cout << "Failed to init GLEW" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	
//	// ע�ᴰ�ڻص�����
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	// ��Ⱦѭ��
//	while (!glfwWindowShouldClose(window)) {	//����Ƿ�رմ���
//		processInput(window);
//
//		// ��Ⱦ
//		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);		//����������ɫ(��ɫ)
//		glClear(GL_COLOR_BUFFER_BIT);				//��������ģʽ
//
//		
//		glfwSwapBuffers(window);					// ����ʾ������������潻��(��ʾ���������е�����)
//		glfwPollEvents();							//����Ƿ����¼�����(�����������ͼ����¼�)
//
//	}
//
//	glfwTerminate();								//��ֹ����
//	return 0;
//}
