#pragma once

#include "Graph2D.h"
#include "Path.h"
#include <functional>
#include <list>

class Pathfinder
{
protected:

	struct Node
	{
		Graph2D::Node *node = nullptr;
		Node *parent = nullptr;
		float gScore;
	};
public:

	Pathfinder(Graph2D * graph);
	~Pathfinder();

	Graph2D *GetGraph();
	void SetGraph(Graph2D *graph);

	void FindPath(Graph2D::Node *startNode, std::function<bool(Graph2D::Node *)> isGoalNodeFunc);

	bool PathFound();

	void UpdateSearch();

	Path& GetPath();

protected:
	Graph2D *m_graph;
	std::function<bool(Graph2D::Node *)> m_isGoalNodeFunc;

	bool m_pathFound;
	Path m_path;
	std::list<Node *> m_open;
	std::list<Node *> m_closed;

private:

	Node *GetNodeInList(std::list<Node *> &list, Graph2D::Node *node);
	void CalculatePath(Node * goal);
};