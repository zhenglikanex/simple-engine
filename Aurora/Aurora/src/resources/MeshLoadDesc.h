#ifndef MESH_LOAD_DESC_H_
#define MESH_LOAD_DESC_H_

#include "AuroraDef.h"
#include "ResLoadDesc.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace aurora
{
	class MeshLoadDesc : public ResLoadDesc
	{
	public:
		MeshLoadDesc(const std::string& name);
		virtual ~MeshLoadDesc();

		std::shared_ptr<void> Create() override;

		Texture2DPtr GetTexture(aiMaterial *mat, aiTextureType type);
		MaterialPtr ProcessMaterail(aiMaterial *mat);
		SubMeshPtr ProcessSubMesh(const MeshPtr& mesh_ptr, aiMesh * ai_mesh, const aiScene *scene);
		void ProcessNode(const MeshPtr& mesh_ptr, aiNode* node, const aiScene* scene);
	private:
		std::string directory_;
	};
}

#endif
