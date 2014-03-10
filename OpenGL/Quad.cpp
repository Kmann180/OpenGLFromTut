#include "Quad.h"


Quad::Quad(void)
{
	//Default shaders
	const char * VertexShader = //vertex shaders deal with objects in 3d space
		"#version 330\n"
		"in vec3 position;"
		"in vec4 color;"
		//"in vec2 texcoord;"
		"out vec4 vColour;"
		"void main() {"
		"	vColour = color;"
		"	gl_Position = vec4 (position, 1.0) ;"
		"}";

	const char * FragmentShader = // Fragment shader deals with pixel data
		"#version 330\n"
		"in vec4 vColour;"
		"out vec4 outColour;"
		"void main () {"
		"	outColour = vColour;"
		"}";

		// compile vertex shader
		m_VertexShader = glCreateShader (GL_VERTEX_SHADER) ;
		glShaderSource (m_VertexShader, 1, &VertexShader, NULL);
		glCompileShader (m_VertexShader);
		printShaderInfoLog(m_VertexShader);////only when done somthing you didnt do smart one :p

		// Compile Fragment Shader
		m_FragmentShader = glCreateShader (GL_FRAGMENT_SHADER) ;
		glShaderSource (m_FragmentShader, 1, &FragmentShader, NULL);
		glCompileShader (m_FragmentShader);
		printShaderInfoLog(m_FragmentShader);////only when done somthing you didnt do smart one :p

		// Link Shaders into Shader Program
		m_ShaderProgram = glCreateProgram();

		glAttachShader (m_ShaderProgram, m_FragmentShader);
		glAttachShader (m_ShaderProgram, m_VertexShader);

		glLinkProgram (m_ShaderProgram);
		printProgramInfoLog(m_ShaderProgram); ////only when done somthing you didnt do smart one :p

		glUseProgram(m_ShaderProgram);

		// create VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		//Create buffers
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		GLfloat points [] = 
		{
			//  coords                 color
			// x      y     z     R     G     B    A
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0,
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0,
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof (points), points, GL_STATIC_DRAW);
		//Specify layout of Vertex data
		GLint posAttrib = glGetAttribLocation (m_ShaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 7*(sizeof(float)),0);

		GLint colAttrib = glGetAttribLocation (m_ShaderProgram, "color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 7*(sizeof(float)), (void*) (3 * sizeof(GLfloat)));

		glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			GLuint elements[] =
			{
			 0,1,2,3
			};
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}


Quad::~Quad(void)
{
}


void Quad::draw()
{
	glUseProgram(m_ShaderProgram);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
}

bool Quad::LoadVertShader(const char* filepath)
{
std::string vs =textFileReader(filepath);
const char* VertexShader = vs.c_str();
glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
glCompileShader(m_VertexShader);
return printShaderInfoLog(m_VertexShader);
}

bool Quad::LoadFragShader(const char* filepath)
{
std::string vs =textFileReader(filepath);
const char* FragmentShader = vs.c_str();
glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
glCompileShader(m_FragmentShader);
return printShaderInfoLog(m_FragmentShader);
}

bool Quad::LinkShaders()
{
	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	glUseProgram(m_ShaderProgram);

	return printProgramInfoLog(m_ShaderProgram);
}