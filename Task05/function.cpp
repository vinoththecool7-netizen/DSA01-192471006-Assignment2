#include <iostream>
class Ticket { static int issued; int seat; public: Ticket():seat(issued<3?++issued:0){} static int count(){return issued;} int get()const{return seat;} };
int Ticket::issued=0;
void makeTickets(){ Ticket t[2]; for(const auto& x:t) std::cout<<"seat "<<x.get()<<'\n'; std::cout<<"issued "<<Ticket::count()<<'\n'; }
int main(){makeTickets();makeTickets();}
