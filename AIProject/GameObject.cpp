#include "GameObject.h"
#include "Behaviour.h"

#include <Texture.h>
#include <Renderer2D.h>
#include <glm\glm.hpp>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

GameObject::GameObject(aie::Texture *tex) :
	m_tex(tex),
	m_friction(1.0f),
	m_rotation(0.0f),
	m_size(20.f),
	m_behaviour(nullptr),
	isDrawn(true),
	m_colour(WHITE)
{
	int randnum = rand() % 10;
	switch (randnum)
	{
	case 1:		m_colour = BLUE;	break;
	case 2:		m_colour = RED;		break;
	case 3:		m_colour = YELLOW;	break;
	case 4:		m_colour = GREEN;	break;
	case 5:		m_colour = ORANGE;	break;
	case 6:		m_colour = TEAL;	break;
	case 7:		m_colour = PURPLE;	break;
	case 8:		m_colour = PINK;	break;
	case 9:		m_colour = WHITE;	break;
	case 10:	m_colour = DARKBLUE;break;
	default:	m_colour = WHITE;	break;
	}
}

GameObject::~GameObject()
{
	SetBehaviour(nullptr);
}

void GameObject::Update(float deltaTime)
{
	//static float eye_relaxer = 0;
	//eye_relaxer += deltaTime;
	//if (eye_relaxer > 0.75f) {
	//
	//	int randnum = rand() % 10;
	//	switch (randnum)
	//	{
	//	case 1:		m_colour = BLUE;	break;
	//	case 2:		m_colour = RED;		break;
	//	case 3:		m_colour = YELLOW;	break;
	//	case 4:		m_colour = GREEN;	break;
	//	case 5:		m_colour = ORANGE;	break;
	//	case 6:		m_colour = TEAL;	break;
	//	case 7:		m_colour = PURPLE;	break;
	//	case 8:		m_colour = PINK;	break;
	//	case 9:		m_colour = WHITE;	break;
	//	default:	m_colour = WHITE;	break;
	//	}
	//	eye_relaxer = 0;
	//}
	if (m_behaviour != nullptr)
		m_behaviour->Update(this, deltaTime);
	SimulatePhysics(deltaTime);
}

void GameObject::Draw(aie::Renderer2D * renderer)
{
	glm::vec2 targetHeading = m_position + m_velocity;

	if (m_behaviour->IsDrawnByGameObject())
	{
		renderer->setRenderColour(0xFFFFFF50);
		renderer->drawCircle(m_position.x, m_position.y, m_size / 2);
		renderer->setRenderColour(ORANGE);
		renderer->drawLine(m_position.x, m_position.y, targetHeading.x, targetHeading.y, 2.0f);
		renderer->setRenderColour(WHITE);
	}

	renderer->setRenderColour(m_colour);
	if (m_tex == nullptr) {
		renderer->drawCircle(m_position.x, m_position.y, 8);
	} else {
		renderer->setRenderColour(m_colour);
		renderer->drawSprite(m_tex, m_position.x, m_position.y, m_size, m_size, m_rotation);
		renderer->setRenderColour(WHITE);
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

	m_rotation = atan2f(m_velocity.y, m_velocity.x);
}

void GameObject::ApplyForce(const glm::vec2 & force)
{
	m_acceleration += force;
}

bool GameObject::GetDraw()
{
	return m_behaviour->IsDrawnByGameObject();
}

float GameObject::GetSize()
{
	return m_size;
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

void GameObject::SetTexture(aie::Texture *tex)
{
	m_tex = tex;
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

void GameObject::SetDraw(bool draw)
{
	m_behaviour->UpdateDrawnByGameObject(draw);
}

void GameObject::SetBehaviour(Behaviour *behaviour)
{
	if (m_behaviour && m_behaviour->IsOwnedByGameObject() == true)
		delete m_behaviour;

	m_behaviour = behaviour;
}

void GameObject::SetSize(float size)
{
	m_size = size;
}

void GameObject::SetColour(int id)
{
	switch (id)
	{
	case GREEN:		m_colour = GREEN;		break;
	case TEAL:		m_colour = TEAL;		break;
	case PURPLE:	m_colour = PURPLE;		break;
	case PINK:		m_colour = PINK;		break;
	case BLUE:		m_colour = BLUE;		break;
	case RED:		m_colour = RED;			break;
	case YELLOW:	m_colour = YELLOW;		break;
	case ORANGE:	m_colour = ORANGE;		break;
	case WHITE:		m_colour = WHITE;		break;
	case DARKBLUE:	m_colour = DARKBLUE;	break;
	default:								break;
	}
}