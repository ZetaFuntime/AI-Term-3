#pragma once

#include "Graph2D.h"
#include "Path.h"
#include <functional>

class Pathfinder
{
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
	std::is_function<bool(Graph2D::Node *)> m_isGoalNodeFunc;

	bool m_pathFound;
	Path m_path;

private:
};