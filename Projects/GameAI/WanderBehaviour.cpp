#include "WanderBehaviour.h"
#include "GameObject.h"
#include <math.h>
#include <iostream>

WanderBehaviour::WanderBehaviour() : 
	Behaviour(),
	m_changetimePassed(0),
	m_applytimePassed(0),
	m_changeThreshold(0.0f),
	m_timeThreshold(0.001f)
{
	m_wanderAngle = ((rand() % 618) - 315) / 100.f;
}

WanderBehaviour::~WanderBehaviour()
{

}

void WanderBehaviour::Update(GameObject *object, float deltaTime)
{
	m_changetimePassed += deltaTime;
	m_applytimePassed += deltaTime;
	if (m_changetimePassed > m_changeThreshold)
	{

		float prevAngle = m_wanderAngle;
		// If the time threshold has been passed, randomise force, 
		// time threshold and friction values
		m_appliedForce = (rand() % 100) + 100;
		m_wanderAngle = prevAngle + ((rand() % 314) - 158)/100.f;
		std::cout << m_wanderAngle << std::endl;
		m_changeThreshold = ((rand() % 50) / 100.f);
		
		m_wanderVector = SetAngle(m_appliedForce, m_wanderAngle);
		m_changetimePassed = 0;
	}
	
	if (m_applytimePassed > m_timeThreshold) {
		object->ApplyForce(m_wanderVector);
		m_applytimePassed = 0;
	}
}

glm::vec2 WanderBehaviour::SetAngle(int strength, float wanderAngle)
{
	glm::vec2 wanderVector;
	wanderVector.x = strength * cos(wanderAngle);
	wanderVector.y = strength * sin(wanderAngle);
	return wanderVector;
}