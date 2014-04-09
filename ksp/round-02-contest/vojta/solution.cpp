#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

typedef unsigned int uint;

struct Node;
typedef std::reference_wrapper<Node> NodeRef;
typedef std::vector<NodeRef> NodeRefs;
typedef std::vector<Node> Nodes;

struct Node {
	uint id;
	bool visited;
	NodeRefs connectedNodes;
	
	Node():
		id(0),
		visited(false),
		connectedNodes(NodeRefs()) {
	}
	
	Node(uint id):
		id(id),
		visited(false),
		connectedNodes(NodeRefs()) {
	}
};

struct Graph {
	Nodes nodes;
	
	Graph():
		nodes(Nodes()) {
	}
	
	void createNodes(const uint nNodes) {
		nodes.resize(0);
		for (uint nodeId = 0; nodeId < nNodes; ++nodeId)
			nodes.push_back(Node(nodeId));
	}
	
	void addEdge(const uint node1Id, const uint node2Id) {
		Node& node1 = nodes[node1Id];
		Node& node2 = nodes[node2Id];
		
		node1.connectedNodes.push_back(node2);
		node2.connectedNodes.push_back(node1);
	}
	
	void visitComponent(Node& node) {
		node.visited = true;
		
		for (Node& connectedNode: node.connectedNodes)
			if (!connectedNode.visited)
			{
				connectedNode.visited = true;
				visitComponent(connectedNode);
			}
	}
	
	uint getVisitedNodesCount() const {
		uint nVisitedNodes = 0;
		
		for (const Node& node: nodes)
			if (node.visited)
				++nVisitedNodes;
		
		return nVisitedNodes;
	}
};

int main() {
	uint nCases;
	std::cin >> nCases;
	
	for (uint iCase = 0; iCase < nCases; ++iCase)
	{
		uint nNodes, vojtaId;
		std::cin >> nNodes >> vojtaId;
		
		Graph facebook;
		facebook.createNodes(nNodes);
		
		while (true)
		{
			uint node1Id, node2Id;
			std::cin >> node1Id >> node2Id;
			if (node1Id == 0 && node2Id == 0)
				break;
			
			facebook.addEdge(node1Id, node2Id);
		}
		
		Node& vojta = facebook.nodes[vojtaId];
		facebook.visitComponent(vojta);
		uint nVisitedNodesWithoutVojta = facebook.getVisitedNodesCount() - 1;
		std::cout << nVisitedNodesWithoutVojta << std::endl;
	}
	
	return 0;
}
