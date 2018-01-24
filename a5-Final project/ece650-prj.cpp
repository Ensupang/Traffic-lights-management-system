#include <memory>
// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <utility>
#include <queue>
#include "graph.hpp"
#include "vc_solver.hpp"


std::queue<Graph> job_q;
sem_t job_q_flag1, job_q_flag2,job_q_flag3;
sem_t next_flag1, next_flag2, next_flag3;
sem_t done_flag1, done_flag2, done_flag3;
// sem_t s_quit;
bool quit_eof = false;
// clockid_t start_time1, start_time2, start_time3, end_time1, end_time2, end_time3;
// timespec s_timespec1, s_timespec2, s_timespec3, e_timespec1, e_timespec2, e_timespec3;
pthread_mutex_t dlock;
pthread_t thr1, thr2, thr3, thr_IO; //thread identifier
std::string ret1, ret2, ret3;
int vernum;
class ToCNF{
  int N;


public:
  ToCNF(int &N);
  std::string check_satisfiable(int &N, int &K, vector < vector<int> > edges);
  std::string result(int &N, vector < vector<int> > edges);

};
ToCNF::ToCNF(int &N){
  this->N = N;


}


std::string ToCNF::result(int &N, vector < vector<int> > edges){
  bool empty_flag = true;
  std::string res;
  for(auto &one_vector: edges) {
    if(! one_vector.empty()) {
      empty_flag = false;
      break;
    }
  }
  if(empty_flag) {
    return "CNF-SAT-VC: ";
  }
  for(int k=1; k<= N; k++){
    // ToCNF *cnf = nullptr;
    // cnf = new ToCNF(N);
    res =ToCNF::check_satisfiable(N,k,edges);

    if(res.size()!=0){
      return res;
      break;
    }

  }
  return "";

}

std::string ToCNF::check_satisfiable(int &N, int &K, vector < vector<int> > edges){

  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());

  Minisat::vec<Minisat::Lit> litls;

  //the size of vertex cover is K and there are N vertexes in Graph

  for(int i=0; i< K*N; i++)
  litls.push(Minisat::mkLit(solver->newVar()));


  //check if it is at least one vertex is the ith vertex in vertex cover
  for(int i=0; i<K; i++){
    Minisat::vec<Minisat::Lit> addlits;
    for(int j=0; j<N; j++){
      addlits.push(litls[j+i*N]);
    }
    solver->addClause(addlits);

  }


  //check whether no one vertex appear twice in a vertex cover
  for(int i=0; i<N; i++){
    for(int j=0; j<K; j++){
      for(int m=j+1; m<K; m++){
        Minisat::vec<Minisat::Lit> addlits;
        addlits.push(~litls[i+j*N]);
        addlits.push(~litls[i+m*N]);
        solver->addClause(addlits);
      }
      //std::cerr<<"j is "<< j<<" size of addlits: " << addlits.size()<<std::endl;
    }
  }


  //check whether no more than one vertex appears in the ith position in a vertex cover
  for(int i=0; i<K; i++){
    for(int j=0; j<N; j++){
      for(int m=j+1; m<N; m++){
        Minisat::vec<Minisat::Lit> addlits;
        addlits.push(~litls[j+i*N]);
        addlits.push(~litls[m+i*N]);
        solver->addClause(addlits);
      }
    }
  }


  //check whether every edge is incident to at least one vertex in the vertex cover
  for(std::size_t src = 0, max =edges.size(); src != max; src++) {
    for(auto &dst: edges[src]) {
      Minisat::vec<Minisat::Lit> addlits;
      for(int i = 0; i < K; i++) {
        // std::cerr <<  K<<" " << src << " " << dst << std::endl;
        addlits.push(litls[src + i*N]);
        addlits.push(litls[dst + i*N]);
      }
      solver->addClause(addlits);
    }

  }




  bool yon = solver->solve();
  std::ostringstream output;
  vector <int> min_vc= {};
  if(yon) {
    output << "CNF-SAT-VC: ";
    for (int i=0; i<N; i++){
      for(int j=0; j<K; j++)
      if(solver->modelValue(litls[i+j*N]) == Minisat::l_True){
        min_vc.push_back(i);
      }

    }
    for(int k=0; k<min_vc.size()-1; k++)
    output<< min_vc[k]<<",";
    output<<min_vc[min_vc.size()-1];

    return output.str();
  }
  return "";

}


