#include"gepch.h"
#include"Transform.h"

namespace gwcEngine
{
	Transform::Transform()
	{
		m_Parent = nullptr;
		SetRotation({ 0.0f, 0.0f, 0.0f });
		m_Position = glm::vec3(0.0f);
		m_Scale = glm::vec3(1.0f);
		m_TransformMat = glm::mat4(1.0f);

		m_Forward = { 0,0,-1 };
		m_Up = { 0,1,0 };
		m_Right = { 1,0,0 };
	}

	//todo - does this take into account relation to parent? i dont think it does.
	const glm::vec3& Transform::GetPosition() const
	{
		return m_Position;
	}

	const glm::quat& Transform::GetRotation() const
	{
		return m_Rotation;
	}

	const glm::vec3& Transform::GetScale() const
	{
		return m_Scale;
	}

	glm::mat4 Transform::GetTransformMatrix() { UpdateTansformMatrix(); return m_TransformMat; }

	void Transform::SetPosition(const glm::vec3& pos)
	{
		m_Position = pos;
		m_OnChange.raiseEvent(*this);
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		m_OnChange.raiseEvent(*this);
	}

	void Transform::SetRotation(const glm::quat& rot)
	{
		m_Rotation = rot;
		UpdateTansformMatrix();
		m_OnChange.raiseEvent(*this);
	}

	void Transform::SetRotation(const glm::vec3& erot)
	{
		m_Rotation = glm::quat(erot * glm::pi<float>() / 180.0f);
		UpdateTansformMatrix();
		m_OnChange.raiseEvent(*this);
	}

	void Transform::SetParent(const Ref<Transform>& parent)
	{
		m_Parent = parent;
		m_OnChange.raiseEvent(*this);
	}

	void Transform::ClearParent()
	{
		m_Parent = nullptr;
		m_OnChange.raiseEvent(*this);
	}

	void Transform::OnChangeSubscribe(Ref<EventCallback<const Transform&>> callback)
	{
		m_OnChange.subscribe(callback);
	}

	Ref<EventCallback<const Transform&>> Transform::OnChangeSubscribe(std::function<bool(const Transform&)> callback)
	{
		return m_OnChange.subscribe(callback);
	}

	void Transform::OnChangeUnsubscribe(Ref<EventCallback<const Transform&>> callback)
	{
		m_OnChange.unsubscribe(callback);
	}

	const glm::vec3& Transform::Forward()const { return m_Forward; }
	const glm::vec3& Transform::Up()const { return m_Up; }
	const glm::vec3& Transform::Right()const { return m_Right; }

	void Transform::Translate(const glm::vec3& direction, float distance)
	{
		m_Position += direction * distance;
	}

	glm::vec3 Transform::GetCompoundPosition() const
	{
		if (m_Parent == nullptr)
			return m_Position;
		else {
			return m_Position + m_Parent->GetPosition();
		}
	}

	glm::quat Transform::GetCompoundRotation() const
	{
		if (m_Parent == nullptr)
			return m_Rotation;
		else {
			return m_Rotation + m_Parent->GetRotation();
		}
	}

	glm::vec3 Transform::GetCompoundScale() const
	{
		if (m_Parent == nullptr)
			return m_Scale;
		else {
			return m_Scale * m_Parent->GetScale();
		}
	}

	void Transform::UpdateTansformMatrix()
	{
		m_TransformMat = glm::translate(glm::mat4(1.0f), GetCompoundPosition()) * glm::mat4(GetCompoundRotation()) * glm::scale(glm::mat4(1.0f), GetCompoundScale());
		m_Forward = glm::normalize(glm::vec4(0, 0, -1, 1) * glm::mat4(GetCompoundRotation()));
		m_Right = glm::normalize(glm::vec4(1, 0, 0, 1) * glm::mat4(GetCompoundRotation()));
		m_Up = glm::normalize(glm::vec4(0, 1, 0, 1) * glm::mat4(GetCompoundRotation()));
	}
}