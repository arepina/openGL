#include "common_header.h"

#include "win_OpenGLApp.h"

#include "shaders.h"


//Repina Anastasia BSE143. HW7. 12.11.2017
//Drawing the triangle, quad, tree, star and boat using OpenGL. Each object has its own init and setup methods.

float fTriangle[9]; // Data to render triangle (3 vertices, each has 3 floats)
float fQuad[12]; // Data to render quad using triangle strips (4 vertices, each has 3 floats)
float fBoat[12]; 
float fMast[12];
float fCanvas[9];
float fSun[365];
float fStar[33];
float fTree[27];
float fTreeRoot[12];
float fTriangleColor[9];
float fQuadColor[12];
float fBoatColor[12];
float fMastColor[12];
float fCanvasColor[9];
float fSunColor[365];
float fStarColor[33];
float fTreeColor[27];
float fTreeRootColor[12];

UINT uiVBO[16];
UINT uiVAO[8];

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

	fBoat[0] = -0.8f; fBoat[1] = -0.8f; fBoat[2] = 0.0f;
	fBoat[3] = -0.9f; fBoat[4] = -0.6f; fBoat[5] = 0.0f;
	fBoat[6] = -0.6f; fBoat[7] = -0.8f; fBoat[8] = 0.0f;
	fBoat[9] = -0.5f; fBoat[10] = -0.6f; fBoat[11] = 0.0f;

	// Setup boat color

	fBoatColor[0] = 0.4f; fBoatColor[1] = 0.4f; fBoatColor[2] = 0.3f;
	fBoatColor[3] = 0.4f; fBoatColor[4] = 0.4f; fBoatColor[8] = 0.3f;
	fBoatColor[6] = 0.4f; fBoatColor[7] = 0.4f; fBoatColor[5] = 0.3f;
	fBoatColor[9] = 0.4f; fBoatColor[10] = 0.4f; fBoatColor[11] = 0.3f;
}

void initMast()
{
	// Setup mast vertices

	fMast[0] = -0.71f; fMast[1] = -0.6f; fMast[2] = 0.0f;
	fMast[3] = -0.71f; fMast[4] = 0.3f; fMast[5] = 0.0f;
	fMast[6] = -0.69f; fMast[7] = -0.6f; fMast[8] = 0.0f;
	fMast[9] = -0.69f; fMast[10] = 0.3f; fMast[11] = 0.0f;

	// Setup mast color

	fMastColor[0] = 0.4f; fMastColor[1] = 0.4f; fMastColor[2] = 0.0f;
	fMastColor[3] = 0.4f; fMastColor[4] = 0.4f; fMastColor[8] = 0.0f;
	fMastColor[6] = 0.4f; fMastColor[7] = 0.4f; fMastColor[5] = 0.0f;
	fMastColor[9] = 0.4f; fMastColor[10] = 0.4f; fMastColor[11] = 0.0f;
}

void initCanvas()
{
	// Setup canvas vertices
	fCanvas[0] = -0.69f; fCanvas[1] = -0.3f; fCanvas[2] = 0.0f;
	fCanvas[3] = -0.69f; fCanvas[4] = 0.3f; fCanvas[5] = 0.0f;
	fCanvas[6] = -0.49f; fCanvas[7] = -0.3f; fCanvas[8] = 0.0f;

	// Setup canvas color

	fCanvasColor[0] = 1.0f; fCanvasColor[1] = 0.0f; fCanvasColor[2] = 0.0f;
	fCanvasColor[3] = 1.0f; fCanvasColor[4] = 0.0f; fCanvasColor[5] = 0.0f;
	fCanvasColor[6] = 1.0f; fCanvasColor[7] = 0.0f; fCanvasColor[8] = 0.0f;
}

void initSun()
{
	float angle = 0;
	float rad = 0.2f;
	const float PI = 3.1415926f;
	int n = 365;
	for (int i = 0; i <= n - 3; i++)
	{
		fSun[i] = rad * cos(angle);
		fSun[i + 1] = rad * sin(angle);
		fSun[i + 2] = 0.0f;
		fSunColor[i] = 0.0f;
		fSunColor[i + 1] = 1.0f;
		fSunColor[i + 2] = 0.0f;
		// update to next angle
		angle += PI * 2 / n;
	}
}

