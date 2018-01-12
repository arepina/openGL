#include "common_header.h"

#include "win_OpenGLApp.h"

#include "shaders.h"
#include "texture.h"
#include "vertexBufferObject.h"

#include "flyingCamera.h"

#include "spotLight.h"
#include "dirLight.h"
#include "pointLight.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define NUMTEXTURES 5

//Repina Anastasia BSE143
//Viual Studio 2017 16/12/2017
//Created different light sources: spot, directional, point
//z nad x buttons - light of objects on and off
//w a s d buttons - moving
//q and e butttons - day and night change
//f - flashlight turn on and off

/* One VBO, where all static data are stored now,
in this tutorial vertex is stored as 3 floats for
position, 2 floats for texture coordinate and
3 floats for normal vector. */

CVertexBufferObject vboSceneObjects;
UINT uiVAOs[1]; // Only one VAO now

CTexture tTextures[NUMTEXTURES];
CFlyingCamera cCamera;

CDirectionalLight dlSun;
CSpotLight slFlashLight;
CSpotLight slFlashLight1;
CSpotLight slFlashLight2;
CSpotLight slFlashLight3;
CPointLight plLight;
CPointLight plLight1;
CPointLight plLight2;
CPointLight plLight3;

#include "static_geometry.h"

void initSceneObjects()
{
	// Prepare all scene objects

	vboSceneObjects.CreateVBO();
	glGenVertexArrays(1, uiVAOs); // Create one VAO
	glBindVertexArray(uiVAOs[0]);

	vboSceneObjects.BindVBO();

	AddSceneObjects(vboSceneObjects);

	vboSceneObjects.UploadDataToGPU(GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}

void initTextures()
{
	// Load textures

	string sTextureNames[] = { "grass.png", "met_wall01a.jpg", "tower.jpg", "box.jpg", "ground.jpg" };

	FOR(i, NUMTEXTURES)
	{
		tTextures[i].LoadTexture2D("data\\textures\\" + sTextureNames[i], true);
		tTextures[i].SetFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
	}
}

void initLight()
{
	cCamera = CFlyingCamera(glm::vec3(0.0f, 10.0f, 120.0f), glm::vec3(0.0f, 10.0f, 119.0f), glm::vec3(0.0f, 1.0f, 0.0f), 25.0f, 0.001f);
	cCamera.SetMovingKeys('W', 'S', 'A', 'D');

	dlSun = CDirectionalLight(glm::vec3(0.13f, 0.13f, 0.13f), glm::vec3(sqrt(2.0f) / 2, -sqrt(2.0f) / 2, 0), 1.0f);//sun intesity


	// Creating spotlight, position and direction will get updated every frame, that's why zero vectors
	
	slFlashLight = CSpotLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1, 15.0f, 0.017f);//spot light params
	slFlashLight1 = CSpotLight(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-100.0f, 10.0f, -100.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1, 15.0f, 0.001f);//spot light params
	slFlashLight2 = CSpotLight(glm::vec3(0.0f, 1.f, 0.0f), glm::vec3(-80.0f, 10.0f, -100.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1, 15.0f, 0.001f);//spot light params
	slFlashLight3 = CSpotLight(glm::vec3(0.0f, 0.f, 1.0f), glm::vec3(-60.0f, 10.0f, -100.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1, 15.0f, 0.001f);//spot light params

	plLight = CPointLight(glm::vec3(0.55f, 0.27f, 0.12f), glm::vec3(0.0f, 10.0f, 0.0f), 0.15f, 0.3f, 0.007f, 0.00008f);//luminescence of objects params
	plLight1 = CPointLight(glm::vec3(1.f, 0.f, 0.f), glm::vec3(100.0f, 10.0f, -100.0f), 0.15f, 0.3f, 0.007f, 0.00001f);//luminescence of objects params
	plLight2 = CPointLight(glm::vec3(0.f, 1.f, 0.f), glm::vec3(60.0f, 10.0f, -100.0f), 0.15f, 0.3f, 0.007f, 0.00001f);//luminescence of objects params
	plLight3 = CPointLight(glm::vec3(0.f, 0.f, 1.f), glm::vec3(20.0f, 10.0f, -100.0f), 0.15f, 0.3f, 0.007f, 0.00001f);//luminescence of objects params

	dlSun.fAmbient = 0;
}

void initBack()
{
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);//back colors
}

// Initializes OpenGL features that will be used.
// lpParam - Pointer to anything you want.
void InitScene(LPVOID lpParam)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	initSceneObjects();

	if (!PrepareShaderPrograms())
	{
		PostQuitMessage(0);
		return;
	}

	initTextures();
	initBack();
	initLight();
}

float fGlobalAngle;

