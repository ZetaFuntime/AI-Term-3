#pragma once

#include "Behaviour.h"
#include <glm\vec2.hpp>
#include <functional>

class ArrivalBehaviour : public Behaviour
{
public:

	ArrivalBehaviour();
	virtual ~ArrivalBehaviour();

	virtual void Update(GameObject *object, float deltaTime);
	virtual void Draw(GameObject *object, aie::Renderer2D *renderer);

	const glm::vec2 &GetTarget();
	void SetTarget(const glm::vec2 & target);

	float GetSlowingRadius();
	void SetSlowingRadius(float radius);

	void OnTargetRadiusEnter(std::function< void() > func);

protected:

	glm::vec2 m_targetPosition;
	float m_slowingRadius;
	float m_targetRadius;
	float m_forceStrength;

	std::function< void() > m_onTargetRadiusEnter;

private:
	glm::vec2 m_lastPosition;
};