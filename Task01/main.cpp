#include <iostream>
void value(long long fee, int p) { fee -= fee*p/100; std::cout << "inside value: " << fee << '\n'; }
void reference(long long& fee, int p) { fee -= fee*p/100; }
void pointer(long long* fee, int p) { if (fee) *fee -= *fee*p/100; }
long long returned(long long fee, int p) { return fee-fee*p/100; }
int main() { long long a=45000,b=a,c=a; value(a,10); reference(b,10); pointer(&c,10); std::cout<<"stored: "<<a<<' '<<b<<' '<<c<<"\nreturned: "<<returned(a,10)<<'\n'; }
