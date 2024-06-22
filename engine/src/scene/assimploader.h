#pragma once

#include <string>
#include <vector>

#include "renderer/renderer.h"
#include "renderer/texture.h"

struct aiScene;
struct aiNode;
struct aiMesh;
struct aiMaterial;

namespace Elysium
{
	class AssimpLoader
	{
	public:
		struct MeshEntry
		{
			std::vector<Renderer::Vertex> Vertices;
			std::vector<uint32_t> Indices;
			std::vector<Shared<Texture2D>> Textures;
		};

	public:
		AssimpLoader();

		void Load(const std::string& file);

		inline const std::vector<MeshEntry>& GetMeshEntries() const
		{ return m_MeshEntries; }

	private:
		void LoadNode(aiNode* node, const aiScene* scene);
		MeshEntry LoadMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Shared<Texture2D>> LoadMaterial(aiMaterial* material,
													uint16_t type,
													const aiScene* scene);

	private:
		std::vector<MeshEntry> m_MeshEntries;
		std::string m_Directory;

		inline
		static std::vector<Shared<Texture2D>> s_TexturesCache;
	};
}