#include <iostream>
#include <math.h>
#include <cstdint>
using namespace std;

class Power
{
    int p_a = 0;
    int p_b = 0;
public:
    Power () {
    }
    void set (int a, int b) {p_a = a; p_b = b;}
    void calculate () {int c; c = pow(p_a, p_b); cout<<c<<endl;}

};

class RGBA
{
    uint8_t m_red = 0;
    uint8_t m_green = 0;
    uint8_t m_blue = 0;
    uint8_t m_alpha = 255;
public:
      RGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : m_red(red), m_green(green), m_blue(blue), m_alpha (alpha)
{
}
void print (){
    cout<<unsigned (m_red)<<unsigned (m_green)<<unsigned (m_blue)<<unsigned (m_alpha)<<endl;
}

};

class Stack
{
private:
    int s_array[10];
    int s_i;
public:
void reset() {
    s_i = 0;
    for (int i = 0; i < 10; ++i) {
        s_array[i] = 0;
    }
}
bool push(int a) {
    if (s_i != 10) {
    s_array[s_i] = a;
    s_i++;
    return true;
    } else return false;
}

void pop () {
    if (s_i == 0)
    cout<<"stack is empty"<<endl;
    else
    s_i--;
}

void print () {
    cout<<'(';
    for (int i = 0; i < s_i; ++i){
        cout<<s_array[i];
    }
    cout<<')'<<endl;
}

};

int main()
{
Power P;
P.set(2,3);
P.calculate();

RGBA R(1,2,3,4);
R.print();

    Stack stack;
    stack.reset();
    stack.print();
    
    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();
    
    stack.pop();
    stack.print();
    
    stack.pop();
    stack.pop();
    stack.print();
    
    return 0;
}