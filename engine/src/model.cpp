#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "math/vector3.hpp"
#include "math/transform.hpp"
#include "renderer/shader.hpp"
#include "renderer/camera.hpp"
#include "renderer/texture.hpp"
#include "model.hpp"
#include "mesh.hpp"
#include "material.hpp"

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

apr::Model::Model() {
}

apr::Model::Model(std::string modelPath) {
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(
		modelPath,
		aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_OptimizeMeshes |
		aiProcess_OptimizeGraph
	);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Could not load model: " << importer.GetErrorString() << std::endl;
		return;
	} else {
		std::cout << "Model imported: " << modelPath << std::endl;
	}

	size_t slashPos = modelPath.find_last_of("/\\");
	const std::string modelDirectory = modelPath.substr(0, slashPos);

	this->processNode(scene->mRootNode, scene, modelDirectory);
}

apr::Model::~Model() {
}

void apr::Model::addPart(const ModelPart& part) {
	this->parts.push_back(part);
}

void apr::Model::draw(const Camera* camera) const {
	apr::Matrix4 worldMatrix = this->node->globalTransform().matrix();
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
		const Shader *shader = part.material->shader;

		part.mesh->getVertexCount();

		part.mesh->bind();
		shader->bind();

		shader->setMatrix4("u_worldMatrix", worldMatrix);
		shader->setMatrix4("u_worldViewProjectionMatrix", worldViewProjectionMatrix);
		shader->setMatrix4("u_inverseTransposeWorldViewMatrix", inverseTransposeWorldViewMatrix);
		shader->setVector3("u_viewPosition", camera->transform.translation());

		shader->setVector3("u_material.ambient", part.material->ambientColor);
		shader->setVector3("u_material.diffuse", part.material->diffuseColor);
		shader->setVector3("u_material.specular", part.material->specularColor);

		shader->setInt("u_material.diffuse", 0);
		shader->setInt("u_material.specular", 1);

		if (part.material->diffuseMap != NULL) {
			glActiveTexture(GL_TEXTURE0);
			part.material->diffuseMap->bind();
		}

		if (part.material->specularMap != NULL) {
			glActiveTexture(GL_TEXTURE1);
			part.material->specularMap->bind();
		}

		shader->setFloat("u_material.shininess", part.material->shininess);

		shader->setVector3("u_pointLight.position", pLight.transform.translation());
		shader->setVector3("u_pointLight.color", pLight.color);
		shader->setFloat("u_pointLight.linear", pLight.linear);
		shader->setFloat("u_pointLight.quadratic", pLight.quadratic);

		shader->setVector3("u_spotLight.position", sLight.transform.translation());
		shader->setVector3("u_spotLight.direction", sLight.transform.forward());
		shader->setVector3("u_spotLight.color", sLight.color);
		shader->setFloat("u_spotLight.innerAngle", sLight.innerAngle);
		shader->setFloat("u_spotLight.outerAngle", sLight.outerAngle);

		shader->setVector3("u_directionalLight.direction", dLight.transform.forward());
		shader->setVector3("u_directionalLight.color", dLight.color);

		glDrawArrays(GL_TRIANGLES, 0, part.mesh->getVertexCount());
	}
}

void apr::Model::processNode(aiNode *node, const aiScene *scene, std::string modelDirectory) {
	for(unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		apr::Mesh *modelMesh = new apr::Mesh(mesh);

		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		apr::Material *modelMaterial = new apr::Material(material, modelDirectory);

		this->addPart({modelMesh, modelMaterial});
	}

	for(unsigned int i = 0; i < node->mNumChildren; i++) {
		this->processNode(node->mChildren[i], scene, modelDirectory);
	}
}
