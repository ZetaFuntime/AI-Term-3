#pragma once

#include "Behaviour.h"
#include <glm\vec2.hpp>
#include <functional>

class SeekBehaviour : public Behaviour
{
public:

	SeekBehaviour();
	virtual ~SeekBehaviour();

	virtual void Update(GameObject *object, float deltaTime);
	virtual void Draw(GameObject * object, aie::Renderer2D *renderer);

	const glm::vec2 &GetTarget();
	void SetTarget(const glm::vec2 &target);

	void SetForceStrength(float strength);
	float GetForceStrength();

	void SetInnerRadius(float radius);
	float GetInnerRadius();

	void SetOuterRadius(float radius);
	float GetOuterRadius();

	void OnInnerRadiusEnter(std::function< void() > func);
	void OnInnerRadiusExit(std::function< void() > func);
	void OnOuterRadiusEnter(std::function< void() > func);
	void OnOuterRadiusExit(std::function< void() > func);

	void SetActivity(bool amIActive);

protected:
	
	glm::vec2 m_targetPosition;
	float m_forceStrength;

	float m_innerRadius;
	float m_outerRadius;

	std::function< void() > m_onInnerRadiusEnter;
	std::function< void() > m_onInnerRadiusExit;
	std::function< void() > m_onOuterRadiusEnter;
	std::function< void() > m_onOuterRadiusExit;

private:

	glm::vec2 m_lastPosition;
};