#pragma once

#include "vertexBufferObject.h"

extern glm::vec3 vCubeVertices[36];
extern unsigned int iCubeindices[36];
extern glm::vec2 vCubeTexCoords[6];

extern glm::vec3 vGround[6];

extern glm::vec3 vPyramidVertices[5];
extern unsigned int iPyramidindices[18];
extern glm::vec2 vPyramidTexCoords[5];
extern glm::vec3 vPyramidNormals[5];

//extern glm::vec3 vCubeNormals[6];
//extern glm::vec3 vCubeVertices2[24];
//extern glm::vec3 vCubeVertices2[8];



int GenerateTorus(CVertexBufferObject &vboDest, float fRadius, float fTubeRadius, int iSubDivAround, int iSubDivTube);
int GenerateCylinder(CVertexBufferObject &vboDest, float fRadius, float fHeight, int iSubDivAround, float fMapU = 1.0f, float fMapV = 1.0f);
void AddSceneObjects(CVertexBufferObject& vboDest);
void AddCube(CVertexBufferObject& vboDest);
void AddPyramid(CVertexBufferObject& vboDest);
extern int iTorusFaces, iTorusFaces2, iCylinderFaces;