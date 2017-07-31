#pragma once
#include "Behaviour.h"
#include <glm\vec2.hpp>

class WanderBehaviour : public Behaviour
{
public:

	WanderBehaviour();
	virtual ~WanderBehaviour();

	virtual void Update(GameObject *object, float deltaTime);
	virtual void Draw(GameObject * object, aie::Renderer2D *renderer);

	glm::vec2 SetAngle(int strength, float wanderAngle);

protected:

	float m_changetimePassed;
	float m_applytimePassed;
	float m_timeThreshold;
	float m_changeThreshold;

	glm::vec2 m_wanderVector;
	float m_wanderAngle;
	int m_appliedForce;

	glm::vec2 m_circleCenter;
	glm::vec2 m_displacement;
	float m_circleRadius;
	float m_forceStrength;

private:
};