#include "GameObject.h"
#include "Behaviour.h"

#include <Texture.h>
#include <Renderer2D.h>
#include <glm\glm.hpp>
#include <iostream>

GameObject::GameObject(aie::Texture *tex) :
	m_tex(tex),
	m_friction(1.0f),
	m_rotation(0.0f),
	m_behaviour(nullptr),
	isDrawn(true),
	m_colour(WHITE)
{

}

GameObject::~GameObject()
{
	SetBehaviour(nullptr);
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

	renderer->setRenderColour(m_colour);
	if (m_tex != nullptr) {
		renderer->drawCircle(m_position.x, m_position.y, 8);
	} else {
		renderer->drawSprite(m_tex, m_position.x, m_position.y, 0, 0, m_rotation);
	}
	if (!m_behaviour->IsDrawnByGameObject())
	{
		renderer->setRenderColour(WHITE);
		renderer->drawLine(m_position.x, m_position.y, targetHeading.x, targetHeading.y, 2.0f);
		renderer->setRenderColour(0xFFFFFFFF);
	}
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
	m_velocity = vel;
}

void GameObject::SetFriction(float friction)
{
	m_friction = friction;
}

void GameObject::SetBehaviour(Behaviour *behaviour)
{
	if (m_behaviour && m_behaviour->IsOwnedByGameObject() == true)
		delete m_behaviour;

	m_behaviour = behaviour;
}

void GameObject::SetColour(int id)
{
	switch (id)
	{
	case GREEN:		m_colour = GREEN;	break;
	case RED:		m_colour = RED;		break;
	case YELLOW:	m_colour = YELLOW;	break;
	case ORANGE:	m_colour = ORANGE;	break;
	case WHITE:		m_colour = WHITE;	break;
	default:							break;

	}
}