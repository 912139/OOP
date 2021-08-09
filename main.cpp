#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <vector>
#include <sstream> 
#include <cstring>
using namespace std;

class Date
{
private:
    int m_day, m_month, m_year;

public:
    Date(int d=1, int m=1, int y=2021): m_day(d), m_month(m), m_year(y)
    { }
    int getDay() {return m_day;}
    int getMonth() {return m_month;}
    int getYear() {return m_year;}
    void initDate (int day, int month, int year) {
    m_day = day;
    m_month = month;
    m_year = year;
    }
    friend ostream& operator<< (ostream &out, const Date &date);
};

ostream& operator<< (ostream &out, const Date &date)
{
    out << date.m_day << ". " << date.m_month << ". " << date.m_year << "\n";
    return out;
}


template<class T>
class Auto_ptr2
{
	T* m_ptr;
public:
	Auto_ptr2(T* ptr=nullptr)
		:m_ptr(ptr)
	{
	}
	
	~Auto_ptr2()
	{
		delete m_ptr;
	}
 
	// Конструктор копирования, который реализовывает семантику перемещения
	Auto_ptr2(Auto_ptr2& a) // примечание: Ссылка не является константной
	{
		m_ptr = a.m_ptr; // перемещаем наш глупый указатель от источника к нашему локальному объекту
		a.m_ptr = nullptr; // подтверждаем, что источник больше не владеет указателем
	}
	
	// Оператор присваивания, который реализовывает семантику перемещения
	Auto_ptr2& operator=(Auto_ptr2& a) // примечание: Ссылка не является константной
	{
		if (&a == this)
			return *this;
 
		delete m_ptr; // подтверждаем, что удалили любой указатель, который наш локальный объект имел до этого
		m_ptr = a.m_ptr; // затем перемещаем наш глупый указатель из источника к нашему локальному объекту
		a.m_ptr = nullptr; // подтверждаем, что источник больше не владеет указателем
		return *this;
	}
 
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr;  }
    friend void exchangeDate(Auto_ptr2<Date>& a, Auto_ptr2<Date>& b);

};

    Auto_ptr2<Date>& comparison (Auto_ptr2<Date>& a, Auto_ptr2<Date>& b)
    {
    if (a->getYear() > b->getYear())
       return a;
    if (a->getYear() < b->getYear())
       return b;
    if (a->getMonth() > b->getMonth())
       return a;
    if (a->getMonth() < b->getMonth())
       return b;
    if (a->getDay() > b->getDay())
       return a;
    if (a->getDay() < b->getDay())
       return b;       
    return a;  
    }

    	void exchangeDate(Auto_ptr2<Date>& a, Auto_ptr2<Date>& b)
	{
		if (&a == &b)
			return;
        Date *buffer;
        buffer = a.m_ptr;
        a.m_ptr = b.m_ptr;
        b.m_ptr = buffer;
	}
 // -------------------код Blackjack, ниже будет класс Deck 7-го урока-------------------------------------
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
// -------------------класс Deck 7-го урока-------------------------------------
class Deck : public Hand
{
public:
    Deck();
    
    virtual ~Deck();
    
    // создает стандартную колоду из 52 карт
    void Populate();
    
    // тасует карты
    void Shuffle();
    
    // раздает одну карту в руку
    void Deal(Hand& aHand);
    
    // дает дополнительные карты игроку
    void AdditionalCards(GenericPlayer& aGenericPlayer);
};

Deck::Deck()
{
    m_Cards.reserve(52);
    Populate();
}

Deck::~Deck()
{}

void Deck::Populate()
{
    Clear();
    // создает стандартную колоду
    for (int s = Card::CLUBS; s <= Card::SPADES; ++s)
    {
        for (int r = Card::ACE; r <= Card::KING; ++r)
        {
            Add(new Card(static_cast<Card::rank>(r),
                         static_cast<Card::suit>(s)));
        }
    }
}

void Deck::Shuffle()
{
    random_shuffle(m_Cards.begin(), m_Cards.end());
}

void Deck::Deal(Hand& aHand)
{
    if (!m_Cards.empty())
    {
        aHand.Add(m_Cards.back());
        m_Cards.pop_back();
    }
    else
    {
        cout << "Out of cards. Unable to deal.";
    }
}

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer)
{
    cout << endl;
    // продолжает раздавать карты до тех пор, пока у игрока не случается
    // перебор или пока он хочет взять еще одну карту
    while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
    {
        Deal(aGenericPlayer);
        cout << aGenericPlayer << endl;
        
        if (aGenericPlayer.IsBusted())
        {
            aGenericPlayer.Bust();
        }
    }
}

