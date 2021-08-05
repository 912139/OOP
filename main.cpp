#include <iostream>
#include <string>
using namespace std;
#include <cassert>
#include <vector>
#include <sstream> 

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

ostream& endll (ostream &out)
{
    out.flush();
    out.put('\n');
    out.put('\n');
    return out;
}

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
    friend ostream& operator<<(ostream& os, const Card& aCard);
    
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


class GenericPlayer : public Hand
{
    friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
    
public:
    GenericPlayer(const string& name = "");
    
    virtual ~GenericPlayer();
    
    // показывает, хочет ли игрок продолжать брать карты
    // Для класса GenericPlayer функция не имеет своей реализации,
    // т.к. для игрока и дилера это будут разные функции
    virtual bool IsHitting() const = 0;
    
    // возвращает значение, если у игрока перебор -
    // сумму очков большую 21
    // данная функция не виртуальная, т.к. имеет одинаковую реализацию
    // для игрока и дилера
    bool IsBusted() const;
    
    // объявляет, что игрок имеет перебор
    // функция одинакова как для игрока, так и для дилера
    void Bust() const;
    
protected:
    string m_Name;
};

GenericPlayer::GenericPlayer(const string& name) :
m_Name(name)
{}
GenericPlayer::~GenericPlayer()
{}


bool GenericPlayer::IsBusted() const
{
    return (GetTotal() > 21);
}


void GenericPlayer::Bust() const
{
    cout << m_Name << " busts.\n";
}

class Player : public GenericPlayer
{
public:
    Player(const string& name = "");
    
    virtual ~Player();
    
    // показывает, хочет ли игрок продолжать брать карты
    virtual bool IsHitting() const;
    
    // объявляет, что игрок победил
    void Win() const;
    
    // объявляет, что игрок проиграл
    void Lose() const;
    
    // объявляет ничью
    void Push() const;
};

bool Player::IsHitting() const
{
    cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}

void Player::Win() const
{
    cout << m_Name << " wins.\n";
}

void Player::Lose() const
{
    cout << m_Name << " loses.\n";
}

void Player::Push() const
{
    cout << m_Name << " pushes.\n";
}

Player::Player(const string& name) :
GenericPlayer(name)
{}
Player::~Player()
{}

class House : public GenericPlayer
{
public:
    House(const string& name = "House");
    
    virtual ~House();
    
    // показывает, хочет ли дилер продолжать брать карты
    virtual bool IsHitting() const;
    
    // переворачивает первую карту
    void FlipFirstCard();
};

bool House::IsHitting() const
{
    return (GetTotal() <= 16);
}

void House::FlipFirstCard()
{
    if (!(m_Cards.empty()))
    {
        m_Cards[0]->Flip();
    }
    else
    {
        cout << "No card to flip!\n";
    }
}

House::House(const string& name) :
GenericPlayer(name)
{}
House::~House()
{}

ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const string SUITS[] = { "c", "d", "h", "s" };
    
    if (aCard.m_IsFaceUp)
    {
        os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
    }
    else
    {
        os << "XX";
    }
    
    return os;
}

ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer)
{
    os << aGenericPlayer.m_Name << ":\t";
    
    vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.m_Cards.empty())
    {
        for (pCard = aGenericPlayer.m_Cards.begin();
             pCard != aGenericPlayer.m_Cards.end();
             ++pCard)
        {
            os << *(*pCard) << "\t";
        }
        
        
        if (aGenericPlayer.GetTotal() != 0)
        {
            cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    }
    else
    {
        os << "<empty>";
    }
    
    return os;
}

int main () {
cout<<getNumber()<<endl;
cout<<"aaa"<<endll; // используем endll
cout<<"bbb"<<endl;
Player player("Ivan");
House house("Dealer");
cout<<player<<endl;
cout<<house<<endl;
Card* card = new(Card);
player.Add(card);
cout<<player<<endl;
 return 0;
}