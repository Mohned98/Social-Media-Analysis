#include "Graph.h"

Graph::Graph()
{

}

void Graph::Read_InputFile()
{
	// Create the object for the input file then open it
	ifstream inputFile;

	// Open the file (the below address should be modified)
	inputFile.open("E:\\College\\3rd Computer\\Second term\\Data Structures\\Project Social Media Analysis\\degree_centrality_test\\input.txt");

	// Nodes and weights in file
	int node1, node2, weight;

	// The first line of the file contains the number of nodes and edges (nodes_n & edges_n)
	inputFile >> nodes_n >> edges_n;

	// Initialize the adjacency matrix (vector of vectors) and the output vector
	vect.resize(nodes_n);
	output_centrality.resize(nodes_n);

	// Fill the adjacency matrix with weights
	for(int i=0; i<edges_n; i++){
		inputFile >> node1 >> node2 >> weight;
		vect[node1].push_back(make_pair(node2, weight));
		vect[node2].push_back(make_pair(node1, weight));
	}
	// Close the opened file
	inputFile.close();
}

void Graph::PrintOutput()
{
	for(int i=0; i<nodes_n; i++){
		cout << output_centrality[i] << endl;
	}
}

Graph::~Graph()
{
}