void initStar()
{
	// Setup star vertices

	fStar[0] = 0.0f; fStar[1] = 0.0f;  fStar[2] = 0.0f;
	fStar[3] = 0.1f; fStar[4] = 0.0f;  fStar[5] = 0.0f;
	fStar[6] = 0.15f; fStar[7] = 0.2f;  fStar[8] = 0.0f;
	fStar[9] = 0.2f; fStar[10] = 0.0f; fStar[11] = 0.0f;
	fStar[12] = 0.3f; fStar[13] = 0.0f; fStar[14] = 0.0f;
	fStar[15] = 0.2f; fStar[16] = -0.1f; fStar[17] = 0.0f;
	fStar[18] = 0.25f; fStar[19] = -0.3f; fStar[20] = 0.0f;
	fStar[21] = 0.15f; fStar[22] = -0.2f; fStar[23] = 0.0f;
	fStar[24] = 0.05f; fStar[25] = -0.3f; fStar[26] = 0.0f;
	fStar[27] = 0.1f; fStar[28] = -0.1f; fStar[29] = 0.0f;
	fStar[30] = 0.0f; fStar[31] = 0.0f; fStar[32] = 0.0f;

	// Setup star color

	fStarColor[0] = 1.0f; fStarColor[1] = 0.0f;  fStarColor[2] = 0.0f;
	fStarColor[3] = 1.0f; fStarColor[4] = 1.0f;  fStarColor[5] = 0.0f;
	fStarColor[6] = 1.0f; fStarColor[7] = 0.0f;  fStarColor[8] = 1.0f;
	fStarColor[9] = 1.0f; fStarColor[10] = 0.0f; fStarColor[11] = 0.0f;
	fStarColor[12] = 1.0f; fStarColor[13] = 1.0f; fStarColor[14] = 0.0f;
	fStarColor[15] = 1.0f; fStarColor[16] = 0.0f; fStarColor[17] = 1.0f;
	fStarColor[18] = 1.0f; fStarColor[19] = 0.0f; fStarColor[20] = 0.0f;
	fStarColor[21] = 1.0f; fStarColor[22] = 1.0f; fStarColor[23] = 0.0f;
	fStarColor[24] = 1.0f; fStarColor[25] = 0.0f; fStarColor[26] = 1.0f;
	fStarColor[27] = 1.0f; fStarColor[28] = 0.0f; fStarColor[29] = 0.0f;
	fStarColor[30] = 1.0f; fStarColor[31] = 1.0f; fStarColor[32] = 0.0f;
}

void initTree()
{
	// Setup tree vertices
	fTree[0] = 0.5f; fTree[1] = 0.7f; fTree[2] = 0.0f;
	fTree[3] = 0.7f; fTree[4] = 0.7f; fTree[5] = 0.0f;
	fTree[6] = 0.6f; fTree[7] = 1.0f; fTree[8] = 0.0f;
	fTree[9] = 0.5f; fTree[10] = 0.4f; fTree[11] = 0.0f;
	fTree[12] = 0.7f; fTree[13] = 0.4f; fTree[14] = 0.0f;
	fTree[15] = 0.6f; fTree[16] = 0.7f; fTree[17] = 0.0f;
	fTree[18] = 0.5f; fTree[19] = 0.1f; fTree[20] = 0.0f;
	fTree[21] = 0.7f; fTree[22] = 0.1f; fTree[23] = 0.0f;
	fTree[24] = 0.6f; fTree[25] = 0.4f; fTree[26] = 0.0f;

	// Setup tree color

	fTreeColor[0] = 0.0f; fTreeColor[1] = 1.0f; fTreeColor[2] = 0.0f;
	fTreeColor[3] = 0.0f; fTreeColor[4] = 1.0f; fTreeColor[5] = 0.0f;
	fTreeColor[6] = 0.0f; fTreeColor[7] = 1.0f; fTreeColor[8] = 0.0f;
	fTreeColor[9] = 0.0f; fTreeColor[10] = 1.0f; fTreeColor[11] = 0.0f;
	fTreeColor[12] = 0.0f; fTreeColor[13] = 1.0f; fTreeColor[14] = 0.0f;
	fTreeColor[15] = 0.0f; fTreeColor[16] = 1.0f; fTreeColor[17] = 0.0f;
	fTreeColor[18] = 0.0f; fTreeColor[19] = 1.0f; fTreeColor[20] = 0.0f;
	fTreeColor[21] = 0.0f; fTreeColor[22] = 1.0f; fTreeColor[23] = 0.0f;
	fTreeColor[24] = 0.0f; fTreeColor[25] = 1.0f; fTreeColor[26] = 0.0f;
}

