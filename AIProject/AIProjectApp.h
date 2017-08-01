#pragma once

#include "Application.h"
#include "Renderer2D.h"

#include <glm\vec2.hpp>
#include <vector>

class GameObject;
class Graph2D;
class Graph2DRenderer;
class Agent;

class AIProjectApp : public aie::Application {
public:

	AIProjectApp();
	virtual ~AIProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void SetupGraph();
	void UpdateGraph(float deltaTime);
	void AddAgent();
	void DrawGraph();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	glm::vec2			m_mousePos;
	float				m_graphToMouseDistance;

	std::vector<Agent* > m_Agents;

	Agent			*m_agent = nullptr;
	Graph2D			*m_graph;

	aie::Texture	*m_agentTex = nullptr;
	
	Graph2DRenderer *m_graphRenderer;
};