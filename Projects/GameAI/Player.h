#pragma once

#include "GameObject.h"
#include "Graph2D.h"

class KeyboardBehaviour;
class SeekBehaviour;
class FollowPathBehaviour;
class Path;
class Graph2D;
class Pathfinder;

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

protected:

	int mX, mY;

	KeyboardBehaviour *m_keyboardBehaviour;
	SeekBehaviour *m_seekBehaviour;
	SeekBehaviour *m_fleeBehaviour;
	FollowPathBehaviour *m_followPathBehaviour;

	Path *m_path;

	Graph2D *m_graph;
	Graph2D::Node *m_startNode;
	Graph2D::Node *m_endNode;
	Pathfinder *m_pathfinder;

private:
};