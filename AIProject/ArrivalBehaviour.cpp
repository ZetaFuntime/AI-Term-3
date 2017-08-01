#include "ArrivalBehaviour.h"
#include "GameObject.h"
#include <Renderer2D.h>
#include <glm\glm.hpp>
#include <iostream>

ArrivalBehaviour::ArrivalBehaviour() :
	Behaviour(),
	m_slowingRadius(100.f),
	m_targetRadius(10.f),
	m_forceStrength(100.f)
{

}
ArrivalBehaviour::~ArrivalBehaviour()
{

}

void ArrivalBehaviour::Update(GameObject *object, float deltaTime)
{
	float lastDistanceToTarget = glm::length(m_targetPosition - m_lastPosition);
	float distanceToTarget = glm::length(m_targetPosition - object->GetPosition());

	// Have we just entered the target radius
	if (m_onTargetRadiusEnter && lastDistanceToTarget > m_targetRadius && distanceToTarget <= m_targetRadius)
		m_onTargetRadiusEnter();

	// --------------------------------------------------------------
	// If the agent is outside the slowing radius, don't slow it down
	// --------------------------------------------------------------
	float slowRatio = (distanceToTarget < m_slowingRadius) ? (distanceToTarget / (m_slowingRadius)) : 1;

	// --------------------------------------------------------------
	// Apply a constant force to the agent which is scaled down as the
	//			  agent gets closer to the destination.
	// --------------------------------------------------------------
	glm::vec2 currentDirToTarget = glm::normalize(m_targetPosition - object->GetPosition()) * slowRatio * m_forceStrength;

	object->SetVelocity(currentDirToTarget);

	m_lastPosition = object->GetPosition();
}

void ArrivalBehaviour::Draw(GameObject *object, aie::Renderer2D *renderer)
{
	if (IsDrawnByGameObject()) {
		renderer->drawBox(m_targetPosition.x, m_targetPosition.y, 10.f, 10.f);
		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.1f);
		renderer->drawCircle(m_targetPosition.x, m_targetPosition.y, m_slowingRadius);
		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.2f);
		renderer->drawCircle(m_targetPosition.x, m_targetPosition.y, m_targetRadius);
		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

const glm::vec2 &ArrivalBehaviour::GetTarget()
{
	return m_targetPosition;
}

void ArrivalBehaviour::SetTarget(const glm::vec2 &target)
{
	m_targetPosition = target;
}

float ArrivalBehaviour::GetSlowingRadius()
{
	return m_slowingRadius;
}

void ArrivalBehaviour::SetSlowingRadius(float radius)
{
	m_slowingRadius = radius;
}

void ArrivalBehaviour::OnTargetRadiusEnter(std::function< void() > func)
{
	m_onTargetRadiusEnter = func;
}