// start three threads for calculation the minimum vertex cover
void * start_thread1(void * arg) {
  int sem_rs1;
  while(true){
    sem_rs1 = sem_wait(&next_flag1);
    if(sem_rs1 != 0){
      std::cerr << "Fail to wait for semaphore next flag!" << std::endl;
      break;
    }
    sem_rs1 = sem_wait(&job_q_flag1);
    if(sem_rs1 != 0){
      std::cerr << "Fail to wait for semaphore job_q flag!" << std::endl;
      break;
    }
    Graph graph = job_q.front();
    ToCNF *cnf = nullptr;
    cnf = new ToCNF(graph.V);
    // pthread_getcpuclockid(pthread_self(), &start_time1);
    // clock_gettime(start_time1, &s_timespec1);
    ret1=cnf->result(graph.V,graph.adjList);
    // pthread_getcpuclockid(pthread_self(), &end_time1);
    // clock_gettime(end_time1, &e_timespec1);
    // struct timespec time_spent = pclock_interval(s_timespec1, e_timespec1);

    sem_rs1 = sem_post(&done_flag1);
    if(sem_rs1 != 0){
      std::cerr << "Fail to post semaphore done flag!" << std::endl;
      break;
    }

  }
  return NULL;
}

void * start_thread2(void * arg) {
  int sem_rs2;
  while(true){
    sem_rs2 = sem_wait(&next_flag2);
    if(sem_rs2 != 0){
      std::cerr << "Fail to wait for semaphore next flag!" << std::endl;
      break;
    }
    sem_rs2 = sem_wait(&job_q_flag2);
    if(sem_rs2 != 0){
      std::cerr << "Fail to wait for semaphore job_q flag!" << std::endl;
      break;
    }
    Graph graph = job_q.front();
    ret2=appro_vc1(graph.V,graph.adjList);

    sem_rs2 = sem_post(&done_flag2);
    if(sem_rs2 != 0){
      std::cerr << "Fail to post semaphore done flag!" << std::endl;
      break;
    }

  }
  return NULL;

}

void * start_thread3(void * arg) {
  int sem_rs3;
  while(true){
    sem_rs3 = sem_wait(&next_flag3);
    if(sem_rs3 != 0){
      std::cerr << "Fail to wait for semaphore next flag!" << std::endl;
      break;
    }
    sem_rs3 = sem_wait(&job_q_flag3);
    if(sem_rs3 != 0){
      std::cerr << "Fail to wait for semaphore job_q flag!" << std::endl;
      break;
    }
    Graph graph = job_q.front();
    ret3=appro_vc2(graph.V,graph.adjList);

    sem_rs3 = sem_post(&done_flag3);
    if(sem_rs3 != 0){
      std::cerr << "Fail to post semaphore done flag!" << std::endl;
      break;
    }

  }
  return NULL;

}
int producer(int vertex_num, std::vector< vector<int> > edges){
  mulock(LOCK,&dlock);
  job_q.push(Graph(vertex_num,edges));
  mulock(UNLOCK,&dlock);
  int rett1 = sem_post(&job_q_flag1);
  int rett2 = sem_post(&job_q_flag2);
  int rett3 = sem_post(&job_q_flag3);
  if(rett1 != 0 || rett2 != 0 || rett3 != 0) {
    std::cerr << "Post queue sem error" << std::endl;
  }
  return 0;
}

bool starts_with(const string& s1, const string& s2) {
  return s2.size() <= s1.size() && s1.compare(0, s2.size(), s2) == 0;
}

