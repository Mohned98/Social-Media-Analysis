#include "Graph.h"

void Graph::DegreeCentrality()
{
	// Compute_degree_centrality of adjacency_list and store it in output_centrality
	for (int i = 0; i < nodes_n; i++)
	{
		output_centrality[i] = vect[i].size();
	}


}