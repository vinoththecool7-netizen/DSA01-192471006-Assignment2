#include <iostream>
#include <string>
class SavingsAccount {
  std::string number; long long balance; static constexpr int capacity=10; long long transactions[capacity]{}; int count=0;
  void record(long long amount);
public:
  SavingsAccount(std::string n,long long b):number(n),balance(b) {}
  bool deposit(long long amount) { if(amount<=0) return false; balance+=amount; record(amount); return true; }
  bool withdraw(long long amount);
  void miniStatement() const;
};
void SavingsAccount::record(long long amount) { if(count==capacity) { for(int i=1;i<count;++i) transactions[i-1]=transactions[i]; --count; } transactions[count++]=amount; }
bool SavingsAccount::withdraw(long long amount) { if(amount<=0||amount>balance) return false; balance-=amount; record(-amount); return true; }
void SavingsAccount::miniStatement() const { std::cout<<number<<" balance "<<balance<<"\ntransactions:"; for(int i=0;i<count;++i) std::cout<<' '<<transactions[i]; std::cout<<'\n'; }
int main() { SavingsAccount a("S001",1000); for(int i=1;i<=11;++i) a.deposit(i); a.withdraw(20); a.miniStatement(); }
