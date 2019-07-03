# Social-Media-Analysis
Graph theory applications based project

## Project Objectives
* Implement different Centrality Algorithms from scratch on an given undirected graph
* Implement Visualization for the Centralities
* The Computation and Visualization aren't dependent
* Centrality Types:
  + Degree Centrality
  + Closeness Centrality
  + Betweenness Centrality

## Detailed Input Steps Description
* The program will read from a file describing the graph named __input.txt__.
* Write in the first line two integers n,m where:
  + n is the number of nodes
  + m is the number of edges in the graph
  + 1 < n < V, 0 < m < E
* Follow by writing m lines describing the edges of the graph contain three integers a, b, c that represents an undirected edge where:
  + a node
  + b node
  + c weight between a and b

## Output Description
* Print n lines showing the centrality measure for all the nodes
* The output will take the form C(NODE)
* Centrality for nodes should be printed ascendingly according to the node’s id

## Degree Centrality
* Simplest centrality measure
* It's simply the number of edges connected to each node
* Already Implemented in the project
* Takes input from input.txt file
* Has an executable for Graph Visualizations in which each node has its own degree Centrality

## Closeness Centrality
* Indicates how close a node is to all other nodes in the network
* Using Dijkstra Algorithm in the implementation
* It is calculated as the average of the shortest path length from the node to every other node in network
* Already Implemented in the project
* Takes input from input.txt file
* Has an executable for Graph Visualizations in which each node has its own closeness Centrality

## Betweeness Centrality
* Measures the number of times a node lies on the shortest path between other nodes
* Using Floyd-Warshall Algorithm in implementation
* Takes input from input.txt file
