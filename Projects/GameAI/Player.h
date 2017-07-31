#pragma once

#include "GameObject.h"
#include "Graph2D.h"
#include <Texture.h>
#include <list>

class KeyboardBehaviour;
class SeekBehaviour;
class FollowPathBehaviour;
class WanderBehaviour;
class ArrivalBehaviour;
class Path;
class Graph2D;
class Pathfinder;

struct Pos
{
	glm::vec2 data;
	float rotation;
	float timer;
};
class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D *renderer);

	void SetGraph(Graph2D *graph);
	Graph2D *GetGraph();

	void DoPathLogic();

	void DoTrailLogic();

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

	aie::Texture*		m_Agent;
	Path*				m_path;
	Graph2D*			m_graph;
	Graph2D::Node*		m_startNode;
	Graph2D::Node*		m_endNode;
	Pathfinder*			m_pathfinder;

	std::list<Pos> m_prevPoints;

private:
};