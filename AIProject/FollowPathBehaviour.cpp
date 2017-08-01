#include "FollowPathBehaviour.h"
#include <Renderer2D.h>
#include "Path.h"
#include "GameObject.h"
#include <glm\glm.hpp>
#include <iostream>

FollowPathBehaviour::FollowPathBehaviour() :
	Behaviour(), m_path(nullptr),
	m_currentPathNodeIndex(0),
	m_forceStrength(100),
	m_nodeRadius(10.f),
	m_patrolBack(false),
	m_patrolMode(false),
	m_pathComplete(false)
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
		if (!m_patrolBack)
			m_currentPathNodeIndex = m_currentPathNodeIndex % path.size();
		glm::vec2 point = path[m_currentPathNodeIndex];
		if (!m_pathComplete) {
			if (glm::length(point - object->GetPosition()) < 20)
			{
				(m_patrolBack) ? m_currentPathNodeIndex -= 1 : m_currentPathNodeIndex += 1;
				if (m_currentPathNodeIndex == path.size() && m_patrolMode)
					m_currentPathNodeIndex -= 1;
			}
		}
		if (m_currentPathNodeIndex == path.size() - 1)
			m_patrolBack = true;
		if ((m_currentPathNodeIndex == 0 && m_patrolBack) || !m_patrolMode)
			m_patrolBack = false;
		if (!m_patrolBack) {
			m_currentPathNodeIndex = m_currentPathNodeIndex % path.size();
		}
		point = path[m_currentPathNodeIndex];
		if (!m_patrolMode && m_currentPathNodeIndex == path.size() - 1)
			m_pathComplete = true;

		// seek toward the point
		glm::vec2 dirToPoint = glm::normalize(point - object->GetPosition());
		object->ApplyForce(dirToPoint * m_forceStrength);

		// For debugging on console
		std::cout << m_currentPathNodeIndex << std::endl;
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

		if (IsDrawnByGameObject()){
			renderer->setRenderColour(
				((iter == path.begin() || iter == path.end() - 1) && m_patrolMode) ? 0x1ABF1555 :
				(iter == path.begin()) ? 0x0910F055 : 0xF1190B55);
			if (iter == path.end()-1 || iter == path.begin())
				renderer->drawCircle(point.x, point.y, m_nodeRadius);
		} else {
			renderer->setRenderColour(
				((iter == path.begin() || iter == path.end() - 1) && m_patrolMode) ? 0x1ABF1555 :
				(iter == path.begin()) ? 0x0910F055 :
				(iter == path.end() - 1) ? 0xF1190B55 : 0xFFFFFF55);
			renderer->drawCircle(point.x, point.y, m_nodeRadius);
		}

		// ------------------------------------------------------------------
		//	If the first point of the path,				it is BLUE,
		//  if the last point of the path,				it is RED,
		//	if the current point being seeked to,		it is ORANGE
		//	if the path is on patrol and is either end,	it is GREEN
		// ------------------------------------------------------------------

		if (IsDrawnByGameObject()) {
			unsigned int color = (index == m_currentPathNodeIndex) ? 0xFF7f00FF : 0xFFFFFFFF;

			renderer->setRenderColour(color);
			renderer->drawCircle(point.x, point.y, 4);

			renderer->setRenderColour(0xFFFFFFFF);

			if (index > 0)
			{
				renderer->drawLine(point.x, point.y, lastPathPoint.x, lastPathPoint.y);
			}
		} else {
			renderer->setRenderColour(0xFF7f00FF);

			if (index == m_currentPathNodeIndex)
			renderer->drawCircle(point.x, point.y, 4);

			renderer->setRenderColour(0xFFFFFFFF);
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

void FollowPathBehaviour::SetPatrolMode(bool activity)
{
	m_patrolMode = activity;
	if (m_patrolMode)
		m_pathComplete = false;
}

bool FollowPathBehaviour::GetPatrolActivity()
{
	return m_patrolMode;
}

bool FollowPathBehaviour::CheckPathComplete()
{
	return m_pathComplete;
}

void FollowPathBehaviour::OnEndPathEnter(std::function<void()> func)
{
	m_onEndPathEnter = func;
}
