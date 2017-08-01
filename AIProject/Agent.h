#pragma once

#include "GameObject.h"
#include "Graph2D.h"
#include <glm\glm.hpp>
#include <list>

class KeyboardBehaviour;
class SeekBehaviour;
class FollowPathBehaviour;
class WanderBehaviour;
class ArrivalBehaviour;
class Path;
class Graph2D;
class Pathfinder;

namespace aie {
	class Font;
	class Texture;
}

struct Pos
{
	glm::vec2 data;
	float rotation;
	int colour;
};

class Agent : public GameObject
{
public:
	Agent(aie::Texture *tex = nullptr);
	virtual ~Agent();

	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D *renderer);

	void SetGraph(Graph2D *graph);
	Graph2D *GetGraph();
	void DoPathLogic();
	void DoTrailLogic();

	// Flock Behaviour functions
	//void Flock(Player *allAgents, unsigned int numAgents,
	//			 float neighbourRadius, float seperationRadius,
	//			 float seperationWeight, float alignmentWeight,
	//			 float coherenceWeight);

	// Flock Behaviour variables - Todo

protected:

	//glm::vec2 Seperation(std::vector<Player *> &neighbours, float seperationRadius);
	//glm::vec2 Alignment(std::vector<Player *> &neighbours);
	//glm::vec2 Coherence(std::vector<Player *> &neighbours);
	//
	//glm::vec2 SteerTo(glm::vec2 target);

protected:

	int mX, mY;
	float m_effectLength;
	float m_trailDelay;
	glm::vec2 prevLocation;
	KeyboardBehaviour *m_keyboardBehaviour;
	SeekBehaviour *m_seekBehaviour;
	SeekBehaviour *m_fleeBehaviour;
	FollowPathBehaviour *m_followPathBehaviour;
	WanderBehaviour *m_wanderBehaviour;
	ArrivalBehaviour *m_arrivalBehaviour;

	Path*				m_path;
	Graph2D*			m_graph;
	Graph2D::Node*		m_startNode;
	Graph2D::Node*		m_endNode;
	Pathfinder*			m_pathfinder;

	std::list<Pos> m_prevPoints;

private:

	const char *m_behaviourName;
};