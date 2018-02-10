#include "common_header.h"

#include "win_OpenGLApp.h"

#include "shaders.h"
#include "texture.h"
#include "vertexBufferObject.h"

#include "flyingCamera.h"

#include "freeTypeFont.h"

#include "skybox.h"
#include "dirLight.h"
#include "material.h"

#include "assimp_model.h"

#include "heightmap.h"

#include "static_geometry.h"

#include "particle_system_tf.h"


CVertexBufferObject vboSceneObjects;
UINT uiVAOSceneObjects;

CFreeTypeFont ftFont;

CSkybox sbMainSkybox;
CFlyingCamera cCamera;

CDirectionalLight dlSun;

CMaterial matShiny;
CAssimpModel amModels[10];

CMultiLayeredHeightmap hmWorld;

int iTorusFaces;

bool bDisplayNormals = false; // Do not display normals by default

CParticleSystemTransformFeedback psMainParticleSystem;

/*-----------------------------------------------

Name:    InitScene

Params:  lpParam - Pointer to anything you want.

Result:  Initializes OpenGL features that will
		 be used.

/*---------------------------------------------*/

void InitScene(LPVOID lpParam)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	if (!PrepareShaderPrograms())
	{
		PostQuitMessage(0);
		return;
	}

	LoadAllTextures();

	vboSceneObjects.CreateVBO();
	glGenVertexArrays(1, &uiVAOSceneObjects); // Create one VAO
	glBindVertexArray(uiVAOSceneObjects);

	vboSceneObjects.BindVBO();

	iTorusFaces = GenerateTorus(vboSceneObjects, 7.0f, 2.0f, 20, 20);
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


	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	// Here we load font with pixel size 32 - this means that if we print with size above 32, the quality will be low
	ftFont.LoadSystemFont("arial.ttf", 32);
	ftFont.SetShaderProgram(&spFont2D);

	cCamera = CFlyingCamera(glm::vec3(0.0f, 30.0f, 100.0f), glm::vec3(0.0f, 30.0f, 99.0f), glm::vec3(0.0f, 1.0f, 0.0f), 20.0f, 0.05f);
	cCamera.SetMovingKeys('W', 'S', 'A', 'D');

	sbMainSkybox.LoadSkybox("data\\skyboxes\\bluefreeze\\", "bluefreeze_front.jpg", "bluefreeze_back.jpg", "bluefreeze_right.jpg", "bluefreeze_left.jpg", "bluefreeze_top.jpg", "bluefreeze_top.jpg");

	dlSun = CDirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(sqrt(2.0f) / 2, -sqrt(2.0f) / 2, 0), 0.5f, 0);

	amModels[0].LoadModelFromFile("data\\models\\house\\house.3ds");
	amModels[1].LoadModelFromFile("data\\models\\treasure_chest_obj\\treasure_chest.obj");
	amModels[2].LoadModelFromFile("data\\models\\cat\\cat.obj");
	amModels[3].LoadModelFromFile("data\\models\\Wolf\\Wolf.obj");
	amModels[4].LoadModelFromFile("data\\models\\fountainOBJ\\fountain.obj");

	CAssimpModel::FinalizeVBO();
	CMultiLayeredHeightmap::LoadTerrainShaderProgram();
	hmWorld.LoadHeightMapFromImage("data\\worlds\\world_like_in_21th.bmp");

	matShiny = CMaterial(1.0f, 32.0f);

	psMainParticleSystem.InitalizeParticleSystem();

	psMainParticleSystem.SetGeneratorProperties(
		glm::vec3(-90.87f, 53.15f, -33.27f), // Where the particles are generated
		glm::vec3(-10, 0, -10), // Minimal velocity
		glm::vec3(10, 20, 10), // Maximal velocity
		glm::vec3(0, -20, 0), // Gravity force applied to particles
		glm::vec3(0.0f, 0.25f, 1.0f), // Color (dark blue)
		1.5f, // Minimum lifetime in seconds
		3.0f, // Maximum lifetime in seconds
		0.25f, // Rendered size
		0.02f, // Spawn every 0.05 seconds
		30); // And spawn 30 particles
}

static float fGlobalAngleNew;

/*-----------------------------------------------

Name:    RenderScene

Params:  lpParam - Pointer to anything you want.

Result:  Renders whole scene.

/*---------------------------------------------*/

