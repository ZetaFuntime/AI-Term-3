#include "GameObject.h"
#include <Renderer2D.h>
#include "Behaviour.h"

GameObject::GameObject() : m_friction (0.0f), m_behaviour(nullptr)
{

}

GameObject::~GameObject()
{
	delete m_behaviour;
}

void GameObject::Update(float deltaTime)
{
	if (m_behaviour != nullptr)
		m_behaviour->Update(this, deltaTime);
	SimulatePhysics(deltaTime);
}

void GameObject::Draw(aie::Renderer2D * renderer)
{

	glm::vec2 targetHeading = m_position + m_velocity;
	renderer->drawCircle(m_position.x, m_position.y, 8);
	renderer->setRenderColour(0xFF7F00FF);
	renderer->drawLine(m_position.x, m_position.y, targetHeading.x, targetHeading.y, 2.0f);
	renderer->setRenderColour(0xFFFFFFFF);

	if (m_behaviour != nullptr)
		m_behaviour->Draw(this, renderer);
}

void GameObject::SimulatePhysics(float deltaTime)
{
	ApplyForce(m_friction * -m_velocity);

	m_velocity += m_acceleration * deltaTime;
	m_position += m_velocity * deltaTime;
	m_acceleration = glm::vec2(0, 0);
} 

void GameObject::ApplyForce(const glm::vec2 & force)
{
	m_acceleration += force;
}

const glm::vec2 & GameObject::GetPosition()
{
	return m_position; 
}

const glm::vec2 & GameObject::GetVelocity()
{
	return m_velocity;
}

float GameObject::GetFriction()
{
	return m_friction;
}

Behaviour *GameObject::GetBehaviour()
{
	return m_behaviour;
}

void GameObject::SetPosition(const glm::vec2 &pos)
{
	m_position = pos;
}

void GameObject::SetVelocity(const glm::vec2 &vel)
{
	m_velocity += vel;
}

void GameObject::SetFriction(float friction)
{
	m_friction = friction;
}

void GameObject::SetBehaviour(Behaviour *behaviour)
{
	delete m_behaviour; 
	m_behaviour = behaviour;
}
