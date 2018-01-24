#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <queue>

enum {
    LOCK,
    UNLOCK,
};

/*
 * Helper routines for pthreads
 */

void pclock(char *msg, clockid_t cid) {
    struct timespec ts;
    printf("%s", msg);
    if (clock_gettime(cid, &ts) == -1) {
	perror("clock_gettime"); exit(0);
    }
    printf("%4ld.%03ld\n", ts.tv_sec, ts.tv_nsec / 1000000);
}

void errp(char *s, int code) {
    fprintf(stderr, "Error: %s -- %s\n", s, strerror(code));
}

void mulock(int ul, pthread_mutex_t *m) {
    int retcode = 0;
    char myErrStr[100];

    if(ul) {
	/* unlock */
	strcpy(myErrStr, "mutex_unlock");
	retcode = pthread_mutex_unlock(m);
    }
    else {
	/* lock */
	strcpy(myErrStr, "mutex_lock");
	retcode = pthread_mutex_lock(m);
    }

    if(retcode) {
	fprintf(stderr, "%s, %s\n", myErrStr, strerror(retcode));
	exit(0);
    }
}



std::string appro_vc1(int &vernum, vector < vector<int> > edges){
  vector<int> vc = {};
  // if there is no edges in E
  bool empty_flag = true;
  for(auto &one_vector: edges) {
    if(! one_vector.empty()) {
      empty_flag = false;
      break;
    }
  }

  if(empty_flag) {
    return "APPROX-VC-1: " ;
  }

  while(!edges.empty()){
  // find the vertex with the largest degree
    int max_degree = edges[0].size();
    int i=0,ver_max=0;
    for(auto &one_vector: edges){
      if(one_vector.size()>max_degree){
        max_degree = one_vector.size();
        ver_max = i;
      }

          i++;
    }
    // std::cout<<"maximum degree of"<<ver_max<< "is that:"<<max_degree<<std::endl;

// add the vertex to the Vertex Cover and remove it and all adjacent edges from G
    vc.push_back(ver_max);
    for(int j=0;j<edges.size();j++){
      if(j==ver_max){
        edges[j].clear();
        break;
      }
    }
      int j=0;
      for(auto &v: edges){
        auto it = std::find(v.begin(), v.end(), ver_max);
        if (it != v.end())
        {
// swap the one to be removed with the last element and remove the item at the end of the container
// to prevent moving all items after ver_max by one
          std::swap(*it, v.back());//v
          v.pop_back();
      }
        // std::cout<<"size of "<<j<<" is:"<<edges[j].size()<<"\n";
        j++;
    }
//check whether the Edges vector is empty
    bool empt_flag=true;
    for(auto &v: edges){
      if(!v.empty()){
        empt_flag = false;
        break;
      }
    }
    if (empt_flag==true){
      // std::cout<<"stop!!"<<std::endl;
      break;
    }

}
  std::ostringstream output;
  output<<"APPROX-VC-1: ";
  std::sort(vc.begin(),vc.end());
  for(int i=0; i<vc.size()-1; i++){
    output<<vc[i]<<",";
  }
    output<<vc[vc.size()-1];

    // std::cout<<std::endl;

  return output.str();
}



std::string appro_vc2(int &vernum, vector <vector<int> > edges){
  vector<int> vc = {};
  vector<int> picked_edge = {};
  // if there is no edges in E
  bool empty_flag = true;
  for(auto &one_vector: edges) {
    if(! one_vector.empty()) {
      empty_flag = false;
      break;
    }
  }

  if(empty_flag) {
    
    return "APPROX-VC-2:  ";
  }

  bool picked_flag[vernum];
  bzero(&picked_flag, sizeof(picked_flag));

  for (int src = 0; src < edges.size(); src++) {
    if (picked_flag[src]) {
      continue;
    }
    for (auto &dst: edges[src]) {
      if (picked_flag[dst] || picked_flag[src]) {
        continue;
      }
      picked_flag[src] = true;
      picked_flag[dst] = true;
    }
  }
  for(int i = 0; i < vernum; i++) {
    if (picked_flag[i]) {
      vc.push_back(i);
    }
  }

//   while(!edges.empty()){
//
//   // pick up the first edge
//     for(int src = 0; src<edges.size();src++){
//
//       for(auto &dst: edges[src]){
//         picked_edge.push_back(src);
//         picked_edge.push_back(dst);
//         vc.push_back(src);
//         vc.push_back(dst);
//         std::cout <<"src: "<<src<<" "<<"dst: "<<dst<<std::endl;
//
//
//         for(int i=0; i<picked_edge.size();i++){
//           for(int j=0;j<edges.size();j++){
//             if(j==picked_edge[i]){
//               std::cout<<"clear " <<j<<"list"<<std::endl;
//               edges[j].clear();
//               for(auto &p: edges[j])
//                 std::cout << "p in cleared list is: "<<p<<std::endl;
//             }
//           }
//           for(auto &v: edges){
//             auto it = std::find(v.begin(),v.end(),picked_edge[i]);
//             if(it!=v.end()){
//               std::cout<<"swap "<< *it<<std::endl;
//               std::swap(*it,v.back());
//               v.pop_back();
//
//             }
//           }
//         }
//
//       }
//     }
//     // check whether the Edges vector is empty
//     bool empt_flag=true;
//     for(auto &v: edges){
//       if(!v.empty()){
//         empt_flag = false;
//         break;
//           }
//         }
//     if (empt_flag==true){
//       // std::cout<<"stop!!"<<std::endl;
//       break;
//     }
// }

std::ostringstream output;
output<<"APPROX-VC-2: ";
std::sort(vc.begin(),vc.end());
for(int i=0; i<vc.size()-1; i++){
  output<<vc[i]<<",";
}
  output<<vc[vc.size()-1];

return output.str();
}
