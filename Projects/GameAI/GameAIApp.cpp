#include "GameAIApp.h"
#include <Texture.h>
#include <Font.h>
#include <Input.h>

#include "GameObject.h"
#include "KeyboardBehaviour.h"
#include "Player.h"

#include "Graph.h"
#include "Graph2D.h"
#include "Graph2DRenderer.h"

#include <glm\glm.hpp>
GameAIApp::GameAIApp() {

}

GameAIApp::~GameAIApp() {

}

bool GameAIApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	
	
	m_graph = new Graph2D();
	m_graphRenderer = new Graph2DRenderer();
	m_graphRenderer->SetGraph(m_graph);

	SetupGraph();

	m_player = new Player();
	m_player->SetPosition(glm::vec2(getWindowWidth()*0.5f, getWindowHeight()*0.5f));
	m_player->SetGraph(m_graph);




	return true;
}

void GameAIApp::shutdown() {

	delete m_graphRenderer;
	delete m_graph;
	delete m_player;
	delete m_font;
	delete m_2dRenderer;
}

void GameAIApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();
	int mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);
	m_mousePos = glm::vec2(mouseX, mouseY);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_graphRenderer->Update(deltaTime);
	
	m_player->Update(deltaTime);

	UpdateGraph(deltaTime);
	// wrap the player around the screen
	// ---------------------------------
	const glm::vec2 &playerPos = m_player->GetPosition();
	if (playerPos.x < 0) m_player->SetPosition(glm::vec2(getWindowWidth(), playerPos.y));
	if (playerPos.x > getWindowWidth()) m_player->SetPosition(glm::vec2(0, playerPos.y));
	if (playerPos.y < 0) m_player->SetPosition(glm::vec2(playerPos.x, getWindowHeight()));
	if (playerPos.y > getWindowHeight()) m_player->SetPosition(glm::vec2(playerPos.x, 0));
	// ---------------------------------
}

void GameAIApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	DrawGraph();

	m_player->Draw(m_2dRenderer);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void GameAIApp::SetupGraph()
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

void GameAIApp::DrawGraph()
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

void GameAIApp::UpdateGraph(float deltaTime)
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
		m_player->Update(deltaTime);
	}
}