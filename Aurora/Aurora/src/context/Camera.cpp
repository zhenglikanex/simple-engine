#include "Camera.h"

#include "SceneNode.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace aurora
{
	Camera::Camera()
		:front_(glm::vec3(0.0f, 0.0f, -1.0f))
		, world_up_(glm::vec3(0.0f, 1.0f, 0.0f))
		, yaw_(-90)
		, pitch_(0)
		, fov_(45)
		, screen_width_(1024)
		, screen_height_(768)
		, near_panel_(0.1f)
		, far_panel_(100.0f)
	{
		UpdateCameraVectors();

		AddVisibleLayer(s_DefautltLayer);
	}

	Camera::~Camera()
	{

	}

	ComponentID Camera::GetComponentId()
	{
		return COMPONENT_ID(*this);
	}

	IComponentPtr Camera::Clone()
	{
		auto camera = MakeCameraPtr();
		return camera;
	}

	void Camera::Copy(const IComponentPtr& component)
	{
		auto camera = std::dynamic_pointer_cast<Camera>(component);
		if (camera)
		{
		}
	}

	glm::mat4x4 Camera::GetCameraMatrix()
	{
		auto scene_node = GetGameObject()->GetComponent<SceneNode>();
		return glm::lookAt(scene_node->position(), scene_node->position() + front_, up_);
	}

	glm::mat4x4 Camera::GetProjectionMatrix()
	{
		return glm::perspective(glm::radians(fov_), screen_width_ / screen_height_, near_panel_, far_panel_);
	}

	bool Camera::CheckVisibleLayer(uint32_t layer_id)
	{
		return std::find(visible_layers_.begin(), visible_layers_.end(), layer_id) != visible_layers_.end();
	}

	void Camera::AddVisibleLayer(uint32_t layer_id)
	{
		visible_layers_.push_back(layer_id);
	}

	void Camera::UpdateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
		front.y = sin(glm::radians(pitch_));
		front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));

		front_ = glm::normalize(front);
		right_ = glm::normalize(glm::cross(front, world_up_));
		up_ = glm::normalize(glm::cross(right_, front_));
	}
}