void * start_thread_IO(void * arg) {
  int res;
  char inputco, mark,comma,opmark;
  char flag = ' ';
  int vernum, vertex1, vertex2;
  Graph * g = nullptr;

  std::string line;
  while(true){
    while(!std::getline(std::cin,line).eof()){
      std::istringstream iss (line);
      try{
        if(starts_with(line,"V ")){
          if (flag == 'V'){
            throw "Error: We are waiting for 'E' Command!";
          }
          iss>>inputco>>vernum;
          g = new Graph(vernum);
          flag = 'V';
          continue;
        }

        if(starts_with(line,"E")){
          if(!g){
            throw "Error: No existed graph!";
          }
          if (flag == 'E'){
            throw "Error: We are waiting for 'V' Command!";
          }

          iss>>inputco>>mark>>mark;
          if(mark=='}'){
            flag = 'E';
            // g->addEdge(0,0);
            producer(g->V,g->adjList);
            res = sem_wait(&done_flag1);
            if(res != 0){
              std::cerr << "Fail to wait semaphore done flag!"<<std::endl;
              break;
            }
            std::cout << ret1 << std::endl;
            res = sem_wait(&done_flag2);
            if(res != 0){
              std::cerr << "Fail to wait semaphore done flag!"<<std::endl;
              break;
            }
            std::cout << ret2 << std::endl;
            res = sem_wait(&done_flag3);
            if(res != 0){
              std::cerr << "Fail to wait semaphore done flag!"<<std::endl;
              break;
            }
            std::cout << ret3 << std::endl;

            mulock(LOCK, &dlock);
            job_q.pop();
            mulock(UNLOCK, &dlock);
            sem_post(&next_flag1);
            sem_post(&next_flag2);
            sem_post(&next_flag3);

            continue;
          }
          else{

            while(mark=='<'){
              iss>>vertex1>>comma>>vertex2>>opmark;
              // std::cout<<vertex1<<" "<<vertex2<<'\n';
              if(vertex1 > vernum -1 || vertex2 > vernum -1){
                throw "Error: Vertex ID for 'E' is invalid!";
              }
              if(vertex1 < 0 || vertex2 < 0){
                throw "Error: Invalid Vertex! Enter a non-negative number!";
              }
              g->addEdge(vertex1,vertex2);
              iss>>comma;
              if(comma!=','){
                break;
              }
              else
              iss>>mark;
            }
            flag = 'E';
            producer(g->V,g->adjList);
            res = sem_wait(&done_flag1);
            if(res != 0){
              std::cerr << "Fail to wait semaphore done flag!"<<std::endl;
              break;
            }
            std::cout << ret1 << std::endl;
            res = sem_wait(&done_flag2);
            if(res != 0){
              std::cerr << "Fail to wait semaphore done flag!"<<std::endl;
              break;
            }
            std::cout << ret2 << std::endl;
            res = sem_wait(&done_flag3);
            if(res != 0){
              std::cerr << "Fail to wait semaphore done flag!"<<std::endl;
              break;
            }
            std::cout << ret3 << std::endl;

            mulock(LOCK, &dlock);
            job_q.pop();
            mulock(UNLOCK, &dlock);
            sem_post(&next_flag1);
            sem_post(&next_flag2);
            sem_post(&next_flag3);

            continue;
          }

        }

      }catch(const char* excep){
        fseek(stdin, 0, SEEK_END);
        fprintf(stderr, "%s\n", excep);
      }
      // getchar();


    }
    quit_eof = true;

    if(job_q.empty() && quit_eof){

      // sem_post(&s_quit);
      break;
    }
  }
  return NULL;
}






int main(int argc, char **argv) {
  int ret;
  pthread_mutex_init(&dlock, NULL);
  sem_init(&done_flag1, 0, 0);
  sem_init(&done_flag2, 0, 0);
  sem_init(&done_flag3, 0, 0);
  sem_init(&job_q_flag1, 0, 0);
  sem_init(&job_q_flag2, 0, 0);
  sem_init(&job_q_flag3, 0, 0);
  sem_init(&next_flag1, 0, 1);
  sem_init(&next_flag2, 0, 1);
  sem_init(&next_flag3, 0, 1);
  // sem_init(&s_quit,0,0);
  ret = pthread_create(&thr1, NULL, &start_thread1, NULL);
  ret = pthread_create(&thr2, NULL, &start_thread2, NULL);
  ret = pthread_create(&thr3, NULL, &start_thread3, NULL);
  ret = pthread_create(&thr_IO, NULL, &start_thread_IO, NULL);

  // if(job_q.empty()){
  //   pthread_cancel(thr_output);
  // } else {
    pthread_join(thr_IO,NULL);
    // sem_wait(&s_quit);
  // }
  pthread_cancel(thr1);
  pthread_cancel(thr2);
  pthread_cancel(thr3);
  return 0;
}
