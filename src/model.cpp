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
		// part.texture.bind();

		part.shader.setMatrix4("u_worldMatrix", worldMatrix);
		part.shader.setMatrix4("u_worldViewProjectionMatrix", worldViewProjectionMatrix);
		part.shader.setMatrix4("u_inverseTransposeWorldViewMatrix", inverseTransposeWorldViewMatrix);
		part.shader.setVector3("u_lightPosition", lightPosition);
		part.shader.setVector3("u_viewPosition", camera->transform.translation());

		part.shader.setVector3("u_material.ambient", part.material.ambient);
		part.shader.setVector3("u_material.diffuse", part.material.diffuse);
		part.shader.setVector3("u_material.specular", part.material.specular);
		part.shader.setFloat("u_material.shininess", part.material.shininess);

		part.shader.setVector3("u_light.ambient", apr::Vector3(1, 1, 1));
		part.shader.setVector3("u_light.diffuse", apr::Vector3(1, 1, 1));
		part.shader.setVector3("u_light.specular", apr::Vector3(1, 1, 1));

		part.shader.bind();

		glDrawArrays(GL_TRIANGLES, 0, part.mesh.getVertexCount());
	}
}
