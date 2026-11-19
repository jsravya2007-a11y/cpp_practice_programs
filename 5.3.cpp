#include<iostream>
using namespace std;
class car{
    int speed=0;
    friend class dashbroad;
    public:
    void  accelerate() { speed+=10;}       
};
class dashbroad{
    public:
    void display(const car &c){
        cout<<"speed="<<c.speed<<"km/h";
    }
};
int main(){
    car c;
     c.accelerate() ; 
    c.accelerate();
    dashbroad ().display(c);
    return 0;
}