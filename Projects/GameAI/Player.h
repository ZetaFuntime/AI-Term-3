#pragma once

#include "GameObject.h"
class KeyboardBehaviour;
class SeekBehaviour;
class FollowPathBehaviour;
class Path;

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D *renderer);

protected:

	KeyboardBehaviour *m_keyboardBehaviour;
	SeekBehaviour *m_seekBehaviour;
	SeekBehaviour *m_fleeBehaviour;
	FollowPathBehaviour *m_followPathBehaviour;

	Path *m_path;


private:
};