#version 330 core
in vec3 f_position;
in vec3 v_color;
in vec3 v_normal;
in vec2 v_texturePosition;

uniform sampler2D u_texture;
uniform vec3 u_lightPosition;
uniform vec3 u_viewPosition;

out vec4 color;

const vec3 ambientColor = vec3(0.3, 0.3, 0.3);
const vec3 lightColor = vec3(1, 1, 1);

void main() {
	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(u_lightPosition - f_position);
	vec3 reflectedLightDirection = reflect(-lightDirection, normal);
	vec3 viewDirection = normalize(u_viewPosition - f_position);

	/* We want a surface to be brighter the more directly light rays are hitting it. The dot product
	 * is useful here.

	 * The dot product of two normalized vectors is in the range [-1, 1], where 1 means the light is
	 * "directly above", and -1 means "directly below" or "behind". The dot product is 0 when the vectors
	 * are in a 90 degree angle. This all means we get bigger values when the light is closer to being
	 * "directly above", and zero or smaller values when the light is not hitting the surface.
	 */
	float diffuseIntensity = max(dot(normal, lightDirection), 0.0);
	vec3 diffuseColor = diffuseIntensity * lightColor;

	/* Calculating the specular intensitity is similar to how we calculated the diffuse. The difference
	 * here is that we determine the intensity based on the angle between the reflected light ray and
	 * the view/eye position.
	 */
	float specularIntensity = pow(max(dot(viewDirection, reflectedLightDirection), 0.0), 32);
	vec3 specularColor = 0.5 * specularIntensity * lightColor;

	vec4 combinedLightColor = vec4((diffuseColor + specularColor + ambientColor) * v_color, 1.0);
	vec4 texturePixelColor = texture(u_texture, v_texturePosition);

	// color = texturePixelColor * combinedLightColor;
	color = combinedLightColor;
}
