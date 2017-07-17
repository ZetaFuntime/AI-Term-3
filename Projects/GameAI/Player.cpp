#include "Player.h"
#include "KeyboardBehaviour.h"
#include <Input.h>
Player::Player() : GameObject()
{
	m_keyboardBehaviour = new KeyboardBehaviour();
	m_keyboardBehaviour->IsOwnedByGameObject(false);

	//m_seekBehaviour = new SeekBehaviour();
	//m_seekBehaviour->SetStrength(100);
	//
	//m_fleeBehaviour = new fleeBehaviour();
	// m_fleeBehaviour->SetStrength(100);
	SetBehaviour(new KeyboardBehaviour());

	SetFriction(0.25f);
}

Player::~Player()
{
	SetBehaviour(nullptr);

	//delete m_seekBehaviour;
	delete m_keyboardBehaviour;
}

void Player::Update(float deltaTime)
{
	// todo: player update logic stuff
	aie::Input *input = aie::Input::getInstance();
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		/*
		m_seekBehaviour = new SeekBehaviour(mouseX,mouseY);
		m_seek->SetStrength(100);
		m_seek->SetTarget(glm::vec2(mX,mY);
		SetBehaviour ( m_seek );
		*/
	}
	else if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		 /*
			  m_flee->SetTarget(glm::vec2(mX,mY));
			  SetBehaviour( m_flee );
		 */
	}

	if (GetBehaviour() != m_keyboardBehaviour && input->getPressedKeys().empty() == false)
	{
		SetBehaviour(m_keyboardBehaviour);
	}

	GameObject::Update(deltaTime);
}

void Player::Draw(aie::Renderer2D *renderer)
{
	// todo: player rendering logic stuff
	GameObject::Draw(renderer);
}