#pragma once
#include "Behaviour.h"

class WanderBehaviour : public Behaviour
{
public:

	WanderBehaviour();
	virtual ~WanderBehaviour();

	virtual void Update(GameObject *object, float deltaTime);

protected:

	float m_timePassed;
	float m_timeThreshold;
	int m_xForce;
	int m_yForce;

private:
};