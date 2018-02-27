#version 330

smooth in vec2 vTexCoord;
smooth in vec3 vNormal;
smooth in vec4 vEyeSpacePos;
smooth in vec3 vWorldPos;
out vec4 outputColor;

uniform sampler2D gSampler;
uniform vec4 vColor;

#include "dirLight.frag"
#include "pointLight.frag"

uniform DirectionalLight sunLight;
uniform PointLight pointLight;
uniform PointLight pointLight1;
uniform PointLight pointLight2;

uniform vec3 vEyePosition;

uniform Material matActive;

#include "shadows.frag"

smooth in vec4 ShadowCoord;
uniform sampler2D shadowMap;


void main()
{
	vec4 vTexColor = texture2D(gSampler, vTexCoord);
	vec4 vMixedColor = vTexColor*vColor;
  
  vec3 vNormalized = normalize(vNormal);

  float visibility = GetVisibility(shadowMap, ShadowCoord);

  vec4 vDiffuseColor = GetDirectionalLightColor(sunLight, vNormalized, visibility);
  vec4 vPointlightColor = getPointLightColor(pointLight, vWorldPos, vNormalized, visibility);
vec4 vPointlightColor1 = getPointLightColor(pointLight1, vWorldPos, vNormalized, visibility);
vec4 vPointlightColor2 = getPointLightColor(pointLight2, vWorldPos, vNormalized, visibility);
  //vec4 vSpecularColor = GetSpecularColor(vWorldPos, vEyePosition, matActive, sunLight, vNormalized, visibility);


	
  //outputColor = vMixedColor * vDiffuseColor;// + vSpecularColor;

	outputColor = vMixedColor * (vDiffuseColor+ vPointlightColor+vPointlightColor1+vPointlightColor2);

}