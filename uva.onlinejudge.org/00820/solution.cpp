#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>

typedef unsigned int uint;

struct nullostream: std::ostream {
};

template <typename T>
nullostream& operator<< (nullostream& os, const T&) {
	return os;
}

nullostream& operator<< (nullostream& os, std::ostream& manip(std::ostream&)) {
	(void)manip;
	return os;
}

static nullostream *debug = new nullostream();
// static std::ostream *debug = &std::cout;

struct Edge;
struct Node;

struct Edge {
	uint visited;
	int flow, capacity;
	Edge *reverse;
	Node *node1, *node2;
	
	Edge():
		visited(0),
		flow(0),
		capacity(0),
		reverse(NULL),
		node1(NULL),
		node2(NULL) {
	}
	
	Edge(int capacity, Node& node1, Node& node2):
		visited(0),
		flow(0),
		capacity(capacity),
		reverse(this),
		node1(&node1),
		node2(&node2) {
	}
	
	Node& other(Node& node) {
		if (&node != node1)
			return *node1;
		if (&node != node2)
			return *node2;
		
		throw std::exception();
	}
	
	bool visit(const uint visit) {
		if (visited == visit)
			return false;
		
		visited = visit;
		return true;
	}
	
	int available() const {
		return capacity - flow;
	}
};

typedef std::vector<Edge *> Edges;
typedef std::map<uint, Node *> Nodes;

struct Node {
	uint id;
	Node *whence;
	Edge *through;
	Edges edges;
	
	Node(uint id):
		id(id),
		whence(NULL),
		through(NULL) {
	}
};

struct Edge_less_available {
	bool operator() (const Edge *const a, const Edge *const b) {
		return a->available() < b->available();
	}
};

bool touches(const Edges& edges, Node& node) {
	for (Edges::const_iterator it = edges.begin(); it != edges.end(); it++)
	{
		Edge& edge = *(*it);
		if (&node == edge.node1)
			return true;
		if (&node == edge.node2)
			return true;
	}
	
	return false;
}

struct Graph {
	int flow;
	uint visit;
	Node *source, *sink;
	
	Nodes nodes;
	Edges edges;
	
	Graph():
		flow(0),
		visit(1),
		source(NULL),
		sink(NULL) {
	}
	
	~Graph() {
		for (Nodes::iterator it = nodes.begin(); it != nodes.end(); it++)
			delete (*it).second;
		for (Edges::iterator it = edges.begin(); it != edges.end(); it++)
			delete (*it);
	}
	
	void add_edge_undirected(const uint idNode1, const uint idNode2, const int capacity) {
		Node& node1 = add_node(idNode1);
		Node& node2 = add_node(idNode2);
		Edge *edge = new Edge(capacity, node1, node2);
		
		edges.push_back(edge);
		node1.edges.push_back(edge);
		node2.edges.push_back(edge);
	}
	
	void add_edge_directed(const uint idNode1, const uint idNode2, const int capacity) {
		Node& node1 = add_node(idNode1);
		Node& node2 = add_node(idNode2);
		
		Edge *edge12 = new Edge(capacity, node1, node2);
		Edge *edge21 = new Edge(capacity, node2, node1);
		
		edge12->reverse = edge21;
		edges.push_back(edge12);
		node1.edges.push_back(edge12);
		
		edge21->reverse = edge12;
		edges.push_back(edge21);
		node2.edges.push_back(edge21);
	}
	
	Node& add_node(const uint id) {
		if (nodes[id] == NULL)
			nodes[id] = new Node(id);
		return *nodes[id];
	}
	
	void dfs(Edges& path) {
		visit++;
		Node& node = *source;
		bool found = dfs_next(path, node);
		if (!found)
			throw std::exception();
	}
	
	bool dfs_next(Edges& path, Node& node) {
		if (&node == sink)
			return true;
		
		for (Edges::iterator it = node.edges.begin(); it != node.edges.end(); it++)
		{
			Edge& edge = *(*it);
			Node& node2 = edge.other(node);
			
			if (touches(path, node2))
				continue;
			if (!edge.visit(visit) || edge.available() <= 0)
				continue;
			
			path.push_back(&edge);
			
			bool result = dfs_next(path, node2);
			if (result)
				return true;
			
			path.pop_back();
		}
		
		return false;
	}
	
	void bfs(Edges& path) {
		visit++;
		
		std::queue<Node *> queue;
		queue.push(source);
		
		while (!queue.empty())
		{
			Node& node = *queue.front();
			queue.pop();
			
			if (&node == sink)
			{
				Node *backtrack = &node;
				while (backtrack != source)
				{
					path.push_back(backtrack->through);
					backtrack = backtrack->whence;
				}
				std::reverse(path.begin(), path.end());
				return;
			}
			
			for (Edges::iterator it = node.edges.begin(); it != node.edges.end(); it++)
			{
				Edge& edge = *(*it);
				Node& node2 = edge.other(node);
				
				if (!edge.visit(visit) || edge.available() <= 0)
					continue;
				
				node2.whence = &node;
				node2.through = &edge;
				queue.push(&node2);
			}
		}
		
		throw std::exception();
	}
	
	void maximize() {
		while (true)
		{
			Edges path;
			
			try {
				dfs(path);
				
				{
					Node *last = source;
					*debug << "path " << visit - 1 << ": " << source->id;
					for (Edges::iterator it = path.begin(); it != path.end(); it++)
					{
						Node *cur = &(*it)->other(*last);
						*debug << " -(" << (*it)->available() << ")- " << cur->id;
						last = cur;
					}
					*debug << std::endl;
				}
			} catch (std::exception) {
				break;
			}
			
			int flowIncrease;
			{
				Edge& edge = **std::min_element(path.begin(), path.end(), Edge_less_available());
				flowIncrease = edge.available();
			}
			
			flow += flowIncrease;
			for (Edges::iterator it = path.begin(); it != path.end(); it++)
			{
				Edge& edge = *(*it);
				edge.flow += flowIncrease;
				if (edge.reverse != &edge)
				{
					Edge& reverse = *edge.reverse;
					reverse.flow -= flowIncrease;
					if (reverse.flow > 100)
						*debug << "danger, Will Robinson: " << reverse.flow << std::endl;
				}
			}
		}
	}
};

int main() {
	uint iCase = 0;
	while (true)
	{
		iCase++;
		
		uint nNodes;
		std::cin >> nNodes;
		if (nNodes == 0)
			break;
		
		Graph net;
		{
			uint idSource, idSink;
			std::cin >> idSource >> idSink;
			net.source = &net.add_node(idSource);
			net.sink = &net.add_node(idSink);
		}
		{
			uint nEdges;
			std::cin >> nEdges;
			for (uint iEdge = 0; iEdge < nEdges; iEdge++)
			{
				uint idNode1, idNode2;
				int capacity;
				std::cin >> idNode1 >> idNode2 >> capacity;
				net.add_edge_directed(idNode1, idNode2, capacity);
			}
		}
		
		for (Edges::iterator it = net.edges.begin(); it != net.edges.end(); it++)
			*debug << (*it)->node1->id << " - " << (*it)->node2->id << ": " << (*it)->capacity << std::endl;
		
		net.maximize();
		
		std::cout << "Network " << iCase << std::endl;
		std::cout << "The bandwidth is " << net.flow << "." << std::endl;
		std::cout << std::endl;
	}
	
	return 0;
}
