#include "List.h"
#include "MyGraph.h"
#include<string>
#include<iostream>
#include "PHI.h"
using namespace std;
void main() {
	MyGraph thang("Data.txt", 'D', 'N');
	List<List<int>> a=thang.Hamilton();
	for (int i = 0; i < a.Length(); i++)
	{
		a.Value(i).Lout();
		cout << endl;
	}
	List<int> c = thang.Euler();
	thang.Dijkstra(1, 4).Lout("->");
	List<PHI<int>> b = thang.coloring();
	for (int i = 0; i < b.Length(); i++)
	{
		cout << b.Value(i).one << "-" << (char)b.Value(i).two<<endl;
	}
	thang.BFS(1,4).Lout("->");
	cout << endl;
	thang.DFS(1, 4).Lout("->");
	cout << endl;
	thang.Kruskal().LoutPHI();
	cout << endl;
	thang.Prim().LoutPHI();

}