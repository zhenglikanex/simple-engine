#ifndef MESH_LOADER_H_
#define MESH_LOADER_H_

#include "AuroraDef.h"
#include "ResLoader.h"
#include "ResManager.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace aurora
{
	class MeshLoader : public ResLoader<MeshPtr>
	{
	public:		
		~MeshLoader()
		{

		}
		MeshPtr Load(const std::string& name);
		TexturePtr GetTexture(aiMaterial *mat, aiTextureType type);
		MaterialPtr ProcessMaterail(aiMaterial *mat);
		SubMeshPtr ProcessSubMesh(const MeshPtr& mesh_ptr, aiMesh * ai_mesh, const aiScene *scene);
		void ProcessNode(const MeshPtr& mesh_ptr, aiNode* node, const aiScene* scene);
	private:
		std::string directory_;
	};

	using MeshManager = ResManager<MeshLoader>;
}

#endif