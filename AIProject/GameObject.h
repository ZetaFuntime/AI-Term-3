#pragma once
#include <glm\vec2.hpp>

namespace aie
{
	class Renderer2D;
	class Texture;
}

enum ColourPalette
{
	GREEN = 0x1ABF15FF, BLUE = 0x0910F0FF,
	YELLOW = 0xE5EC13FF, ORANGE = 0xF1740BFF, 
	TEAL = 0x11E3DDFF, RED = 0xF1190BFF, 
	PURPLE = 0x7411E3FF, WHITE = 0xFFFFFFFF, 
	PINK = 0xFA22EA, DARKBLUE = 0x012345FF
};

class Behaviour;

class GameObject
{
public:

	GameObject(aie::Texture *tex = nullptr);
	virtual ~GameObject();

	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D *renderer);
	void SimulatePhysics(float deltaTime);
	void ApplyForce(const glm::vec2 &force);

// --------------------------------------------------------
//	Setter functions for all relevant values
// --------------------------------------------------------

#pragma region Setters

	void SetTexture(aie::Texture *tex);
	void SetPosition(const glm::vec2 &pos);
	void SetVelocity(const glm::vec2 &vel);
	void SetFriction(float friction);
	void SetBehaviour(Behaviour *behaviour);
	void SetSize(float size);
	void SetDraw(bool draw);
	void SetColour(int id);

#pragma endregion

// --------------------------------------------------------
//	Getter functions for all relevant values
// --------------------------------------------------------

#pragma region Getters
	
	bool GetDraw();
	float GetSize();
	const glm::vec2 & GetPosition();
	const glm::vec2 & GetVelocity();
	float GetFriction();
	Behaviour *GetBehaviour();

#pragma endregion

protected:

	ColourPalette m_colour;
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;

	bool isDrawn;
	float m_rotation;
	float m_friction;
	float m_size;

	aie::Texture	*m_tex;
	Behaviour		*m_behaviour;

private:
};