#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <string>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

class Node;
class Edge;
class NodeList;
typedef vector<Edge *> EdgeList;
class NodeListQue;

class Node {
	public:
		bool visited;
		string name;
		EdgeList edges;
		
		Node(string name):
			visited(false),
			name(name),
			edges() { };
};

class NodeList:
	public vector<Node *> {
	public:
		Node *findByName(string name);
		bool findArbitrage();
};

class NodeListQue:
	public queue<NodeList *> { };

class Edge {
	public:
		bool visited;
		Node *node;
		unsigned int from, to;
	
		Edge():
			visited(false),
			node(NULL),
			from(0),
			to(0) { };
};

Node *NodeList::findByName(string name) {
	for (NodeList::iterator i = this->begin(); this->end() != i; i++)
		if (0 == name.compare((*i)->name))
			return *i;
	return NULL;
}

bool NodeList::findArbitrage() {
	NodeListQue *nodeListQue;
	NodeList *nodeList, *nodeListNew;
	Node *node, *former, *latter;
	double ratio;
	
	nodeListQue = new NodeListQue();
	
	for (NodeList::iterator i = this->begin(); this->end() != i; i++)
	{
		nodeList = new NodeList();
		nodeList->push_back(*i);
		nodeListQue->push(nodeList);
	}
	
	while (!nodeListQue->empty())
	{
		nodeList = nodeListQue->front();
		nodeListQue->pop();
		node = nodeList->back();
		
		for (EdgeList::iterator i = node->edges.begin(); node->edges.end() != i; i++)
		{
			if ((*i)->visited)
				continue;
			ratio = 1.0;
/*		for (NodeList::iterator j = nodeList->end() - 2; (nodeList->begin() ) != j; j--)*/
			for (int j = nodeList->size() - 2; j > 0; j--)
			{
				/*former = *(j - 1);*/
				former = nodeList->at(j - 1);
				for (EdgeList::iterator k = former->edges.begin(); former->edges.end() != k; k++)
				{
					latter = (*k)->node;
					if (latter != former)
						continue;
					ratio *= (double)((*k)->to) / (double)((*k)->from);
					break;
				}
				if (former == node)
				{
					if (1.0 < ratio)
						return true;
					break;/**/
				}
			}
			nodeListNew = new NodeList(*nodeList);
			nodeListNew->push_back((*i)->node);
			nodeListQue->push(nodeListNew);
		}
		delete nodeList;
	}
	
	delete nodeListQue;
	return false;
}

#define LINE_LENGTH 1024

int main(int argc, char *argv[]) {
	char line[LINE_LENGTH];
	unsigned int c, r, p;
	NodeList *nodeList;
	Edge *edge;
	
	argc = argc; argv = argv;
	
	nodeList = new NodeList();
	
	while (true)
	{
		fgets(line, LINE_LENGTH, stdin);
		sscanf(line, "%u", &c);
		if (0 == c)
			break;
		
		fgets(line, LINE_LENGTH, stdin);
		p = 0;
		for (unsigned int i = 0; c > i; i++)
		{
			line[p + 3] = '\0';
			nodeList->push_back(new Node(&(line[p])));
			p += 4;
		}
		fgets(line, LINE_LENGTH, stdin);
		sscanf(line, "%u", &r);
		for (unsigned int i = 0; r > i; i++)
		{
			fgets(line, LINE_LENGTH, stdin);
			line[3] = '\0';
			line[7] = '\0';
			printf("%s %s %s\n", line, line + 4, line + 8);
			edge = new Edge();
			sscanf(&(line[8]), "%u:%u", &(edge->from), &(edge->to));
			edge->node = nodeList->findByName(&(line[4]));
			nodeList->findByName(line)->edges.push_back(edge);
		}
		
		if (nodeList->findArbitrage())
			printf("Arbitrage");
		else
			printf("Ok");
		printf("\n");
		
		for (NodeList::iterator i = nodeList->begin(); nodeList->end() != i; i++)
			delete (*i);
		nodeList->clear();
	}
	
	delete nodeList;
	
	return 0;
}
