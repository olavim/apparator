#include <fstream>
#include <sstream>
#include <string>

#include "math.hpp"
#include "camera.hpp"
#include "texture.hpp"
#include "model.hpp"

namespace apr = apparator;

void apr::Model::addPart(const ModelPart& part) {
	this->parts.push_back(part);
}

void apr::Model::draw(const Camera* camera) {
	apr::Matrix4 worldMatrix = this->transform.matrix();
	apr::Matrix4 worldViewProjectionMatrix = worldMatrix * camera->matrix();
	apr::Matrix4 inverseTransposeWorldViewMatrix = worldMatrix;
	inverseTransposeWorldViewMatrix.transpose();
	inverseTransposeWorldViewMatrix.invert();

	apr::Vector3 lightPosition(0, 0, 3);

	for (unsigned int i = 0; i < this->parts.size(); i++) {
		ModelPart part = this->parts[i];

		part.mesh.bind();
		part.shader.bind();

		part.shader.setMatrix4("u_worldMatrix", worldMatrix);
		part.shader.setMatrix4("u_worldViewProjectionMatrix", worldViewProjectionMatrix);
		part.shader.setMatrix4("u_inverseTransposeWorldViewMatrix", inverseTransposeWorldViewMatrix);
		part.shader.setVector3("u_lightPosition", lightPosition);
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

		part.shader.setVector3("u_light.ambient", apr::Vector3(1, 1, 1));
		part.shader.setVector3("u_light.diffuse", apr::Vector3(1, 1, 1));
		part.shader.setVector3("u_light.specular", apr::Vector3(1, 1, 1));

		glDrawArrays(GL_TRIANGLES, 0, part.mesh.getVertexCount());
	}
}
