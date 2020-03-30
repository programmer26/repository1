#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

void program(unsigned* program, unsigned vertex_shader, unsigned fragment_shader);

void shader(unsigned* shader, GLenum type, const char** src);

void textures(unsigned* texture_id, GLenum target, int w, int h, unsigned char* data);

void create_buffer(unsigned* buffer_id, int cnt, GLenum target, int data_size, void* data);

void destroy_window(GLFWwindow* window);

float a(float degrees);

GLFWwindow* create_window(int width, int height, const char* title, int full_screen);

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	: m_pos(pos), m_rot(rot), m_scale(scale) {}

	glm::mat4 GetModel() 
	{
		glm::mat4 PosMatrix = glm::translate(m_pos);
		glm::mat4 RotXmatrix = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 RotYmatrix = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 RotZmatrix = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));
		glm::mat4 ScaleMatrix = glm::scale(m_scale);

		glm::mat4 Rotation = RotZmatrix * RotYmatrix * RotXmatrix;
		return PosMatrix * Rotation * ScaleMatrix;
	}

	glm::vec3& GetPos()
	{
		return m_pos;
	}
	glm::vec3& GetRot()
	{
		return m_rot;
	}
	void SetScale(const glm::vec3& scale) 
	{ 
		m_scale = scale; 
	}
private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};

#define fl (sizeof(float))
#define fl2 (sizeof(float) * 2)
#define fl3 (sizeof(float) * 3)
#define fl4 (sizeof(float) * 4)
#define fl5 (sizeof(float) * 5)
#define fl6 (sizeof(float) * 6)
#define fl7 (sizeof(float) * 7)
#define fl8 (sizeof(float) * 8)
#define fl9 (sizeof(float) * 9)
#define fl10 (sizeof(float) * 10)
#define fl11 (sizeof(float) * 11)
#define fl12 (sizeof(float) * 12)
#define fl13 (sizeof(float) * 13)
#define fl14 (sizeof(float) * 14)
#define fl15 (sizeof(float) * 15)
#define fl16 (sizeof(float) * 16)
#define fl17 (sizeof(float) * 17)
#define fl18 (sizeof(float) * 18)
#define fl19 (sizeof(float) * 19)
#define fl20 (sizeof(float) * 20)
#define fl21 (sizeof(float) * 21)
#define fl22 (sizeof(float) * 22)
#define fl23 (sizeof(float) * 23)
#define fl24 (sizeof(float) * 24)
#define fl25 (sizeof(float) * 25)
#define fl26 (sizeof(float) * 26)
#define fl27 (sizeof(float) * 27)
#define fl28 (sizeof(float) * 28)
#define fl29 (sizeof(float) * 29)
#define fl30 (sizeof(float) * 30)