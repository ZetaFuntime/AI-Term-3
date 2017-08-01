#include "Graph2DRenderer.h"
#include "Graph2D.h"
#include <Renderer2D.h>

Graph2DRenderer::Graph2DRenderer() : m_graph(nullptr)
{

}

Graph2DRenderer::~Graph2DRenderer()
{

}

void Graph2DRenderer::Update(float dt)
{

}

void Graph2DRenderer::Draw(aie::Renderer2D *renderer)
{
	renderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.25f);
	// Render each of the nodes
	auto &nodes = m_graph->GetNodes();
	for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		Graph2D::Node *node = (*iter);
		renderer->drawCircle(node->data.x, node->data.y, 8);
	}

	// Render a line between each of the node connections
	for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		Graph2D::Node *node = (*iter);
		auto &edges = node->connections;
		for (auto eIter = edges.begin(); eIter != edges.end(); eIter++)
		{
			Graph2D::Node *to = (*eIter).to;
			renderer->drawLine(
				node->data.x, node->data.y,
				to->data.x, to->data.y, 1.0f);
		}
	}
}

Graph2D *Graph2DRenderer::GetGraph()
{
	return m_graph;
}

void Graph2DRenderer::SetGraph(Graph2D *graph)
{
	m_graph = graph;
}