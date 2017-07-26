#pragma once
#include "Behaviour.h"
#include <glm\vec2.hpp>

class WanderBehaviour : public Behaviour
{
public:

	WanderBehaviour();
	virtual ~WanderBehaviour();

	virtual void Update(GameObject *object, float deltaTime);

	glm::vec2 SetAngle(int strength, float wanderAngle);

protected:

	float m_changetimePassed;
	float m_applytimePassed;
	float m_timeThreshold;
	float m_changeThreshold;

	glm::vec2 m_wanderVector;
	float m_wanderAngle;
	int m_appliedForce;

private:
};