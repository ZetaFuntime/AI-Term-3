#pragma once

#include "Behaviour.h"
#include <glm\vec2.hpp>

class ArrivalBehaviour : public Behaviour
{
public:

	ArrivalBehaviour();
	virtual ~ArrivalBehaviour();

	virtual void Update(GameObject *object, float deltaTime);
	virtual void Draw(GameObject *object, aie::Renderer2D *renderer);

	float GetSlowingRadius();
	void SetSlowingRadius(float radius);

protected:

	float m_slowingRadius;

private:
};