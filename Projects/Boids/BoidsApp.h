#pragma once

#include "Application.h"
#include "Renderer2D.h"

class Agent;

class BoidsApp : public aie::Application {
public:

	BoidsApp();
	virtual ~BoidsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void ResetAgentsCenter();
	void ResetAgentsGrid(unsigned int numCols, float xSpacing, float ySpacing);

protected:

	const unsigned int NUM_AGENTS = 50;
	aie::Texture *m_agentTexture = nullptr;
	Agent *m_agents = nullptr;

	float m_seperationRadius = 32;
	float m_neibourRadious = 50;
	float m_seperationWeight = 1.0f;
	float m_allignmentWeight = 1.0f;
	float m_cohesiouWeight = 1.0f;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};