void initTreeRoot()
{
	// Setup tree root vertices

	fTreeRoot[0] = 0.55f; fTreeRoot[1] = 0.1f; fTreeRoot[2] = 0.0f;
	fTreeRoot[3] = 0.55f; fTreeRoot[4] = 0.0f; fTreeRoot[5] = 0.0f;
	fTreeRoot[6] = 0.65f; fTreeRoot[7] = 0.1f; fTreeRoot[8] = 0.0f;
	fTreeRoot[9] = 0.65f; fTreeRoot[10] = 0.0f; fTreeRoot[11] = 0.0f;

	// Setup tree root color

	fTreeRootColor[0] = 0.4f; fTreeRootColor[1] = 0.4f; fTreeRootColor[2] = 0.0f;
	fTreeRootColor[3] = 0.4f; fTreeRootColor[4] = 0.4f; fTreeRootColor[8] = 0.0f;
	fTreeRootColor[6] = 0.4f; fTreeRootColor[7] = 0.4f; fTreeRootColor[5] = 0.0f;
	fTreeRootColor[9] = 0.4f; fTreeRootColor[10] = 0.4f; fTreeRootColor[11] = 0.0f;
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
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), fCanvas, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[9]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), fCanvasColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void setupSun()
{
	// Setup whole sun
	glBindVertexArray(uiVAO[8]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[16]);
	glBufferData(GL_ARRAY_BUFFER, 365 * sizeof(float), fSun, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[17]);
	glBufferData(GL_ARRAY_BUFFER, 365 * sizeof(float), fSunColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void setupStar()
{
	// Setup whole sun
	glBindVertexArray(uiVAO[5]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[10]);
	glBufferData(GL_ARRAY_BUFFER, 33 * sizeof(float), fStar, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[11]);
	glBufferData(GL_ARRAY_BUFFER, 33 * sizeof(float), fStarColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void setupTree()
{
	// Setup whole canvas
	glBindVertexArray(uiVAO[6]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[12]);
	glBufferData(GL_ARRAY_BUFFER, 27 * sizeof(float), fTree, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[13]);
	glBufferData(GL_ARRAY_BUFFER, 27 * sizeof(float), fTreeColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void setupTreeRoot()
{
	// Setup whole canvas
	glBindVertexArray(uiVAO[7]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[14]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), fTreeRoot, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[15]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), fTreeRootColor, GL_STATIC_DRAW);
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
	initStar();
	initTree();
	initTreeRoot();
	//initSun();

	glGenVertexArrays(8, uiVAO); 
	glGenBuffers(16, uiVBO);

	setupTriangle();
	setupQuad();
	setupBoat();
	setupMast();
	setupCanvas();
	setupStar();
	setupTree();
	setupTreeRoot();
	//setupSun();

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

	//glBindVertexArray(uiVAO[7]);
	//glDrawArrays(GL_LINE_STRIP, 0, 365);

	glBindVertexArray(uiVAO[5]);
	glDrawArrays(GL_LINE_STRIP, 0, 33);

	glBindVertexArray(uiVAO[6]);
	glDrawArrays(GL_TRIANGLES, 0, 27);
	
	glBindVertexArray(uiVAO[7]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4) ;

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