#include "FollowPathBehaviour.h"
#include <Renderer2D.h>
#include "Path.h"
#include "GameObject.h"
#include <glm\glm.hpp>

FollowPathBehaviour::FollowPathBehaviour() : 
	Behaviour(), m_path(nullptr), 
	m_currentPathNodeIndex(0), 
	m_forceStrength(100), 
	m_nodeRadius(10.f)
{

}

FollowPathBehaviour::~FollowPathBehaviour()
{

}

void FollowPathBehaviour::Update(GameObject *object, float deltaTime)
{
	auto & path = m_path->GetPath();
	if (path.empty() == false)
	{
		m_currentPathNodeIndex = m_currentPathNodeIndex % path.size();
		glm::vec2 point = path[m_currentPathNodeIndex];
		if (glm::length(point - object->GetPosition()) < 20)
		{
			m_currentPathNodeIndex += 1;
		}

		m_currentPathNodeIndex = m_currentPathNodeIndex % path.size();
		point = path[m_currentPathNodeIndex];

		// seek toward the point
		glm::vec2 dirToPoint = glm::normalize(point - object->GetPosition());
		object->ApplyForce(dirToPoint * m_forceStrength);


	}
}

void FollowPathBehaviour::Draw(GameObject *object, aie::Renderer2D *renderer)
{
	auto &path = m_path->GetPath();
	glm::vec2 lastPathPoint;
	int index = 0;
	for (auto iter = path.begin(); iter != path.end(); iter++, index++)
	{
		glm::vec2 point = (*iter);

		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.5f);
		renderer->drawCircle(point.x, point.y, m_nodeRadius);

		unsigned int color = (index == m_currentPathNodeIndex)? 0xFF7f00FF : 0xFFFFFFFF;

		renderer->setRenderColour(color);
		renderer->drawCircle(point.x, point.y, 4);
		if (index > 0)
		{
			renderer->drawLine(point.x, point.y, lastPathPoint.x, lastPathPoint.y);
		}
		lastPathPoint = point;
	}

	// restore colour back to white
	renderer->setRenderColour(0xFFFFFFFF);
}

void FollowPathBehaviour::SetPath(Path * path)
{
	m_path = path;
}

Path * FollowPathBehaviour::GetPath()
{
	return m_path;
}

float FollowPathBehaviour::GetForceStrength()
{
	return m_forceStrength;
}

void FollowPathBehaviour::SetForceStrength(float strength)
{
	m_forceStrength = strength;
}

void FollowPathBehaviour::SetNodeRadius(float radius)
{
	m_nodeRadius = radius;
}

float FollowPathBehaviour::GetNodeRadius()
{
	return m_nodeRadius;
}
