#include "Graph.h"

void Graph::floydWarshall() {

	vector<vector<int>> dist(nodes_n, vector<int>(nodes_n)); //contains shortest distance from source to destination
	vector<vector<int>> seq(nodes_n, vector<int>(nodes_n)); //contains shortest path from source to destination
	vector<vector<int>> distk(nodes_n, vector<int>(nodes_n)); //contains shortest distance from Kth iteration between source to destination
	vector<vector<int>> seqk(nodes_n, vector<int>(nodes_n)); //contains shortest path from Kth iteration between source to destination
	int i, j, k; //iterators

	//Initialization distk and seqk matrices to 0
	for (i = 0; i < nodes_n; i++) {
		for (j = 0; j < nodes_n; j++) {
			if (i == j) {
				distk[i][j] = INF;
				seqk[i][j] = INF;
			}
			else {
				distk[i][j] = 0;
				seqk[i][j] = 0;
			}
		}
	}

	// Initialization of seq matrix
	for (i = 0; i < nodes_n; i++)
		for (j = 0; j < nodes_n; j++)
			if (i == j)
				seq[i][j] = 0;
			else
				seq[i][j] = j;

	//sorting of vector of pairs for correct parsing
	for (i = 0; i < nodes_n; i++) {
		std::sort(vect[i].begin(), vect[i].end());
	}

	// Initialization of dist matrix
	for (i = 0; i < nodes_n; i++) {
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

	for (k = 0; k < nodes_n; k++) {
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
		for (i = 0; i < nodes_n; i++) {

			//for kth iteration we skip the kth row
			if (i == k) {
				continue;
			}

			for (j = 0; j < nodes_n; j++) {

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
					seqk[i][j] = k;  //kth iteration, as indexing starts from 0 so, we add 1
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

	//print the distance array and sequence array result
	printf("Distance array: \n");
	for (i = 0; i < nodes_n; i++) {
		for (j = 0; j < nodes_n; j++) {
			if (dist[i][j] == INF) {
				printf("%10s ", "INF");
			}
			else {
				printf("%10d ", dist[i][j]);
			}
		}
		printf("\n");
	}

	printf("Sequence array: \n");
	for (i = 0; i < nodes_n; i++) {
		for (j = 0; j < nodes_n; j++) {
			if (seq[i][j] == INF) {
				printf("%10s ", "INF");
			}
			else {
				printf("%10d ", seq[i][j]);
			}
		}
		printf("\n");
	}
}

void Graph::BetweennessCentrality()
{
	floydWarshall();
}