#pragma once

#include <vector>
#include <glm\glm.hpp>

namespace aie
{
	class Renderer2D;
	class Texture;
};

class Agent
{
public:

	Agent();
	~Agent();

	void Init(aie::Texture *tex, glm::vec2 pos, glm::vec2 vel, float maxSpeed);

	void Flock(Agent *allAgents, unsigned int numAgents, 
		float neibourRadious, float seperationRadius,
		float seperationWeight, float allignmenWeight, float coherenceWeight);

	void Update(float deltaTime);
	void Draw(aie::Renderer2D *renderer);

	void WrapAroundScreen(float windowWidth, float windowHeight);

protected:

	glm::vec2 Seperation(std::vector<Agent *> &neibours, float seperationRadius);
	glm::vec2 Alignment(std::vector<Agent *> &neibours);
	glm::vec2 Cohereence(std::vector<Agent *> &neibours);

	glm::vec2 StearTo(glm::vec2 target);

protected:

	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;

	float m_maxSpeed;
	aie::Texture *m_texture;

private:
};
