#include <iostream>
#include <sstream>
#include <vector>
//include some head file in order to run cnf-sat
#include <memory>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
using namespace std;
const int room = 1000;//As large as possible
const int infinity = 99;
int length[room];
typedef struct
{
	int VerNum;
	int Edge[room][room];
} Graph;
Graph G;
//Initialize the graph's edge and get the number of vertices
void VGraph(Graph *G,int v)
{
	for (int a = 0; a < room; ++a)
	{
		for (int b = 0; b < room; ++b)
		{
			G->Edge[a][b] = infinity;
		}
	}
	G->VerNum = v;
}
//Create the graph, if there is an edge between two vertices, G.Edge of them becomes 1
int EGraph(Graph *G)
{
	char E;
	int i,j,k,x,y;
	string e;
	//initialize the Graph
	for(int a=0;a<G->VerNum;++a)
	{
		for(int b=0;b<G->VerNum;++b)
		{
			G->Edge[a][b]=infinity;
		}
	}
	cin>>E>>e;
	if (cin.eof())
		return 2;
	else
	{
		if(E!='E')
		{
			cin.clear();
			cin.ignore(100,'\n');
			cerr << "Error:Wrong instruction!" << endl;
			return 0;
		}
		if(e=="{}")
		{//cout<<" "<<endl;
			return 3;
		}
		for(i=0; e[i]!='\0';++i)
		{
			if(e[i]=='<')
			{
				for(j = 1; e[i + j] != ','; ++j)
					if (j == 1)
						x = int(e[i + j] - 48);
					else
						x = (10*x)+int(e[i+j]-48);
			}
			else if (e[i]==','&&e[i-1] >='0'&&e[i-1]<='9')
			{
				for (k=1; e[i+k]!='>';++k)
					if (k==1)
						y=int(e[i+k]-48);
					else
						y=(10*y)+int(e[i+k]-48);
			}
			else if (e[i]=='>')
			{
				if (x>=G->VerNum||y>=G->VerNum)
				{
					cin.clear();
					cin.ignore(100,'\n');
					cerr<<"Error:Out of range!"<<endl;
					return 0;
				}
				else if (x!=y)
					G->Edge[x][y] = 1;
			}
		}
		return 1;
	}
}
int MinVer(Graph G)
{
	//cout<<"I am in MinVer"<<endl;
	int k=0;
	int i;
	int j;
	int h;
	vector<vector<Minisat::Lit> > x;
	Minisat::vec<Minisat::Lit> lit_list;
	x.resize(G.VerNum);
	while(true)
	{	
		std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
		for(i=0;i<G.VerNum;i++)
			x[i].resize(k);
		for(i=0;i<G.VerNum;i++)
			for(j=0;j<k;j++)
				//create G.VerNum*k positive literals over G.VerNum*k new variables
				x[i][j]= Minisat::mkLit(solver->newVar());
		//(1)∀i ∈ [1, k], a clause (x 1,i ∨ x 2,i ∨ · · · ∨ x n,i )
		for(i=0;i<k;i++)
		{
			for(j=0;j<G.VerNum;j++)
					//x[1][1]||x[2][1]||x[3][1]...
					lit_list.push(x[j][i]);
			solver->addClause_(lit_list);
			lit_list.clear();
		}
		//(2)∀m ∈ [1, n], ∀p, q ∈ [1, k] with p < q, a clause (¬x m,p ∨ ¬x m,q )
		for(i=0;i<G.VerNum;i++)
			for(j=0;j<k-1;j++)
				for(h=j+1;h<k;h++)
					solver->addClause(~x[i][j], ~x[i][h]);
		//(3)∀m ∈ [1, k], ∀p, q ∈ [1, n] with p < q, a clause (¬x p,m ∨ ¬x q,m )
		for(i=0;i<k;i++)
			for(j=0;j<G.VerNum-1;j++)
				for(h=j+1;h<G.VerNum;h++)
					solver->addClause(~x[j][i], ~x[h][i]);
		//(4)∀hi, ji ∈ E, a clause (x i,1 ∨ x i,2 ∨ · · · ∨ x i,k ∨ x j,1 ∨ x j,2 ∨ · · · ∨ x j,k )
		for(i=0;i<G.VerNum;i++)
			for(j=0;j<G.VerNum;j++)
				if (G.Edge[i][j] == 1)
				{
					for(h=0;h<k;h++)
						lit_list.push(x[i][h]);
					for(h=0;h<k;h++)
						lit_list.push(x[j][h]);
					solver->addClause_(lit_list);
					lit_list.clear();
				}
		//check whether the CNF in the solver is satisfiable
		bool res = solver->solve();
		//std::cout << "The result is: " << res << "\n";
		if(res==0)
		{
			//end solver
			solver.reset (new Minisat::Solver());
			k++;
			continue;
		}
		else if(res==1)
		{
			int MV[k];
			int m=0;
			for(i=0;i<G.VerNum;i++)
				for(int j=0;j<k;j++)
				{	//cout<<"x["<<i<<"]["<<j<<"]="<<Minisat::toInt(solver->modelValue(x[i][j]))<<endl;
					if(Minisat::toInt(solver->modelValue(x[i][j]))==0)
					{MV[m]=i;m++;}	
				}
			//MV.sort();
			for(m=0;m<k;m++)
				cout<<MV[m]<<" ";
			cout<<endl;
			//end solver
			solver.reset (new Minisat::Solver());
			return 0;
		}
	}
}
int main()
{
	while (true)
	{
		char V;
		int f;
		int v;
		int cheo = 1;
		cin >> V;
		if (cin.eof())
			break;
		else
		{
			if(V=='V')
			{								
				cin >> v;
				VGraph(&G, v);
			}
			else if(V!='V')
			{
				cerr << "Error:Wrong instruction!" << endl;
				cin.clear();
				cin.ignore(100,'\n');
				cheo = 0;
			}
			if(cheo == 1)
			{
				f = EGraph(&G);
				while (f==0)
					f=EGraph(&G);
				if (f==2)
					break;
				//cout<<"ready to go into MinVer()"<<endl;
				if(f!=3)MinVer(G);
				cheo=0;
			}
		}
	}
	return 0;
}
