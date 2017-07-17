#include "KeyboardBehaviour.h"
#include <Input.h>
#include "GameObject.h"
KeyboardBehaviour::KeyboardBehaviour(int upKey, int downKey, int leftKey, int rightKey) :
	Behaviour(),
	m_upKey(upKey),
	m_downKey(downKey),
	m_rightKey(rightKey),
	m_leftKey(leftKey)
{
	if (m_upKey == 0) m_upKey = aie::INPUT_KEY_W;
	if (m_downKey == 0) m_downKey = aie::INPUT_KEY_S;
	if (m_leftKey == 0) m_leftKey = aie::INPUT_KEY_A;
	if (m_rightKey == 0) m_rightKey = aie::INPUT_KEY_D;
}

KeyboardBehaviour::~KeyboardBehaviour()
{

}

void KeyboardBehaviour::Update(GameObject * object, float deltaTime)
{
	if (aie::Input::getInstance()->isKeyDown(m_upKey))
		object->ApplyForce(glm::vec2(0, 100));
	if (aie::Input::getInstance()->isKeyDown(m_downKey))
		object->ApplyForce(glm::vec2(0, -100));
	if (aie::Input::getInstance()->isKeyDown(m_leftKey))
		object->ApplyForce(glm::vec2(-100, 0));
	if (aie::Input::getInstance()->isKeyDown(m_rightKey))
		object->ApplyForce(glm::vec2(100, 0));
}

int KeyboardBehaviour::GetUpKey()
{
	return m_upKey;
}

int KeyboardBehaviour::GetDownKey()
{
	return m_downKey;
}

int KeyboardBehaviour::GetLeftKey()
{
	return m_leftKey;
}

int KeyboardBehaviour::GetRightKey()
{
	return m_rightKey;
}

void KeyboardBehaviour::SetUpKey(int key)
{
	m_upKey = key;
}

void KeyboardBehaviour::SetDownKey(int key)
{
	m_downKey = key;
}

void KeyboardBehaviour::SetLeftKey(int key)
{
	m_leftKey = key;
}

void KeyboardBehaviour::SetRightKey(int key)
{
	m_rightKey = key;
}
