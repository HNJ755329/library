#include <bits/stdc++.h>
#include <queue>

int main(){
  std::priority_queue<int> pque;
  pque.push(1); 
  pque.push(3); 
  pque.push(5); 
  pque.push(8); 
  pque.push(4);
  pque.push(4);
  pque.push(0);

  while(!pque.empty()){
    printf("%d \n",pque.top());
    pque.pop();
  } 
  return 0;
}