#include "GameAIApp.h"
#include <Texture.h>
#include <Font.h>
#include <Input.h>

#include "GameObject.h"
#include "KeyboardBehaviour.h"

GameAIApp::GameAIApp() {

}

GameAIApp::~GameAIApp() {

}

bool GameAIApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_player = new GameObject();
	m_player->SetPosition(glm::vec2(getWindowWidth()*0.5f, getWindowHeight()*0.5f));
	m_player->SetFriction(0.5f);
	m_player->SetBehaviour(new KeyboardBehaviour());
	return true;
}

void GameAIApp::shutdown() {

	delete m_player;
	delete m_font;
	delete m_2dRenderer;
}

void GameAIApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_player->ApplyForce(glm::vec2(100, 0));


	m_player->Update(deltaTime); 

	const glm::vec2 &playerPos = m_player->GetPosition();
	if (playerPos.x < 0) m_player->SetPosition(glm::vec2(getWindowWidth(), playerPos.y));
	if (playerPos.x > getWindowWidth()) m_player->SetPosition(glm::vec2(0, playerPos.y));
	if (playerPos.y < 0) m_player->SetPosition(glm::vec2(playerPos.x, getWindowHeight()));
	if (playerPos.y > getWindowHeight()) m_player->SetPosition(glm::vec2(playerPos.x, 0));

}

void GameAIApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_player->Draw(m_2dRenderer);
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}