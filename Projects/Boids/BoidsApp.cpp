#include "BoidsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Agent.h"

#include <imgui.h>

BoidsApp::BoidsApp() {

}

BoidsApp::~BoidsApp() {

}

bool BoidsApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_agentTexture = new aie::Texture("./textures/Agent.png");

	m_agents = new Agent[NUM_AGENTS];

	ResetAgentsCenter();

	return true;
}

void BoidsApp::shutdown() {

	delete[] m_agents;

	delete m_agentTexture;
	delete m_font;
	delete m_2dRenderer;
}

void BoidsApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	for (int i = 0; i < NUM_AGENTS; i++)
	{
		m_agents[i].Flock(m_agents, NUM_AGENTS, 
			m_neibourRadious, m_seperationRadius, 
			m_seperationWeight, m_allignmentWeight, m_cohesiouWeight);
		m_agents[i].Update(deltaTime);
		m_agents[i].WrapAroundScreen(getWindowWidth(), getWindowHeight());
	}

	ImGui::SliderFloat("Neibourhood Radius", &m_neibourRadious, 0, 200.0f);
	ImGui::SliderFloat("Seperation Radius", &m_seperationRadius, 0, m_neibourRadious);
	ImGui::SliderFloat("Allignment Weight", &m_allignmentWeight, 0.0f, 5.0f);
	ImGui::SliderFloat("Seperation Weight", &m_seperationWeight, 0.0f, 5.0f);
	ImGui::SliderFloat("Cohesion Weight", &m_cohesiouWeight, 0.0f, 1.0f);
	if (ImGui::Button("Reset Center")) ResetAgentsCenter();
	if (ImGui::Button("Reset Grid")) ResetAgentsGrid(15, getWindowWidth() / 15.0f, getWindowHeight() / 7.5f);
}

void BoidsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!

	for (int i = 0; i < NUM_AGENTS; i++)
	{
		m_agents[i].Draw(m_2dRenderer);
	}
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void BoidsApp::ResetAgentsCenter()
{
	glm::vec2 agentStartPos(getWindowWidth() / 2.0f, getWindowHeight() / 2.0f);
	glm::vec2 agentStartVel;
	for (int i = 0; i < NUM_AGENTS; i++)
	{
		float a = (360.0f / (float)NUM_AGENTS) * (float)i;

		agentStartVel.x = sin(a);
		agentStartVel.y = cos(a);

		m_agents[i].Init(m_agentTexture, agentStartPos, agentStartVel, 100);
	}
}
void BoidsApp::ResetAgentsGrid(unsigned int numCols, float xSpacing, float ySpacing)
{
	for (int i = 0; i < NUM_AGENTS; i++)
	{

		unsigned int xi = i % numCols;
		unsigned int yi = i / numCols;

		m_agents[i].Init(m_agentTexture, glm::vec2(xi*xSpacing, yi*ySpacing), glm::vec2(0, 1), 100.0f);

	}
}