#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <algorithm>

#include "../prettyprint.hpp"

typedef unsigned int uint;

struct vertex {
	uint id;
	uint processed;
	bool solved;
	bool solving;
	std::vector<vertex *> edges_from;
	std::vector<vertex *> edges_to;
	std::set<vertex *> dominated_by;
	std::set<vertex *> dominates;
};

std::ostream& operator<< (std::ostream& out, const vertex& v) {
	out << "vertex[" << v.id << "]";
	
	return out;
}
std::ostream& operator<< (std::ostream& out, const vertex *const v) {
	out << *v;
	
	return out;
}
std::ostream& operator<< (std::ostream& out, const std::set<vertex *> *const s) {
	out << *s;
	
	return out;
}

std::set<vertex *> set_intersection(std::vector< std::set<vertex *> *>& sets) {
	if (sets.size() == 0)
		return {};
	
	std::set<vertex *> *left = new std::set<vertex *>(**sets.begin());
	if (sets.size() == 1)
		return *left;
	
	for (std::vector< std::set<vertex *> *>::iterator right = sets.begin() + 1; right != sets.end(); right++)
	{
		std::set<vertex *> *result = new std::set<vertex *>();
		std::set_intersection(left->begin(), left->end(), (*right)->begin(), (*right)->end(), std::inserter(*result, result->begin()));
		delete left;
		left = result;
	}
	std::set<vertex *> result(*left);
	delete left;
	return result;
}

void reach_vertex(vertex& currentVertex, vertex& startVertex) {
	currentVertex.dominated_by.insert(&currentVertex);
	currentVertex.dominates.insert(&currentVertex);
	currentVertex.dominated_by.insert(&startVertex);
	startVertex.dominates.insert(&currentVertex);
}

bool solve_vertex(vertex& currentVertex) {
	if (currentVertex.processed == 0)
		return false;
	
	if (currentVertex.solved)
		return true;
	currentVertex.solved = true;
	
	std::vector< std::set<vertex *> *> sets;
	for (std::vector<vertex *>::iterator fromVertex = currentVertex.edges_from.begin(); fromVertex != currentVertex.edges_from.end(); fromVertex++)
		if (solve_vertex(**fromVertex))
			sets.push_back(&(*fromVertex)->dominated_by);
	std::set<vertex *> dominated_by = set_intersection(sets);
std::cout << currentVertex << " dominated_by " << dominated_by << " (intersection of: " << sets << ")" << std::endl;
	for (std::set<vertex *>::iterator dominatingVertex = dominated_by.begin(); dominatingVertex != dominated_by.end(); dominatingVertex++)
	{
		currentVertex.dominated_by.insert(*dominatingVertex);
		(*dominatingVertex)->dominates.insert(&currentVertex);
	}
	
	currentVertex.solved = true;
	return currentVertex.solved;
}

int main() {
	uint nCases;
	std::cin >> nCases;
	
	for (uint iCase = 0; iCase < nCases; iCase++)
	{
		uint nVertices;
		std::cin >> nVertices;
		
		std::vector<vertex> vertices(nVertices);
		for (uint iCurrentVertex = 0; iCurrentVertex < nVertices; iCurrentVertex++)
		{
			vertex& currentVertex = vertices[iCurrentVertex];
			currentVertex.id = iCurrentVertex;
		}
		for (uint iFromVertex = 0; iFromVertex < nVertices; iFromVertex++)
		{
			vertex& fromVertex = vertices[iFromVertex];
			for (uint iToVertex = 0; iToVertex < nVertices; iToVertex++)
			{
				vertex& toVertex = vertices[iToVertex];
				uint is_edge;
				std::cin >> is_edge;
				if (is_edge && fromVertex.id != toVertex.id)
				{
					fromVertex.edges_to.push_back(&toVertex);
					toVertex.edges_from.push_back(&fromVertex);
				}
			}
		}
		
		std::queue<vertex *> to_process;
		to_process.push(&vertices[0]);
		while (!to_process.empty())
		{
			vertex& currentVertex = *to_process.front();
			to_process.pop();
			currentVertex.processed = 1;
			reach_vertex(currentVertex, vertices[0]);
			for (std::vector<vertex *>::iterator toVertex = currentVertex.edges_to.begin(); toVertex != currentVertex.edges_to.end(); toVertex++)
				if ((*toVertex)->processed == 0)
					to_process.push(*toVertex);
		}
		to_process.push(&vertices[0]);
		while (!to_process.empty())
		{
			vertex& currentVertex = *to_process.front();
			to_process.pop();
			currentVertex.processed = 2;
			solve_vertex(currentVertex);
			for (std::vector<vertex *>::iterator toVertex = currentVertex.edges_to.begin(); toVertex != currentVertex.edges_to.end(); toVertex++)
				if ((*toVertex)->processed == 1)
					to_process.push(*toVertex);
		}
		
		std::cout << "Case " << iCase + 1 << ":" << std::endl;
		std::string delimiter_line = std::string(2 * nVertices + 1, '-');
		delimiter_line[0] = '+';
		delimiter_line[delimiter_line.size() - 1] = '+';
		
		std::cout << delimiter_line << std::endl;
		for (uint iDominatingVertex = 0; iDominatingVertex < nVertices; iDominatingVertex++)
		{
			vertex& dominatingVertex = vertices[iDominatingVertex];
			for (uint iDominatedVertex = 0; iDominatedVertex < nVertices; iDominatedVertex++)
			{
				vertex& dominatedVertex = vertices[iDominatedVertex];
				std::cout << "|";
				std::cout << (dominatedVertex.dominated_by.count(&dominatingVertex) > 0 ? "Y" : "N");
			}
			std::cout << "|" << std::endl;
			std::cout << delimiter_line << std::endl;
		}
	}
	
	return 0;
}
