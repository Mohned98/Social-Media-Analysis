#pragma once
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
class Graph
{
private:
	int nodes_n, edges_n;
	vector< vector< pair<int, int> > >vect;
	vector<double>output_centrality;
public:
	Graph();
	void Read_InputFile();
	void DegreeCentrality();
	void ClosenessCentrality();
	void BetweennessCentrality();
	void PrintOutput();
	~Graph();
};

