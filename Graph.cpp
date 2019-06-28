#include "Graph.h"

 Graph::Graph(int v)
{
	this->nodes_n = v;
	vect =  vector< vector< pair<int, int> > >(v) ;
}

 Graph::Graph()
 {
	// vect = vector< vector< pair<int, int> > >(nodes_n);
 }
 void Graph::Read_InputFile()
 {
	 // Create the object for the input file then open it
	 ifstream inputFile;

	 // Open the file (the below address should be modified)
	 inputFile.open("E:\\courses\\social network DS project\\vs_habd\\closeness_centrality_1\\input.txt");

	 // Nodes and weights in file
	 int node1, node2, weight;

	 // The first line of the file contains the number of nodes and edges (nodes_n & edges_n)
	 inputFile >> nodes_n >> edges_n;

	 // Initialize the adjacency matrix (vector of vectors) and the output vector
	 vect.resize(nodes_n);
	 output_centrality.resize(nodes_n);
	 edges.resize(edges_n);
	 // Fill the adjacency matrix with weights
	 for (int i = 0; i < edges_n; i++) {
		 inputFile >> node1 >> node2 >> weight;
		 vect[node1].push_back(make_pair(node2, weight));
		 vect[node2].push_back(make_pair(node1, weight));
	 }
	 // Close the opened file
	 inputFile.close();
 }
 void Graph::visualization_input() {
	 ifstream inputFile;
	 inputFile.open("E:\\courses\\social network DS project\\vs_habd\\closeness_centrality_1\\input.txt");
	 int node1, node2, weight;
	 inputFile >> nodes_n >> edges_n;
	 edges.resize(edges_n);
	 // Fill the adjacency matrix with weights
	 for (int i = 0; i < edges_n; i++) {
		 inputFile >> node1 >> node2 >> weight;
		 edges[i].second = weight;
		 edges[i].first.first = node1;
		 edges[i].first.second = node2;
	 }
	 // Close the opened file
	 inputFile.close();
 }

void Graph::PrintOutput()
{
	for (int i = 0; i < nodes_n; i++) {
		cout << output_centrality[i] << endl;
	}
}

void Graph::visualize() {
	visualization_input();
	int maxW = max_weight();
	double maxC = max_closeness();
	ofstream myfile;
	myfile.open("trial.js");
	//myfile << "var w = window.outerWidth;"<<"\n";
	//myfile << "var h = window.outerHeight;"<<"\n";//Get the browser window's height and width
	myfile << " var graph = {"<<"\n"<<"\t"<<"nodes: ["<<"\n \t \t";
	for (int i = 0; i < nodes_n-1; i++) {
		int x = i + 3;
		int y = i + 1;
		float size = .5 + ((output_centrality[i]) / maxC)*(5 - .5); // it's an interpolation assuming that the maximum size is 5 so modify it as you like
		long color = 0x005000 + ((float)(output_centrality[i]) / maxW)*(0xFFFFF0);//you can adjust this color
		myfile << "{ id: " << "\"n" + to_string(i) + "\", label: " << "\""<<(char)(65+i)<<"\""<<", x: "<<x<<", y: "<<y<<", size: "<<size<<", color: " << "'#" << color << "'},"<<"\n \t \t";

	}
	float size = .5 + ((output_centrality[nodes_n-1]) / maxC)*(5 - .5);
	long color = 0x005000 + ((float)(output_centrality[nodes_n-1]) / maxW)*(0xFFFFF0);
	myfile << "{ id: " << "\"n" + to_string(nodes_n-1) + "\", label: " << "\"" << (char)(65 + nodes_n-1) << "\"" << ", x: 0, y: 0, size: "<< size <<", color: " << "'#" << color << "'}" << "\n \t"<<"],";
	
	// this is the part of edges in js file 

	myfile << "\n" << "\t" << "edges: [" << "\n \t \t";
	for (int i = 0; i < edges_n - 1; i++) {
		float size = .5 + ((float)(edges[i].second)/maxW)*(5-.5); // it's an interpolation assuming that the maximum size is 5 so modify it as you like
		long color=BLACK+ ((float)(edges[i].second) / maxW)*(0xFFFFF0);//you can adjust this color
		myfile << "{ id: " << "\"e" + to_string(i) + "\", source: " << "\"n" + to_string(edges[i].first.first) << "\" , target: " << "\"n" + to_string(edges[i].first.second) << "\"" << ", color: "<<"'#"<<color<<"', type:'line', size: "<<size<<"}," << "\n \t \t";
		
	}
	 size = .5 + ((float)(edges[edges_n - 1].second) / maxW)*(5 - .2);
	 color = BLACK + ((float)(edges[edges_n - 1].second) / maxW)*(0xFFFFF0);//you can adjust this color
	myfile << "{ id: " << "\"e" + to_string(edges_n - 1) + "\", source: " << "\"n" + to_string(edges[edges_n - 1].first.first) << "\" , target: " << "\"n" + to_string(edges[edges_n - 1].first.second) << "\"" << ", color: " << "'#" << color << "', type:'line', size: 5 }," << "\n \t" << "] \n"<< "}";


	myfile.close();

}
int Graph::max_weight() {
	int max = 0;
	for (int i = 0; i < edges_n; i++) {
		if (edges[i].second > max)
			max = edges[i].second;
	}
	return max;
}

double Graph::max_closeness() {
	double max = 0;
	for (int i = 0; i < nodes_n; i++) {
		if (output_centrality[i] > max)
			max = output_centrality[i];
	}
	return max;
}

Graph::~Graph()
{
}
void Graph::addEdge(int u, int v, int w)
{
	pair<int,int> p1 (v , w);
	vect[u].push_back(p1);
	vect[v].push_back(make_pair(u, w));
}





/*


void Graph::ClosenessCentrality()
{
	//vector<vector<int>>each_node_closenes(nodes_n, vector<int>(nodes_n));
	vector<double>each_node_closenes(nodes_n);

	vector<int> parents(nodes_n, -1);
	for (int i = 0; i < nodes_n; i++) {
		vector<int> distance(nodes_n, INF);
		shortestPath(i, distance);
		each_node_closenes[i]=((nodes_n-1)/ sum_vector(distance));
	}
	for (int i = 0; i < nodes_n; i++) {
		cout << each_node_closenes[i];
		cout << "\n";
	}

}

void Graph::shortestPath(int src, vector<int>& dist)
{
	// Create a priority queue to store vertices that
	// are being preprocessed. This is weird syntax in C++.
	// Refer below link for details of this syntax
	priority_queue< pair<int,int>, vector <pair<int,int>>, greater<pair<int,int>> > pq;

	// Create a vector for distances and initialize all
	// distances as infinite (INF)


	// Insert source itself in priority queue and initialize
	// its distance as 0.
	pq.push(make_pair(0, src));
	dist[src] = 0;

	/* Looping till priority queue becomes empty (or all
	  distances are not finalized) */
/*
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
printf("Vertex   Distance from Source\n");
for (int i = 0; i < nodes_n; ++i)
	printf("%d \t\t %d\n", i, dist[i]);
}



*/