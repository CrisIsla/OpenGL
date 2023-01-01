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
	GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle :)", NULL, NULL); // A window of 800 x 600 named 'HelloWindow!'
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

	// NEW CODE STARTS HERE

	float vertices[] = { // We define the coordinate of the three vertices of the triangle.
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO); // We crate a Vertex Array Object (explanation later)
	glGenBuffers(1, &VBO); // We generate a Vertex Buffer Object (VBO), that is used to store large amounts of data, like vertices.

	glBindVertexArray(VAO); // We bind the VAO so we can use it.

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // We bind the buffer object we created to a ARRAY BUFFER object.
	// Every time we call GL_ARRAY_BUFFER object, we are using the VBO we just created (that is binded to the array buffer object)

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // So here we are copying the vertices[] data into the buffer's memory.

	glEnableVertexAttribArray(0); // We tell OpenGL that this is the VAO we want to use to draw for now on.

	// Now, to procces the triangle data, we have to create a vertex shader and a fragment shader.
	// This shaders are writen in GLSL.

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// In order to use it, we must create a new shader object, bind it, and compile it.

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// We should check if the compilation succeded.

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	const char* fragmentShaderSource = "#version 330\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Now that we have both shaders ready, we have to link both shader objects into a shader program.

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram(); // We create a new shader program object. Now, we have to link the vertex and fragment shaders to it.

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// Everything is ready to draw. Now, we specify that we want to use the shader program we just created.

	glUseProgram(shaderProgram);

	// We also delete the shader objects that we are not going to use anymore.

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Then, we tell OpenGL how is our vertex data stored. This is, a vertex per 12 bytes, were each component is stores in 4 bytes.

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// With everything we have we should be able to draw a triangle already, but imagine we wanted to draw multiples triangles. We should set everything
	// up each time we want to draw a new one. There is where a VAO comes up. A VAO stores a configuration so multiples object can use it. In this case,
	// line 55 is telling OpenGL that that is the configuration we want to use to draw from that point.

	// NEW CODE ENDS HERE

	while (!glfwWindowShouldClose(window))
	{
		processInput(window); // Check if ESCAPE key is being press. If so, it closes the window.

		// Rendering commands should be added here
		glClearColor(0.2f, 0.5f, 0.3f, 1.0f); // Clears the screen with the color specified.
		glClear(GL_COLOR_BUFFER_BIT); // GL_COLOR_BUFFER_BIT makes it so it clears the screen with the color specified in glClearColor function. This function has two other options.

		// CODE TO DRAW A TRIANGLE STARTS HERE

		glUseProgram(shaderProgram); // This line and the next one are innecesary. We already configure this things early. It's here just to be consistent.
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // Tells OpenGL to draw  3 vertices in a "triangle maner".

		// CODE TO DRAW A TRIANGLE ENDS HERE


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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
