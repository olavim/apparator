#version 330 core
layout(location = 0) in vec3 in_vertexPosition;
layout(location = 1) in vec3 in_vertexNormal;
layout(location = 2) in vec2 in_texturePosition;

uniform mat4 u_worldMatrix;
uniform mat4 u_worldViewProjectionMatrix;
uniform mat4 u_inverseTransposeWorldViewMatrix;

out vec3 f_position;
out vec3 v_normal;
out vec2 v_texturePosition;

void main() {
	gl_Position = vec4(in_vertexPosition, 1) * u_worldViewProjectionMatrix;
	f_position = vec3(vec4(in_vertexPosition, 1.0) * u_worldMatrix);
	v_normal = in_vertexNormal * mat3(u_inverseTransposeWorldViewMatrix);
	v_texturePosition = in_texturePosition;
}
