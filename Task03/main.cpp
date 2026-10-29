#include <iostream>
struct Parcel { double kg; bool express=false; bool insured=false; };
double compute(double kg,bool express,bool insured) { return kg*50+(express?30:0)+(insured?20:0); }
double charge(int grams,bool express=false,bool insured=false) { std::cout<<"grams "; return compute(grams/1000.0,express,insured); }
double charge(double kg,bool express=false,bool insured=false) { std::cout<<"kg "; return compute(kg,express,insured); }
double charge(const Parcel& p) { std::cout<<"parcel "; return compute(p.kg,p.express,p.insured); }
int main() { std::cout<<charge(2)<<'\n'; std::cout<<charge(2.0)<<'\n'; std::cout<<charge(2.0f)<<'\n'; std::cout<<charge(Parcel{2,true,false})<<'\n'; std::cout<<charge(2,true)<<'\n'; std::cout<<charge(2.0,true,true)<<'\n'; }
