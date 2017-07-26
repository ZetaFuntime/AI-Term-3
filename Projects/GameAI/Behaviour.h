#pragma once

class GameObject;
namespace aie
{
	class Renderer2D;
};

class Behaviour 
{
public:

	Behaviour() : m_isOwned(true) { }
	virtual ~Behaviour() { }

	virtual void Update(GameObject * object, float deltaTime) { }
	virtual void Draw(GameObject *object, aie::Renderer2D *renderer) { }

	bool IsOwnedByGameObject() { return m_isOwned; }
	void IsOwnedByGameObject(bool isOwned) { m_isOwned = isOwned; }

	bool IsActive() { return m_isActive; }
	void IsActive(bool amIactive) { m_isActive = amIactive; }

protected:

	bool m_isOwned;
	bool m_isActive;

private:
};