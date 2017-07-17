#include "SeekBehaviour.h"
#include "GameObject.h"
#include <Renderer2D.h>
#include <glm\glm.hpp>

SeekBehaviour::SeekBehaviour()
{

}
SeekBehaviour::~SeekBehaviour()
{

}

void SeekBehaviour::Update(GameObject *object, float deltaTime)
{
	float lastDistanceToTarget = glm::length(m_targetPosition - m_lastPosition);
	float distanceToTarget = glm::length(m_targetPosition - object->GetPosition());

	// have we just entered the inner radius
	if (m_onInnerRadiusEnter && lastDistanceToTarget > m_innerRadius && distanceToTarget <= m_innerRadius)
		m_onInnerRadiusEnter();

	// have we just exited the inner radius
	if (m_onInnerRadiusExit && lastDistanceToTarget <= m_innerRadius && distanceToTarget > m_innerRadius)
		m_onInnerRadiusExit();

	// have we just entered the outer radius
	if (m_onOuterRadiusEnter && lastDistanceToTarget > m_outerRadius && distanceToTarget <= m_outerRadius)
		m_onOuterRadiusEnter();

	// have we just exited the outer radius
	if (m_onOuterRadiusExit && lastDistanceToTarget <= m_outerRadius && distanceToTarget > m_outerRadius)
		m_onOuterRadiusExit();


	glm::vec2 dirToTarget = glm::normalize(m_targetPosition - object->GetPosition()) * m_forceStrength;
	object->ApplyForce(dirToTarget);

	m_lastPosition = object->GetPosition();
}

void SeekBehaviour::Draw(GameObject * object, aie::Renderer2D *renderer)
{
	renderer->drawBox(m_targetPosition.x, m_targetPosition.y,10.f,10.f);
	renderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.5f);
	renderer->drawCircle(m_targetPosition.x, m_targetPosition.y, m_innerRadius);
	renderer->drawCircle(m_targetPosition.x, m_targetPosition.y, m_outerRadius);

	renderer->setRenderColour(1.0f,1.0f,1.0f,1.0f);
}

const glm::vec2 &SeekBehaviour::GetTarget()
{
	return m_targetPosition;
}

void SeekBehaviour::SetTarget(const glm::vec2 &target)
{
	m_targetPosition = target;
}

void SeekBehaviour::SetForceStrength(float strength)
{
	m_forceStrength = strength;
}

float SeekBehaviour::GetForceStrength()
{
	return m_forceStrength;
}

void SeekBehaviour::SetInnerRadius(float radius)
{
	m_innerRadius = radius;
}

float SeekBehaviour::GetInnerRadius()
{
	return m_innerRadius;
}

void SeekBehaviour::SetOuterRadius(float radius)
{
	m_outerRadius = radius;
}

float SeekBehaviour::GetOuterRadius()
{
	return m_outerRadius;
}

void SeekBehaviour::OnInnerRadiusEnter(std::function< void() > func)
{
	m_onInnerRadiusEnter = func;
}

void SeekBehaviour::OnInnerRadiusExit(std::function< void() > func)
{
	m_onInnerRadiusExit = func;
}

void SeekBehaviour::OnOuterRadiusEnter(std::function< void() > func)
{
	m_onOuterRadiusEnter = func;
}

void SeekBehaviour::OnOuterRadiusExit(std::function< void() > func)
{
	m_onOuterRadiusExit = func;
}