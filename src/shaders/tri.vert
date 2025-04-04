#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aMaterialColor;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out vec3 MaterialColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 worldPos = model * vec4(aPos, 1.0);
	FragPos = worldPos.xyz;

	mat3 normalMatrix = mat3(transpose(inverse(model)));
	Normal = normalize(normalMatrix * aNormal);

	TexCoord = aTexCoord;
	MaterialColor = aMaterialColor;

	gl_Position = projection * view * worldPos;
}
