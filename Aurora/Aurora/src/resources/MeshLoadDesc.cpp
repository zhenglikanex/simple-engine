#include "MeshLoadDesc.h"

#include <string>
#include <vector>

#include "FileHelper.h"
#include "Mesh.h"
#include "SubMesh.h"
#include "VertexLayout.h"
#include "Material.h"
#include "Resources.h"


// SubMesh对应于aiMesh
// Mesh只是一个SubMesh的容器,相当于一个Model的网格的集合

namespace aurora
{
	MeshLoadDesc::MeshLoadDesc(const std::string& name)
	{
		name_ = name;
	}

	MeshLoadDesc::~MeshLoadDesc()
	{

	}

	Texture2DPtr MeshLoadDesc::GetTexture(aiMaterial *mat, aiTextureType type)
	{
		// 目前只支持一张纹理
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			auto texture = LoadTexture2D(directory_ + "/" + str.C_Str());
			return texture;
		}

		return nullptr;
	}

	MaterialPtr MeshLoadDesc::ProcessMaterail(aiMaterial *mat)
	{
		auto tex_noraml = GetTexture(mat, aiTextureType_NORMALS);
		auto tex_diffuse = GetTexture(mat, aiTextureType_DIFFUSE);
		auto tex_specular = GetTexture(mat, aiTextureType_SPECULAR);

		// 根据纹理选择添加的material
		// TODO：暂时没实现其他材质
		MaterialPtr material;
		if (tex_diffuse)
		{
			if (tex_noraml && tex_specular)
			{
				return Resources::s_kSimpleMtl->Clone();
			}
			else if(tex_noraml) 
			{
				return Resources::s_kSimpleMtl->Clone();
			}
			else if (tex_specular)
			{
				return Resources::s_kSimpleMtl->Clone();
			}
			else {
				return Resources::s_kSimpleMtl->Clone();
			}

			return Resources::s_kSimpleMtl->Clone();
		}

		return Resources::s_kSimpleMtl->Clone();
	}

	SubMeshPtr MeshLoadDesc::ProcessSubMesh(const MeshPtr& mesh_ptr, aiMesh * ai_mesh, const aiScene *scene)
	{
		std::vector<Vertex_P3FN3FT2FT3FB3F> vertices;
		std::vector<uint32_t> indexs;

		Vertex_P3FN3FT2FT3FB3F vertex;

		for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++)
		{
			vertex.position = glm::vec3(ai_mesh->mVertices[i].x, ai_mesh->mVertices[i].y, ai_mesh->mVertices[i].z);
			vertex.normal = glm::vec3(ai_mesh->mNormals[i].x, ai_mesh->mNormals[i].y, ai_mesh->mNormals[i].z);
			vertex.texcoords = glm::vec2(ai_mesh->mTextureCoords[0][i].x, ai_mesh->mTextureCoords[0][i].y);
			vertex.tangent = glm::vec3(ai_mesh->mTangents[i].x, ai_mesh->mTangents[i].y, ai_mesh->mTangents[i].z);
			vertex.bitangent = glm::vec3(ai_mesh->mBitangents[i].x, ai_mesh->mBitangents[i].y, ai_mesh->mBitangents[i].z);

			vertices.push_back(vertex);
		}

		//现在通过每个网格的面（一个面是一个网格它的三角形）并检索相应的顶点索引
		for (uint32_t i = 0; i < ai_mesh->mNumFaces; ++i) {
			aiFace face = ai_mesh->mFaces[i];
			for (uint32_t j = 0; j < face.mNumIndices; j++) {
				indexs.push_back(face.mIndices[j]);
			}
		}

		auto submesh_ptr = MakeSubMeshPtr(
			mesh_ptr,
			VertexBuffer(VertexLayout::kP3FN3FT2FT3FB3F, vertices.size(), (uint8_t*)vertices.data()),
			IndexBuffer(IndexLayout::k32Bit, indexs.size(), (uint8_t*)indexs.data()),
			ProcessMaterail(scene->mMaterials[ai_mesh->mMaterialIndex]));

		return submesh_ptr;
	}

	void MeshLoadDesc::ProcessNode(const MeshPtr& mesh_ptr, aiNode* node, const aiScene* scene)
	{
		for (uint32_t i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			mesh_ptr->AddSubMesh(ProcessSubMesh(mesh_ptr, mesh, scene));
		}

		for (uint32_t i = 0; i < node->mNumChildren; ++i)
		{
			ProcessNode(mesh_ptr, node->mChildren[i], scene);
		}
	}

	std::shared_ptr<void> MeshLoadDesc::Create()
	{
		auto full_path = FileHelper::GetInstance()->GetFullPath(name());
		if (full_path.empty())
		{
			return nullptr;
		}

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(full_path.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// check for errors
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			LOG_ERROR() << "Error::ASSIMP::" << importer.GetErrorString() << LOG_END();
			return nullptr;
		}

		MeshPtr mesh_ptr = MakeMeshPtr();

		// 保存模型的目录,用于加载纹理
		directory_ = name().substr(0, name().find_last_of('/'));
		ProcessNode(mesh_ptr, scene->mRootNode, scene);

		return mesh_ptr;
	}
}