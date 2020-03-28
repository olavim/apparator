#version 330 core
in vec3 f_position;
in vec3 v_color;
in vec3 v_normal;
in vec2 v_texturePosition;

uniform sampler2D u_texture;
uniform vec3 u_lightPosition;

out vec4 color;

const vec3 ambientColor = vec3(0.3, 0.3, 0.3);
const vec3 lightColor = vec3(1, 1, 1);

void main() {
	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(u_lightPosition - f_position);

	/* We want a surface to be brighter the more directly light rays are hitting it. The dot product
	 * is useful here.

	 * The dot product of two normalized vectors is in the range [-1, 1], where 1 means the light is
	 * "directly above", and -1 means "directly below" or "behind". The dot product is 0 when the vectors
	 * are in a 90 degree angle. This all means we get bigger values when the light is closer to being
	 * "directly above", and zero or smaller values when the light is not hitting the surface.
	 */
	float diffuseBrightness = max(dot(normal, lightDirection), 0.0);
	vec3 diffuseColor = diffuseBrightness * lightColor * v_color;

	vec4 combinedLightColor = vec4(diffuseColor + ambientColor, 1.0);
	vec4 texturePixelColor = texture(u_texture, v_texturePosition);

	color = texturePixelColor * combinedLightColor;
}
