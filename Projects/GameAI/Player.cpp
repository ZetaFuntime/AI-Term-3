#include "Player.h"
#include "KeyboardBehaviour.h"
#include "SeekBehaviour.h"

#include <Input.h>

Player::Player() : GameObject()
{
	m_keyboardBehaviour = new KeyboardBehaviour();
	m_keyboardBehaviour->IsOwnedByGameObject(false);

	m_seekBehaviour = new SeekBehaviour();
	m_seekBehaviour->IsOwnedByGameObject(false);
	m_seekBehaviour->SetForceStrength(100);
	m_seekBehaviour->SetInnerRadius(20);
	m_seekBehaviour->SetOuterRadius(100);
	m_seekBehaviour->OnInnerRadiusEnter([this]() {
		SetBehaviour(m_keyboardBehaviour);
	});

	m_fleeBehaviour = new SeekBehaviour();
	m_fleeBehaviour->IsOwnedByGameObject(false);
	m_fleeBehaviour->SetForceStrength(-100);
	m_fleeBehaviour->SetInnerRadius(20);
	m_fleeBehaviour->SetOuterRadius(100);
	m_fleeBehaviour->OnOuterRadiusExit([this]() {
	 SetBehaviour(m_keyboardBehaviour);
	});

	SetBehaviour(new KeyboardBehaviour());

	SetFriction(0.25f);
}

Player::~Player()
{
	SetBehaviour(nullptr);

	delete m_fleeBehaviour;
	delete m_seekBehaviour;
	delete m_keyboardBehaviour;
}

void Player::Update(float deltaTime)
{
	// todo: player update logic stuff
	aie::Input *input = aie::Input::getInstance();
	int mX, mY;
	input->getMouseXY(&mX, &mY);

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		m_seekBehaviour->SetTarget(glm::vec2(mX,mY));
		SetBehaviour ( m_seekBehaviour);
	}
	else if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		m_fleeBehaviour->SetTarget(glm::vec2(mX,mY));
		SetBehaviour( m_fleeBehaviour );
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