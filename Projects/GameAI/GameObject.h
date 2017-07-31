#pragma once

#include <glm\vec2.hpp>

namespace aie
{
	class Renderer2D;
}

enum ColourPalette
{
	GREEN = 0x1ABF15FF, YELLOW = 0xE5EC13FF, ORANGE = 0xF1740BFF, RED = 0xF1190BFF, WHITE = 0xFFFFFFFF
};

class Behaviour;

class GameObject
{
public:

	GameObject();
	virtual ~GameObject();

	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D *renderer);

	void SimulatePhysics(float deltaTime);

	void ApplyForce(const glm::vec2 &force);
	const glm::vec2 & GetPosition();
	const glm::vec2 & GetVelocity();
	float GetFriction();
	Behaviour *GetBehaviour();

	void SetPosition(const glm::vec2 &pos);
	void SetVelocity(const glm::vec2 &vel);
	void SetFriction(float friction);
	void SetBehaviour(Behaviour *behaviour);
	ColourPalette paletteSwitch();

	void SetColour(int id);

protected:

	ColourPalette m_colour;
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;

	float m_rotation;
	float m_friction;

	Behaviour *m_behaviour;

private:
};