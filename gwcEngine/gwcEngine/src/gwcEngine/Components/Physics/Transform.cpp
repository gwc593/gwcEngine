#include"gepch.h"
#include"Transform.h"
#include <glm/gtx/matrix_decompose.hpp>

namespace gwcEngine
{
	Transform::Transform()
	{
		m_Parent = nullptr;
		m_TransformMat = glm::mat4(1.0f);
		SetRotation({ 0.0f, 0.0f, 0.0f });
		SetPosition({ 0,0,0 });
		SetScale({ 1,1,1 });

		m_Forward = { 0,0,-1 };
		m_Up = { 0,1,0 };
		m_Right = { 1,0,0 };
		Decompose();
	}

	Transform::Transform(const Transform& other)
	{
		m_TransformMat = other.m_TransformMat;
		m_Parent = other.m_Parent;
		Decompose();
	}

	Transform::Transform(Transform&& other) noexcept
	{
		m_TransformMat = other.m_TransformMat;
		m_Parent = std::move(other.m_Parent);
	
		Decompose();

	}

	const glm::vec3 Transform::GetPosition(const Space& space)
	{
		switch (space) {
			case(Space::local): return m_Position;
			case(Space::world): {

				glm::vec4 homoPos = GetTransformMatrix() * glm::vec4(0, 0, 0, 1.0);
				return  { homoPos.x,homoPos.y,homoPos.z };

			}
		}
		return m_Position;
	}

	const glm::quat Transform::GetRotation(const Space& space) const
	{
		switch (space) {
			case(Space::local): return m_Rotation;
			case(Space::world): {

				if (m_Parent == nullptr)
					return m_Rotation;
				else {
					return m_Parent->GetRotation() * m_Rotation;
				}
			}
		}

		return m_Rotation;
	}

	const glm::vec3 Transform::GetScale(const Space& space) const
	{
		switch (space) {
			case(Space::local): return m_Scale;
			case(Space::world): {
				if (m_Parent == nullptr)
					return m_Scale;
				else {
					return m_Scale * m_Parent->GetScale(Space::world);
				}
			}
		}
		return m_Scale;
	}

	glm::mat4 Transform::GetTransformMatrix() { UpdateTansformMatrix(); return m_TransformMat; }

	void Transform::SetPosition(const glm::vec3& pos)
	{
		m_Position = pos;
		UpdateTansformMatrix();
		m_OnChange.raiseEvent(*this);
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		UpdateTansformMatrix();
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

	void Transform::SetTransform(const glm::mat4& transform)
	{
		m_TransformMat = transform;
		Decompose();
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
		m_OnChange.raiseEvent(*this);
	}


	void Transform::UpdateTansformMatrix()
	{
		//order                                            3                       2                          1
		//scale, then rotate, then translate
		m_TransformMat = glm::translate(glm::mat4(1.0f), m_Position) * glm::mat4(m_Rotation) * glm::scale(glm::mat4(1.0f), m_Scale);
		if (m_Parent != nullptr)
			m_TransformMat = m_Parent->GetTransformMatrix()* m_TransformMat;

		m_Forward = glm::rotate(GetRotation(Space::world), glm::vec4(0, 0, -1, 1));
		m_Right = glm::rotate(GetRotation(Space::world), glm::vec4(1, 0, 0, 1));
		m_Up = glm::rotate(GetRotation(Space::world), glm::vec4(0,1, 0, 1));

	}

	void Transform::Decompose()
	{
		glm::decompose(m_TransformMat, m_Scale, m_Rotation, m_Position, m_Scew,m_Perspective);
	}
}