#include "Graph.h"


 Graph::Graph(string file_name)
 {
	 this->file_name = file_name;
 }

 void Graph::Read_InputFile()
 {
	 // Create the object for the input file then open it
	 ifstream inputFile;

	 // Open the file (the below address should be modified)
	 inputFile.open(file_name);

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

 void Graph::PrintOutput()
 {
	 for (int i = 0; i < nodes_n; i++) 
	 {
		 cout << setprecision(12);
		 cout << output_centrality[i] << endl;
	 }
 }
 
 void Graph::visualization_input() {
	 ifstream inputFile;
	 inputFile.open(file_name);
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

 void Graph::visualize() {
	 visualization_input();
	 int maxW = max_weight();
	 double maxC = max_closeness();
	 ofstream myfile;
	 myfile.open("trial.js");
	 //myfile << "var w = window.outerWidth;"<<"\n";
	 //myfile << "var h = window.outerHeight;"<<"\n";//Get the browser window's height and width
	 myfile << " var graph = {" << "\n" << "\t" << "nodes: [" << "\n \t \t";
	 for (int i = 0; i < nodes_n - 1; i++) {
		 double x = (2 * i % 400);
		 //double y =(.2*i+.1) ;
		 double y = (2 * i % 200) + .1;
		 //double y = i*.1 ;
		 float size = 50 + ((output_centrality[i]) / maxC)*(5 - .5); // it's an interpolation assuming that the maximum size is 5 so modify it as you like
		 long color = 0x005000 + ((float)(output_centrality[i]) / maxC)*(0xFFFFF0);//you can adjust this color
		 myfile << "{ id: " << "\"n" + to_string(i) + "\", label: " << "\"" << (char)(65 + (i % 26)) << (i / 26) << "\"" << ", x: " << x << ", y: " << y << ", size: " << size << ", color: " << "'#" << color << "'}," << "\n \t \t";

	 }
	 int x = (nodes_n - 1 * 3) % 500;
	 int y = (nodes_n - 1 * 2) % 100;
	 float size = 50 + ((output_centrality[nodes_n - 1]) / maxC)*(5 - .5);
	 long color = 0x005000 + ((float)(output_centrality[nodes_n - 1]) / maxC)*(0xFFFFF0);
	 myfile << "{ id: " << "\"n" + to_string(nodes_n - 1) + "\", label: " << "\"" << (char)(65 + (nodes_n - 1) % 26) << (nodes_n - 1) / 26 << "\"" << ", x: " << x << ", y: " << y << ", size: " << size << ", color: " << "'#" << color << "'}" << "\n \t" << "],";

	 // this is the part of edges in js file 

	 myfile << "\n" << "\t" << "edges: [" << "\n \t \t";
	 color = 0x00FF00;
	 for (int i = 0; i < edges_n - 1; i++) {
		 float size = 10 + ((float)(edges[i].second) / maxW)*(10 - .5); // it's an interpolation assuming that the maximum size is 5 so modify it as you like
																		//float size = 2;
																		//long color=BLACK+ ((float)(edges[i].second) / maxW)*(0x00FF00);//you can adjust this color

		 myfile << "{ id: " << "\"e" + to_string(i) + "\", source: " << "\"n" + to_string(edges[i].first.first) << "\" , target: " << "\"n" + to_string(edges[i].first.second) << "\"" << ", color: " << "'#" << color << "', type:'line', size: " << size << "}," << "\n \t \t";

	 }
	 size = 10 + ((float)(edges[edges_n - 1].second) / maxW)*(10 - .2);
	 // color = BLACK + ((float)(edges[edges_n - 1].second) / maxW)*(0xFFF0F0);//you can adjust this color
	 myfile << "{ id: " << "\"e" + to_string(edges_n - 1) + "\", source: " << "\"n" + to_string(edges[edges_n - 1].first.first) << "\" , target: " << "\"n" + to_string(edges[edges_n - 1].first.second) << "\"" << ", color: " << "'#" << color << "', type:'line', size: 5 }," << "\n \t" << "] \n" << "}";

	 myfile.close();
	 open_html();

 }

void Graph::open_html()
{
	//const wchar_t* trivial = L"c\help\helpFile.html";
	LPCTSTR helpFile = (L"proj.html");
	ShellExecute(NULL, (L"open"), helpFile, NULL, NULL, SW_SHOWNORMAL);
	system("PAUSE");
}

int Graph::max_weight() 
{
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

