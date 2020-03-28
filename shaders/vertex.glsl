#version 330 core
layout(location = 0) in vec3 in_vertexPosition;
layout(location = 1) in vec3 in_vertexNormal;
layout(location = 2) in vec3 in_vertexColor;
layout(location = 3) in vec2 in_texturePosition;

uniform mat4 u_worldMatrix;
uniform mat4 u_worldViewProjectionMatrix;
uniform mat4 u_inverseTransposeWorldViewMatrix;

out vec3 f_position;
out vec3 v_color;
out vec3 v_normal;
out vec2 v_texturePosition;

void main() {
	gl_Position = vec4(in_vertexPosition, 1) * u_worldViewProjectionMatrix;
	f_position = vec3(u_worldMatrix * vec4(in_vertexPosition, 1.0));
	v_color = in_vertexColor;
	v_normal = mat3(u_inverseTransposeWorldViewMatrix) * in_vertexNormal;
	v_texturePosition = in_texturePosition;
}
