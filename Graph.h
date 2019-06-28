#pragma once
#include <vector>
#include <queue>
#include <utility>
#include <fstream>
#include <string>
//#include <bits/stdc++.h> 
#include <iostream>
#include <sstream>
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
	vector< vector< pair<int, int> > >vect;
	vector<double>output_centrality;
	vector< pair<pair<int,int>, int>>edges;
public:
	 Graph(int v);
	 Graph();
	void visualization_input();
	void Read_InputFile();
	void DegreeCentrality();
	void ClosenessCentrality();
	void BetweennessCentrality();
	void PrintOutput();
	void shortestPath(int src, vector<int>& dist);
	void addEdge(int u, int v, int w);
	void visualize();
	int max_weight();
	double max_closeness();
	 ~Graph();
};

