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
		auto ToTexChannel = [](aiTextureType type)
		{
			Material::TexChannel type_by_channel[aiTextureType::aiTextureType_UNKNOWN] = { Material::TexChannel::kMaxChannel };
			type_by_channel[aiTextureType::aiTextureType_NORMALS] = Material::TexChannel::kNoraml;
			type_by_channel[aiTextureType::aiTextureType_DIFFUSE] = Material::TexChannel::kDiffuse;
			type_by_channel[aiTextureType::aiTextureType_SPECULAR] = Material::TexChannel::kSpecular;

			return type_by_channel[type];
		};

		auto material_ptr = MakeMaterialPtr();

		auto tex_noraml = GetTexture(mat, aiTextureType_NORMALS);
		auto tex_diffuse = GetTexture(mat, aiTextureType_DIFFUSE);
		auto tex_specular = GetTexture(mat, aiTextureType_SPECULAR);

		if (tex_noraml)
		{
			material_ptr->AttachTexture(ToTexChannel(aiTextureType_NORMALS), tex_noraml);
		}

		if (tex_diffuse)
		{
			material_ptr->AttachTexture(ToTexChannel(aiTextureType_DIFFUSE), tex_diffuse);
		}

		if (tex_specular)
		{
			material_ptr->AttachTexture(ToTexChannel(aiTextureType_SPECULAR), tex_specular);
		}

		// 根据纹理选择添加的Shader
		ShaderPtr shader_ptr;

		if (tex_noraml && tex_diffuse && tex_specular)
		{
			shader_ptr = ShaderManager::s_kNormalDiffuseSpecularShader;
		}
		else if (tex_noraml && tex_diffuse)
		{
			shader_ptr = ShaderManager::s_kNoramlDiffuseShader;
		}
		else if (tex_noraml && tex_specular)
		{
			shader_ptr = ShaderManager::s_kNoramlSpecularShader;
		}
		else if (tex_diffuse && tex_specular)
		{
			shader_ptr = ShaderManager::s_kDiffuseSpecularShader;
		}
		else if (tex_noraml)
		{
			shader_ptr = ShaderManager::s_kNoramlShader;
		}
		else if (tex_diffuse)
		{
			shader_ptr = ShaderManager::s_kDiffuseShader;
		}
		else if (tex_specular)
		{
			shader_ptr = ShaderManager::s_kSpecularShader;
		}

		// 如果没有,赋予一simpleshader
		if (!shader_ptr)
		{
			shader_ptr = ShaderManager::s_kSimpleShader;
		}

		material_ptr->set_shader_ptr(shader_ptr);

		return material_ptr;
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