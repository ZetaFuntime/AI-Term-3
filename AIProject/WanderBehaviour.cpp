#include "WanderBehaviour.h"
#include "GameObject.h"
#include <glm\vec2.hpp>
#include <glm\glm.hpp>
#include <math.h>
#include <iostream>
#include <Renderer2D.h>

WanderBehaviour::WanderBehaviour() :
	Behaviour(),
	m_circleRadius(100.f),
	m_forceStrength(100.f)
{
	m_wanderAngle = ((rand() % 618) - 315) / 100.f;
}

WanderBehaviour::~WanderBehaviour()
{

}

void WanderBehaviour::Update(GameObject *object, float deltaTime)
{
	// -----------------------------------------------------------
	// Version 1 - Wandering Algorithm based on random direction
	//			   and force.
	// -----------------------------------------------------------
	//m_changetimePassed += deltaTime;
	//m_applytimePassed += deltaTime;
	//if (m_changetimePassed > m_changeThreshold)
	//{
	//
	//	float prevAngle = m_wanderAngle;
	//	// If the time threshold has been passed, randomise force, 
	//	// time threshold and friction values
	//	m_appliedForce = (rand() % 100) + 100;
	//	m_wanderAngle = prevAngle + ((rand() % 314) - 158)/100.f;
	//	std::cout << m_wanderAngle << std::endl;
	//	m_changeThreshold = ((rand() % 50) / 100.f);
	//	
	//	m_wanderVector = SetAngle(m_appliedForce, m_wanderAngle);
	//	m_changetimePassed = 0;
	//}
	//
	//if (m_applytimePassed > m_timeThreshold) {
	//	object->ApplyForce(m_wanderVector);
	//	m_applytimePassed = 0;
	//}

	// ----------------------------------------------------------
	// Version 2 - Wandering algorithm based on random normalised
	//			   vector and randomised displacement forces
	// ----------------------------------------------------------

	m_circleCenter = glm::normalize(object->GetVelocity());
	m_circleCenter = glm::vec2(m_circleCenter.x*m_forceStrength,
		m_circleCenter.y*m_forceStrength);

	float prevAngle = m_wanderAngle;
	m_wanderAngle = prevAngle + ((rand() % 314) - 158) / 100.f;
	m_displacement = SetAngle(m_circleRadius, m_wanderAngle);

	glm::vec2 wanderForce = m_circleCenter + m_displacement;
	object->ApplyForce(wanderForce);
}

void WanderBehaviour::Draw(GameObject * object, aie::Renderer2D * renderer)
{
	if (IsDrawnByGameObject()) {
		glm::vec2 agentPos = object->GetPosition();
		glm::vec2 wanderForce = m_circleCenter + m_displacement;

		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.25f);
		renderer->drawCircle(agentPos.x + m_circleCenter.x, agentPos.y + m_circleCenter.y, m_circleRadius);

		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
		renderer->drawLine(agentPos.x, agentPos.y, agentPos.x + m_circleCenter.x, agentPos.y + m_circleCenter.y);
		renderer->drawLine(agentPos.x, agentPos.y, agentPos.x + wanderForce.x, agentPos.y + wanderForce.y);
	}
}

glm::vec2 WanderBehaviour::SetAngle(float strength, float wanderAngle)
{
	glm::vec2 wanderVector;
	wanderVector.x = strength * cos(wanderAngle);
	wanderVector.y = strength * sin(wanderAngle);
	return wanderVector;
}