layout(location = VERT_POSITION) in vec3 position;
layout(location = VERT_TEXCOORD) in vec2 texcoord;

out Vertex
{
	vec2 texcoord;
} Vert;

void main(void)
{
	
	Vert.texcoord = texcoord;

	gl_Position = vec4(position, 1.0);
}
