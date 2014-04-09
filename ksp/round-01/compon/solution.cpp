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
typedef std::map<char, Node> NodeMap;

struct Node {
	NodeRefs connectedNodes;
	bool visited;
	
	Node():
		connectedNodes(NodeRefs()),
		visited(false) {
	}
};

struct Graph {
	NodeMap nodes;
	
	Graph():
		nodes(NodeMap()) {
	}
	
	void ensureNodeExists(char nodeName) {
		if (nodes.count(nodeName) == 0)
			nodes[nodeName] = Node();
	}
	
	void addEdge(char nodeName1, char nodeName2) {
		ensureNodeExists(nodeName1);
		ensureNodeExists(nodeName2);
		
		nodes[nodeName1].connectedNodes.push_back(nodes[nodeName2]);
		nodes[nodeName2].connectedNodes.push_back(nodes[nodeName1]);
	}
	
	void visitComponent(Node& node) {
		node.visited = true;
		for (Node& connectedNode: node.connectedNodes)
			if (!connectedNode.visited)
				visitComponent(connectedNode);
	}
	
	uint getComponentCount() {
		uint componentCount = 0;
		for (auto nodeKeyValuePair: nodes)
		{
			Node& node = nodeKeyValuePair.second;
			
			if (!node.visited)
			{
				++componentCount;
				visitComponent(node);
			}
		}
		return componentCount;
	}
};

int main() {
	std::string line;
	
	uint nCases;
	std::getline(std::cin, line);
	std::stringstream(line) >> nCases;
	std::getline(std::cin, line);
	
	for (uint iCase = 0; iCase < nCases; ++iCase)
	{
		Graph graph;
		
		char lastNodeName;
		std::getline(std::cin, line);
		std::stringstream(line) >> lastNodeName;
		
		for (char nodeName = 'A'; nodeName <= lastNodeName; ++nodeName)
			graph.ensureNodeExists(nodeName);
		
		while (true)
		{
			std::getline(std::cin, line);
			if (std::cin.fail() || line.length() == 0)
				break;
			
			graph.addEdge(line[0], line[1]);
		}
		
		if (iCase > 0)
			std::cout << std::endl;
		std::cout << graph.getComponentCount() << std::endl;
	}
	
	return 0;
}
