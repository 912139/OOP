#include <iostream>
#include <string>
#include <math.h> 
using namespace std;

class Person {
string m_name;
int m_age;
string m_gender;
int m_weight;

public:
    Person (){}
//методы переназначения имени, возраста и веса
void changeNamePerson (string name) {
    m_name = name;
}

void changeAgePerson (int age) {
    m_age = age;
}

void changeWeightPerson (int weight) {
    m_weight = weight;
}


friend class Student;
};

class Student : public Person {
int m_year_of_study;

public:

Student () {}

Student (string name, int age, string gender, int weight, int year_of_study) {
    m_name = name;
    m_age = age;
    m_gender = gender;
    m_weight = weight;
    m_year_of_study = year_of_study;

}

void initStudent (string name, int age, string gender, int weight, int year_of_study)
{
    m_name = name;
    m_age = age;
    m_gender = gender;
    m_weight = weight;
    m_year_of_study = year_of_study;
}

void showStudent () const
{
cout<<"Name:"<<m_name<<endl<<"Age:"<<m_age<<endl<<"Gender:"<<m_gender<<endl<<"Weight:"<<m_weight<<endl<<"Year of study:"<<m_year_of_study<<endl;
}
//метод переназначения года обучения
void changingTheStudentsYear(int year_of_study) {
m_year_of_study = year_of_study;
}
//метод увеличения года обучения
void increaseTheStudentsYear() {
m_year_of_study++;
}

string getName() const
{
return m_name;
}

};

struct Node {
    Student s;
    Node* next;
    Node () : next(nullptr) {}
};

struct List {
    int counter_students;
    Node* head;
    Node* last;
    List () : counter_students(0), head(nullptr), last(nullptr) {}
};

void addingToTheList (List* StudentsList, Student student) {
    Node* CurrentStudent = new Node;
    CurrentStudent->s = student;
    if (StudentsList->head == NULL) {
    StudentsList->counter_students++;
    StudentsList->head = CurrentStudent;
    StudentsList->last = CurrentStudent;
    } else {
    StudentsList->counter_students++;
    StudentsList->last->next = CurrentStudent;
    StudentsList->last = CurrentStudent;

}
}


List* createNewStudent (List* StudentsList, string name, int age, string gender, int weight, int year_of_study)
{
    Student student(name, age, gender, weight, year_of_study);
    addingToTheList(StudentsList, student);
  
 return StudentsList;
 }

 void searchStudent (List* StudentsList, string name) 
 {
     Node* CurrentNode = StudentsList->head;
     do
     {
        if (CurrentNode->s.getName() == name) {
        CurrentNode->s.showStudent();
        return;
        }
       CurrentNode = CurrentNode->next;
     } while (CurrentNode->next != NULL);
      if (CurrentNode->s.getName() == name)
      {
      CurrentNode->s.showStudent();
      return;
      }
cout<<"Student is not found"<<endl;
 }

 void counterStudents (List* StudentsList)
{
     cout<<"The number of students is: "<<StudentsList->counter_students<<endl;
}

//Задание 2

class Fruit {
string f_name;
string f_color;
public:
Fruit(string name, string color) {
f_name = name; 
f_color = color;
}

string getName () const {
return  f_name;  
}

string getColor () const {
return  f_color;  
}
};

class Apple : public Fruit {
public:

Apple(string color) 
: Fruit ("apple", color) {}

Apple(string name, string color) 
: Fruit (name, color) {}

};

class Banana : public Fruit {
public:

Banana() 
: Fruit ("banana", "yellow") {}
};

class GrannySmith : public Apple {
public:
GrannySmith() 
: Apple ("Granny Smith apple", "green") {}
};

//ЗАДАНИЕ 3////////////////////////////////
class Human {
//карты из колоды
enum c_cards {A = 10, K = 10, Q = 10, J = 10, _10 = 10, _9 = 9, _8 = 8, _7 = 7, _6 = 6, _5 = 5, _4 = 4, _3 = 3, _2 = 2};
int h_bank; //банк игрока
c_cards h_hand[10]; //рука игрока
public: 
Human() {}
};

class Dealer : public Human {
public: 
Dealer() : Human() {}
//действия дилера в игре
void getPlay() {} //дилер начинает игру
void getAnalysis() {} //дилер анализирует и руку и берёт карту если нужно
void getResult() {} //дилер заканчивает игру
//.......
};

class Player : public Human {
public: 
Player() {}
//действия игрока в игре
void getBet () {}
void hit () {}
void stand () {}
void split () {}
void fdouble () {}
void surrender () {}
//.......


};

int main()
{
    //ЗАДАНИЕ 1////////////////////////////////
    Student StudentInna("Inna", 18, "woman", 55, 1);
    StudentInna.changeNamePerson("Anna"); //метод переназначения имени
    StudentInna.changeAgePerson(17); //метод переназначения возраста
    StudentInna.changeWeightPerson(60); //метод переназначения веса
    StudentInna.changingTheStudentsYear(2); //метод переназначения года обучения
    StudentInna.increaseTheStudentsYear(); //метод увеличения года обучения
    //StudentInna.showStudent();
    List* StudentsList = new List; //Создание пустого списка студентов
    //добавление в список студента "Anna"
    addingToTheList(StudentsList, StudentInna); //метод добавления студента в список
    //Создание и добавление в список новых студентов
    StudentsList = createNewStudent(StudentsList, "Alex", 20, "man", 70, 3); //метод создания студента с добавлением в список
    StudentsList = createNewStudent(StudentsList, "Ivan", 18, "man", 60, 1);
    StudentsList = createNewStudent(StudentsList, "Igor", 18, "man", 65, 1);
    searchStudent(StudentsList, "Igor");//метод вывода человека по запросу
    counterStudents(StudentsList);//метод вывода счётчика студентов
    //ЗАДАНИЕ 2////////////////////////////////
    Apple a("red");
    Banana b;
    GrannySmith c;
    cout<<"My "<<a.getName()<<" is "<<a.getColor()<<".\n";
    cout<<"My "<<b.getName()<<" is "<<b.getColor()<<".\n";
    cout<<"My "<<c.getName()<<" is "<<c.getColor()<<".\n";
    //ЗАДАНИЕ 3////////////////////////////////
    Human human;
    Dealer dealer;
    Player player;
    return 0;
}