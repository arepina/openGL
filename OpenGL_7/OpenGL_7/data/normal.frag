
uniform sampler2D colorTexture, depthTexture;


in Vertex
{
	vec2 texcoord;
} Vert;

layout(location = FRAG_OUTPUT0) out vec4 color;

void main(void)
{
		color = texture(colorTexture, Vert.texcoord);
}
