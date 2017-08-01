#include "Path.h"

Path::Path()
{
}

Path::~Path()
{
}

void Path::PushPathSegment(const glm::vec2 & point)
{
	m_pathPoints.push_back(point);
}

void Path::PopPathSegment()
{
	if (m_pathPoints.empty() == false)
		m_pathPoints.pop_back();
}

void Path::Clear()
{
	m_pathPoints.clear();
}

std::vector<glm::vec2>& Path::GetPath()
{
	return m_pathPoints;
}