class Game
{
public:
    Game(const vector<string>& names);
    
    ~Game();
    
    // проводит игру в Blackjack
    void Play();
    
private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;
};

// Конструктор этого класса принимает ссылку на вектор строк, представляющих
// имена игроков-людей. Конструктор создает объект класса Player для каждого имени
Game::Game(const vector<string>& names)
{
    // создает вектор игроков из вектора с именами
    vector<string>::const_iterator pName;
    for (pName = names.begin(); pName != names.end(); ++pName)
    {
        m_Players.push_back(Player(*pName));
    }
    
    // запускает генератор случайных чисел
    srand(static_cast<unsigned int>(time(0)));
    m_Deck.Populate();
    m_Deck.Shuffle();
}

Game::~Game()
{}

void Game::Play()
{
    // раздает каждому по две стартовые карты
    vector<Player>::iterator pPlayer;
    for (int i = 0; i < 2; ++i)
    {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            m_Deck.Deal(*pPlayer);
        }
        m_Deck.Deal(m_House);
    }
    
    // прячет первую карту дилера
    m_House.FlipFirstCard();
    
    // открывает руки всех игроков
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        cout << *pPlayer << endl;
    }
    cout << m_House << endl;
    
    // раздает игрокам дополнительные карты
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        m_Deck.AdditionalCards(*pPlayer);
    }
    
    // показывает первую карту дилера
    m_House.FlipFirstCard();
    cout << endl << m_House;
    
    // раздает дилеру дополнительные карты
    m_Deck.AdditionalCards(m_House);
    
    if (m_House.IsBusted())
    {
        // все, кто остался в игре, побеждают
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            if (!(pPlayer->IsBusted()))
            {
                pPlayer->Win();
            }
        }
    }
    else
    {
        // сравнивает суммы очков всех оставшихся игроков с суммой очков дилера
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();
             ++pPlayer)
        {
            if (!(pPlayer->IsBusted()))
            {
                if (pPlayer->GetTotal() > m_House.GetTotal())
                {
                    pPlayer->Win();
                }
                else if (pPlayer->GetTotal() < m_House.GetTotal())
                {
                    pPlayer->Lose();
                }
                else
                {
                    pPlayer->Push();
                }
            }
        }
        
    }
    
    // очищает руки всех игроков
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        pPlayer->Clear();
    }
    m_House.Clear();
}


int main()
{
    cout<<"Practical task number 1"<<endl;
    Auto_ptr2<Date> today(new Date);
    Auto_ptr2<Date> date(new Date);
    today->initDate(9,8,2021);
    cout<<"Today "<<*today;
    cout<<"Today day is "<<today->getDay()<<endl;
    cout<<"Today month is "<<today->getMonth()<<endl;
    cout<<"Today year is "<<today->getYear()<<endl;
    cout<<"date: "<<*date;
    date = today;
    if (today.isNull())
    cout<<"today is nullptr"<<endl;
    if (!date.isNull())
    cout<<"date: "<<*date;
    
    cout<<"Practical task number 2"<<endl;
    Auto_ptr2<Date> date1(new Date);
    Auto_ptr2<Date> date2(new Date);
    Auto_ptr2<Date> result(new Date);
    date1->initDate(5,9,2021);
    date2->initDate(7,9,2021);
    cout<<"date1: "<<*date1;
    cout<<"date2: "<<*date2;
    cout<<"Max date: "<<*comparison(date1, date2); 
    exchangeDate(date1, date2);
    cout<<"date1: "<<*date1;
    cout<<"date2: "<<*date2;

    cout<<"Practical task number 3 (main Blackjack)"<<endl;
    vector<string> names;
    string name;
    char response;
    const int number_of_players = 7; //максимальное количество игроков
do
{
   for (int i = 0; i < number_of_players; ++i)
   {
        cout<<"Enter a player name: ";
        getline(cin, name);  
        if (name.length() != 0)
        names.push_back(name);
        else i = number_of_players;
    } 
    Game game(names);
    game.Play();
    cout<<"Would you like to play again? Y / N";
    cin >> response;
    names.clear();
    cin.ignore(32767, '\n');
 } while (response == 'y' || response == 'Y');
return 0;
}