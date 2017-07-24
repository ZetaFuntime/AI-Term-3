#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <glm\vec2.hpp>

class GameObject;
class Graph2D;
class Graph2DRenderer;
class Player;

class GameAIApp : public aie::Application {
public:

	GameAIApp();
	virtual ~GameAIApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void SetupGraph();
	void UpdateGraph(float deltaTime);
	void DrawGraph();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	glm::vec2			m_mousePos;
	float				m_graphToMouseDistance;

	Player *m_player = nullptr;

	Graph2D *m_graph;
	Graph2DRenderer *m_graphRenderer;
};