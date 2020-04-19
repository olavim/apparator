#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "material.hpp"
#include "math.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "resources.hpp"

namespace apr = apparator;

apr::Material::Material(const aiMaterial *material, std::string modelDirectory, ResourceManager& resMgr) {
		aiString diffuseTexPath;
		aiString specularTexPath;
		aiReturn diffuseTexStatus = material->GetTexture(aiTextureType_DIFFUSE, 0, &diffuseTexPath);
		aiReturn specularTexStatus = material->GetTexture(aiTextureType_SPECULAR, 0, &specularTexPath);

		if (diffuseTexStatus == aiReturn_SUCCESS) {
			this->diffuseMap = resMgr.loadTexture(
				diffuseTexPath.C_Str(),
				modelDirectory + "/" + std::string(diffuseTexPath.C_Str())
			);
		} else {
			this->diffuseMap = NULL;
		}

		if (specularTexStatus == aiReturn_SUCCESS) {
			this->specularMap = resMgr.loadTexture(
				specularTexPath.C_Str(),
				modelDirectory + "/" + std::string(specularTexPath.C_Str())
			);
		} else {
			this->specularMap = NULL;
		}

		this->shader = resMgr.loadShader(
			"textured",
			"resources/shaders/textured.vert",
			"resources/shaders/textured.frag"
		);

		material->Get(AI_MATKEY_SHININESS, this->shininess);
}
