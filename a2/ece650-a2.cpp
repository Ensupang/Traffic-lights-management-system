#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
const int room = 100;//As large as possible
const int infinity = 99;
int length[room];
typedef struct
{
	int VerNum;
	int Edge[room][room];
} Graph;
Graph G;
/*Dijkstra Algorithm*/
void Dijkstra(int Num, int s1, int *length, int *prev, int edge[room][room])
{
	bool s[room];
	for (int i = 0; i < Num; ++i)
	{
		length[i] = edge[s1][i];
		s[i] = 0;
		if (length[i] == infinity)
			prev[i] = -1;
		else
			prev[i] = s1;
	}
	length[s1] = 0;
	s[s1] = 1;
	for (int i = 1; i < Num; ++i)
	{
		int tmp = infinity;
		int u = s1;
		for (int j = 0; j < Num; ++j)
			if ((!s[j]) && length[j]<tmp)
			{
				u = j;
				tmp = length[j];
			}
		s[u] = 1;
		for (int j = 0; j < Num; ++j)
			if ((!s[j]) && edge[u][j]<infinity)
			{
				int newlen = length[u] + edge[u][j];
				if (newlen < length[j])
				{
					length[j] = newlen;
					prev[j] = u;/*Remember the shortest edge*/
				}
			}
	}
}
/*Output the shortest edge*/
int Output(int *prev, int v, int u)
{
	int q[room];
	int count = 1;
	q[count] = u;
	count++;
	int tmp = prev[u];
	if (u == v)
	{
		cout << u << endl;
		return 1;
	}
	if (tmp == -1)
	{
		cerr << "Error:No edge between these two vertices!" << endl;
		return 0;
	}
	while (tmp != v)
	{
		q[count] = tmp;
		count++;
		tmp = prev[tmp];
		if (tmp == -1)
		{
			cerr << "Error:No edge between these two vertices!" << endl;
			return 0;
		}
	}
	q[count] = v;
	for (int i = count; i >= 1; --i)
		if (i != 1)
			cout << q[i] << "-";
		else
			cout << q[i] << endl;
	return 1;
}
/*Initialize the graph's edge and get the number of vertices*/
void VGraph(Graph *G,int v)
{
	for (int a = 0; a < 100; ++a)
	{
		for (int b = 0; b < 100; ++b)
		{
			G->Edge[a][b] = infinity;
		}
	}
	G->VerNum = v;
}
/*Create the graph, if there is an edge between two vertices, G.Edge of them becomes 1*/
int EGraph(Graph *G)
{
	char E;
	int i, j, k, x, y;
	string e;
	for (int a = 0; a < G->VerNum; ++a)
	{
		for (int b = 0; b < G->VerNum; ++b)
		{
			G->Edge[a][b] = infinity;
		}
	}
	//cout << "Insert E" << endl;
	cin >> E >> e;
	if (cin.eof())
		return 2;
	else
	{
		if (E != 'E')
		{
			if (E == 's')
				cin >> e;
			cerr << "Error:Wrong instruction!" << endl;
			return 0;
		}
		for (i = 0; e[i] != '\0'; ++i)
		{
			if (e[i] == '<')
			{
				for (j = 1; e[i + j] != ','; ++j)
					if (j == 1)
						x = int(e[i + j] - 48);
					else
						x = (10 * x) + int(e[i + j] - 48);
			}
			else if (e[i] == ','&&e[i - 1] >= '0'&&e[i - 1] <= '9')
			{
				for (k = 1; e[i + k] != '>'; ++k)
					if (k == 1)
						y = int(e[i + k] - 48);
					else
						y = (10 * y) + int(e[i + k] - 48);
			}
			else if (e[i] == '>')
			{
				if (x >= G->VerNum || y >= G->VerNum)
				{
					cerr << "Error:Out of range!" << endl;
					return 0;
				}
				else if (x != y)
				{
					G->Edge[x][y] = 1;
					G->Edge[y][x] = 1;
				}
			}
		}
		return 1;
	}
}
/*Get the head vertex and the tail vertex, and we need to find out the shortest edge between them*/
int sGraph(Graph G,int s1,int s2)
{
	int prev[room];
	int count = 0;
	int count2 = 0;
	if (s1 >= G.VerNum || s2 >= G.VerNum)
	{
		cerr << "Error:Out of range!" << endl;
		return 0;
	}
	for (int a = 0; a<G.VerNum; ++a)
		for (int b = 0; b<G.VerNum; ++b)
			if (G.Edge[a][b] == 1)
			{
				if (a == s1 || b == s1)
					count++;
				if (a == s2 || b == s2)
					count2++;
			}
	if (count == 0 || count2 == 0)
	{
		if (s1 != s2)
		{
			cerr << "Error:No edge between these two vertices!" << endl;
			return 0;
		}
		else
		{
			cout << s1 << endl;
			return 1;
		}
	}
	for (int i = 1; i <= G.VerNum; ++i)
		length[i] = infinity;
	Dijkstra(G.VerNum, s1, length, prev, G.Edge);
	return Output(prev, s1, s2);
}
int main()
{
	for (int a = 0; a < 100; ++a)
	{
		for (int b = 0; b < 100; ++b)
		{
			G.Edge[a][b] = infinity;
		}
	}
	
	while (!cin.eof())
	{
		char S, V;
		int f;
		int s1, s2, v, cheo = 1, che, chei;
		string w;
		//cout << "Insert V" << endl;
		cin >> V;
		if (cin.eof())
			break;
		else
		{
			if (V == 'V')
			{
				cin >> v;
				G.VerNum = v;
			}
			else if (V != 'V')
			{
				if (V == 's')
				{
					cin >> v;
					cin >> v;
				}
				else if (V == 'E')
				{
					cin >> w;
				}
				cerr << "Error:Wrong instruction!" << endl;
				cheo = 0;
			}
			while (cheo == 1)
			{
				chei = 1;
				f = EGraph(&G);
				while (f == 0)
				{
					f = EGraph(&G);
				}
				if (f == 2)
				{
					break;
				}
				while (chei == 1)
				{
					//cout << "Insert s or V" << endl;
					cin >> S;
					if (cin.eof())
					{
						cheo = 0;
						f = 2;
						break;
					}
					if (S == 's')
					{
						cin >> s1 >> s2;
						che = sGraph(G, s1, s2);
						while (che == 0)
						{
							cin >> S;
							if (cin.eof())
							{
								cheo = 0;
								chei = 0;
								f = 2;
								break;
							}
							if (S == 's')
							{
								cin >> s1 >> s2;
								che = sGraph(G, s1, s2);
							}
							else
							{
								cin >> v;
								VGraph(&G, v);
								chei = 0;
								break;
							}
						}
					}
					else if (S == 'V')
					{
						cin >> v;
						VGraph(&G, v);
						chei = 0;
					}
					else
					{
						cerr << "Error:Wrong instruction!" << endl;
						cin >> w;
						chei = 1;
					}
				}
			}
			if (f == 2)
				break;
		}
	}
	return 0;
}