#include <iostream>
class Time { int h,m; public: Time(int h,int m):h(h),m(m){} friend inline int minutesBetween(const Time& a,const Time& b){int d=(a.h-b.h)*60+a.m-b.m; return d<0?-d:d;} friend inline bool earlier(const Time& a,const Time& b){return a.h*60+a.m<b.h*60+b.m;} };
int main(){Time a(11,55),b(12,5); std::cout<<std::boolalpha<<minutesBetween(a,b)<<' '<<earlier(a,b)<<'\n'<<minutesBetween(a,a)<<' '<<earlier(a,a)<<'\n';}
