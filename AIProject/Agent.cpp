#include "Agent.h"
#include "KeyboardBehaviour.h"
#include "SeekBehaviour.h"
#include "Path.h"
#include "FollowPathBehaviour.h"
#include "WanderBehaviour.h"
#include "ArrivalBehaviour.h"

#include <glm\glm.hpp>
#include <Input.h>
#include <Renderer2D.h>
#include <Texture.h>
#include <math.h>
#include <iostream>

#include "Graph2D.h"
#include "Pathfinder.h"

Agent::Agent(aie::Texture *tex) : 
	GameObject(tex),
	m_startNode(nullptr),
	m_endNode(nullptr),
	m_graph(nullptr)
{
	m_keyboardBehaviour = new KeyboardBehaviour();
	m_keyboardBehaviour->IsOwnedByGameObject(false);

	m_seekBehaviour = new SeekBehaviour();
	m_seekBehaviour->IsOwnedByGameObject(false);
	m_seekBehaviour->OnOuterRadiusEnter([this]() {
		m_arrivalBehaviour->SetTarget(m_seekBehaviour->GetTarget());
		SetBehaviour(m_arrivalBehaviour);
	});

	m_fleeBehaviour = new SeekBehaviour();
	m_fleeBehaviour->IsOwnedByGameObject(false);
	m_fleeBehaviour->SetForceStrength(-100);
	m_fleeBehaviour->OnOuterRadiusExit([this]() {
		SetBehaviour(m_wanderBehaviour);
	});

	m_arrivalBehaviour = new ArrivalBehaviour();
	m_arrivalBehaviour->IsOwnedByGameObject(false);
	m_arrivalBehaviour->OnTargetRadiusEnter([this]() {
		SetBehaviour(m_keyboardBehaviour);
	});

	m_path = new Path();

	m_followPathBehaviour = new FollowPathBehaviour();
	m_followPathBehaviour->IsOwnedByGameObject(false);
	m_followPathBehaviour->SetPath(m_path);

	m_wanderBehaviour = new WanderBehaviour();
	m_wanderBehaviour->IsOwnedByGameObject(false);

	SetBehaviour(new KeyboardBehaviour());

	SetFriction(1.0f);

	prevLocation = GetPosition();
	m_effectLength = 8.0f;

	SetDraw(true);
}

Agent::~Agent()
{
	SetBehaviour(nullptr);

	delete m_path;
	delete m_followPathBehaviour;
	delete m_fleeBehaviour;
	delete m_seekBehaviour;
	delete m_keyboardBehaviour;
	delete m_wanderBehaviour;
}

void Agent::Update(float deltaTime)
{
	// todo: player update logic stuff
	aie::Input *input = aie::Input::getInstance();
	input->getMouseXY(&mX, &mY);

	// --------------- Seek Behaviour Command ----------------------
	// Agent will seek towards a given point from the user
	// -------------------------------------------------------------
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		m_seekBehaviour->SetTarget(glm::vec2(mX, mY));
		SetBehaviour(m_seekBehaviour);
	}

	// --------------- Flee Behaviour Command ----------------------
	// Agent will flee from a given point from the user
	// -------------------------------------------------------------
	else if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		m_fleeBehaviour->SetTarget(glm::vec2(mX, mY));
		SetBehaviour(m_fleeBehaviour);
	}

	// --------------- Follow Behaviour Command --------------------
	// Agent will follow a path designated by the user, from the
	// start point to the end point.
	// -------------------------------------------------------------
	else if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_MIDDLE))
	{
		DoPathLogic();
	}

	else if (GetBehaviour() != m_followPathBehaviour)
	{
		m_startNode = nullptr;
		m_endNode = nullptr;
	}

	// --------------- Follow path - Patrol Mode toggle ------------
	// Agent will follow a path designated by the user, between the
	// start point and the end point.
	// (Only available during follow path behaviour)
	// -------------------------------------------------------------
	if (GetBehaviour() == m_followPathBehaviour && input->wasKeyPressed(aie::INPUT_KEY_TAB))
	{
		if (!m_followPathBehaviour->GetPatrolActivity()) {
			m_followPathBehaviour->SetPatrolMode(true);
		}
		else {
			m_followPathBehaviour->SetPatrolMode(false);
		}
	}
	// --------------- Wander Behaviour Command --------------------
	// Agents will automatically move forward with a random force
	// with the direction being adjusted at random intervals with
	// random amounts.
	// -------------------------------------------------------------
	else if (input->wasKeyPressed(aie::INPUT_KEY_T))
	{
		SetBehaviour(m_wanderBehaviour);
	}
	
	// -------------- Keyboard Behaviour Command -------------------
	// Agents will follow direction given by WASD controls from
	// the user.
	// -------------------------------------------------------------
	if (GetBehaviour() != m_keyboardBehaviour && input->wasKeyPressed(aie::INPUT_KEY_BACKSPACE))
	{
		SetBehaviour(m_keyboardBehaviour);
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_UP))
	{
		SetDraw(true);
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
	{
		SetDraw(false);
	}

	// Update all gameobjects currently in use
	GameObject::Update(deltaTime);

	// Update the trails left by player objects
	DoTrailLogic();
}

