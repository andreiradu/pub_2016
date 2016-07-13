#include <Engine/Rendering/OpenGLRenderer.h>
#include "Rendering/glew.h"
#include <gl/GL.h>
namespace Engine
{
	const char* vertSource = "\
#version 120\
\n\
attribute vec4 Position;\n\
attribute vec2 Texcoord;\n\
varying vec2 uv;\n\
\n\
void main()\
{\
	gl_Position = vec4(2.0*(Position.xy-0.5), 0.0, 1.0);\n\
	uv = Texcoord;\
}						\
		";
	const char* fragSource = "\
#version 120\
\n\
varying vec2 uv;\n\
uniform float alpha;\
uniform sampler2D tex;\n\
void main()\
\n\
{\
	vec4 color = texture2D(tex, uv);\n\
	gl_FragColor = vec4(color.rgb,alpha);\n\
}\
		";
GLuint program;
void Renderer::Init()
{
	glewInit();
	GLint dummyVal = -1;
	static const int ERROR_BUFFER_SIZE = 1024;
	char errorBuffer[ERROR_BUFFER_SIZE];
	GLuint vshader;
	GLuint fshader;
	vshader = glCreateShader(GL_VERTEX_SHADER);
	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	

	glShaderSource(vshader, 1, &vertSource, NULL);
	glCompileShader(vshader);
	//if (glGetError() != GL_NO_ERROR)
	{
		int dummyVal;
		glGetShaderInfoLog(vshader, ERROR_BUFFER_SIZE, &dummyVal, errorBuffer);
		printf("Vertex Shader Compile Error %s", errorBuffer);
	}
	

	glShaderSource(fshader, 1, &fragSource, NULL);
	glCompileShader(fshader);
	//if (glGetError() != GL_NO_ERROR)
	{
		int dummyVal;
		glGetShaderInfoLog(fshader, ERROR_BUFFER_SIZE, &dummyVal, errorBuffer);
		printf("Fragment Shader Compile Error %s", errorBuffer);
	}
	program = glCreateProgram();
	glAttachShader(program, fshader);
	glAttachShader(program, vshader);
	glLinkProgram(program); 
//	if (glGetError() != GL_NO_ERROR)
	{
		glGetProgramInfoLog(program, ERROR_BUFFER_SIZE, &dummyVal, errorBuffer);
		int a = 0;
	}
	int a = glGetError();
	a = 0;
}

void Renderer::BeginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::EndFrame()
{
}
struct SVertex
{
	float pos[4] = { 0.0f,0.0f,0.0f,1.0f };
	float uv[2] = { 0.0f, 0.0f };
};
void Renderer::RenderSprite(Sprite& sprite, uint32_t posX, uint32_t posY)
{
	GLint locPosition = glGetAttribLocation(program, "Position");
	GLint locUV = glGetAttribLocation(program, "Texcoord");
	GLint locTex = glGetUniformLocation(program, "tex");

	glUseProgram(program);
	glViewport(0, 0, m_width, m_height);
	int a = glGetError();
	//cache this
	GLuint tempVBO;
	GLuint tempIBO;
	glGenBuffers(1, &tempVBO);
	glGenBuffers(1, &tempIBO);

	glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempIBO);


	glUniform1i(locTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite.m_tex->GetHandle());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	a = glGetError();

	SVertex buff[4];
	buff[0].pos[0] = (float)posX/(float)(m_width);
	buff[0].pos[1] = 1.0f - (float)posY/(float)(m_height);
	buff[0].uv[0] = sprite.m_lowerLeftX * 1.0f / sprite.m_tex->GetWidth();
	buff[0].uv[1] = sprite.m_lowerLeftY * 1.0f / sprite.m_tex->GetHeight();

	buff[1].pos[0] = (float)posX / (float)(m_width);
	buff[1].pos[1] = 1.0f - (float)(posY + sprite.m_upperRightY - sprite.m_lowerLeftY) / (float)(m_height);
	buff[1].uv[0] = sprite.m_lowerLeftX * 1.0f / sprite.m_tex->GetWidth();
	buff[1].uv[1] = sprite.m_upperRightY * 1.0f / sprite.m_tex->GetHeight();

	buff[2].pos[0] = (float)(posX + sprite.m_upperRightX - sprite.m_lowerLeftX) / (float)(m_width);
	buff[2].pos[1] = 1.0f - (float)(posY + sprite.m_upperRightY - sprite.m_lowerLeftY) / (float)(m_height);
	buff[2].uv[0] = sprite.m_upperRightX * 1.0f / sprite.m_tex->GetWidth();;
	buff[2].uv[1] = sprite.m_upperRightY * 1.0f / sprite.m_tex->GetHeight();

	buff[3].pos[0] = (float)(posX + sprite.m_upperRightX - sprite.m_lowerLeftX) / (float)(m_width);
	buff[3].pos[1] = 1.0f - (float)posY / (float)(m_height);
	buff[3].uv[0] = sprite.m_upperRightX * 1.0f / sprite.m_tex->GetWidth();
	buff[3].uv[1] = sprite.m_lowerLeftY * 1.0f / sprite.m_tex->GetHeight();
	uint16_t indices[] = { 0,1,2,2,3,0 };

	glBufferData(GL_ARRAY_BUFFER, 4 * 6 * sizeof(float), buff, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,6 * sizeof(uint16_t), indices, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(locPosition);
	glVertexAttribPointer(locPosition, 4, GL_FLOAT, false, 6 * sizeof(float), NULL);

	glEnableVertexAttribArray(locUV);
	glVertexAttribPointer(locUV, 2, GL_FLOAT, false, 6 * sizeof(float), (const void*)(4*sizeof(float)));

	a = glGetError();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
	a = glGetError();
	glDeleteBuffers(1, &tempVBO);
	glDeleteBuffers(1, &tempIBO);

}
}