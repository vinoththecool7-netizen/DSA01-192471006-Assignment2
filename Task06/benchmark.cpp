#include <chrono>
#include <iostream>
struct Time { int h,m; int minutesTo(const Time& b) const {int d=h*60+m-b.h*60-b.m; return d<0?-d:d;} int hour() const{return h;} int minute() const{return m;} };
inline int inlined(const Time& a,const Time& b){int d=a.h*60+a.m-b.h*60-b.m; return d<0?-d:d;}
#if defined(__clang__) || defined(__GNUC__)
__attribute__((noinline))
#endif
int noninline(const Time& a,const Time& b){int d=a.h*60+a.m-b.h*60-b.m; return d<0?-d:d;}
int getters(const Time& a,const Time& b){int d=a.hour()*60+a.minute()-b.hour()*60-b.minute(); return d<0?-d:d;}
template<class F> void bench(const char* name,F f){ Time a{9,45},b{13,10}; volatile long long sum=0; auto start=std::chrono::steady_clock::now(); for(int i=0;i<10000000;++i){a.m=i%60; sum+=f(a,b);} auto end=std::chrono::steady_clock::now(); std::cout<<name<<": "<<std::chrono::duration<double,std::milli>(end-start).count()<<" ms checksum "<<sum<<'\n'; }
int main(){bench("inline",[](const Time&a,const Time&b){return inlined(a,b);}); bench("noinline",[](const Time&a,const Time&b){return noninline(a,b);}); bench("member",[](const Time&a,const Time&b){return a.minutesTo(b);}); bench("getters",[](const Time&a,const Time&b){return getters(a,b);});}
