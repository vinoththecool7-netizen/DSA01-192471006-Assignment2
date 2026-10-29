#include <chrono>
#include <iostream>
#include <vector>
#include <cassert>
struct Shift { std::vector<int> a; size_t count=0; explicit Shift(size_t k):a(k){} void add(int x){if(count==a.size()){for(size_t i=1;i<count;++i)a[i-1]=a[i]; --count;} a[count++]=x;} std::vector<int> list()const{return {a.begin(),a.begin()+count};} };
struct Ring { std::vector<int> a; size_t start=0,count=0; explicit Ring(size_t k):a(k){} void add(int x){if(count<a.size()){a[(start+count)%a.size()]=x;++count;}else{a[start]=x;start=(start+1)%a.size();}} std::vector<int> list()const{std::vector<int> out; for(size_t i=0;i<count;++i)out.push_back(a[(start+i)%a.size()]);return out;} };
template<class T> double measure(size_t k,int n){T v(k); auto begin=std::chrono::steady_clock::now(); for(int i=0;i<n;++i)v.add(i); auto end=std::chrono::steady_clock::now(); auto result=v.list(); assert(result.size()==k && result.front()==n-static_cast<int>(k) && result.back()==n-1); return std::chrono::duration<double,std::milli>(end-begin).count();}
int main(){ for(size_t k:{10u,50u,1000u}) { constexpr int n=200000; Shift s(k); Ring r(k); for(int i=0;i<n;++i){s.add(i);r.add(i);} assert(s.list()==r.list()); std::cout<<"capacity "<<k<<" inserts "<<n<<" identical yes shift "<<measure<Shift>(k,n)<<" ms ring "<<measure<Ring>(k,n)<<" ms\n"; } }
