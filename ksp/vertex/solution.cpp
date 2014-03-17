#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
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
	
	void createNodes(uint nNodes) {
		nodes.resize(0);
		nodes.push_back(Node(0));
		for (uint nodeId = 1; nodeId <= nNodes; ++nodeId)
			nodes.push_back(Node(nodeId));
	}
	
	void addEdge(uint nodeFromId, uint nodeToId) {
		nodes[nodeFromId].connectedNodes.push_back(nodes[nodeToId]);
	}
	
	void unvisit() {
		for (Node& node: nodes)
			node.visited = false;
	}
	
	void visitComponent(Node& node) {
		for (Node& connectedNode: node.connectedNodes)
			if (!connectedNode.visited)
			{
				connectedNode.visited = true;
				visitComponent(connectedNode);
			}
	}
	
	NodeRefs getUnreachableNodes(uint nodeSourceId) {
		NodeRefs unreachableNodes;
		
		unvisit();
		visitComponent(nodes[nodeSourceId]);
		
		for (Node& node: nodes)
			if (node.id > 0 && !node.visited)
				unreachableNodes.push_back(node);
		
		return unreachableNodes;
	}
};

int main() {
	while (true)
	{
		uint nNodes;
		std::cin >> nNodes;
		
		if (nNodes == 0)
			break;
		
		Graph graph;
		graph.createNodes(nNodes);
		
		while (true)
		{
			uint nodeFromId;
			std::cin >> nodeFromId;
			
			if (nodeFromId == 0)
				break;
			
			while (true)
			{
				uint nodeToId;
				std::cin >> nodeToId;
				
				if (nodeToId == 0)
					break;
				
				graph.addEdge(nodeFromId, nodeToId);
			}
		}
		
		uint nTests;
		std::cin >> nTests;
		
		for (uint iTest = 0; iTest < nTests; ++iTest)
		{
			uint nodeSourceId;
			std::cin >> nodeSourceId;
			
			NodeRefs unreachableNodes = graph.getUnreachableNodes(nodeSourceId);
			std::cout << unreachableNodes.size();
			for (Node& node: unreachableNodes)
				std::cout << ' ' << node.id;
			std::cout << std::endl;
		}
	}
	
	return 0;
}
