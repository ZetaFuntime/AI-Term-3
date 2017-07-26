#include "WanderBehaviour.h"
#include "GameObject.h"
#include <math.h>

WanderBehaviour::WanderBehaviour() : 
	Behaviour(),
	m_timePassed(0),
	m_timeThreshold(2.f)
{

}

WanderBehaviour::~WanderBehaviour()
{

}

void WanderBehaviour::Update(GameObject *object, float deltaTime)
{
	m_timePassed += deltaTime;

	if (m_timePassed > m_timeThreshold)
	{
		// If the time threshold has been passed, randomise force, 
		// time threshold and friction values

		float newXForce = ((rand() % 10000) - 5000);
		float newYForce = ((rand() % 10000) - 5000);
		m_timeThreshold = ((rand() % 50) / 10.f);

		object->ApplyForce(glm::vec2(newXForce, newYForce));

		m_timePassed = 0;
	}
}