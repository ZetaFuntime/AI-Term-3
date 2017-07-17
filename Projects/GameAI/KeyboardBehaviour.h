#pragma once
#include "Behaviour.h"

class KeyboardBehaviour : public Behaviour
{
public:
	KeyboardBehaviour(int upKey = 0, int downKey = 0, int leftKey = 0, int rightKey = 0);
	virtual ~KeyboardBehaviour();

	virtual void Update(GameObject *object, float deltaTime);

	int GetUpKey();
	int GetDownKey();
	int GetLeftKey();
	int GetRightKey();

	void SetUpKey(int key);
	void SetDownKey(int key);
	void SetLeftKey(int key);
	void SetRightKey(int key);

protected:

	int m_upKey;
	int m_downKey;
	int m_leftKey;
	int m_rightKey;
private:
};