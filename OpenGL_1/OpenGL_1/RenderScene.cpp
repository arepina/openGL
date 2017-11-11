#include "common_header.h"

#include "win_OpenGLApp.h"

#include "shaders.h"


float fTriangle[9]; // Data to render triangle (3 vertices, each has 3 floats)
float fQuad[12]; // Data to render quad using triangle strips (4 vertices, each has 3 floats)
float fBoat[12]; 
float fMast[12];
float fCanvas[9];
float fTriangleColor[9];
float fQuadColor[12];
float fBoatColor[12];
float fMastColor[12];
float fCanvasColor[9];

UINT uiVBO[10];
UINT uiVAO[5];

CShader shVertex, shFragment;
CShaderProgram spMain;

void initTriangle()
{
	// Setup triangle vertices
	fTriangle[0] = -1.0f; fTriangle[1] = 0.7f; fTriangle[2] = 0.0f;
	fTriangle[3] = -0.6f; fTriangle[4] = 0.7f; fTriangle[5] = 0.0f;
	fTriangle[6] = -0.8f; fTriangle[7] = 1.0f; fTriangle[8] = 0.0f;

	// Setup triangle color

	fTriangleColor[0] = 1.0f; fTriangleColor[1] = 0.0f; fTriangleColor[2] = 0.0f;
	fTriangleColor[3] = 0.0f; fTriangleColor[4] = 1.0f; fTriangleColor[5] = 0.0f;
	fTriangleColor[6] = 0.0f; fTriangleColor[7] = 0.0f; fTriangleColor[8] = 1.0f;
}

void initQuad()
{
	// Setup quad vertices

	fQuad[0] = -0.9f; fQuad[1] = 0.4f; fQuad[2] = 0.0f;
	fQuad[3] = -0.9f; fQuad[4] = 0.7f; fQuad[5] = 0.0f;
	fQuad[6] = -0.7f; fQuad[7] = 0.4f; fQuad[8] = 0.0f;
	fQuad[9] = -0.7f; fQuad[10] = 0.7f; fQuad[11] = 0.0f;

	// Setup quad color

	fQuadColor[0] = 1.0f; fQuadColor[1] = 0.0f; fQuadColor[2] = 0.0f;
	fQuadColor[3] = 0.0f; fQuadColor[4] = 1.0f; fQuadColor[8] = 0.0f;
	fQuadColor[6] = 0.0f; fQuadColor[7] = 0.0f; fQuadColor[5] = 1.0f;
	fQuadColor[9] = 1.0f; fQuadColor[10] = 1.0f; fQuadColor[11] = 0.0f;
}

void initBoat()
{
	// Setup boat vertices

	fBoat[0] = -0.2f; fBoat[1] = -0.8f; fBoat[2] = 0.0f;
	fBoat[3] = -0.3f; fBoat[4] = -0.6f; fBoat[5] = 0.0f;
	fBoat[6] = 0.2f; fBoat[7] = -0.8f; fBoat[8] = 0.0f;
	fBoat[9] = 0.3f; fBoat[10] = -0.6f; fBoat[11] = 0.0f;

	// Setup boat color

	fBoatColor[0] = 0.4f; fBoatColor[1] = 0.4f; fBoatColor[2] = 0.3f;
	fBoatColor[3] = 0.4f; fBoatColor[4] = 0.4f; fBoatColor[8] = 0.3f;
	fBoatColor[6] = 0.4f; fBoatColor[7] = 0.4f; fBoatColor[5] = 0.3f;
	fBoatColor[9] = 0.4f; fBoatColor[10] = 0.4f; fBoatColor[11] = 0.3f;
}

