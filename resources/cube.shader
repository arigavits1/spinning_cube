#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec4 aColor;
out vec2 TexCoords;
out float textureMergeAmount;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;
uniform float textureMergeAmountUniform;

void main()
{
	textureMergeAmount = textureMergeAmountUniform;
	TexCoords = aTexCoords;
	aColor = vec4(color, 1.0);
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

in vec4 aColor;
out vec4 FragColor;
in float textureMergeAmount;

uniform sampler2D texture1;
uniform sampler2D texture2;

in vec2 TexCoords;

void main()
{
	FragColor = mix(texture(texture1, TexCoords), texture(texture2, TexCoords), textureMergeAmount) * aColor;
}
