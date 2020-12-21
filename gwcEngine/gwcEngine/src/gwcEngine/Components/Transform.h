#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gwcEngine
{
	class Transform
	{
	public:
		Transform();

		//todo - does this take into account relation to parent? i dont think it does.
		const glm::vec3& GetPosition() const;

		const glm::quat& GetRotation() const;

		const glm::vec3& GetScale() const;

		glm::mat4 GetTransformMatrix();
		
		void SetPosition(const glm::vec3& pos);

		void SetScale(const glm::vec3& scale);

		void SetRotation(const glm::quat& rot);

		void SetRotation(const glm::vec3& erot);

		void SetParent(const Ref<Transform>& parent);

		void ClearParent();

		void OnChangeSubscribe(Ref<EventCallback<const Transform&>> callback);

		Ref<EventCallback<const Transform&>> OnChangeSubscribe(std::function<bool(const Transform&)> callback);

		void OnChangeUnsubscribe(Ref<EventCallback<const Transform&>> callback);

		const glm::vec3& Forward()const;
		const glm::vec3& Up()const;
		const glm::vec3& Right()const;

		void Translate(const glm::vec3& direction, float distance);

	private:

		glm::vec3 GetCompoundPosition() const;


		glm::quat GetCompoundRotation() const;

		glm::vec3 GetCompoundScale() const;

		void UpdateTansformMatrix();

	private:

		glm::quat m_Rotation;
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		glm::mat4 m_TransformMat;
		
		glm::vec3 m_Forward;
		glm::vec3 m_Right;
		glm::vec3 m_Up;
		Ref<Transform> m_Parent;
		Event<const Transform&> m_OnChange;
	};
}