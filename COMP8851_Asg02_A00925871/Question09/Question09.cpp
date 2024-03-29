/*========================================================================================
	Question 09
	
	Demonstrates performing a topological sort on a directed acyclic graph represented 
	by an adjacency matrix.
    
    Copyright 2018 Erick Fernandez de Arteaga. All rights reserved.
        https://www.linkedin.com/in/erick-fda
        https://github.com/erick-fda
        https://bitbucket.org/erick-fda
	
========================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*========================================================================================
	Constants
========================================================================================*/
const std::string HORIZONTAL_RULE = "-------------------------------------";

const int NUM_VERTICES = 7;
const int NULL_VERTEX = -1;

std::vector<int> sortedList = std::vector<int>();

/*
	The graph is represented as an adjacency matrix.
	This graph is made to mirror that shown in Figure 9.4 in chapter 9 of the textbook.

	Each inner list represents the seven possible predecessors each vertex can have, including itself.
	
	True indicates that the corresponding node is a predecessor, and false indicates that it is not.
	Thus, the fact that GRAPH[1][0] is true indicates that vertex 1 is a predecessor to vertex 2 
	(keeping zero-indexing in mind).
*/
std::vector<std::vector<bool>> GRAPH =
{
	//							V1		V2		V3		V4		V5		V6		V7
	/* V1's predecessors */ {	false,	false,	false,	false,	false,	false,	false	},
	/* V2's predecessors */ {	true,	false,	false,	false,	false,	false,	false	},
	/* V3's predecessors */ {	true,	false,	false,	true,	false,	false,	false	},
	/* V4's predecessors */ {	true,	true,	false,	false,	true,	false,	false	},
	/* V5's predecessors */ {	false,	true,	false,	false,	false,	false,	false	},
	/* V6's predecessors */ {	false,	false,	true,	true,	false,	false,	true	},
	/* V7's predecessors */ {	false,	false,	false,	true,	true,	false,	false	}
};

/*========================================================================================
	Functions
========================================================================================*/
/*
	Removes the vertex with the given index from the graph.
*/
void RemoveVertexFromGraph(int index)
{
	for (int eachVertex = 0; eachVertex < GRAPH.size(); ++eachVertex)
	{
		GRAPH[eachVertex][index] = false;
	}
}

/*
	Returns the index of a vertex currently in the graph that has an indegree of zero.
	Ignores vertices that have already been sorted.
	
	If there are multiple zero-indegree vertices in the graph, simply returns the 
	first one found.

	Returns NULL_VERTEX if no zero-indegree vertex is found.
*/
int FindNextVertexWithIndegreeZero()
{
	/* For each vertex... */
	for (int vertex = 0; vertex < GRAPH.size(); ++vertex)
	{
		/* If this vertex has already been sorted, ignore it. */
		if (std::find(sortedList.begin(), sortedList.end(), vertex) != sortedList.end())
		{
			continue;
		}

		bool hasPredecessor = false;

		/* For each potential predecessor... */
		for (int pre = 0; pre < GRAPH[0].size(); ++pre)
		{
			/* If this vertex has a predecessor, its not the one we want. */
			if (GRAPH[vertex][pre])
			{
				hasPredecessor = true;
				break;
			}
		}

		/* If no predecessors were found on this vertex, this is the one we want. */
		if (!hasPredecessor)
		{
			return vertex;
		}
	}

	/* If we went through all vertices without finding a suitable one, return NULL_VERTEX. */
	return NULL_VERTEX;
}

/*========================================================================================
	Main Function
========================================================================================*/
int main()
{
	std::cout << HORIZONTAL_RULE << "\n\tQuestion 09\n" << HORIZONTAL_RULE << "\n\n";

	/* Topological Sort */

	/* For the number of vertices in the graph... */
	for (int i = 0; i < NUM_VERTICES; ++i)
	{
		/* Get the next vertex with indegree zero. */
		int nextVertex = FindNextVertexWithIndegreeZero();
		if (NULL_VERTEX == nextVertex)
		{
			std::cout << "ERROR: GRAPH contains a cycle.";
			return 1;
		}

		/* Add the vertex to the sorted list and remove it from the graph. */
		sortedList.push_back(nextVertex);
		RemoveVertexFromGraph(nextVertex);
	}

	/* Print result. */
	std::cout << "Topological sort for graph in textbook Figure 9.4 in Chapter 9:\n\n";
	for (int vertex = 0; vertex < sortedList.size(); ++vertex)
	{
		std::cout << "V" << sortedList[vertex] + 1 << "\n";
	}
	std::cout << "\n";

	std::cout << "Press any key to quit...";
	std::cin.ignore();
	return 0;
}
