#pragma once

#include "Behaviour.h"
#include <functional>
class Path;

class FollowPathBehaviour : public Behaviour
{
public:
	FollowPathBehaviour();
	virtual ~FollowPathBehaviour();

	virtual void Update(GameObject *object, float deltaTime);
	virtual void Draw(GameObject *object, aie::Renderer2D *renderer);

	void SetPath(Path *path);
	Path *GetPath();

	float GetForceStrength();
	void SetForceStrength(float strength);

	void SetNodeRadius(float radius);
	float GetNodeRadius();

	void SetPatrolMode(bool activity);
	bool GetPatrolActivity();

	bool CheckPathComplete();

	void OnEndPathEnter(std::function< void() > func);

protected:

	int m_currentPathNodeIndex;

	Path *m_path;

	float m_forceStrength;
	float m_nodeRadius;

	std::function< void() > m_onEndPathEnter;
	bool m_patrolBack;
	bool m_patrolMode;
	bool m_pathComplete;

private:

};