#pragma once

#include "vertexBufferObject.h"

extern glm::vec3 vCubeVertices[36];
extern unsigned int iCubeindices[36];
extern glm::vec2 vCubeTexCoords[6];
extern glm::vec3 vGround[6];
extern glm::vec3 vPyramidVertices[16];
extern unsigned int iPyramidindices[16];
extern glm::vec2 vPyramidTexCoords[3];
extern glm::vec3 vPyramid[12];
//extern glm::vec3 vCubeNormals[6];
//extern glm::vec3 vCubeVertices2[24];
//extern glm::vec3 vCubeVertices2[8];



int GenerateTorus(CVertexBufferObject &vboDest, float fRadius, float fTubeRadius, int iSubDivAround, int iSubDivTube);
int GenerateCylinder(CVertexBufferObject &vboDest, float fRadius, float fHeight, int iSubDivAround, float fMapU = 1.0f, float fMapV = 1.0f);
void AddSceneObjects(CVertexBufferObject& vboDest);
void AddCube(CVertexBufferObject& vboDest);
void AddPyramid(CVertexBufferObject& vboDest);
extern int iTorusFaces, iTorusFaces2, iCylinderFaces;