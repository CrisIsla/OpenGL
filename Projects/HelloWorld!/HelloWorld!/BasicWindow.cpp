#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height); // this function is used to resize the window whenever the user resizes it.

void processInput(GLFWwindow* window); // this function checks if a key is being press.

int main()
{
	glfwInit(); // In order to use glfw, it has to be initialized.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // First argument is the option we want to configure, and the second is the value we want to set to it.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // In this case, we set the minor and major OpenGL version to 3, so it only works with this range of versions.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Then, we set the OpenGL profile to the core profile.

	// After the initialization, we need to create a window object.
	GLFWwindow* window = glfwCreateWindow(800, 600, "HelloWindow!", NULL, NULL); // A window of 800 x 600 named 'HelloWindow!'
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // We make this window our current context.

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // We want to initialize GLAD before using any OpenGL function.
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600); // This function tells OpenGL the parameters of the window, in this case, we say start from the origin to 800 x 600.

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // In case the window is resized by the user, it resizes the image displayed too.

	while (!glfwWindowShouldClose(window))
	{
		processInput(window); // Check if ESCAPE key is being press. If so, it closes the window.

		// Rendering commands should be added here
		glClearColor(0.2f, 0.5f, 0.3f, 1.0f); // Clears the screen with the color specified.
		glClear(GL_COLOR_BUFFER_BIT); // GL_COLOR_BUFFER_BIT makes it so it clears the screen with the color specified in glClearColor function. This function has two other options.

		// Check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
