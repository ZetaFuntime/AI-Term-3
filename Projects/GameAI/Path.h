#pragma once

#include <glm\vec2.hpp>
#include <vector>

class Path
{
public:
	Path();
	~Path();

	void PushPathSegment(const glm::vec2& point);
	void PopPathSegment();

	void Clear();

	std::vector<glm::vec2> &GetPath();

protected:

	std::vector<glm::vec2> m_pathPoints;
private:
};