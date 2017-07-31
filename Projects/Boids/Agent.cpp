
#include "Agent.h"
#include <Renderer2D.h>
#include <Texture.h>
#include <vector>

#include <glm\gtx\vector_angle.hpp>

Agent::Agent()
{

}

Agent::~Agent()
{

}

void Agent::Init(aie::Texture *tex, glm::vec2 pos, glm::vec2 vel, float maxSpeed)
{
	m_position = pos;
	m_velocity = vel * maxSpeed;
	m_texture = tex;

	m_maxSpeed = maxSpeed;
}

void Agent::Update(float deltaTime)
{
	m_velocity += m_acceleration;
	m_acceleration = glm::vec2();

	//if (glm::length(m_velocity) > m_maxSpeed)
		m_velocity = glm::normalize(m_velocity) * m_maxSpeed;

	m_position += m_velocity * deltaTime;
}

void Agent::Draw(aie::Renderer2D *renderer)
{
	
	float rotation = glm::orientedAngle(glm::vec2(0.0f, 1.0f), glm::normalize(m_velocity));
	renderer->drawSprite(m_texture, m_position.x, m_position.y, 0, 0, rotation);
}

void Agent::WrapAroundScreen(float windowWidth, float windowHeight)
{
	if (m_position.x > windowWidth) m_position.x = 0;
	if (m_position.x < 0 ) m_position.x = windowWidth;
	if (m_position.y > windowHeight) m_position.y = 0;
	if (m_position.y < 0) m_position.y = windowHeight;
}

void Agent::Flock(Agent *allAgents, unsigned int numAgents, float neibourRadious, float seperationRadius, float seperationWeight, float allignmenWeight, float coherenceWeight)
{
	std::vector<Agent *> neibours;
	for (int i = 0; i < numAgents; i++)
	{
		float distance = glm::length(allAgents[i].m_position - m_position);
		if (distance < neibourRadious)
			neibours.push_back(&allAgents[i]);
	}

	glm::vec2 acceleration;
	acceleration += Seperation(neibours, seperationRadius) * seperationWeight;
	acceleration += Alignment(neibours) * allignmenWeight;
	acceleration += Cohereence(neibours) * coherenceWeight;

	m_acceleration += acceleration;
}

glm::vec2 Agent::Seperation(std::vector<Agent *> &neibours, float seperationRadius)
{
	glm::vec2 mean;
	float numToSeperate = 0;
	for (auto iter = neibours.begin(); iter != neibours.end(); iter++)
	{
		float distance = glm::length(m_position - (*iter)->m_position);
		if (distance > 0.0f && distance < seperationRadius)
		{
			mean += (m_position - (*iter)->m_position) / distance;
			numToSeperate += 1.0f;
		}
	}

	if( numToSeperate > 0)
		return mean / numToSeperate;

	return glm::vec2(0, 0);
}

glm::vec2 Agent::Alignment(std::vector<Agent *> &neibours)
{
	glm::vec2 mean;
	float count = 0;
	for (auto iter = neibours.begin(); iter != neibours.end(); iter++)
	{
		mean += glm::normalize((*iter)->m_velocity);
		count += 1.0f;
	}

	if (count > 0)
		return mean / count;

	return glm::vec2(0, 0);
}

glm::vec2 Agent::Cohereence(std::vector<Agent *> &neibours)
{
	if (neibours.empty())
		return glm::vec2();

	glm::vec2 sum;
	for (auto iter = neibours.begin(); iter != neibours.end(); iter++)
	{
		sum += (*iter)->m_position;
	}

	return StearTo( sum / (float)neibours.size());
}

glm::vec2 Agent::StearTo(glm::vec2 target)
{
	glm::vec2 desired = target - m_position;
	float distance = glm::length(desired);

	if (distance <= 0.0f)
		return glm::vec2();

	desired = glm::normalize(desired) * m_maxSpeed;
	glm::vec2 stear = desired - m_velocity;

	return glm::normalize(stear);
}