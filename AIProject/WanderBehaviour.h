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

	glm::vec2 SetAngle(float strength, float wanderAngle);

protected:

	float m_wanderAngle;
	glm::vec2 m_circleCenter;
	glm::vec2 m_displacement;
	float m_circleRadius;
	float m_forceStrength;

private:
};