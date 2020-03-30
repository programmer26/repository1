#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Header.h"
#include "math.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
	unsigned buffer, vertex_shader, fragment_shader, program_id, vao, EBO, tex;
	GLint mat, mat2, mat3, Matrix, width, height, obsolete;
	
	unsigned char* image_data = stbi_load("image.jpg", &width, &height, &obsolete, 0);
	if(image_data == NULL)
	{
		std::cerr << "Texture failed to load!" << std::endl;
		return -1;
	}
	const char* ver_src =
		"#version 440 core\n"
		"\n"
		"layout(location = 0) in vec3 coordinates;\n"
		"layout(location = 1) in vec3 color;\n"
		"layout(location = 2) in vec2 TexCoord;\n"
		"uniform mat4 transform;\n"
		"out vec3 to_frag;\n"
		"out vec2 texCoord;\n"
		"void main()\n"
		"{\n"
		"   to_frag = color;\n"
		"	texCoord = TexCoord;\n"
		"	gl_Position = transform * vec4(coordinates, 1.0f);\n"
		"}\n";

	const char* frag_src =
		"#version 440 core\n"
		"\n"
		"in vec3 to_frag;\n"
		"in vec2 texCoord;\n"
		"out vec4 to_the_screen;\n"
		"uniform sampler2D sample123;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	to_the_screen = texture(sample123, texCoord);\n"
		"}\n";

	GLFWwindow* window = create_window(1920, 1080, "OpenGL", 0);
	if(window == NULL)
	{
		return -1;
	}

	float data[] = {
	   -0.5f, -0.5f, 0.0f,
		1.0f,  0.0f, 0.0f,
	    0.0f,  1.0f,       //TexCoord

		0.5f, -0.5f, 0.0f,
		1.0f,  0.0f, 0.0f,
		1.0f,  1.0f,      //TexCoord

		0.5f,  0.5f, 0.0f, //Coord
		0.5f,  0.0f, 0.0f, //Color
		1.0f,  0.0f,       //TexCoord

		-0.5f, 0.5f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f
	};
	unsigned short indices[] = {
		0, 1, 2,
		0, 2, 3
	};
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	create_buffer(&buffer, 1, GL_ARRAY_BUFFER, sizeof(data), data);
	create_buffer(&EBO, 1, GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices);

	shader(&vertex_shader, GL_VERTEX_SHADER, &ver_src);
	shader(&fragment_shader, GL_FRAGMENT_SHADER, &frag_src);
	program(&program_id, vertex_shader, fragment_shader);

	textures(&tex, GL_TEXTURE_2D, width, height, image_data);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, fl8, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, fl8, (void*)fl3);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, fl8, (void*)fl6);

	Transform transform;
	Matrix = glGetUniformLocation(program_id, "transform");
	float angle = 0.0f;
	while(!glfwWindowShouldClose(window))
	{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

		glm::mat4 Model = transform.GetModel();
		glUniformMatrix4fv(Matrix, 1, GL_FALSE, &Model[0][0]);


		transform.GetPos().x = sinf(angle);
		transform.GetRot().y = angle * 2;
		transform.SetScale(glm::vec3(cosf(angle), cosf(angle), cosf(angle)));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		glfwSwapBuffers(window);

		glfwSwapInterval(1);
		glfwPollEvents();
		angle += 0.01;
	}

	printf("\n%s\n", glGetString(GL_VERSION));
	printf("%s\n", glGetString(GL_VENDOR));
	destroy_window(window);
	system("PAUSE");
	return 0;
}
