#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gwcEngine
{
	enum class Space
	{
		local = 0,
		world
	};

	class Transform
	{
	public:
		Transform();
		Transform(const Transform& other);
		Transform(Transform&& other) noexcept;

		~Transform() = default;
		
		const glm::vec3 GetPosition(const Space& space = Space::local) ;

		const glm::quat GetRotation(const Space& space = Space::local) const;

		const glm::vec3 GetScale(const Space& space) const;

		glm::mat4 GetTransformMatrix();
		
		void SetPosition(const glm::vec3& pos);

		void SetScale(const glm::vec3& scale);

		void SetRotation(const glm::quat& rot);

		void SetRotation(const glm::vec3& erot);

		void SetParent(const Ref<Transform>& parent);

		void SetTransform(const glm::mat4& transform);

		void ClearParent();

		void OnChangeSubscribe(Ref<EventCallback<const Transform&>> callback);

		Ref<EventCallback<const Transform&>> OnChangeSubscribe(std::function<bool(const Transform&)> callback);

		void OnChangeUnsubscribe(Ref<EventCallback<const Transform&>> callback);

		const glm::vec3& Forward()const;
		const glm::vec3& Up()const;
		const glm::vec3& Right()const;

		void Translate(const glm::vec3& direction, float distance);

	private:

		void Decompose();

		void UpdateTansformMatrix();

	private:

		glm::quat m_Rotation;
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		glm::mat4 m_TransformMat;
		glm::vec3 m_Scew;
		glm::vec4 m_Perspective;
		glm::vec3 m_Forward;
		glm::vec3 m_Right;
		glm::vec3 m_Up;
		Ref<Transform> m_Parent;
		Event<const Transform&> m_OnChange;
	};
}