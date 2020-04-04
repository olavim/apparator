#include <fstream>
#include <sstream>
#include <string>

#include "math.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include "texture.hpp"
#include "model.hpp"

namespace apr = apparator;

class Light {
	public:
		apr::Transform transform;
		apr::Vector3 color;

		Light(apr::Vector3 c) : color(c) {}
};

class PointLight : public Light {
	public:
		float linear;
		float quadratic;

		PointLight(apr::Vector3 _color, float _linear, float _quadratic)
			: Light(_color), linear(_linear), quadratic(_quadratic) {};
};

class SpotLight : public Light {
	public:
		float innerAngle;
		float outerAngle;

		SpotLight(apr::Vector3 _color, float _innerAngle, float _outerAngle)
			: Light(_color), innerAngle(_innerAngle), outerAngle(_outerAngle) {};
};

class DirectionalLight : public Light {
	public:
		DirectionalLight(apr::Vector3 _color) : Light(_color) {};
};

void apr::Model::addPart(const ModelPart& part) {
	this->parts.push_back(part);
}

void apr::Model::draw(const Camera* camera) {
	apr::Matrix4 worldMatrix = this->transform.matrix();
	apr::Matrix4 worldViewProjectionMatrix = worldMatrix * camera->matrix();
	apr::Matrix4 inverseTransposeWorldViewMatrix = worldMatrix;
	inverseTransposeWorldViewMatrix.transpose();
	inverseTransposeWorldViewMatrix.invert();

	PointLight pLight({1, 1, 1}, 0.045f, 0.0075f);
	pLight.transform.setTranslation({0, 3, 0});

	SpotLight sLight({1, 1, 1}, 0.9978f, 0.953f);
	sLight.transform.setTranslation(camera->transform.translation());
	sLight.transform.setRotation(camera->transform.rotation());

	DirectionalLight dLight({1, 1, 1});
	dLight.transform.setRotation({{1, 0, 0}, 1.5});

	for (unsigned int i = 0; i < this->parts.size(); i++) {
		ModelPart part = this->parts[i];

		part.mesh.bind();
		part.shader.bind();

		part.shader.setMatrix4("u_worldMatrix", worldMatrix);
		part.shader.setMatrix4("u_worldViewProjectionMatrix", worldViewProjectionMatrix);
		part.shader.setMatrix4("u_inverseTransposeWorldViewMatrix", inverseTransposeWorldViewMatrix);
		part.shader.setVector3("u_viewPosition", camera->transform.translation());

		if (part.material.type == MaterialType::COLORED) {
			part.shader.setVector3("u_material.ambient", part.material.ambientColor);
			part.shader.setVector3("u_material.diffuse", part.material.diffuseColor);
			part.shader.setVector3("u_material.specular", part.material.specularColor);
		}

		if (part.material.type == MaterialType::TEXTURED) {
			part.shader.setInt("u_material.diffuse", 0);
			glActiveTexture(GL_TEXTURE0);
			part.material.diffuseMap->bind();

			part.shader.setInt("u_material.specular", 1);
			glActiveTexture(GL_TEXTURE1);
			part.material.specularMap->bind();
		}

		part.shader.setFloat("u_material.shininess", part.material.shininess);

		part.shader.setVector3("u_pointLight.position", pLight.transform.translation());
		part.shader.setVector3("u_pointLight.color", pLight.color);
		part.shader.setFloat("u_pointLight.linear", pLight.linear);
		part.shader.setFloat("u_pointLight.quadratic", pLight.quadratic);

		part.shader.setVector3("u_spotLight.position", sLight.transform.translation());
		part.shader.setVector3("u_spotLight.direction", sLight.transform.forward());
		part.shader.setVector3("u_spotLight.color", sLight.color);
		part.shader.setFloat("u_spotLight.innerAngle", sLight.innerAngle);
		part.shader.setFloat("u_spotLight.outerAngle", sLight.outerAngle);

		part.shader.setVector3("u_directionalLight.direction", dLight.transform.forward());
		part.shader.setVector3("u_directionalLight.color", dLight.color);

		glDrawArrays(GL_TRIANGLES, 0, part.mesh.getVertexCount());
	}
}
