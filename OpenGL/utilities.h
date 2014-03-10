#ifndef _UTIL_H_
#define _UTIL_H_
#include <glew.h>
#include <glfw3.h>
#include <SOIL.h>

//Terry's Math lib
#include <TerrehByteMath.h>
//other helper functions
#include "GLLog.h"
#include "TextFileReader.h"


#include <string>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <functional>
using namespace tbyte;
extern Matrix4 * Ortho;
void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, tbyte::Matrix4 * mat);

struct Vertex
{
	union
	{
		struct 
		{
			tbyte::Vector3 Pos;
			tbyte::Vector4 Color;
			tbyte::Vector2 UV;
		};
		
		struct
		{
			float X, Y, Z, W;
			float R, G, B, A;
			float U, V;
		};
	};
	

	bool operator == (const Vertex& rhs)
	{
		return (X == rhs.X && Y == rhs.Y && Z == rhs.Z && W == rhs.W && U == rhs.U && V == rhs.V && R == rhs.R && G == rhs.G && B == rhs.B && A == rhs.A );
	}
};



#endif