#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include <functional>

typedef unsigned int uint;

struct Node;
typedef std::reference_wrapper<Node> NodeRef;
typedef std::queue<NodeRef> NodeRefQueue;
typedef std::vector<NodeRef> NodeRefs;
typedef std::vector<Node> Nodes;

struct BoomResult {
	uint size;
	uint firstDay;
	
	BoomResult():
		size(0),
		firstDay(0) {
	}
};

struct Node {
	bool visited;
	uint dayVisited;
	NodeRefs connectedNodes;
	
	Node():
		visited(false),
		dayVisited(0),
		connectedNodes(NodeRefs()) {
	}
};

struct Graph {
	Nodes nodes;
	
	Graph():
		nodes(Nodes()) {
	}
	
	void createNodes(uint nNodes) {
		nodes.resize(nNodes);
	}
	
	void addEdge(uint nodeFromId, uint nodeToId) {
		nodes[nodeFromId].connectedNodes.push_back(nodes[nodeToId]);
	}
	
	void unvisit() {
		for (Node& node: nodes)
			node.visited = false;
	}
	
	BoomResult getBoomResult(uint nodeSourceId) {
		NodeRefQueue queue;
		
		unvisit();
		nodes[nodeSourceId].dayVisited = 0;
		nodes[nodeSourceId].visited = true;
		queue.push(nodes[nodeSourceId]);
		
		uint lastDay = 0;
		
		while (!queue.empty())
		{
			Node& node = queue.front();
			queue.pop();
			
			for (Node& connectedNode: node.connectedNodes)
				if (!connectedNode.visited)
				{
					connectedNode.visited = true;
					connectedNode.dayVisited = node.dayVisited + 1;
					queue.push(connectedNode);
					
					lastDay = connectedNode.dayVisited;
				}
		}
		
		if (lastDay == 0)
			return BoomResult();
		
		std::vector<uint> sizesOnDays(lastDay + 1);
		
		for (Node& node: nodes)
			if (node.visited)
				++sizesOnDays[node.dayVisited];
		
		auto maxSizeOnDay = std::max_element(sizesOnDays.begin() + 1, sizesOnDays.end());
		
		BoomResult boomResult;
		boomResult.firstDay = std::distance(sizesOnDays.begin(), maxSizeOnDay);
		boomResult.size = *maxSizeOnDay;
		return boomResult;
	}
};

int main() {
	uint nNodes;
	std::cin >> nNodes;
	
	Graph graph;
	graph.createNodes(nNodes);
	
	for (uint nodeFromId = 0; nodeFromId < nNodes; ++nodeFromId)
	{
		uint nEdges;
		std::cin >> nEdges;
		
		for (uint iEdge = 0; iEdge < nEdges; ++iEdge)
		{
			uint nodeToId;
			std::cin >> nodeToId;
			
			graph.addEdge(nodeFromId, nodeToId);
		}
	}
	
	uint nTests;
	std::cin >> nTests;
	
	for (uint iTest = 0; iTest < nTests; ++iTest)
	{
		uint nodeSourceId;
		std::cin >> nodeSourceId;
		
		BoomResult boomResult = graph.getBoomResult(nodeSourceId);
		if (boomResult.size == 0)
			std::cout << 0 << std::endl;
		else
			std::cout << boomResult.size << ' ' << boomResult.firstDay << std::endl;
	}
	
	return 0;
}
