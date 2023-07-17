#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec4 Color;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	TexCoords = aTexCoords;
	Color = vec4(0.7, 0.3, 0.2, 1.0);
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

in vec4 Color;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

in vec2 TexCoords;

void main()
{
	FragColor = mix(texture(texture1, TexCoords), texture(texture2, TexCoords), 0.2);
}