void RenderScene(LPVOID lpParam)
{
	// Typecast lpParam to COpenGLControl pointer
	COpenGLControl* oglControl = (COpenGLControl*)lpParam;
	oglControl->ResizeOpenGLViewportFull();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	spMain.UseProgram();

	spMain.SetUniform("matrices.projMatrix", oglControl->GetProjectionMatrix());
	spMain.SetUniform("matrices.viewMatrix", cCamera.Look());

	spMain.SetUniform("gSampler", 0);

	spMain.SetUniform("matrices.modelMatrix", glm::mat4(1.0));
	spMain.SetUniform("matrices.normalMatrix", glm::mat4(1.0));
	spMain.SetUniform("vColor", glm::vec4(1, 1, 1, 1));

	// This values will set the darkness of whole scene, that's why such name of variable :D
	static float fAngleOfDarkness = 45.0f;
	// You can play with direction of light with '+' and '-' key
	if (Keys::Key(VK_ADD))fAngleOfDarkness += appMain.sof(90);
	if (Keys::Key(VK_SUBTRACT))fAngleOfDarkness -= appMain.sof(90);
	// Set the directional vector of light
	dlSun.vDirection = glm::vec3(-sin(fAngleOfDarkness*3.1415f / 180.0f), -cos(fAngleOfDarkness*3.1415f / 180.0f), 0.0f);

	dlSun.iSkybox = 1;
	dlSun.SetUniformData(&spMain, "sunLight");

	spMain.SetUniform("matrices.modelMatrix", glm::translate(glm::mat4(1.0), cCamera.vEye));
	sbMainSkybox.RenderSkybox();

	dlSun.iSkybox = 0;
	dlSun.SetUniformData(&spMain, "sunLight");

	spMain.SetUniform("matrices.modelMatrix", glm::mat4(1.0));

	spMain.SetUniform("vEyePosition", cCamera.vEye);
	matShiny.SetUniformData(&spMain, "matActive");

	// Render a house

	CAssimpModel::BindModelsVAO();

	glm::mat4 mModel = glm::translate(glm::mat4(1.0), glm::vec3(40.0f, 17.0f, 0));
	mModel = glm::scale(mModel, glm::vec3(8, 8, 8));

	spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
	amModels[0].RenderModel();

	// ... and a treasure chest

	mModel = glm::translate(glm::mat4(1.0), glm::vec3(-10.0f, 17.5f, 0));
	mModel = glm::scale(mModel, glm::vec3(0.5f, 0.5f, 0.5f));

	spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
	amModels[1].RenderModel();

	//Render cat and wolf
	mModel = glm::translate(glm::mat4(1.0), glm::vec3(-30.0f, 17.5, 0));
	mModel = glm::scale(mModel, glm::vec3(10.f, 10.f, 10.f));

	spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
	amModels[2].RenderModel();

	mModel = glm::translate(glm::mat4(1.0), glm::vec3(-20.0f, 17.5, 0));
	mModel = glm::scale(mModel, glm::vec3(5.f, 5.f, 5.f));

	spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
	amModels[3].RenderModel();

	// Render fountain

	mModel = glm::translate(glm::mat4(1.0), glm::vec3(-90.87f, 35.15f, -33.27f));
	mModel = glm::scale(mModel, glm::vec3(0.5f, 0.5f, 0.5f));

	spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
	amModels[4].RenderModel();

	// Render 3 rotated tori to create interesting object

	tTextures[5].BindTexture();
	glBindVertexArray(uiVAOSceneObjects);

	static float fGlobalAngle = 0.0f;

	FOR(i, 2)
	{
		glm::vec3 vCenter = glm::vec3(-30 + i * 40, 30, -20);
		mModel = glm::translate(glm::mat4(1.0), vCenter);
		if (i == 0)mModel = glm::rotate(mModel, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		glDrawArrays(GL_TRIANGLES, 0, iTorusFaces * 3);

		mModel = glm::translate(glm::mat4(1.0), vCenter + glm::vec3(0.01f, 0.0f, 0.0f));
		if (i == 0)mModel = glm::rotate(mModel, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		mModel = glm::rotate(mModel, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		glDrawArrays(GL_TRIANGLES, 0, iTorusFaces * 3);

		mModel = glm::translate(glm::mat4(1.0), vCenter + glm::vec3(0.00f, 0.01f, 0.0f));

		if (i == 0)mModel = glm::rotate(mModel, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		mModel = glm::rotate(mModel, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		spMain.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		glDrawArrays(GL_TRIANGLES, 0, iTorusFaces * 3);
	}

	//fGlobalAngle += appMain.sof(10.0f);
	fGlobalAngle += fGlobalAngleNew;
	if (fGlobalAngle > 100)
		fGlobalAngle = 0;

	// Now we're going to render terrain

	hmWorld.SetRenderSize(300.0f, 35.0f, 300.0f);
	CShaderProgram* spTerrain = CMultiLayeredHeightmap::GetShaderProgram();

	spTerrain->UseProgram();

	spTerrain->SetUniform("matrices.projMatrix", oglControl->GetProjectionMatrix());
	spTerrain->SetUniform("matrices.viewMatrix", cCamera.Look());

	spTerrain->SetUniform("vEyePosition", cCamera.vEye);
	matShiny.SetUniformData(spTerrain, "matActive");

	// We bind all 5 textures - 3 of them are textures for layers, 1 texture is a "path" texture, and last one is
	// the places in heightmap where path should be and how intense should it be
	FOR(i, 5)
	{
		char sSamplerName[256];
		sprintf_s(sSamplerName, "gSampler[%d]", i);//_s
		tTextures[i].BindTexture(i);
		spTerrain->SetUniform(sSamplerName, i);
	}

	// ... set some uniforms
	spTerrain->SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", glm::mat4(1.0));
	spTerrain->SetUniform("vColor", glm::vec4(1, 1, 1, 1));

	dlSun.SetUniformData(spTerrain, "sunLight");

	// ... and finally render heightmap
	hmWorld.RenderHeightmap();

	if (bDisplayNormals)
	{
		spNormalDisplayer.UseProgram();
		spNormalDisplayer.SetUniform("fNormalLength", 1.0f);
		spNormalDisplayer.SetUniform("matrices.projMatrix", oglControl->GetProjectionMatrix());
		spNormalDisplayer.SetUniform("matrices.viewMatrix", cCamera.Look());

		CAssimpModel::BindModelsVAO();

		// ... Render the house again

		glm::mat4 mModel = glm::translate(glm::mat4(1.0), glm::vec3(40.0f, 17.0f, 0));
		mModel = glm::scale(mModel, glm::vec3(8, 8, 8));

		spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		amModels[0].RenderModel(GL_POINTS);

		// ... and the treasure chest again

		mModel = glm::translate(glm::mat4(1.0), glm::vec3(-10.0f, 17.5f, 0));
		mModel = glm::scale(mModel, glm::vec3(0.5f, 0.5f, 0.5f));

		spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		amModels[1].RenderModel(GL_POINTS);

		//Render cat and wolf again
		mModel = glm::translate(glm::mat4(1.0), glm::vec3(-30.0f, 17.5, 0));
		mModel = glm::scale(mModel, glm::vec3(10.f, 10.f, 10.f));

		spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		amModels[2].RenderModel(GL_POINTS);

		mModel = glm::translate(glm::mat4(1.0), glm::vec3(-20.0f, 17.5, 0));
		mModel = glm::scale(mModel, glm::vec3(5.f, 5.f, 5.f));

		spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		amModels[3].RenderModel(GL_POINTS);

		// Render fountain again

		mModel = glm::translate(glm::mat4(1.0), glm::vec3(-90.87f, 35.15f, -33.27f));
		mModel = glm::scale(mModel, glm::vec3(0.5f, 0.5f, 0.5f));

		spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
		amModels[4].RenderModel(GL_POINTS);

		glBindVertexArray(uiVAOSceneObjects);

		FOR(i, 2)
		{
			glm::vec3 vCenter = glm::vec3(-30 + i * 40, 30, -20);
			mModel = glm::translate(glm::mat4(1.0), vCenter);
			if (i == 0)mModel = glm::rotate(mModel, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
			spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
			glDrawArrays(GL_POINTS, 0, iTorusFaces * 3);

			mModel = glm::translate(glm::mat4(1.0), vCenter + glm::vec3(0.01f, 0.0f, 0.0f));
			if (i == 0)mModel = glm::rotate(mModel, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
			mModel = glm::rotate(mModel, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
			glDrawArrays(GL_POINTS, 0, iTorusFaces * 3);

			mModel = glm::translate(glm::mat4(1.0), vCenter + glm::vec3(0.00f, 0.01f, 0.0f));

			if (i == 0)mModel = glm::rotate(mModel, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
			mModel = glm::rotate(mModel, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", mModel);
			glDrawArrays(GL_POINTS, 0, iTorusFaces * 3);
		}

		spNormalDisplayer.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", hmWorld.GetScaleMatrix());
		hmWorld.RenderHeightmapForNormals();
	}

	tTextures[6].BindTexture();

	psMainParticleSystem.SetMatrices(oglControl->GetProjectionMatrix(), cCamera.vEye, cCamera.vView, cCamera.vUp);

	psMainParticleSystem.UpdateParticles(appMain.sof(1.0f));
	psMainParticleSystem.RenderParticles();

	cCamera.Update();

	// Print something over scene

	spFont2D.UseProgram();
	glDisable(GL_DEPTH_TEST);
	spFont2D.SetUniform("matrices.projMatrix", oglControl->GetOrthoMatrix());

	int w = oglControl->GetViewportWidth(), h = oglControl->GetViewportHeight();

	spFont2D.SetUniform("vColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ftFont.Print("OpenGL_5 2017-2018", 20, 20, 24);
	ftFont.Print("Repina Anastasia BSE143", 20, 45, 24);

	ftFont.PrintFormatted(20, h - 30, 20, "FPS: %d", oglControl->GetFPS());

	ftFont.PrintFormatted(20, h - 80, 20, "Specular Intensity: %.2f (Press 'Q' and 'E' to change)", matShiny.fSpecularIntensity);
	if (Keys::Key('Q'))matShiny.fSpecularIntensity -= appMain.sof(0.2f);
	if (Keys::Key('E'))matShiny.fSpecularIntensity += appMain.sof(0.2f);

	ftFont.PrintFormatted(20, h - 110, 20, "Specular Power: %.2f (Press 'Z' and 'C' to change)", matShiny.fSpecularPower);
	if (Keys::Key('Z'))matShiny.fSpecularPower -= appMain.sof(8.0f);
	if (Keys::Key('C'))matShiny.fSpecularPower += appMain.sof(8.0f);

	ftFont.PrintFormatted(20, h - 140, 20, "Displaying Normals: %s (Press 'N' to toggle)", bDisplayNormals ? "Yes" : "Nope");
	if (Keys::Onekey('N'))bDisplayNormals = !bDisplayNormals;

	ftFont.PrintFormatted(20, h - 170, 20, "Angle of darkness: (Press '+', '-' to change)");

	ftFont.PrintFormatted(900, h - 80, 20, "Color change: (Press '1', '2', '3' to change)");
	if (Keys::Key('1'))
	{
		psMainParticleSystem.SetColor(glm::vec3(1.0f, 0.0f, 0.f)); // red
	}
	if (Keys::Key('2'))
	{
		psMainParticleSystem.SetColor(glm::vec3(0.f, 1.f, 0.f)); // green
	}
	if (Keys::Key('3'))
	{
		psMainParticleSystem.SetColor(glm::vec3(0.f, 0.f, 1.f)); // blue
	}
	ftFont.PrintFormatted(900, h - 110, 20, "Particles number %d (Press '4', '5' to change)", psMainParticleSystem.GetNumParticles());
	if (Keys::Key('4'))
	{
		psMainParticleSystem.SetNumParticles(psMainParticleSystem.GetNumParticles() + 500);
	}
	if (Keys::Key('5'))
	{
		psMainParticleSystem.SetNumParticles(psMainParticleSystem.GetNumParticles() - 500);
	}
	ftFont.PrintFormatted(900, h - 140, 20, "Speed particles: %.2f (Press '6', '7' to change)", psMainParticleSystem.GetSpeed());
	if (Keys::Key('6'))
	{
		glm::vec3 speed = psMainParticleSystem.GetSpeed();
		speed += 0.1;
		psMainParticleSystem.SetSpeed(speed);
	}
	if (Keys::Key('7'))
	{
		glm::vec3 speed = psMainParticleSystem.GetSpeed();
		speed -= 0.1;
		psMainParticleSystem.SetSpeed(speed);
	}
	ftFont.PrintFormatted(900, h - 170, 20, "Speed torus: %.2f (Press '8', '9' to change)", fGlobalAngleNew);
	if (Keys::Key('8'))
	{
		fGlobalAngleNew += appMain.sof(1.0f);
	}
	if (Keys::Key('9'))
	{
		fGlobalAngleNew -= appMain.sof(1.0f);
	}

	glEnable(GL_DEPTH_TEST);
	if (Keys::Onekey(VK_ESCAPE))PostQuitMessage(0);

	oglControl->SwapBuffers();
}

/*-----------------------------------------------

Name:    ReleaseScene

Params:  lpParam - Pointer to anything you want.

Result:  Releases OpenGL scene.

/*---------------------------------------------*/

void ReleaseScene(LPVOID lpParam)
{
	FOR(i, NUMTEXTURES)tTextures[i].DeleteTexture();
	sbMainSkybox.DeleteSkybox();

	spMain.DeleteProgram();
	spOrtho2D.DeleteProgram();
	spFont2D.DeleteProgram();
	FOR(i, NUMSHADERS)shShaders[i].DeleteShader();
	ftFont.DeleteFont();

	glDeleteVertexArrays(1, &uiVAOSceneObjects);
	vboSceneObjects.DeleteVBO();

	hmWorld.ReleaseHeightmap();
	CMultiLayeredHeightmap::ReleaseTerrainShaderProgram();
}