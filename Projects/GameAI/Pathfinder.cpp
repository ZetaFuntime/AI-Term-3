#include "Pathfinder.h"
#include "Graph2D.h"


Pathfinder::Pathfinder(Graph2D * graph)
{
	m_graph = graph;
	m_pathFound = false;
}

Pathfinder::~Pathfinder()
{

}

Graph2D *Pathfinder::GetGraph()
{
	return m_graph;
}

void Pathfinder::SetGraph(Graph2D *graph)
{
	m_graph = graph;
}

void Pathfinder::FindPath(Graph2D::Node *startNode, std::function<bool(Graph2D::Node *)> isGoalNodeFunc)
{

}

bool Pathfinder::PathFound()
{
	return m_pathFound;
}

void Pathfinder::UpdateSearch()
{

}

Path &Pathfinder::GetPath()
{
	return m_path;
}