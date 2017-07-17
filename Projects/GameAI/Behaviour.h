#pragma once

class GameObject;
namespace aie
{
	class Renderer2D;
};

class Behaviour 
{
public:

	Behaviour() { }
	virtual ~Behaviour() { }

	virtual void Update(GameObject * object, float deltaTime) { }
	virtual void Draw(GameObject *object, aie::Renderer2D *renderer) { }

protected:
private:
};