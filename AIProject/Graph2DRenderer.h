#pragma once

class Graph2D;
namespace aie {

	class Renderer2D;
}

class Graph2DRenderer
{
public:

	Graph2DRenderer();
	~Graph2DRenderer();

	void Update(float dt);
	void Draw(aie::Renderer2D *renderer);

	Graph2D *GetGraph();
	void SetGraph(Graph2D *graph);

protected:

	Graph2D *m_graph;

private:
};