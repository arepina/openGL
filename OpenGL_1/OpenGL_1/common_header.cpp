/*#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")

#include "common_header.h"
#include "win_OpenGLApp.h"
#include "shaders.h"

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "gl/glut.h"
#include <string>
#include <GL/freeglut.h>

using namespace std;


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	RenderScene;
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1350, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Repina Anastasia BSE143 HW7");
	InitScene;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}*/