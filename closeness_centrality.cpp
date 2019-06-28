#include "Graph.h"

long double sum_vector(vector<int>x) {
	long double sum = 0;
	for (int i = 0; i < x.size(); i++)
		sum += x[i];
	return sum;
}

void Graph::ClosenessCentrality()
{
	//vector<vector<int>>each_node_closenes(nodes_n, vector<int>(nodes_n));
	//vector<double>each_node_closenes(nodes_n);

	vector<int> parents(nodes_n, -1);
	for (int i = 0; i < nodes_n; i++) {
		vector<int> distance(nodes_n, INF);
		shortestPath(i, distance);
		output_centrality[i] = ((nodes_n - 1) / sum_vector(distance));
	}
/*	for (int i = 0; i < nodes_n; i++) {
		cout << output_centrality[i];
		cout << "\n";
	}
	*/
}

void Graph::shortestPath(int src, vector<int>& dist)
{
	// Create a priority queue to store vertices that 
	// are being preprocessed. This is weird syntax in C++. 
	// Refer below link for details of this syntax 
	priority_queue< pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>> > pq;

	// Create a vector for distances and initialize all 
	// distances as infinite (INF) 


	// Insert source itself in priority queue and initialize 
	// its distance as 0. 
	pq.push(make_pair(0, src));
	dist[src] = 0;

	/* Looping till priority queue becomes empty (or all
	  distances are not finalized) */
	while (!pq.empty())
	{
		// The first vertex in pair is the minimum distance 
		// vertex, extract it from priority queue. 
		// vertex label is stored in second of pair (it 
		// has to be done this way to keep the vertices 
		// sorted distance (distance must be first item 
		// in pair) 
		int u = pq.top().second;
		pq.pop();

		// 'i' is used to get all adjacent vertices of a vertex 
		//list< pair<int, int> >::iterator i;
		for (unsigned int i = 0; i < vect[u].size(); ++i)
		{
			// Get vertex label and weight of current adjacent 
			// of u. 
			int v = vect[u][i].first;
			int weight = vect[u][i].second;

			//  If there is shorted path to v through u. 
			if (dist[v] > dist[u] + weight)
			{
				// Updating distance of v 
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}

	// Print shortest distances stored in dist[] 
/*	printf("Vertex   Distance from Source\n");
	for (int i = 0; i < nodes_n; ++i)
		printf("%d \t\t %d\n", i, dist[i]);*/
}
