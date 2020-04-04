#version 330 core
in vec3 f_position;
in vec3 v_normal;
in vec2 v_texturePosition;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct PointLight {
	vec3 position;
	vec3 color;
	float linear;
	float quadratic;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	vec3 color;
	float innerAngle;
	float outerAngle;
};

struct DirectionalLight {
	vec3 direction;
	vec3 color;
};

uniform vec3 u_viewPosition;
uniform Material u_material;
uniform PointLight u_pointLight;
uniform SpotLight u_spotLight;
uniform DirectionalLight u_directionalLight;

out vec4 color;

vec3 computeLighting(vec3 normal, vec3 lightDirection, vec3 lightColor, vec3 diffuse, vec3 specular, float attenuation) {
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

	vec3 diffuseColor = diffuseIntensity * diffuse;
	vec3 specularColor = specularIntensity * specular;

	return attenuation * lightColor * (diffuseColor + specularColor);
}

void main() {
	vec3 normal = normalize(v_normal);
	vec3 vertexToPointLightDirection = normalize(u_pointLight.position - f_position);
	vec3 directionalLightDirection = normalize(-u_directionalLight.direction);
	vec3 vertexToSpotLightDirection = normalize(u_spotLight.position - f_position);

	float distance = length(u_pointLight.position - f_position);
	float pointLightAttenuation = 1.0 / (1 + u_pointLight.linear * distance + u_pointLight.quadratic * (distance * distance));

	float theta = dot(vertexToSpotLightDirection, normalize(u_spotLight.direction));
	float epsilon = u_spotLight.innerAngle - u_spotLight.outerAngle;
	float spotLightAttenuation = clamp((theta - u_spotLight.outerAngle) / epsilon, 0.0, 1.0);

	vec3 materialDiffuse = vec3(texture(u_material.diffuse, v_texturePosition));
	vec3 materialSpecular = vec3(texture(u_material.specular, v_texturePosition));

	vec3 combinedColor = materialDiffuse;
	combinedColor += computeLighting(normal, vertexToPointLightDirection, u_pointLight.color, materialDiffuse, materialSpecular, pointLightAttenuation);
	combinedColor += computeLighting(normal, vertexToSpotLightDirection, u_spotLight.color, materialDiffuse, materialSpecular, spotLightAttenuation);
	combinedColor += computeLighting(normal, directionalLightDirection, u_directionalLight.color, materialDiffuse, materialSpecular, 1);

	color = vec4(combinedColor, 1.0);
}
