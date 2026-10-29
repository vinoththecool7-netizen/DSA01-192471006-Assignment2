#include <iostream>
#include <vector>
#include <stdexcept>
int& highest(int* a, int n) { if(n<=0) throw std::invalid_argument("empty"); int best=0; for(int i=1;i<n;++i) if(a[i]>a[best]) best=i; return a[best]; }
const int& highestReadOnly(const int* a, int n) { if(n<=0) throw std::invalid_argument("empty"); int best=0; for(int i=1;i<n;++i) if(a[i]>a[best]) best=i; return a[best]; }
int highestCopy(const int* a, int n) { return highestReadOnly(a,n); }
int main() { int marks[]={60,80,70}; highest(marks,3)+=2; std::cout<<"moderated: "<<marks[1]<<'\n'; highest(marks,3)=90; int copy=highestCopy(marks,3); copy=0; std::cout<<"assigned: "<<highestReadOnly(marks,3)<<" copy: "<<copy<<'\n'; std::vector<int> v{1,2}; auto index=std::size_t{1}; v.push_back(3); std::cout<<"index after growth: "<<v[index]<<'\n'; }
