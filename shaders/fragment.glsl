#version 330 core
in vec3 fragmentColor;
in vec2 texturePosition;

out vec4 color;

uniform sampler2D tex;

void main() {
	color = texture(tex, texturePosition) * vec4(fragmentColor, 1.0);
}
