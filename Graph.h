#pragma once
#include <vector>
#include <queue>
#include <utility>
#include <fstream>
#include <string>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <functional>
#include <algorithm>

#define INF 999999
#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define BLUE 0x0000FF
#define RED 0xFF0000

using namespace std;
class Graph
{
private:
	int nodes_n, edges_n;
	string file_name;
	vector< vector< pair<int, int> > >vect;
	vector<double>output_centrality;
	vector< pair<pair<int,int>, int>>edges;

	void shortestPath(int src, vector<int>& dist);
	double sum_vector(vector<int>&x, unsigned int size);
	int max_weight();
	double max_closeness();
	void open_html();
	void GetPaths(int i, int j, vector<vector<vector<int> > > &seq, vector<vector<int>>&pair_paths);
public:
	 Graph(string file_name);
	 void Read_InputFile();
	 void PrintOutput();
	void DegreeCentrality();
	void ClosenessCentrality();
	void BetweennessCentrality();
	void visualization_input();
	void visualize();
	 ~Graph();
};

