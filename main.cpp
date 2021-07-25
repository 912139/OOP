#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Figure {
public:
Figure () {}
virtual ~Figure () {cout<<"Object Figure has been deleted"<<endl;}
virtual void area() {}
};

class Parallelogram : public Figure {
protected:
float m_height;
float m_base;
public:
Parallelogram (float height, float base) : m_height(height), m_base(base) {}
~Parallelogram () {cout<<"Object Parallelogram has been deleted"<<endl;}
void area() override {cout<<"The area of the Parallelogram: "<<m_height*m_base<<endl;}
};

class Circle : public Figure {
float m_radius;
float const m_Pi = 3.14;
public:
Circle (float radius) : m_radius (radius) {}
~Circle () {cout<<"Object Circle has been deleted"<<endl;}
void area() override {cout<<"The area of the Circle: "<<m_radius*m_Pi<<endl;}
};

class Rectangle : public Parallelogram{
public:
Rectangle (float side1, float side2) : Parallelogram(side1, side2) {}
~Rectangle () {cout<<"Object Rectangle has been deleted"<<endl;}
void area() override {cout<<"The area of the Rectangle: "<<m_height*m_base<<endl;}
};

class Square : public Parallelogram{
public:
Square (float side1) :  Parallelogram(side1, side1) {}
~Square () {cout<<"Object Square has been deleted"<<endl;}
void area() override {cout<<"The area of the Square: "<<m_height*m_base<<endl;}
};

class Rhombus : public Parallelogram{
public:
Rhombus (float side1) :  Parallelogram(side1, side1) {}
~Rhombus () {cout<<"Object Rhombus has been deleted"<<endl;}
void area() override {cout<<"The area of the Rhombus: "<<m_height*m_base<<endl;}
};

class Car {
string company;
string model;
public:
Car() {cout<<"The Car has been created"<<endl;}
virtual ~Car() {}
};

class PassengerCar : virtual public Car {
public:
PassengerCar() {cout<<"The PassengerCar has been created"<<endl;}
~PassengerCar() {}
};

class Bus : virtual public Car  {
public:
Bus() {cout<<"The Bus has been created"<<endl;}
~Bus() {}
};

class Minivan : public PassengerCar, Bus {
public:
Minivan() {cout<<"The Minivan has been created"<<endl;}
~Minivan() {}
};

class Fraction {
int m_numerator;
int m_denominator;
public:
Fraction(int numerator, int denominator) {
    if (denominator == 0) {
        cout<<"Unable to create an object with denominator = 0."<<endl; 
        cout<<"The denominator is reassigned to 1"<<endl;
        m_numerator = 1;
        m_denominator = denominator;
    } else
    m_numerator = numerator;
    m_denominator = denominator;
}
friend Fraction operator+ (const Fraction &d1, const Fraction &d2);
friend Fraction operator- (const Fraction &d1, const Fraction &d2);
friend Fraction operator* (const Fraction &d1, const Fraction &d2);
friend Fraction operator/ (const Fraction &d1, const Fraction &d2);
Fraction operator- () const {
    return Fraction (-m_numerator, m_denominator);
}
friend bool operator== (const Fraction &d1, const Fraction &d2);
friend bool operator!= (const Fraction &d1, const Fraction &d2);
friend bool operator< (const Fraction &d1, const Fraction &d2);
friend bool operator> (const Fraction &d1, const Fraction &d2);
friend bool operator<= (const Fraction &d1, const Fraction &d2);
friend bool operator>= (const Fraction &d1, const Fraction &d2);
void getFraction() const 
{ 
    if (m_numerator == 0) 
    cout<<0<<endl; 
    else if (abs(m_numerator) == m_denominator)
    cout<<m_numerator/m_denominator;
    else
    cout<<m_numerator<<'/'<<m_denominator;
}
virtual ~Fraction() {}
};

Fraction operator+(const Fraction &d1, const Fraction &d2) {
 if (d1.m_denominator ==  d2.m_denominator) {
    return Fraction(d1.m_numerator + d2.m_numerator, d1.m_denominator);
 }
 else {
    return Fraction(d1.m_numerator*d2.m_denominator + d2.m_numerator*d1.m_denominator, d1.m_denominator*d2.m_denominator);
}
}

