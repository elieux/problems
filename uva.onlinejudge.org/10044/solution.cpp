#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <queue>

#define BUFFER_LENGTH 1024 * 1024
#define rte() (((char *)NULL)[0] = 'K')
#define tle() while (true)

using namespace std;

class Node;
class Nodes;
typedef queue<Node *> NodeQueue;

class Nodes:
	public vector<Node *> {
	public:
		Node *findByName(const string name);
};

class Node {
	public:
		string name;
		bool visited;
		unsigned int erdos;
		Nodes nodes;
		
		Node(string name):
			name(name),
			visited(false),
			erdos(0),
			nodes(Nodes()) { }
};

Node *Nodes::findByName(const string name) {
	for (Nodes::iterator i = this->begin(); this->end() > i; i++)
		if (0 == name.compare((*i)->name))
			return (*i);
	return NULL;
}

string correctString(const string str) {
	unsigned int i, j;
	unsigned int length;
	char c_str[10240];
	
	strcpy(c_str, str.c_str());
	length = strlen(c_str);
	j = 0;
	for (i = 0; length > i; i++)
		if (isalpha(c_str[i]))
			c_str[j++] = tolower(c_str[i]);
	c_str[j] = '\0';
	return string(c_str);
}

int main(int argc, char *argv[]) {
	char buffer[BUFFER_LENGTH];
	Nodes *nodes = NULL;
	Node *node = NULL;
	unsigned int nCases, nPapers, nNames;
	char *comma, *previousComma;
	Nodes *paperNodes = NULL;
	NodeQueue *nodeQueue = NULL;
	
	argc = argc; argv = argv;
	
	nodes = new Nodes();
	nodeQueue = new NodeQueue();
	paperNodes = new Nodes();
	
	do 
		fgets(buffer, BUFFER_LENGTH, stdin);
	while (1 != sscanf(buffer, "%u", &nCases));
	
	for (unsigned int i = 0; nCases > i; i++)
	{
		do 
			fgets(buffer, BUFFER_LENGTH, stdin);
		while (2 != sscanf(buffer, "%u %u", &nPapers, &nNames));
		
		nodes->push_back(new Node(correctString(string("Erdos, P."))));
		
		for (unsigned int j = 0; nPapers > j; j++)
		{
			do
				fgets(buffer, BUFFER_LENGTH, stdin);
			while ('\n' == buffer[0]);
			strchr(buffer, ':')[0] = '\0';
			previousComma = buffer;
			comma = buffer;
			while (NULL != strchr(comma, ',') && NULL != (comma = strchr(strchr(comma, ',') + 1, ',')))
			{
				comma[0] = '\0';
				if (NULL == (node = nodes->findByName(correctString(string(previousComma)))))
					nodes->push_back(node = new Node(correctString(string(previousComma))));
				paperNodes->push_back(node);
				comma = &(comma[1]);
				previousComma = comma;
			}
			if (NULL != strchr(previousComma, ','))
			{
				if (NULL == (node = nodes->findByName(correctString(string(previousComma)))))
					nodes->push_back(node = new Node(correctString(string(previousComma))));
				paperNodes->push_back(node);
			}
			for (Nodes::iterator iNode = paperNodes->begin(); paperNodes->end() > iNode; iNode++)
				for (Nodes::iterator jNode = paperNodes->begin(); paperNodes->end() > jNode; jNode++)
					if (iNode != jNode)
					{
						(*iNode)->nodes.push_back(*jNode);
						(*jNode)->nodes.push_back(*iNode);
					}
			paperNodes->clear();
		}
		
		nodeQueue->push(nodes->findByName(correctString(string("Erdos, P."))));
		nodeQueue->back()->visited = true;
		while (!nodeQueue->empty())
		{
			node = nodeQueue->front();
			nodeQueue->pop();
			for (Nodes::iterator iNode = node->nodes.begin(); node->nodes.end() > iNode; iNode++)
				if (!(*iNode)->visited)
				{
					(*iNode)->visited = true;
					(*iNode)->erdos = node->erdos + 1;
					nodeQueue->push(*iNode);
				}
		}
		
		printf("Scenario %u\n", i + 1);
		for (unsigned int j = 0; nNames > j; j++)
		{
			do
				fgets(buffer, BUFFER_LENGTH, stdin);
			while ('\n' == buffer[0]);
			if (NULL != strchr(buffer, '\n'))
				strchr(buffer, '\n')[0] = '\0';
			printf("%s ", buffer);
			node = nodes->findByName(correctString(string(buffer)));
			if (NULL == node || !node->visited)
				printf("infinity");
			else
				printf("%u", node->erdos);
			printf("\n");
		}
		
		for (Nodes::iterator iNode = nodes->begin(); nodes->end() > iNode; iNode++)
			delete *iNode;
		nodes->clear();
	}
	
	delete nodes;
	delete paperNodes;
	delete nodeQueue;
	
	return 0;
}
