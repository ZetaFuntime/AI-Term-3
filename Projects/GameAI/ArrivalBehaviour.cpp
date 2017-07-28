#include "ArrivalBehaviour.h"
#include "GameObject.h"
#include <Renderer2D.h>
#include <glm\glm.hpp>

ArrivalBehaviour::ArrivalBehaviour() : 
	Behaviour(),
	m_slowingRadius(50.f)
{

}
ArrivalBehaviour::~ArrivalBehaviour()
{

}

void ArrivalBehaviour::Update(GameObject *object, float deltaTime)
{
	object->GetVelocity();
}

void ArrivalBehaviour::Draw(GameObject *object, aie::Renderer2D *renderer)
{

}

float ArrivalBehaviour::GetSlowingRadius()
{
	return m_slowingRadius;
}

void ArrivalBehaviour::SetSlowingRadius(float radius)
{
	m_slowingRadius = radius;
}
