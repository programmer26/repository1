#include "Header.h"
#include <stdio.h>

GLFWwindow* create_window(int width, int height, const char* title, int full_screen)
{
	GLFWwindow* temp;
	if(!glfwInit())
	{
		printf("GLFW failed to initialize!\n");
		return NULL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	if(full_screen)
		temp = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
	else temp = glfwCreateWindow(width, height, title, NULL, NULL);

	glfwMakeContextCurrent(temp);

	if(glewInit() != GLEW_OK)
	{
		printf("GLEW failed to initialize!\n");
		return NULL;
	}
	return temp;
}

void textures(unsigned* texture_id, GLenum target, int w, int h, unsigned char* data)
{
	glGenTextures(1, texture_id);
	glBindTexture(target, *texture_id);
	glTexImage2D(target, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(target);
}

void create_buffer(unsigned* buffer_id, int cnt, GLenum target, int data_size, void* data)
{
	glGenBuffers(cnt, buffer_id);
	glBindBuffer(target, *buffer_id);
	glBufferData(target, data_size, data, GL_STATIC_DRAW);
}

void shader(unsigned* shader, GLenum type, const char** src)
{
	int result;
	*shader = glCreateShader(type);
	glShaderSource(*shader, 1, src, NULL);
	glCompileShader(*shader);

	glGetShaderiv(*shader, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &maxLength);
		char errorLog[1024];
		glGetShaderInfoLog(*shader, maxLength, &maxLength, &errorLog[0]);
		if(type == GL_VERTEX_SHADER)
		{
			printf("Vertex shader failed to compile\n");
		}
		else
			printf("Fragment shader failed to compile\n");

		for(int i = 0; errorLog[i] != '\0'; ++i)
		{
			printf("%c", errorLog[i]);
		}
		glDeleteShader(*shader);
		return;
	}
	else
	{
		GLint maxLength = 0;
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &maxLength);
		if(maxLength == 0)
		{
			printf("Compilation was successful\n");
			return;
		}
		char errorLog[1024];
		glGetShaderInfoLog(*shader, maxLength, &maxLength, &errorLog[0]);
		for(int i = 0; errorLog[i] != '\0'; ++i)
		{
			printf("%c", errorLog[i]);
		}
	}
}

void program(unsigned* program, unsigned vertex_shader, unsigned fragment_shader)
{
	GLint result, mat;
	*program = glCreateProgram();
	glAttachShader(*program, vertex_shader);
	glAttachShader(*program, fragment_shader);
	glLinkProgram(*program);
	glGetProgramiv(*program, GL_LINK_STATUS, &result);
	if(result == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(*program, GL_INFO_LOG_LENGTH, &maxLength);

		char errorLog[1024];
		glGetProgramInfoLog(*program, maxLength, &maxLength, &errorLog[0]);

		for(int i = 0; errorLog[i] != '\0'; ++i)
		{
			printf("%c", errorLog[i]);
		}
		glDeleteProgram(*program);
		return;
	}
	else printf("Link was successful!\n");
	glUseProgram(*program);
}
void destroy_window(GLFWwindow* window)
{
	glfwDestroyWindow(window);
}
float a(float degrees)
{
	return degrees * (3.14159f / 180);
}
