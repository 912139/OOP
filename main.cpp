#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <vector>
#include <sstream> 
#include <cstdlib>
#include <iomanip>
using namespace std;

class Ex
{
    double x;
public:
Ex (double a) : x(a) {};
~Ex () {};
double getX ()
{
    return x;
}
};

class Bar
{
    double y;
public:
Bar () : y(0) {};
~Bar () {};
void set (int a)
{
    if ((y + a) > 100)
    throw Ex(a*y);
    y = a;
}
double getY ()
{
    return y;
}
};

class IllegalCommand
{
    int m_position;
    char m_direction;
    const string m_error = "Invalid command. Please try again.";
public:
IllegalCommand (int position, char direction) : m_position(position), m_direction(direction) {};
virtual ~IllegalCommand () {};
string getError() {return m_error;}
int getPosition() {return m_position;}
int getDirection() {return m_direction;}
};

class OffTheField{
    int m_position;
    char m_direction;
    const string m_error = "You are out of the field! Please try again.";
public:
OffTheField (int position, char direction) : m_position(position), m_direction(direction) {};
virtual ~OffTheField () {};
string getError() {return m_error;}
int getPosition() {return m_position;}
int getDirection() {return m_direction;}
};

int getNumber ()
{
stringstream myString; // переменная для обработки ввода пользователя
string input; //ввод пользователя
int number; //ожидаемое число
string other; // иные данные кроме ожидаемого числа

while (true)
{
  getline (cin, input);
  myString << input;
  myString >> number; 

  if (!myString.fail()) // проверяем являются ли входные данные ожидаемым числом
  {
      myString >> other;
      if (myString.fail()) //проверяем вводил ли пользователь что-то кроме числа
      {
      return number;
      }
  }
 else {
     cout << "That input is invalid. Please try again!"<<endl;
     myString.str("");
     myString.clear();
      }
}
}

class Robot 
{
    int m_position;
public: 
Robot(int position) : m_position(position) {}
virtual ~Robot () {}
friend void print(Robot &R);
void move (char path_direction)
{
    switch (path_direction)
    {
        case ('w'):
        m_position -=10;
        if (m_position < 0)
        {
        m_position +=10;
        throw OffTheField(m_position, path_direction);
        }
        break;
        case ('s'):
        m_position +=10;
        if (m_position > 100)
        {
        m_position -=10;
        throw OffTheField(m_position, path_direction);
        }      
        break;
        case ('a'):
        m_position--;
        if (m_position%10 == 0)
        {
        m_position++;
        throw OffTheField(m_position, path_direction);
        }
        break;
        case ('d'):
        m_position++;
        if (m_position%10 == 1)
        {
        m_position--;
        throw OffTheField(m_position, path_direction);
        }
        break;
        case ('q'):
        break;
    default: throw IllegalCommand(m_position, path_direction);
    }
}
};

void print () 
{
    int i = 1;
    while (i <=100)
    {
        for (int j = 0; j < 10; ++j)
        {
            cout<<i<<'\t';
            i++;
        }
      cout<<endl;  
    }

}

void print (Robot &R)
{
    int i = 1;
    while (i <=100)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (i != R.m_position)
            cout<<i<<'\t';
            else 
            cout<<"{{R}}"<<'\t';
            i++;
        }
      cout<<endl;  
    }    
}

int main()
{
  div_t divresult;
  int a = 4;
  int b = 0;
try
{
if (b == 0)
throw "The denominator is zero!";
divresult = div(a,b);
cout <<"Quotient: "<<divresult.quot<<endl<<"Remainder: "<<divresult.rem;
} 
catch (const char* DivisionByZero)
{
cerr << "Error: " <<DivisionByZero<<endl;
}

Bar bar;
int n;
do
{
    try {
        cout<<"Enter the number: ";
        n = getNumber();
        if (n != 0)
        {
        bar.set(n);
        cout<<bar.getY();
        }
    } catch (Ex ex)
    {
      cerr <<"Error: (y + n) > 100! "<<"Ex.x = "<<ex.getX()<<endl;
    }
}while (n != 0);

int position;
char m;
cout<<"This is the field:"<<endl;
print();
do
{
cout<<"Enter the starting coordinate: ";
position = getNumber();
if (position > 100 || position < 0)
cout<<"Incorrect starting coordinates. Please try again!"<<endl;
}while (position > 100 || position < 0);
Robot r(position);
print(r);
do
{
try
{
cout<<"Choose the direction of movement (w - UP, a - LEFT, s - DOWN, d - RIGHT): "<<endl;
cout<<"If you want to exit, press q"<<endl;
cin>>m;
if (m !='q')
{
 r.move(m);
 print(r);
}
}
catch (IllegalCommand &illegalCommand)
{
cerr<<"Error: "<<illegalCommand.getError()<<" Position: "<<illegalCommand.getPosition()<<" Path direction = "<<static_cast<char>(illegalCommand.getDirection())<<endl;
}
catch (OffTheField &offTheField)
{
cerr<<"Error: "<<offTheField.getError()<<" Position: "<<offTheField.getPosition()<<" Path direction = "<<static_cast<char>(offTheField.getDirection())<<endl;
}
catch (...) // обработчик catch-all
{
    cout << "We caught an exception of an undetermined type!\n";
}


}while (m != 'q');
  return 0;
}