#include <iostream>
#include <string>
using namespace std;
#include <cassert> // для assert()
#include <vector>

template <class T>
class Pair1 { 
private:
T number_1;
T number_2;
public:
Pair1(T a, T b) : number_1(a), number_2(b) {}
~Pair1()
{}
T first () const {
    return number_1;
}
T second () const {
    return number_2;
}
};

template <class T, class U> 
class Pair2
{ 
private:
T number_1;
U number_2;
public:
Pair2(T a, U b) : number_1(a) , number_2(b) {}
~Pair2() {}
T first () const {
    return number_1;
}
U second () const {
    return number_2;
}
};

template <class T> 
class Pair3
{ 
private:
string number_1;
T number_2;
public:
Pair3(string a, T b) : number_1(a) , number_2(b) {}
~Pair3() {}
string first () const {
    return number_1;
}
T second () const {
    return number_2;
}
};

template <class T>
class StringValuePair: public Pair3<T>
{ 
public:
StringValuePair(string a, T b) : Pair3<T>(a, b) {}
~StringValuePair() {};
};

class Card
{
public:
    enum rank {
        ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        JACK, QUEEN, KING
    };
    enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };
    
    Card(rank r = ACE, suit s = SPADES, bool ifu = true);
    int GetValue() const;
    void Flip();
    
private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu)
{}

int Card::GetValue() const
{
    int value = 0;
    if (m_IsFaceUp)
    {
        value = m_Rank;
        if (value > 10)
        {
            value = 10;
        }
    }
    return value;
}

void Card::Flip()
{
    m_IsFaceUp = !(m_IsFaceUp);
}

class Hand
{
public:
    Hand();
    // виртуальный деструктор
    virtual ~Hand();
    
    // добавляет карту в руку
    void Add(Card* pCard);
    
    // очищает руку от карт
    void Clear();
    
    //получает сумму очков карт в руке, присваивая тузу
    // значение 1 или 11 в зависимости от ситуации
    int GetTotal() const;
    
protected:
    vector<Card*> m_Cards;
};

Hand::Hand()
{
    m_Cards.reserve(7);
}
// деструктор по-прежнему виртуальный
// это уже можно не обозначать
Hand::~Hand()
{
    Clear();
}

void Hand::Add(Card* pCard)
{
    m_Cards.push_back(pCard);
}

void Hand::Clear()
{
    // проходит по вектору, освобождая всю память в куче
    vector<Card*>::iterator iter = m_Cards.begin();
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        delete *iter;
        *iter = 0;
    }
    // очищает вектор указателей
    m_Cards.clear();
}

int Hand::GetTotal() const
{
    // если карт в руке нет, возвращает значение 0
    if (m_Cards.empty())
    {
        return 0;
    }
    
    //если первая карта имеет значение 0, то она лежит рубашкой вверх:
    // вернуть значение 0
    if (m_Cards[0]->GetValue() == 0)
    {
        return 0;
    }
    
    // находит сумму очков всех карт, каждый туз дает 1 очко
    int total = 0;
    vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        total += (*iter)->GetValue();
    }
    
    // определяет, держит ли рука туз
    bool containsAce = false;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        if ((*iter)->GetValue() == Card::ACE)
        {
            containsAce = true;
        }
    }
    
    // если рука держит туз и сумма довольно маленькая, туз дает 11 очков
    if (containsAce && total <= 11)
    {
        // добавляем только 10 очков, поскольку мы уже добавили
        // за каждый туз по одному очку
        total += 10;
    }
    
    return total;
}


class GenericPlayer : public Hand {
string name;
public:
GenericPlayer(string n) : name(n) {}
~GenericPlayer () {}
virtual bool IsHitting() const;
bool IsBoosted() const;
void Bust() const;
};

bool GenericPlayer::IsBoosted() const {
if (GetTotal() > 21)
return true;
else return false;
}

void GenericPlayer::Bust() const {
    if (IsBoosted())
    cout<<"Еhe player: "<<name<<" has too much!";
    else cout<<"no";
}

int main () {
 Pair1<int> p1(6, 9);
 cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
 const Pair1<double> p2(3.4, 7.8);
 cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
cout<<"------------------"<<endl;
 Pair2<int, double> p3(6, 7.8);
 cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';
 const Pair2<double, int> p4(3.4, 5);
 cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';
cout<<"------------------"<<endl;
 StringValuePair<int> svp("Amazing", 7);
 std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
 return 0;
}