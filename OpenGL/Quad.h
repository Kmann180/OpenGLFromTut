#ifndef _QUAD_H_
#define _QUAD_H_

#include <glew.h>
#include <GLLog.h>
#include "TextFileReader.h"

class Quad
{
public:
	Quad(void);
	~Quad(void);
	GLuint m_VBO; // vertex buffer
	GLuint m_EBO; // vertex buffer
	GLuint m_VAO; // vertex buffer

	GLuint m_FragmentShader;
	GLuint m_VertexShader;
	GLuint m_ShaderProgram;

bool Quad::LoadVertShader(const char* filepath);
bool Quad::LoadFragShader(const char* filepath);
bool Quad::LinkShaders();

	void draw();
private:

};

#endif