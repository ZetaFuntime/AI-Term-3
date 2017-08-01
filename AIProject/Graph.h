#pragma once
#include <vector>

template<class TNodeData, class TEdgeData>

class Graph
{
public:

	struct Node;
	struct Edge;

	struct Node
	{
		TNodeData data;
		std::vector<Edge> connections;
	};

	struct Edge
	{
		Node *to;
		TEdgeData data;
	};

public:

	Graph()
	{

	}

	virtual ~Graph()
	{
		for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++)
			delete (*iter);
		m_nodes.clear();
	}

	Node *AddNode(const TNodeData &data)
	{
		Node *node = new Node();
		node->data = data;
		m_nodes.push_back(node);
		return node;
	}

	void AddEdge(Node *nodeA, Node *nodeB, const TEdgeData &data, bool Bidirectional)
	{
		Edge e;
		e.data = data;
		e.to = nodeB;
		nodeA->connections.push_back(e);

		if (Bidirectional)
		{
			AddEdge(nodeB, nodeA, data, false);
		}
	}

	const std::vector<Node*> & GetNodes() {
		return m_nodes;
	}

protected:

	std::vector<Node *> m_nodes;

private:
};