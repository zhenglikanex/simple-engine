//#include <iostream>
//
//#define GLEW_STATIC
//
//#include "glew/glew.h"
//#include "glfw/glfw3.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);		//调整OpenGL视口大小
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {		// 检查Esc键是否按下
//		glfwSetWindowShouldClose(window, true);						// 设置窗口关闭
//	}
//}
//
//int OpenGLSrc()
//{
//	// 初始化glfw窗口
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		//指定OpenGL的主版本号
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);		//指定OpenGL的子版本号
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//使用OpenGL的核心模式
//
//	GLFWwindow* window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL);		//创建窗口;
//	if (window == NULL) {
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();		//如果出错，则终止进程;
//		return -1;
//	}
//	glfwMakeContextCurrent(window);		//将窗口的上下文环境设置位当前主线程的上下文环境;
//
//	// 初始化
//	if (glewInit() != GLEW_OK) {
//		std::cout << "Failed to init GLEW" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	
//	// 注册窗口回调函数
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	// 渲染循环
//	while (!glfwWindowShouldClose(window)) {	//检测是否关闭窗口
//		processInput(window);
//
//		// 渲染
//		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);		//设置清屏颜色(黄色)
//		glClear(GL_COLOR_BUFFER_BIT);				//设置清屏模式
//
//		
//		glfwSwapBuffers(window);					// 将显示缓存和离屏缓存交换(显示离屏缓存中的内容)
//		glfwPollEvents();							//检查是否有事件触发(例如鼠标输入和键盘事件)
//
//	}
//
//	glfwTerminate();								//终止进程
//	return 0;
//}
