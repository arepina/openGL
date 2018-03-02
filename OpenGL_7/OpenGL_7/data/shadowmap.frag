uniform sampler2DShadow depthTexture;


uniform struct Light
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
} light;


uniform struct Material
{
	sampler2D texture;

	vec4  ambient;
	vec4  diffuse;
	vec4  specular;
	vec4  emission;
	float shininess;
} material;

in Vertex
{
	vec2 texcoord;
	vec4 smcoord;
	vec3 normal;
	vec3 lightDir;
	vec3 viewDir;
} Vert;

layout(location = FRAG_OUTPUT0) out vec4 color;

float PCF(in vec4 smcoord)
{
	float res = 0.0;

	res += textureProjOffset(depthTexture, smcoord, ivec2(-1,-1));
	res += textureProjOffset(depthTexture, smcoord, ivec2( 0,-1));
	res += textureProjOffset(depthTexture, smcoord, ivec2( 1,-1));
	res += textureProjOffset(depthTexture, smcoord, ivec2(-1, 0));
	res += textureProjOffset(depthTexture, smcoord, ivec2( 0, 0));
	res += textureProjOffset(depthTexture, smcoord, ivec2( 1, 0));
	res += textureProjOffset(depthTexture, smcoord, ivec2(-1, 1));
	res += textureProjOffset(depthTexture, smcoord, ivec2( 0, 1));
	res += textureProjOffset(depthTexture, smcoord, ivec2( 1, 1));

	return (res / 9.0);
}

void main(void)
{
	
	vec3 normal   = normalize(Vert.normal);
	vec3 lightDir = normalize(Vert.lightDir);
	vec3 viewDir  = normalize(Vert.viewDir);

		float shadow  = PCF(Vert.smcoord);

		color = material.emission;

		color += material.ambient * light.ambient;

		float NdotL = max(dot(normal, lightDir), 0.0);
	color += material.diffuse * light.diffuse * NdotL;

		float RdotVpow = max(pow(dot(reflect(-lightDir, normal), viewDir), material.shininess), 0.0);
	color += material.specular * light.specular * RdotVpow;

		color *= texture(material.texture, Vert.texcoord) * shadow;
}
