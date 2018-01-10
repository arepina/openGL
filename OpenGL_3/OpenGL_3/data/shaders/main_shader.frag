#version 330

smooth in vec2 vTexCoord;
smooth in vec3 vNormal;
smooth in vec3 vEyeSpacePos;
smooth in vec3 vWorldPos;
out vec4 outputColor;

uniform sampler2D gSampler;
uniform vec4 vColor;

#include "dirLight.frag"
#include "spotLight.frag"
#include "pointLight.frag"

uniform DirectionalLight sunLight;
uniform SpotLight spotLight;
uniform PointLight pointLight;

uniform SpotLight spotLight1;
uniform SpotLight spotLight2;
uniform SpotLight spotLight3;

uniform PointLight pointLight1;
uniform PointLight pointLight2;
uniform PointLight pointLight3;

void main()
{
	vec3 vNormalized = normalize(vNormal);
	
	vec4 vTexColor = texture2D(gSampler, vTexCoord);
	vec4 vMixedColor = vTexColor*vColor;
	vec4 vDirLightColor = getDirectionalLightColor(sunLight, vNormal);
	vec4 vSpotlightColor = GetSpotLightColor(spotLight, vWorldPos);
	vec4 vSpotlightColor1 = GetSpotLightColor(spotLight1, vWorldPos);
	vec4 vSpotlightColor2 = GetSpotLightColor(spotLight2, vWorldPos);
	vec4 vSpotlightColor3 = GetSpotLightColor(spotLight3, vWorldPos);
	vec4 vPointlightColor = getPointLightColor(pointLight, vWorldPos, vNormalized);
	vec4 vPointlightColor1 = getPointLightColor(pointLight1, vWorldPos, vNormalized);
	vec4 vPointlightColor2 = getPointLightColor(pointLight2, vWorldPos, vNormalized);
	vec4 vPointlightColor3 = getPointLightColor(pointLight3, vWorldPos, vNormalized);
	outputColor = vMixedColor*(vDirLightColor+vSpotlightColor+vSpotlightColor1+vSpotlightColor2+vSpotlightColor3+vPointlightColor+vPointlightColor1+vPointlightColor2+vPointlightColor3);
}