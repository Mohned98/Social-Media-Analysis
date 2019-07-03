#include "Graph.h"

double Graph::sum_vector(vector<int>&x, unsigned int size)
{
	double sum = 0;
	for (unsigned int i = 0; i < size; i++)
		sum += x[i];
	return sum;
}

void Graph::shortestPath(int src, vector<int>& distance)
{
	priority_queue< pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>> > pq;
	pq.push(make_pair(0, src));
	distance[src] = 0;
	while (!pq.empty())
	{
		//pick
		int picked_node = pq.top().second;
		pq.pop();
		//check and update
		for (unsigned int i = 0; i < vect[picked_node].size(); i++)
		{
			int adjacent_node = vect[picked_node][i].first;
			int node_weight = vect[picked_node][i].second;
			if (distance[adjacent_node] > distance[picked_node] + node_weight)
			{
				distance[adjacent_node] = distance[picked_node] + node_weight;
				pq.push(make_pair(distance[adjacent_node], adjacent_node));
			}
		}
	}
}

void Graph::ClosenessCentrality()
{
	for (int i = 0; i < nodes_n; i++)
	{
		vector<int> distance(nodes_n, INF);
		shortestPath(i, distance);
		output_centrality[i] = ((nodes_n - 1) / sum_vector(distance, nodes_n));
	}
}