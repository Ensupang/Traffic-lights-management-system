#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
using namespace std;
int rgen(int argc, char **argv)
{
	argv[0]=(char*)"rgen";
        int mes=execv("rgen",argv);
	if(mes==-1)
		perror("Error:from rgen");
	return 0;
}
int a1(void)
{
	char* argv[3];
	argv[0]=(char*)"python";
	argv[1]=(char*)"ece650-a1.py";
	argv[2]=nullptr;
	int mes=execvp("python",argv);
	if(mes==-1)
		perror("Error:from a1");
	return 0;
}
int a2(void)
{
	char* argv2[2];
	argv2[0]=(char*)"ece650-a2";
	argv2[1]=nullptr;
        int mes=execv("ece650-a2",argv2);
	if(mes==-1)
		perror("Error:from a2");
	return 0;
}
int type(void) 
{
	while (!cin.eof()) 
	{
	string line;
	getline(cin, line);
	if (line.size () > 0)
		cout<<line<<endl;
	}
	return 0;
}
//main function
int main(int argc, char **argv)
{
	vector<pid_t> kids;
// create a pipe "a3"
	int a3[2];
	pipe(a3);
//create a pipe "RgenToA1"
	int RgenToA1[2];
	pipe(RgenToA1);
	pid_t child_pid;
//create a----first----------------------------------------------------------------fork
	child_pid = fork ();
//if this is the child fork
	if (child_pid == 0)
	{
		// redirect stdout to the pipe
		dup2(RgenToA1[1], STDOUT_FILENO);
		close(RgenToA1[0]);
		close(RgenToA1[1]);
		// start process A
		return rgen(argc, argv);
	}
	else if (child_pid < 0) 
	{
		cerr << "Error: could not fork\n";
		return 1;
	}
	kids.push_back(child_pid);
//create a-------------------------------------------------------------------------fork
	child_pid = fork ();
//if this is the child fork
	if (child_pid == 0)
	{
		dup2(RgenToA1[0], STDIN_FILENO);
		close(RgenToA1[0]);
		close(RgenToA1[1]);
		// redirect stdout to the pipe
		dup2(a3[1], STDOUT_FILENO);
		close(a3[0]);
		close(a3[1]);
		// start process A
		return a1();
	}
	else if (child_pid < 0) 
	{
		cerr << "Error: could not fork\n";
		return 1;
	}
	kids.push_back(child_pid);
//create--------------------------------------------------------------------another fork
	child_pid = fork();
	if (child_pid == 0)
	{
		// redirect stdin from the pipe
		dup2(a3[0], STDIN_FILENO);
		close(a3[1]);
		close(a3[0]);
		// start process C
		return a2();
	}
	else if (child_pid < 0) 
	{
		cerr << "Error: could not fork\n";
		return 1;
	}
	kids.push_back(child_pid);
	child_pid = 0;
// redirect stdout to the pipe
	dup2(a3[1], STDOUT_FILENO);
	close(a3[0]);
	close(a3[1]);
// start process B
	int res=type();
// send kill signal to all children
	for (pid_t k : kids) 
	{
		int status;
		kill (k, SIGTERM);
		waitpid(k, &status, 0);
	}
// exit with return code of process B
	return res;
}