Fraction operator-(const Fraction &d1, const Fraction &d2) {
 if (d1.m_denominator ==  d2.m_denominator) {
    return Fraction(d1.m_numerator - d2.m_numerator, d1.m_denominator);
 }
 else {
    return Fraction(d1.m_numerator*d2.m_denominator - d2.m_numerator*d1.m_denominator, d1.m_denominator*d2.m_denominator);
}
}

Fraction operator*(const Fraction &d1, const Fraction &d2) {
    return Fraction(d1.m_numerator*d2.m_numerator, d1.m_denominator*d2.m_denominator);
}

Fraction operator/(const Fraction &d1, const Fraction &d2) {
    return Fraction(d1.m_numerator*d2.m_denominator, d1.m_denominator*d2.m_numerator);
}

bool operator==(const Fraction &d1, const Fraction &d2) {
    if (d1.m_numerator*d2.m_denominator == d2.m_numerator*d1.m_denominator)
    return true;
    else return false;
}

bool operator<(const Fraction &d1, const Fraction &d2) {
    if (d1.m_numerator*d2.m_denominator < d2.m_numerator*d1.m_denominator)
    return true;
    else return false;
}

bool operator!=(const Fraction &d1, const Fraction &d2) {
    if (operator ==(d1, d2))
    return false;
    else return true;
}

bool operator>(const Fraction &d1, const Fraction &d2) {
    if (d1.m_numerator*d2.m_denominator > d2.m_numerator*d1.m_denominator)
    return true;
    else return false;
}

bool operator<=(const Fraction &d1, const Fraction &d2) {
    if (operator >(d1, d2))
    return false;
    else return true;
}

bool operator>=(const Fraction &d1, const Fraction &d2) {
    if (operator <(d1, d2))
    return false;
    else return true;
}

class Card {
enum m_suit {hearts, diamonds, clubs, spades};
enum m_card_value {ace, king, queen, jack, ten, nine, eight, seven, six, five, four, three, two};
bool m_card_status;
public:
Card () {}
virtual ~Card () {}
bool Flip() {return !m_card_status;}
m_card_value GetValue() const {return m_card_value{};}
};

int main () {
    {
    Rhombus r(4);
    Figure* rhombus = &r;
    rhombus->area();
    }
   
    Car car;
    PassengerCar passengerCar;
    Bus bus;
    Minivan minivan;

    Fraction f1(3,4);
    Fraction f2(1,6);
    Fraction fsum(0,0);
    fsum = f1 + f2;
    f1.getFraction(); cout<<" + "; f2.getFraction(); cout<<" = ";
    fsum.getFraction();
    cout<<endl;
    fsum = f1 - f2;
    f1.getFraction(); cout<<" - "; f2.getFraction(); cout<<" = ";
    fsum.getFraction();
    cout<<endl;
    fsum = f1 * f2;
    f1.getFraction(); cout<<" * "; f2.getFraction(); cout<<" = ";
    fsum.getFraction();
    cout<<endl;
    fsum = f1 / f2;
    f1.getFraction(); cout<<" / "; f2.getFraction(); cout<<" = ";
    fsum.getFraction();
    cout<<endl;
    cout<<"-("; fsum.getFraction();cout<<") = ";
    fsum = -fsum;
    fsum.getFraction();
    cout<<endl;
    f1.getFraction(); cout<<" == "; f2.getFraction(); cout<<": ";
    cout<<boolalpha<<(f1 == f2)<<endl;
    f1.getFraction(); cout<<" != "; f2.getFraction(); cout<<": ";
    cout<<boolalpha<<(f1 != f2)<<endl;
    f1.getFraction(); cout<<" < "; f2.getFraction(); cout<<": ";
    cout<<boolalpha<<(f1 < f2)<<endl;
    f1.getFraction(); cout<<" > "; f2.getFraction(); cout<<": ";
    cout<<boolalpha<<(f1 > f2)<<endl;
    f1.getFraction(); cout<<" <= "; f2.getFraction(); cout<<": ";
    cout<<boolalpha<<(f1 <= f2)<<endl;
    f1.getFraction(); cout<<" >= "; f2.getFraction(); cout<<": ";
    cout<<boolalpha<<(f1 >= f2)<<endl;
    return 0;
}