// Renders whole scene.
// lpParam - Pointer to anything you want.
void RenderScene(LPVOID lpParam)
{
	// Typecast lpParam to COpenGLControl pointer
	COpenGLControl* oglControl = (COpenGLControl*)lpParam;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	spMain.UseProgram();

	glm::mat4 mModelMatrix, mView;

	// Set spotlight parameters

	glm::vec3 vSpotLightPos = cCamera.vEye;
	glm::vec3 vCameraDir = glm::normalize(cCamera.vView - cCamera.vEye);
	// Move down a little
	vSpotLightPos.y -= 3.2f;
	// Find direction of spotlight
	glm::vec3 vSpotLightDir = (vSpotLightPos + vCameraDir*75.0f) - vSpotLightPos;
	vSpotLightDir = glm::normalize(vSpotLightDir);
	// Find vector of horizontal offset
	glm::vec3 vHorVector = glm::cross(cCamera.vView - cCamera.vEye, cCamera.vUp);
	vSpotLightPos += vHorVector*3.3f;
	// Set it
	slFlashLight.vPosition = vSpotLightPos;
	slFlashLight.vDirection = vSpotLightDir;

	slFlashLight.SetUniformData(&spMain, "spotLight");

	slFlashLight1.SetUniformData(&spMain, "spotLight1");

	slFlashLight2.SetUniformData(&spMain, "spotLight2");

	slFlashLight3.SetUniformData(&spMain, "spotLight3");

	plLight.SetUniformData(&spMain, "pointLight");

	plLight1.SetUniformData(&spMain, "pointLight1");

	plLight2.SetUniformData(&spMain, "pointLight2");
	plLight3.SetUniformData(&spMain, "pointLight3");

	oglControl->ResizeOpenGLViewportFull();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	spMain.UseProgram();

	spMain.SetUniform("matrices.projMatrix", oglControl->GetProjectionMatrix());
	spMain.SetUniform("gSampler", 0);

	mView = cCamera.Look();
	spMain.SetUniform("matrices.viewMatrix", &mView);

	mModelMatrix = glm::translate(glm::mat4(1.0f), cCamera.vEye);

	spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
	spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mView*mModelMatrix)));

	glBindVertexArray(uiVAOs[0]);

	dlSun.SetUniformData(&spMain, "sunLight");

	spMain.SetUniform("vColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	spMain.SetUniform("matrices.modelMatrix", glm::mat4(1.0f));
	spMain.SetUniform("matrices.normalMatrix", glm::mat4(1.0f));

	// Render ground

	tTextures[0].BindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Render cubes
	glm::mat4 mModelToCamera;

	tTextures[3].BindTexture();
	float PI = float(atan(1.0)*4.0);

	FOR(j, 6)//stairs number
		FOR(i, 20)//cubes number
	{
		//glm::vec3 vPos = glm::vec3(cos(PI/4 * i) * 30.0f, 4.0f, sin(PI/4*i) * 30.0f);
		glm::vec3 vPos = glm::vec3(30.0f, 4.0f + 8.0f*j, 0.0f);
		mModelMatrix = glm::mat4(1.0f);
		mModelMatrix = glm::rotate(mModelMatrix, PI / 8 * i + PI / 16 * j, glm::vec3(0.0f, 1.0f, 0.0f));
		mModelMatrix = glm::translate(mModelMatrix, vPos);
		mModelMatrix = glm::scale(mModelMatrix, glm::vec3(8.0f, 8.0f, 8.0f));
		// We need to transform normals properly, it's done by transpose of inverse matrix of rotations and scales
		spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
		spMain.SetUniform("matrices.modelMatrix", mModelMatrix);
		glDrawArrays(GL_TRIANGLES, 6, 36);
	}

	// render torus 
	tTextures[1].BindTexture();
	// Now it's gonna float in the air
	glm::vec3 vPos = glm::vec3(0.0f, 10.0, 0.0f);
	mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
	mModelMatrix = glm::rotate(mModelMatrix, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
	spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
	glDrawArrays(GL_TRIANGLES, 42, iTorusFaces * 3);

	tTextures[2].BindTexture();
	mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
	mModelMatrix = glm::rotate(mModelMatrix, fGlobalAngle, glm::vec3(1.0f, 0.0f, 0.0f));
	spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
	spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
	glDrawArrays(GL_TRIANGLES, 42 + iTorusFaces * 3, iTorusFaces2 * 3);

	cCamera.Update();

	if (Keys::Onekey('F'))//flashlight
		slFlashLight.bOn = 1 - slFlashLight.bOn;

	if (Keys::Key('Q'))//day
	{
		dlSun.fAmbient += 0.001;
		dlSun.vColor.r += 0.001;
		dlSun.vColor.g += 0.001;
		dlSun.vColor.b += 0.001;
	}
	if (Keys::Key('E'))//night
	{
		dlSun.fAmbient -= 0.001;
		dlSun.vColor.r -= 0.001;
		dlSun.vColor.g -= 0.001;
		dlSun.vColor.b -= 0.001;
	}
	dlSun.fAmbient = min(max(0.0f, dlSun.fAmbient), 1.0f);
	dlSun.vColor.r = min(max(0.0f, dlSun.vColor.r), 1.0f);
	dlSun.vColor.g = min(max(0.0f, dlSun.vColor.g), 1.0f);
	dlSun.vColor.b = min(max(0.0f, dlSun.vColor.b), 1.0f);

	if(dlSun.fAmbient >= 0.5f)
		slFlashLight.bOn = 0;
	else
		slFlashLight.bOn = 1;

	if (Keys::Key('Z')) plLight.fAmbient += 0.01;//objects light
	if (Keys::Key('X')) plLight.fAmbient -= 0.01;
	plLight.fAmbient = min(max(0.0f, plLight.fAmbient), 1.0f);

	glEnable(GL_DEPTH_TEST);
	if (Keys::Onekey(VK_ESCAPE))PostQuitMessage(0);
	fGlobalAngle += appMain.sof(1.0f);
	oglControl->SwapBuffers();
}

// Releases OpenGL scene.
// lpParam - Pointer to anything you want.
void ReleaseScene(LPVOID lpParam)
{
	FOR(i, NUMTEXTURES)tTextures[i].DeleteTexture();

	spMain.DeleteProgram();
	FOR(i, NUMSHADERS)shShaders[i].DeleteShader();

	glDeleteVertexArrays(1, uiVAOs);
	vboSceneObjects.DeleteVBO();
}