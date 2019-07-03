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
void open_html() {
	//const wchar_t* trivial = L"c\help\helpFile.html";
	LPCTSTR helpFile = (L"proj.html");
	ShellExecute(NULL, (L"open"), helpFile, NULL, NULL, SW_SHOWNORMAL);
	system("PAUSE");
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
	double x=0;
	double y=0;
	double prev_x = 0;
	double prev_y = 0;

	myfile << " var graph = {" << "\n" << "\t" << "nodes: [" << "\n \t \t";
	for (int i = 0; i < nodes_n - 1; i++) {
		//double x = (2 * i % 400 + .5*i*i);
		//double y = (2 * i % 200) + .5;
		
		//rand()%10-10
		//double x = rand() % 10 - 10;
		//double y = rand() % 10 - 10;
		// the first quarter of the polygon
		if (i == 0) {
			x = 0;
			y = 0;
			prev_x = x;
			prev_y = y;
		}
		else if (i <= nodes_n / 4) {
			x = prev_x + 1+(0.08*i)-.5*i;
			y = prev_y + 1 +(0.1*i);
			prev_x = x;
			prev_y = y;
		}
		else if (i <= nodes_n / 2 && i > nodes_n / 4) {
			x = prev_x + 1 + (0.09*i) - .2*i;
			y = prev_y - 1 - (0.09*i);
			prev_x = x;
			prev_y = y;
		}
		else if (i <= 3*nodes_n / 4 && i > nodes_n / 2) {
			x = prev_x - 1  + .1*i;
			y = prev_y - 1 - (0.08*i);
			prev_x = x;
			prev_y = y;
		}
		else {
			x = prev_x - 1 +0.09*i;
			y = prev_y + 1 + (0.07*i);
			prev_x = x;
			prev_y = y;
		}
		double size;
		long color;
		if (output_centrality[i] == maxC) {
			size = 50+((output_centrality[i] *4) / maxC)*(14); // it's an interpolation assuming that the maximum size is 5 so modify it as you like
			color = 0x0000FF;
		}
		else {
			size = 50+ ((output_centrality[i] *4) / maxC)*(10); // it's an interpolation assuming that the maximum size is 5 so modify it as you like
			//long color =  ((double)(output_centrality[i]) / maxC)*(0x00000);//you can adjust this color
			//	long long color = (long long)((0xFFFFFF)+((double)(output_centrality[i]) / maxC)*(0xFF0000-0XFF00FF)) ;
			color = 0x605000 + ((float)(output_centrality[i]) / maxC)*(0xFFFFF0);
		
		}
		 
		myfile << "{ id: " << "\"n" + to_string(i) + "\", label: " << "\"" << i << "\"" << ", x: " << x << ", y: " << y << ", size: " << size << ", color: " << "'#" << color << "'}," << "\n \t \t";

	}
	x = prev_x - 1 + 0.04*(nodes_n - 1);
	y = prev_y + 1 + (0.07*(nodes_n - 1));
	//int x = (nodes_n - 1 * 3) % 500;
	//int y = (nodes_n - 1 * 2) % 100;
	float size =  50+((output_centrality[nodes_n - 1])*4 / maxC)*(10);
	//double color = (0xFFFFFF +((double)(output_centrality[nodes_n - 1]) / maxC)*(0xFF0000 - 0XFF00FF));
	long color = 0x605000 + ((float)(output_centrality[nodes_n - 1]) /( maxC))*(0xFFFFF0);

	myfile << "{ id: " << "\"n" + to_string(nodes_n - 1) + "\", label: " << "\"" << (nodes_n - 1 )<< "\"" << ", x: " << x << ", y: " << y << ", size: " << size << ", color: " << "'#" << color << "'}" << "\n \t" << "],";

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