void Agent::Draw(aie::Renderer2D *renderer)
{
	// temp rendering for start and end node
	if (m_startNode != nullptr) renderer->drawCircle(m_startNode->data.x, m_startNode->data.y, 4);
	if (m_endNode != nullptr) renderer->drawCircle(m_endNode->data.x, m_endNode->data.y, 4);

	// Draw path that has been travelled
	for (auto iter = m_prevPoints.begin(); iter != m_prevPoints.end(); iter++)
	{

		renderer->setRenderColour(iter->colour);
		renderer->drawBox(iter->data.x, iter->data.y, 4.f, 1.f, iter->rotation);
	}

	// Draw all gameobjects currently in use
	GameObject::Draw(renderer);
}

void Agent::SetGraph(Graph2D *graph)
{
	m_graph = graph;
}

Graph2D *Agent::GetGraph()
{
	return m_graph;
}

void Agent::DoPathLogic()
{
	std::vector<Graph2D::Node *> nearbyNodes;
	m_graph->GetNearbyNodes(glm::vec2(mX, mY), 8, nearbyNodes);

	if (nearbyNodes.empty() == false)
	{
		if (m_startNode == nullptr)
		{
			m_startNode = nearbyNodes[0];
		}
		else if (m_endNode == nullptr)
		{
			m_endNode = nearbyNodes[0];
			m_pathfinder = new Pathfinder(m_graph);
			m_pathfinder->FindPath(m_startNode, [this](Graph2D::Node *n) {
				return n == m_endNode;
			});

			while (m_pathfinder->PathFound() == false)
			{
				m_pathfinder->UpdateSearch();
			}

			Path &p = m_pathfinder->GetPath();
			auto pathPoints = p.GetPath();
			for (auto iter = pathPoints.rbegin(); iter != pathPoints.rend(); iter++)
			{
				m_path->PushPathSegment((*iter));
			}

			//m_path->Clear();
			//m_path->PushPathSegment(m_startNode->data);
			//m_path->PushPathSegment(m_endNode->data);

			SetBehaviour(m_followPathBehaviour);
		}
		else
		{
			m_startNode = nullptr;
			m_endNode = nullptr;
			delete m_pathfinder;
			m_pathfinder = nullptr;
			m_path->Clear();
		}
	}
	if (GetBehaviour() != m_followPathBehaviour)
	{
		SetBehaviour(m_followPathBehaviour);
		m_path->Clear();
	}
	//m_path->PushPathSegment(glm::vec2(mX, mY));
}

void Agent::DoTrailLogic()
{
	float dist = glm::length(GetPosition() - prevLocation);
	if (dist > m_effectLength)
	{
		// Record the latest point
		Pos prevPoint;
		prevPoint.data = GetPosition();

		glm::vec2 targetHeading = prevPoint.data + GetVelocity();
		prevPoint.rotation = atan2f(targetHeading.y - prevPoint.data.y,
			targetHeading.x - prevPoint.data.x);

		int randnum = rand() % 10;
		switch (randnum)
		{
		case 1:		prevPoint.colour = BLUE;	break;
		case 2:		prevPoint.colour = RED;		break;
		case 3:		prevPoint.colour = YELLOW;	break;
		case 4:		prevPoint.colour = GREEN;	break;
		case 5:		prevPoint.colour = ORANGE;	break;
		case 6:		prevPoint.colour = TEAL;	break;
		case 7:		prevPoint.colour = PURPLE;	break;
		case 8:		prevPoint.colour = PINK;	break;
		case 9:		prevPoint.colour = WHITE;	break;
		case 10:	prevPoint.colour = DARKBLUE; break;
		default:	prevPoint.colour = WHITE;	break;
		}

		m_prevPoints.push_back(prevPoint);

		// If the trail gets too long, pop the last point
		if (m_prevPoints.size() > 50)
			m_prevPoints.pop_front();

		// Update previous position
		prevLocation = GetPosition();
	}
}