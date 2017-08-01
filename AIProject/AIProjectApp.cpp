#include "AIProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include "GameObject.h"
#include "KeyboardBehaviour.h"
#include "Agent.h"

#include "Graph.h"
#include "Graph2D.h"
#include "Graph2DRenderer.h"

#include <glm\glm.hpp>

AIProjectApp::AIProjectApp() {

}

AIProjectApp::~AIProjectApp() {

}

bool AIProjectApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_graph = new Graph2D();
	m_graphRenderer = new Graph2DRenderer();
	m_graphRenderer->SetGraph(m_graph);

	SetupGraph();
	for (unsigned int i = 0; i < 20; i++)
	{
		AddAgent();
	}
	return true;
}

void AIProjectApp::shutdown() {

	delete m_graphRenderer;
	delete m_graph;

	for (auto iter = m_Agents.begin(); iter != m_Agents.end(); iter++)
	{
		delete (*iter);
	}

	delete m_font;
	delete m_2dRenderer;
}

void AIProjectApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_graphRenderer->Update(deltaTime);

	for (auto iter = m_Agents.begin(); iter != m_Agents.end(); iter++)
	{
		(*iter)->Update(deltaTime);
	}
	//m_player->Update(deltaTime);

	UpdateGraph(deltaTime);

	// wrap the player around the screen
	// ---------------------------------
	for (auto iter = m_Agents.begin(); iter != m_Agents.end(); iter++)
	{
		//-----------------Original code for wrapping the agents around the screen-------------
		const glm::vec2 &agentPos = (*iter)->GetPosition();
		if (agentPos.x < 0) (*iter)->SetPosition(glm::vec2(getWindowWidth(), agentPos.y));
		if (agentPos.x > getWindowWidth()) (*iter)->SetPosition(glm::vec2(0, agentPos.y));
		if (agentPos.y < 0) (*iter)->SetPosition(glm::vec2(agentPos.x, getWindowHeight()));
		if (agentPos.y > getWindowHeight()) (*iter)->SetPosition(glm::vec2(agentPos.x, 0));

		//-------------------------Original code for bouncing off edges------------------------
		//const glm::vec2 &agentPos = (*iter)->GetPosition();
		//if (agentPos.x < 0) (*iter)->ApplyForce(glm::vec2(10000,0));
		//if (agentPos.x > getWindowWidth()) (*iter)->ApplyForce(glm::vec2(-10000, 0));
		//if (agentPos.y < 0) (*iter)->ApplyForce(glm::vec2(0, 10000));
		//if (agentPos.y > getWindowHeight()) (*iter)->ApplyForce(glm::vec2(0, -10000));

		//------------------Original code for bouncing off edges with correct velocity---------
		//const glm::vec2 &agentVel = (*iter)->GetVelocity();
		//const glm::vec2 &agentPos = (*iter)->GetPosition();
		//if (agentPos.x < 0 || agentPos.x > getWindowWidth()) (*iter)->ApplyForce(glm::vec2(-(agentVel.x*2),0));
		//if (agentPos.y < 0 || agentPos.y > getWindowHeight()) (*iter)->ApplyForce(glm::vec2(0, -agentVel.y*2));
	}

}

void AIProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	DrawGraph();

	for (auto iter = m_Agents.begin(); iter != m_Agents.end(); iter++)
	{
		(*iter)->Draw(m_2dRenderer);
	}
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void AIProjectApp::SetupGraph()
{
	int numRows = 10;
	int numCols = 15;
	float spacing = 50;
	float xOffset = 50;
	float yOffset = 50;
	m_graphToMouseDistance = spacing;

	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			m_graph->AddNode(glm::vec2(
				x * spacing + xOffset,
				y * spacing + yOffset
			));
		}
	}

	// loop through all the nodes
	auto nodes = m_graph->GetNodes();
	for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		auto node = (*iter);
		// get all nodes within a radius around the current node
		std::vector<Graph2D::Node *> surroundingNodes;
		m_graph->GetNearbyNodes(node->data, 75, surroundingNodes);
		for (auto connectionsIter = surroundingNodes.begin(); connectionsIter != surroundingNodes.end(); connectionsIter++)
		{
			// make sure we don't connect to ourselves
			if ((*connectionsIter) == node)
				continue;

			float dist = glm::length((*connectionsIter)->data - node->data);
			m_graph->AddEdge(node, (*connectionsIter), dist, false);
		}
	}
}

void AIProjectApp::DrawGraph()
{
	m_graphRenderer->Draw(m_2dRenderer);
	// Render lines from the mouse position to nearby nodes
	m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
	std::vector<Graph2D::Node *> surroundingNodes;
	m_graph->GetNearbyNodes(m_mousePos, 75, surroundingNodes);
	for (auto Iter = surroundingNodes.begin(); Iter != surroundingNodes.end(); Iter++)
	{
		m_2dRenderer->drawLine(m_mousePos.x, m_mousePos.y, (*Iter)->data.x, (*Iter)->data.y);
	}
}

void AIProjectApp::UpdateGraph(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	m_graphRenderer->Update(deltaTime);
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		std::vector<Graph2D::Node *> surroundingNodes;
		m_graph->GetNearbyNodes(m_mousePos, 75, surroundingNodes);

		auto addedNode = m_graph->AddNode(m_mousePos);

		for (auto iter = surroundingNodes.begin(); iter != surroundingNodes.end(); iter++)
		{
			float dist = glm::length(addedNode->data - (*iter)->data);
			m_graph->AddEdge((*iter), addedNode, dist, true);
		}
		m_agent->Update(deltaTime);
	}
}

void AIProjectApp::AddAgent()
{
	m_agent = new Agent();
	m_agent->SetPosition(glm::vec2(getWindowWidth()*0.5f, getWindowHeight()*0.5f));
	m_agent->SetGraph(m_graph);
	m_agent->ApplyForce(glm::vec2(1, 1));
	m_Agents.push_back(m_agent);
}