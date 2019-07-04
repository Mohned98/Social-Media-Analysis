#include "Graph.h"

void Graph::GetPaths(int i, int j, vector<vector<vector<int> > > &seq, vector<vector<int>>&pair_paths)
{
	for (unsigned int k = 0; k<seq[i][j].size(); k++)
	{
		if (seq[i][j][k] == j)
		{
			vector<int>temp;
			temp.push_back(i);
			temp.push_back(j);
			pair_paths.push_back(temp);
		}
		else
		{
			vector<vector<int>>pair_pathsi_k;
			GetPaths(i, seq[i][j][k], seq, pair_pathsi_k);
			vector<vector<int>>pair_pathsk_j;
			GetPaths(seq[i][j][k], j, seq, pair_pathsk_j);
			for (unsigned int c = 0; c < pair_pathsi_k.size(); c++)
			{
				for (unsigned int m = 0; m < pair_pathsk_j.size(); m++)
				{
					vector<int>temp = pair_pathsi_k[c];
					temp.insert(temp.end(), pair_pathsk_j[m].begin() + 1, pair_pathsk_j[m].end());
					pair_paths.push_back(temp);
				}
			}
		}
	}
}


void Graph::BetweennessCentrality()
{
	vector<vector<int>> dist(nodes_n, vector<int>(nodes_n)); //contains shortest distance from source to destination
	vector<vector<vector<int> > > seq(nodes_n, vector<vector<int> >(nodes_n)); //contains shortest path from source to destination
	vector<vector<int>> distk(nodes_n, vector<int>(nodes_n)); //contains shortest distance from Kth iteration between source to destination
	vector<vector<vector<int> > > seqk(nodes_n, vector<vector<int> >(nodes_n)); //contains shortest path from Kth iteration between source to destination
	int i, j, k; //iterators

				 //Initialization distk and seqk matrices to 0
	for (i = 0; i < nodes_n; i++)
	{
		for (j = 0; j < nodes_n; j++) {
			if (i == j)
			{
				distk[i][j] = INF;
				//seqk[i][j] = INF;
			}
			else {
				distk[i][j] = 0;
				//seqk[i][j] = 0;
			}
		}
	}

	// Initialization of seq matrix
	for (i = 0; i < nodes_n; i++)
		for (j = 0; j < nodes_n; j++)
			if (i == j)
				//seq[i][j].push_back(0);
				continue;
			else
				seq[i][j].push_back(j);

	//sorting of vector of pairs for correct parsing
	for (i = 0; i < nodes_n; i++)
	{
		sort(vect[i].begin(), vect[i].end());
	}

	// Initialization of dist matrix
	for (i = 0; i < nodes_n; i++)
	{
		k = 0;
		for (j = 0; j < nodes_n; j++)
		{
			if (i == j)
				dist[i][j] = 0;
			else if (k < vect[i].size() && vect[i][k].first == j) {
				dist[i][j] = vect[i][k].second;
				k++;
			}
			else {
				dist[i][j] = INF;
			}
		}
	}

	for (k = 0; k < nodes_n; k++)
	{
		//step 1:
		//for each iteration we copy the kth row and kth column to the current array
		for (i = 0; i < nodes_n; i++) {
			//copy row
			distk[k][i] = dist[k][i];
			seqk[k][i] = seq[k][i];

			//copy column
			distk[i][k] = dist[i][k];
			seqk[i][k] = seq[i][k];
		}

		//step 2:  
		//compute the distance and sequence value for current iteration
		for (i = 0; i < nodes_n; i++)
		{
			//for kth iteration we skip the kth row
			if (i == k) {
				continue;
			}
			for (j = 0; j < nodes_n; j++)
			{
				//for kth iteration we skip the kth column
				if (j == k) {
					continue;
				}
				//if i and j are same i.e., referring to same vertex we skip it
				if (i == j) {
					continue;
				}
				//checking
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					distk[i][j] = dist[i][k] + dist[k][j];
					seqk[i][j].clear();
					seqk[i][j].push_back(k);
				}
				else if (dist[i][j] == dist[i][k] + dist[k][j])
				{
					seqk[i][j].push_back(k);
				}
				else {
					distk[i][j] = dist[i][j];
					seqk[i][j] = seq[i][j];
				}
			}
		}

		//step 3:
		//copy content of Dk and Sk to D and S
		for (i = 0; i < nodes_n; i++) {
			for (j = 0; j < nodes_n; j++) {
				dist[i][j] = distk[i][j];
				seq[i][j] = seqk[i][j];
			}
		}
	}

	for (int i = 0; i <nodes_n; i++)
	{
		for (int j = 0; j < nodes_n; j++)
		{
			if (i>j)
			{
				vector<vector<int>>pair_paths;
				GetPaths(i, j, seq, pair_paths);
				for (unsigned int i1 = 0; i1 < pair_paths.size() - 1; i1++)
				{
					if (pair_paths[i1] == pair_paths[i1 + 1])
					{
						pair_paths.erase(pair_paths.begin() + i1 + 1);
					}
				}
				vector<bool>nodes_flags(nodes_n, false);
				int no_paths = pair_paths.size();
				for (unsigned int k = 0; k < pair_paths.size(); k++)
				{
					for (unsigned int l = 1; l < pair_paths[k].size() - 1; l++)
					{
						int picked_node = pair_paths[k][l];
						double node_count = 0;
						if (nodes_flags[picked_node] == false)
						{
							nodes_flags[picked_node] = true;
							for (unsigned int z = 0; z < pair_paths.size(); z++)
							{
								node_count += count(pair_paths[z].begin() + 1, pair_paths[z].end() - 1, picked_node);
							}
							output_centrality[picked_node] += (node_count / no_paths);
						}

					}
				}
			}
		}
	}
}