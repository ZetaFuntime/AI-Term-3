#include "Graph2D.h"
#include <glm\glm.hpp>
Graph2D::Graph2D()
{

}

Graph2D::~Graph2D()
{

}

void Graph2D::GetNearbyNodes(const glm::vec2 & pos, float radius, std::vector<Graph2D::Node*>& out_nodes)
{
	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++)
	{
		float dist = glm::length(pos - (*iter)->data);
		if (dist < radius)
			out_nodes.push_back((*iter));
	}
}