void initMast()
{
	// Setup mast vertices

	fMast[0] = -0.01f; fMast[1] = -0.6f; fMast[2] = 0.0f;
	fMast[3] = -0.01f; fMast[4] = 0.3f; fMast[5] = 0.0f;
	fMast[6] = 0.01f; fMast[7] = -0.6f; fMast[8] = 0.0f;
	fMast[9] = 0.01f; fMast[10] = 0.3f; fMast[11] = 0.0f;

	// Setup mast color

	fMastColor[0] = 0.4f; fMastColor[1] = 0.4f; fMastColor[2] = 0.0f;
	fMastColor[3] = 0.4f; fMastColor[4] = 0.4f; fMastColor[8] = 0.0f;
	fMastColor[6] = 0.4f; fMastColor[7] = 0.4f; fMastColor[5] = 0.0f;
	fMastColor[9] = 0.4f; fMastColor[10] = 0.4f; fMastColor[11] = 0.0f;
}

void initCanvas()
{
	// Setup canvas vertices
	fCanvas[0] = 0.01f; fCanvas[1] = -0.3f; fCanvas[2] = 0.0f;
	fCanvas[3] = 0.01f; fCanvas[4] = 0.3f; fCanvas[5] = 0.0f;
	fCanvas[6] = 0.27f; fCanvas[7] = -0.3f; fCanvas[8] = 0.0f;

	// Setup canvas color

	fCanvasColor[0] = 1.0f; fCanvasColor[1] = 0.0f; fCanvasColor[2] = 0.0f;
	fCanvasColor[3] = 1.0f; fCanvasColor[4] = 0.0f; fCanvasColor[5] = 0.0f;
	fCanvasColor[6] = 1.0f; fCanvasColor[7] = 0.0f; fCanvasColor[8] = 0.0f;
}

void setupTriangle()
{
	// Setup whole triangle
	glBindVertexArray(uiVAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), fTriangle, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), fTriangleColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void setupQuad()
{
	// Setup whole quad
	glBindVertexArray(uiVAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), fQuad, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[3]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), fQuadColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void setupBoat()
{
	// Setup whole boat
	glBindVertexArray(uiVAO[2]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[4]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), fBoat, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[5]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), fBoatColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void setupMast()
{
	// Setup whole mast
	glBindVertexArray(uiVAO[3]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[6]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), fMast, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[7]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), fMastColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void setupCanvas()
{
	// Setup whole canvas
	glBindVertexArray(uiVAO[4]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[8]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), fCanvas, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[9]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), fCanvasColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}


// Initializes OpenGL features that will be used.
// lpParam - Pointer to anything you want.
void InitScene(LPVOID lpParam)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//Changed the background color

	initTriangle();

	initQuad();
	
	initBoat();

	initMast();

	initCanvas();

	glGenVertexArrays(5, uiVAO); // Generate 5 VAOs
	glGenBuffers(10, uiVBO); // And 10 VBOs

	setupTriangle();

	setupQuad();

	setupBoat();

	setupMast();

	setupCanvas();

	// Load shaders and create shader program

	shVertex.LoadShader("data\\shaders\\shader.vert", GL_VERTEX_SHADER);
	shFragment.LoadShader("data\\shaders\\shader.frag", GL_FRAGMENT_SHADER);

	spMain.CreateProgram();
	spMain.AddShaderToProgram(&shVertex);
	spMain.AddShaderToProgram(&shFragment);

	spMain.LinkProgram();
	spMain.UseProgram();
}

// Renders whole scene.
// lpParam - Pointer to anything you want.
void RenderScene(LPVOID lpParam)
{
	// Typecast lpParam to COpenGLControl pointer
	COpenGLControl* oglControl = (COpenGLControl*)lpParam;

	// We just clear color
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(uiVAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(uiVAO[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(uiVAO[2]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(uiVAO[3]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(uiVAO[4]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	
	oglControl->SwapBuffersM();
}

// Releases OpenGL scene.
// lpParam - Pointer to anything you want.
void ReleaseScene(LPVOID lpParam)
{
	spMain.DeleteProgram();

	shVertex.DeleteShader();
	shFragment.DeleteShader();
}