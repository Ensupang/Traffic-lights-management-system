#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <vector>
using namespace std;
int i;
int j;
char ch;
int rd_s;
int rd_n;
int rd_l;
int upper=0;
void remove(int rd__s)
{
	string street_name[rd__s];
	int k=0;
	int g=1;
	for(i=0;i<rd__s;i++)
	{
		street_name[i]="AAAAAA";
		street_name[i][k]=street_name[i][k]+g;
		g++;
		if(i!=0&&i%24==0)
			{k+=1;g=1;}
		cout<<'r'<<' '<<"\""<<street_name[i]<<"\""<<endl;
	}
}
int recreate(int s, int n, int c, int l)
{
	ifstream urandom("/dev/urandom");
	if (urandom.fail()) 
	{
		cerr << "Error: cannot open /dev/urandom\n";
		return 1;
	}
//get a random number for rd_s([2,s])
	urandom.read(&ch,1);
	rd_s=(unsigned int)ch%s+1;
	while (rd_s<2)
	{
		urandom.read(&ch,1);
		rd_s=(unsigned int)ch%s+1;
	}
//cout<<"rd_s="<<rd_s<<endl;

//after getting rd_s, rd_n and rd_l, begin to generate the streets
	string street_name[rd_s];
	vector<vector<int>> check_same_street;
	vector<int> help;
	int k=0;
	int g=1;
	int count=0;
	int decide=1;
	unsigned int d=0;
	for(i=0;i<rd_s;i++)
	{
		street_name[i]="AAAAAA";
		street_name[i][k]=street_name[i][k]+g;
		g++;
		if(i!=0&&i%24==0)
			{k+=1;g=1;}
//get a random number for rd_n([1,n])
		urandom.read(&ch,1);
		rd_n=(unsigned int)ch%n+1;
		while (rd_n<1)
		{
			urandom.read(&ch,1);
			rd_n=(unsigned int)ch%n+1;
		}
		int line_segment[(rd_n+1)*2];
//cout<<"rd_n="<<rd_n<<endl;
		for(j=0;j<(rd_n+1)*2;j++)
		{
//get a random number for line_segment([-c,c])
			int out_of_range=0;
			urandom.read(&ch,1);
			line_segment[j]=((int)ch)%(c+1);
			if(j>1&&j%2==1)
				while(line_segment[j]<=line_segment[j-2])
				{
					line_segment[j]=line_segment[j]+1;
					out_of_range++;
					if(out_of_range>41)
					{
						cerr<<"Error:failed to generate valid input for 40 simultaneous attempts"<<endl;
						exit(0);
					}
				}
			help.push_back(line_segment[j]);
			if(j>1)
			{
				if(line_segment[j]==line_segment[j-2])
					count++;
				else
					count=0;
			}
			if(count==2)
			{
				j--;
				count=0;
			}
		}
		check_same_street.push_back(help);
		help.clear();
		if(i>1)
			for(int a=i-1;a>=0;a--)
				for(unsigned int b=0;b<check_same_street[a].size();b++)
				{
					if(check_same_street[i][d]==check_same_street[a][b])
					{
						d++;
						if(d==check_same_street[i].size())
						{
							decide=0;
							i--;d=0;check_same_street.pop_back();upper++;
							if(upper>25)
							{
								cerr<<"Error:failed to generate valid input for 25 simultaneous attempts"<<endl;
								exit(0);
							}
						}
						else if(d==check_same_street[a].size())
						{
							decide=0;
							i--;d=0;check_same_street.erase(check_same_street.begin()+a,check_same_street.begin()+a+1);upper++;
							if(upper>25)
							{
								cerr<<"Error:failed to generate valid input for 25 simultaneous attempts"<<endl;
								exit(0);
							}
						}
					}
					else
						d=0;
				}				
//cout the command
		if(decide==1)
		{
			cout<<'a'<<' '<<"\""<<street_name[i]<<"\""<<' ';
			for(j=0;j<(rd_n+1)*2;j++)
			{
				if(j==0)
					cout<<"(";
				else if(j%2==0)
					cout<<")(";
				else
					cout<<",";
				cout<<line_segment[j];
			}
			cout<<")"<<endl;
		}
	}
	cout<<'g'<<endl;
	urandom.read(&ch,1);
	rd_l=(unsigned int)ch%l+1;
	while (rd_l<5)
	{
		urandom.read(&ch,1);
		rd_l=(unsigned int)ch%l+1;
	}
	urandom.close();
	return rd_l;
}
int check_s(int num)
{
	if(num<2)
		{
			cerr<<"Error:the value of s is out of range"<<endl;
			return 1;
		}
	else
		return 0;
}
int check_n(int num)
{
	if(num<1)
		{
			cerr<<"Error:the value of n is out of range"<<endl;
			return 1;
		}
	else
		return 0;
}
int check_l(int num)
{
	if(num<5)
		{
			cerr<<"Error:the value of l is out of range"<<endl;
			return 1;
		}
	else
		return 0;
}
int main(int argc, char **argv) 
{
//get from command -s -n -l -c
	int s=10;
	int n=5;
	int l=5;
	int c=20;
	string str;
	if(cin.eof()!=1)
	{
	if(argc>=3)
	{
		str=argv[2];
		stringstream stm(str);
		if(argv[1][1]=='s')
		{
		stm>>s;
		if(check_s(s))
			exit(0);
		}
		else if(argv[1][1]=='n')
		{
		stm>>n;
		if(check_n(n))
			exit(0);
		}
		else if(argv[1][1]=='l')
		{
		stm>>l;
		if(check_l(l))
			exit(0);
		}
		else if(argv[1][1]=='c')
			stm>>c;
		else
		{
			cerr<<"Error:wrong instruction!"<<endl;
			exit(0);
		}
		if(argc>=5)
		{
			str=argv[4];
			stringstream stm(str);
			if(argv[3][1]=='n')
			{
			stm>>n;
			if(check_n(n))
				exit(0);
			}
			else if(argv[3][1]=='s')
			{
			stm>>s;
			if(check_s(s))
				exit(0);
			}
			else if(argv[3][1]=='l')
			{
			stm>>l;
			if(check_l(l))
				exit(0);
			}
			else if(argv[3][1]=='c')
				stm>>c;
			else
			{
				cerr<<"Error:wrong instruction!"<<endl;
				exit(0);
			}
			if(argc>=7)
			{
				str=argv[6];
				stringstream stm(str);
				if(argv[5][1]=='l')
				{
				stm>>l;
				if(check_l(l))
					exit(0);
				}
				else if(argv[5][1]=='s')
				{
				stm>>s;
				if(check_s(s))
					exit(0);
				}
				else if(argv[5][1]=='n')
				{
				stm>>n;
				if(check_n(n))
					exit(0);
				}
				else if(argv[5][1]=='c')
					stm>>c;
				else
				{
					cerr<<"Error:wrong instruction!"<<endl;
					exit(0);
				}
				if(argc>=9)
				{
					str=argv[8];
					stringstream stm(str);
					if(argv[7][1]=='l')
					{
					stm>>l;
					if(check_l(l))
						exit(0);
					}
					else if(argv[7][1]=='s')
					{
					stm>>s;
					if(check_s(s))
						exit(0);
					}
					else if(argv[7][1]=='n')
					{
					stm>>n;
					if(check_n(n))
						exit(0);
					}
					else if(argv[7][1]=='c')
						stm>>c;
					else
					{
						cerr<<"Error:wrong instruction!"<<endl;
						exit(0);
					}
					if(argc>=11)
					{
						cerr<<"Error:wrong instruction!"<<endl;
						exit(0);
					}
				}
			}
		}
	}
//cout<<"s="<<s<<" n="<<n<<" l="<<l<<" c="<<c<<endl;
//get a random number
	ifstream urandom("/dev/urandom");
	if (urandom.fail()) 
	{
		cerr << "Error: cannot open /dev/urandom\n";
		return 1;
	}

//get a random number for rd_l([5,l])
	urandom.read(&ch,1);
	rd_l=(unsigned int)ch%l+1;
	while (rd_l<5)
	{
		urandom.read(&ch,1);
		rd_l=(unsigned int)ch%l+1;
	}
	recreate(s,n,c,l);
	sleep(rd_l);
	remove(rd_s);
// close random stream
	urandom.close();
	while(1)
	{
		int time=recreate(s,n,c,l);
//cout<<"time="<<time<<endl;
		sleep(time);
		remove(rd_s);
	}
	}
	return 0;
}
