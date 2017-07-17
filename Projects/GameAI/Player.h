#pragma once

#include "GameObject.h"
#include "KeyboardBehaviour.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D *renderer);

protected:

	KeyboardBehaviour *m_keyboardBehaviour;
private:
};