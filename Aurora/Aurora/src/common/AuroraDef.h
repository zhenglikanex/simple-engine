#ifndef AURORA_DEF_H_
#define AURORA_DEF_H_

#include <iostream>
#include <memory>
#include <ctime>
#include <chrono>
#include <iomanip>

#include "LogManager.h"
#include "Singleton.h"
#include "Global.h"

#define MAKE_SHARED_PTR(class_name) \
template<typename ... Args> \
class_name##Ptr Make##class_name##Ptr(Args&& ... args) \
{	\
	return std::make_shared<class_name##>(std::forward<Args>(args)...); \
}

#define LOG_END() LogManager::s_log_end
#define LOG() LogManager::GetInstance()->Log()
#define LOG_INFO() LOG() << "[INFO]"
#define LOG_ERROR() LOG() << "[ERROR]"
#define LOG_DEBUG() LOG() << "[DEBUG]"
#define LOG_WARNING() LOG() << "[WARNING]"
#define LOG_TRACE() LOG() << "[TARCE]"

const uint32_t s_DefautltLayer = 0;

namespace aurora
{
	class Config;
	using ConfigPtr = std::shared_ptr<Config>;
	MAKE_SHARED_PTR(Config);

	class Window;
	using WindowPtr = std::shared_ptr<Window>;
	MAKE_SHARED_PTR(Window);

	class OGLRenderer;
	using OGLRendererPtr = std::shared_ptr<OGLRenderer>;
	MAKE_SHARED_PTR(OGLRenderer);

	class OGLDeviceContext;
	using OGLDeviceContextPtr = std::shared_ptr<OGLDeviceContext>;
	MAKE_SHARED_PTR(OGLDeviceContext);

	class Context;
	using ContextPtr = std::shared_ptr<Context>;
	MAKE_SHARED_PTR(Context);

	class Mesh;
	using MeshPtr = std::shared_ptr<Mesh>;
	using MeshWeakPtr = std::weak_ptr<Mesh>;
	MAKE_SHARED_PTR(Mesh);

	class SubMesh;
	using SubMeshPtr = std::shared_ptr<SubMesh>;
	using SubMeshWeakPtr = std::weak_ptr<SubMesh>;
	MAKE_SHARED_PTR(SubMesh);

	class Image;
	using ImagePtr = std::shared_ptr<Image>;
	MAKE_SHARED_PTR(Image);

	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;
	MAKE_SHARED_PTR(Texture);

	class Texture2D;
	using Texture2DPtr = std::shared_ptr<Texture2D>;
	MAKE_SHARED_PTR(Texture2D);

	class TextureCube;
	using TextureCubePtr = std::shared_ptr<TextureCube>;
	MAKE_SHARED_PTR(TextureCube);

	class Material;
	using MaterialPtr = std::shared_ptr<Material>;
	MAKE_SHARED_PTR(Material);

	class Shader;
	using ShaderPtr = std::shared_ptr<Shader>;
	MAKE_SHARED_PTR(Shader);

	class FrameBufferObject;
	using FrameBufferObjectPtr = std::shared_ptr<Shader>;
	MAKE_SHARED_PTR(FrameBufferObject);

	class IComponent;
	using IComponentPtr = std::shared_ptr<IComponent>;
	MAKE_SHARED_PTR(IComponent);

	class GameObject;
	using GameObjectPtr = std::shared_ptr<GameObject>;
	using GameObjectWeakPtr = std::weak_ptr<GameObject>;
	MAKE_SHARED_PTR(GameObject);

	class SceneNode;
	using SceneNodePtr = std::shared_ptr<SceneNode>;
	using SceneNodeWeakPtr = std::weak_ptr<SceneNode>;
	MAKE_SHARED_PTR(SceneNode);

	class MeshRenderer;
	using MeshRendererPtr = std::shared_ptr<MeshRenderer>;
	using MeshRendererWeakPtr = std::weak_ptr<MeshRenderer>;
	MAKE_SHARED_PTR(MeshRenderer);

	class Camera;
	using CameraPtr = std::shared_ptr<Camera>;
	using CameraWeakPtr = std::weak_ptr<Camera>;
	MAKE_SHARED_PTR(Camera);

	class Light;
	using LightPtr = std::shared_ptr<Light>;
	using LightWeakPtr = std::weak_ptr<Light>;
	MAKE_SHARED_PTR(Light);

	class PointLight;
	using PointLightPtr = std::shared_ptr<PointLight>;
	using PointLightWeakPtr = std::weak_ptr<PointLight>;
	MAKE_SHARED_PTR(PointLight);
}

#endif
