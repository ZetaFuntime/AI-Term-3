#pragma once

#include "Graph.h"
#include <glm\vec2.hpp>

class Graph2D : public Graph<glm::vec2, float>
{
public:

	Graph2D();
	virtual ~Graph2D();

	// Todo: Add Save file and Load file functionality

	//void SaveToFile(const char *filename);
	//void LoadFromFile(const char *filename);

	void GetNearbyNodes(const glm::vec2& pos, float radius, std::vector<Graph2D::Node *> &out_nodes);

protected:
private:
};