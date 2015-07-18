#ifndef GRAPHIC_H
#define GRAPHIC_H
#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "List.h"
#include "QueueList.h"
#include "Stack.h"
#include "PHI.h"
#include<fstream>

class MyGraph
{
private:
	int _matrix[100][100];
	int _n;
	//------------------------------//
	void DFSmain(bool *checknode, Stack<int>&road, int x, int y, bool &finish)const;
	bool BFSmain(bool *checknode, List<int>&road, int x,int y)const;

	/*This Funstion's role is review the graphic has driection Euler
	return -1: even number
	return -2: impossible
	return >=0: the graphic has two note's rank odd*/
	int Review()const;
	void Search_Euler(int matrix[][100], int x, List<int>&road, bool &kt);
	void Try(int n, bool *checknode, int &start, Stack<int> _stack, List<List<int>>&);
public:
	MyGraph();
	MyGraph(int n);
	/*contructor,include: filename is file's name and type: + D: the type input file is graphic
	+ M: the type input file is matrix, typeH ( Y: the graphic has direction and N the graphic does not have direction) */
	MyGraph(string filename, char type, char typeH);

	//SET
	/*add a edge into graphic with 
	input: x to y 
	typeH ( Y: the graphic has direction and N the graphic does not have direction)
	oma is number on edge*/
	void setEdge(int x, int y, char typeH,int oma);

	/*add a node x into graphic*/
	void setNode(int x);

	//GET
	/*return ranks of a note*/
	int getRank(int x)const;

	/*Depth first search: include start from node x to node y*/
	List<int> DFS(int x,int y);

	/*breadth first search: incldue start from node x to node y*/
	List<int> BFS(int x,int y);

	/*finding the shortest path*/
	List<int> Dijkstra(int x, int y)const;

	List<PHI<int>> Prim()const;
	List<PHI<int>> Kruskal()const;

	List<List<int>> Hamilton();

	List<int> Floyd();

	/*coloring for graphic*/
	List<PHI<int>> coloring()const;

	List<int> Euler();

	bool Connectivity()const;

	void GraphicOut()const;

	~MyGraph();
};
#endif // !GRAPHIC_H



