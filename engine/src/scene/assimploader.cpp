#include "assimploader.h"

#include "core/log.h"

#include "renderer/renderer.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>

namespace Elysium
{
	AssimpLoader::AssimpLoader()
	{
	}

	void AssimpLoader::Load(const std::string& file)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(file, aiProcess_Triangulate |
													   aiProcess_FlipUVs |
													   aiProcess_GenSmoothNormals |
													   aiProcess_JoinIdenticalVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			ES_CORE_ERROR("Failed to load mesh: {0}", file);
			return;
		}

		m_Directory = file.substr(0, file.find_last_of('/') + 1);

		LoadNode(scene->mRootNode, scene);
	}

	void AssimpLoader::LoadNode(aiNode* node, const aiScene* scene)
	{
		for (uint32_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_MeshEntries.push_back(LoadMesh(mesh, scene));
		}

		for (uint32_t i = 0; i < node->mNumChildren; i++)
			LoadNode(node->mChildren[i], scene);
	}

	AssimpLoader::MeshEntry AssimpLoader::LoadMesh(aiMesh* mesh, const aiScene* scene)
	{
		MeshEntry meshEntry{};

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			auto textures = LoadMaterial(material, aiTextureType_DIFFUSE, scene);
			meshEntry.Textures = std::move(textures);
		}

		for (uint32_t i = 0; i < mesh->mNumVertices; i++)
		{
			Renderer::Vertex vertex{};

			memcpy(&vertex.Position[0],
				   &mesh->mVertices[i],
				   sizeof(aiVector3D));

			if (mesh->mTextureCoords[0])
			{
				memcpy(&vertex.TexCoord[0],
					   &mesh->mTextureCoords[0][i],
					   sizeof(aiVector2D));
				vertex.TexIndex = 0;
			}
			else
			{
				vertex.TexCoord = glm::vec2(0.0f, 0.0f);
			}

			meshEntry.Vertices.push_back(vertex);
		}

		for (uint32_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (uint32_t j = 0; j < face.mNumIndices; j++)
				meshEntry.Indices.push_back(face.mIndices[j]);
		}

		return meshEntry;
	}

	std::vector<Shared<Texture2D>>
	AssimpLoader::LoadMaterial(aiMaterial* material,
							   uint16_t type,
							   const aiScene* scene)
	{
		std::vector<Shared<Texture2D>> textures;

		for (uint32_t i = 0; i < material->GetTextureCount((aiTextureType)type); i++)
		{
			aiString str;
			material->GetTexture((aiTextureType)type, i, &str);
			std::string path = m_Directory + str.C_Str();
			bool alreadyLoaded = false;
			for (auto& tex : s_TexturesCache)
			{
				if (tex->GetPath() == path) // already loaded
				{
					textures.push_back(tex);
					alreadyLoaded = true;
				}
			}

			if (!alreadyLoaded)
			{
				auto texture = Texture2D::Create(path, false);
				textures.push_back(texture);
				s_TexturesCache.push_back(texture);
			}
		}

		return textures;
	}
}