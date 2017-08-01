#include "Pathfinder.h"
#include "Graph2D.h"


Pathfinder::Pathfinder(Graph2D * graph)
{
	m_graph = graph;
	m_pathFound = false;
}

Pathfinder::~Pathfinder()
{
	for (auto iter = m_open.begin(); iter != m_open.end(); iter++)
		delete (*iter);

	for (auto iter = m_closed.begin(); iter != m_closed.end(); iter++)
		delete (*iter);

	m_open.clear();
	m_closed.clear();
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
	Node *node = new Node();
	node->node = startNode;
	node->gScore = 0;
	node->parent = nullptr;

	m_open.push_back(node);

	m_isGoalNodeFunc = isGoalNodeFunc;

	m_pathFound = false;
}

bool Pathfinder::PathFound()
{
	return m_pathFound;
}

void Pathfinder::UpdateSearch()
{
	if (m_open.empty())
	{
		m_pathFound = true;
	}

	if (m_pathFound == false)
	{
		// get the best node from the open list
		// move it to the closed list
		Node *node = m_open.back();
		m_open.pop_back();
		m_closed.push_back(node);

		if (m_isGoalNodeFunc(node->node))
		{
			CalculatePath(node);
			m_pathFound = true;
			return;
		}
		auto edges = node->node->connections;
		for (unsigned int i = 0; i < edges.size(); i++)
		{
			Graph2D::Edge& edge = edges[i];
			Graph2D::Node *child = edge.to;

			float cost = edge.data;
			float gScore = node->gScore + cost;

			Node *nodeInList = GetNodeInList(m_open, child);
			if (nodeInList == nullptr)
				nodeInList = GetNodeInList(m_closed, child);

			if (nodeInList == nullptr)
			{
				Node *newNode = new Node();
				newNode->node = child;
				newNode->gScore = gScore;
				newNode->parent = node;

				m_open.push_back(newNode);
			}
			else
			{
				if (nodeInList->gScore > gScore)
				{
					nodeInList->parent = node;
					nodeInList->gScore = gScore;
				}
			}
		}

		m_open.sort([this](Node *a, Node *b) {
			return a->gScore > b->gScore;
		});
	}
}

Path &Pathfinder::GetPath()
{
	return m_path;
}

Pathfinder::Node *Pathfinder::GetNodeInList(std::list<Node *> &list, Graph2D::Node *node)
{
	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		if ((*iter)->node == node)
			return (*iter);
	}

	return nullptr;
}

void Pathfinder::CalculatePath(Node *goal)
{
	m_path.Clear();
	Node *current = goal;
	while (current != nullptr)
	{
		m_path.PushPathSegment(current->node->data);
		current = current->parent;
	}
}