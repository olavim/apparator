#version 330 core
in vec3 f_position;
in vec3 v_normal;
in vec2 v_texturePosition;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 u_lightPosition;
uniform vec3 u_viewPosition;
uniform Material u_material;
uniform Light u_light;

out vec4 color;

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

	/* Calculating the specular intensitity is similar to how we calculated the diffuse. The difference
	 * here is that we determine the intensity based on the angle between the reflected light ray and
	 * the view/eye position.
	 */
	float specularIntensity = pow(max(dot(viewDirection, reflectedLightDirection), 0.0), u_material.shininess);

	vec3 ambientColor = u_light.ambient * u_material.ambient;
	vec3 diffuseColor = u_light.diffuse * (diffuseIntensity * u_material.diffuse);
	vec3 specularColor = u_light.specular * (specularIntensity * u_material.specular);

	vec4 combinedLightColor = vec4(diffuseColor + specularColor + ambientColor, 1.0);

	// color = texturePixelColor * combinedLightColor;
	color = combinedLightColor;
}
