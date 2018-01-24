#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <queue>
#include <string.h>
using namespace std;
// Use this value as Infinite since I assume a graph larger than this won't be tested on this code
#define INF 2 << 22

// Create the class for graph and define necessary properties and functions
// adjList  stores the whole adjacency list structure
// addEdge function connects an edge u with another edge v
// BFS function find the shortest path using breadth-first searching

class Graph{

public:
	int V;
	vector < vector<int> >  adjList;

public:
	Graph(int const &V);
	Graph(int const &V, vector < vector<int> >  adjList);
	void addEdge(int const &u, int const &v);
	bool getEdge(int const &u, int const &v);
	char * BFS(int const &v1, int const &v2);
	void printList();
};


// Initialize the graph with node count and scale the adjacency list with node count
Graph::Graph(int const &V){
	this->V = V;
	adjList.resize(V);
}

Graph::Graph(int const &V, vector < vector<int> >  adjList ){
	this->V = V;
	this->adjList = adjList;
}


// Go to the (u) th vector position then add v to the linked list
void Graph::addEdge(int const &u, int const &v){
	bool flag=true;
	for(auto &it: adjList[u]){
		if(it==v){
			flag=false;
			break;
		}
		}
	if(flag==true){
		adjList[u].push_back(v);
	}

	for(auto &it: adjList[v]){
		if(it==u){
			flag=false;
			break;
		}
		}
	if(flag==true){
		adjList[v].push_back(u);
	}
}

// Test addEdge function
bool Graph::getEdge(int const &u, int const &v) {
	bool ret = false;
	for(auto &i: adjList[u]) {
		if(i == v) {
			ret = true;
			break;
		}
	}
	return ret;
}

// Find path though the graph from a given node to another
// If start and end node are same then nothing to do just print that node

char*  findPath(int const &startNode, int const &endNode, int* &parent){
	char* str = (char*)malloc(sizeof(char) * 100);
	if( startNode == endNode || endNode == -1){

		sprintf(str, "%d", startNode);

	}
	else{
		char * next = findPath(startNode, parent[endNode], parent);
		strcpy(str, next);
		sprintf(str+strlen(next), "-%d", endNode);

	}
	return str;
}

void Graph::printList() {
	for(int i = 0; i < V; i++) {
		printf("%d -> ", i);
		for(auto &j: adjList[i]) {
			printf("%d", j);
		}
		printf("\n");
	}
}



// Set distance array to infinite for all nodes and parent to -1. Set distance
// of parent node to zero and push to the queue. Take it out of queue and push
// all the reachable nodes from current node to queue.
// Also set the distance of the current node as the distance of its parent node
// plus one assuming all the distances are one instead of another same value.
// Set parent of current node to the node that was taken out of queue.
char * Graph::BFS(int const &v1, int const &v2){

	int *dist = new int[V];
	int *parent = new int[V];
	for(int v = 0; v < V; ++v){
		dist[v] = INF;
		parent[v] = -1;
	}

	dist[v1] = 0;
	queue<int> Q;
	Q.push( v1 );


	while( !Q.empty() ){
		int u = Q.front();
		Q.pop();

		//cout << u << " ";

		vector<int>::iterator it;
		for(it = adjList[u].begin(); it != adjList[u].end(); ++it){
			if( dist[*it] == INF ){
				Q.push(*it);
				dist[*it] = dist[u] + 1;
				parent[*it] = u;
			}
		}
	}




	// Try to find the shortest path from current node to another
	char * ret= nullptr;
	if( dist[v2] != INF ){
		ret = findPath(v1,v2,parent);

		printf("%s\n", ret);
	}

	else{

		fprintf(stderr, "Error: No paths available\n");

	}
	return ret;
}
