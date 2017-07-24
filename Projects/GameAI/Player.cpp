#include "Player.h"
#include "KeyboardBehaviour.h"
#include "SeekBehaviour.h"
#include "Path.h"
#include "FollowPathBehaviour.h"

#include <Input.h>
#include <Renderer2D.h>

#include "Graph2D.h"
#include "Pathfinder.h"

Player::Player() : GameObject()
{
	m_graph =		nullptr;
	m_startNode =	nullptr;
	m_endNode =		nullptr;

	m_keyboardBehaviour = new KeyboardBehaviour();
	m_keyboardBehaviour->IsOwnedByGameObject(false);

	m_seekBehaviour = new SeekBehaviour();
	m_seekBehaviour->IsOwnedByGameObject(false);
	m_seekBehaviour->SetForceStrength(100);
	m_seekBehaviour->SetInnerRadius(20);
	m_seekBehaviour->SetOuterRadius(100);
	m_seekBehaviour->OnInnerRadiusEnter([this]() {
		SetBehaviour(m_keyboardBehaviour);
	});

	m_fleeBehaviour = new SeekBehaviour();
	m_fleeBehaviour->IsOwnedByGameObject(false);
	m_fleeBehaviour->SetForceStrength(-100);
	m_fleeBehaviour->SetInnerRadius(20);
	m_fleeBehaviour->SetOuterRadius(100);
	m_fleeBehaviour->OnOuterRadiusExit([this]() {
	 SetBehaviour(m_keyboardBehaviour);
	});

	m_path = new Path();

	m_followPathBehaviour = new FollowPathBehaviour();
	m_followPathBehaviour->IsOwnedByGameObject(false);
	m_followPathBehaviour->SetPath(m_path);

	SetBehaviour(new KeyboardBehaviour());

	SetFriction(1.0f);
}

Player::~Player()
{
	SetBehaviour(nullptr);

	delete m_path;
	delete m_followPathBehaviour;
	delete m_fleeBehaviour;
	delete m_seekBehaviour;
	delete m_keyboardBehaviour;
}

void Player::Update(float deltaTime)
{
	// todo: player update logic stuff
	aie::Input *input = aie::Input::getInstance();
	int mX, mY;
	input->getMouseXY(&mX, &mY);

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		m_seekBehaviour->SetTarget(glm::vec2(mX,mY));
		SetBehaviour ( m_seekBehaviour);
	}

	else if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		m_fleeBehaviour->SetTarget(glm::vec2(mX,mY));
		SetBehaviour( m_fleeBehaviour );
	}

	else if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_MIDDLE))
	{
		std::vector<Graph2D::Node *> nearbyNodes;
		m_graph->GetNearbyNodes(glm::vec2(mX,mY), 8, nearbyNodes);

		if (nearbyNodes.empty() == false)
		{
			if (m_startNode == nullptr)
			{
				m_startNode = nearbyNodes[0];
			}
			else if (m_endNode == nullptr)
			{
				m_endNode = nearbyNodes[0];
				// TODO: start our pathfinding
				m_pathfinder = new Pathfinder(m_graph);
				m_pathfinder->FindPath(m_startNode, [this](Graph2D::Node *n) {
					return n == m_endNode;
				});

				//while (m_pathfinder->PathFound() == false)
				{
					m_pathfinder->UpdateSearch();
				}

				//Path p = m_pathfinder->GetPath();
				m_path->Clear();
				m_path->PushPathSegment(m_startNode->data);
				m_path->PushPathSegment(m_endNode->data);

				SetBehaviour(m_followPathBehaviour);
			}
			else
			{
				m_startNode = nullptr;
				m_endNode = nullptr;
				delete m_pathfinder;
				m_pathfinder = nullptr;
			}
		}
		//if (GetBehaviour() != m_followPathBehaviour)
		//{
		//	SetBehaviour(m_followPathBehaviour);
		//	m_path->Clear();
		//}
		//
		//m_path->PushPathSegment(glm::vec2(mX, mY));
	}

	if (GetBehaviour() != m_keyboardBehaviour && input->getPressedKeys().empty() == false)
	{
		SetBehaviour(m_keyboardBehaviour);
	}

	GameObject::Update(deltaTime);
}

void Player::Draw(aie::Renderer2D *renderer)
{
	// todo: player rendering logic stuff

	// temp rendering for start and end node
	if (m_startNode != nullptr) renderer->drawCircle(m_startNode->data.x, m_startNode->data.y, 4);
	if (m_endNode != nullptr) renderer->drawCircle(m_endNode->data.x, m_endNode->data.y, 4);
	GameObject::Draw(renderer);
}

void Player::SetGraph(Graph2D *graph)
{
	m_graph = graph;
}

Graph2D *Player::GetGraph()
{
	return m_graph;
}