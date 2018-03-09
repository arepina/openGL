
layout(location = VERT_POSITION) in vec3 position;
layout(location = VERT_TEXCOORD) in vec2 texcoord;
layout(location = VERT_NORMAL)   in vec3 normal;


uniform struct Transform
{
	mat4 model;
	mat4 viewProjection;
	mat4 light;
	mat3 normal;
	vec3 viewPosition;
} transform;


uniform struct Light
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
} light;


out Vertex
{
	vec2 texcoord;
	vec4 smcoord;
	vec3 normal;
	vec3 lightDir;
	vec3 viewDir;
} Vert;

void main(void)
{
	
	vec4 vertex   = transform.model * vec4(position, 1.0);

	
	Vert.smcoord  = transform.light * vertex;
	
        
	Vert.texcoord = texcoord;
	
	
	Vert.normal   = transform.normal * normal;
	
	
	Vert.lightDir = vec3(light.position);
	
	
	Vert.viewDir  = transform.viewPosition - vec3(vertex);

	
	gl_Position = transform.viewProjection * vertex;
}
