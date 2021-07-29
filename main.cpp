#include <iostream>
#include <string>
#include <cassert> // для assert()
#include <vector>
#include <algorithm>
using namespace std;

class ArrayInt
{
private:
    int m_length;
    int *m_data;

public:
    ArrayInt(): m_length(0), m_data(nullptr)
    { }

    ArrayInt(int length):
    m_length(length)
    {
        assert(length >= 0);

        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    ~ArrayInt()
    {
        delete[] m_data;
    }

void erase()
    {
        delete[] m_data;

        // Здесь нам нужно указать m_data значение nullptr, чтобы на выходе не было висячего указателя
        m_data = nullptr;
        m_length = 0;
    }
    int getLength() { return m_length; }

    int* getData() { return m_data; }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }
    
void resize(int newLength)
    {
        // Если массив уже нужной длины — return
        if (newLength == m_length)
            return;

        // Если нужно сделать массив пустым — делаем это и затем return
        if (newLength <= 0)
        {
            erase();
            return;
        }

        // Теперь знаем, что newLength >0
        // Выделяем новый массив
        int *data = new int[newLength];

        // Затем нужно разобраться с количеством копируемых элементов в новый массив
        // Нужно скопировать столько элементов, сколько их есть в меньшем из массивов
        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            // Поочередно копируем элементы
            for (int index=0; index < elementsToCopy ; ++index)
                data[index] = m_data[index];
        }

        // Удаляем старый массив, так как он нам уже не нужен
        delete[] m_data;

        // И используем вместо старого массива новый! Обратите внимание, m_data указывает
        // на тот же адрес, на который указывает наш новый динамически выделенный массив. Поскольку
        // данные были динамически выделенные — они не будут уничтожены, когда выйдут из области видимости
        m_data = data;
        m_length = newLength;
    }

void insertBefore(int value, int index)
    {
        // Проверка корректности передаваемого индекса
        assert(index >= 0 && index <= m_length);

        // Создаем новый массив на один элемент больше старого массива
        int *data = new int[m_length+1];

        // Копируем все элементы до index-а
        for (int before=0; before < index; ++before)
            data[before] = m_data[before];

        // Вставляем новый элемент в новый массив
        data [index] = value;

        // Копируем все значения после вставляемого элемента
        for (int after=index; after < m_length; ++after)
            data[after+1] = m_data[after];

        // Удаляем старый массив и используем вместо него новый 
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

void push_back(int value) { insertBefore(value, m_length); }

void pop_back() {
    assert(m_length > 0);
    m_data[m_length] = 0;
    m_length--;
}

void pop_front() {
    assert(m_length > 0);
    for (int current=0; current < m_length; ++current)
            m_data[current] = m_data[current+1];
            m_data[m_length] = 0;
            m_length--;

}

void sort () {
 quicksort(this->getData(), this->getLength());
}

void quicksort(int *m_data, int m_length) {
    //Указатели в начало и в конец массива
    int i = 0;
    int j = m_length - 1;

    //Центральный элемент массива
    int mid = m_data[m_length / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while(m_data[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while(m_data[j] > mid) {
            j--;
        }
        //Меняем элементы местами
        if (i <= j) {
            int tmp = m_data[i];
            m_data[i] = m_data[j];
            m_data[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);

    //Рекурсивные вызовы, если осталось, что сортировать
    if(j > 0) {
        //"Левый кусок"
        quicksort(m_data, j + 1);
    }
    if (i < m_length) {
        //"Правый кусок"
        quicksort(&m_data[i], m_length - i);
    }
}

void printArrayInt () {
    for (int i=0; i < m_length; ++i)
            cout<<m_data[i]<<' ';
            cout<<endl;
}
};

class Card {
enum rank {ace = 1, king = 10, queen = 10, jack = 10, ten = 10, nine = 9, eight = 8, seven = 7, six = 6, five = 5, four = 4, three = 3, two = 2};
enum suit {hearts, diamonds, clubs, spades};
rank m_Rank;
suit m_Suit;
bool m_IsFaceUp;
public:
Card (rank Rank, suit Suit, bool IsFaceUp) : m_Rank(Rank), m_Suit(Suit), m_IsFaceUp(IsFaceUp)  {}
virtual ~Card () {}

int GetValue() {
    return m_Rank;
}

void Flip() {
m_IsFaceUp = !m_IsFaceUp;
}
};

class Hand {
vector<Card*> m_Cards;

void Add(Card* pCard) {
    m_Cards.push_back(pCard);
}
void Clear() {
    m_Cards.clear();
}
int GetTotal() {
    int total;
    int ace;
    vector<Card*>::iterator the_iterator;
    the_iterator = m_Cards.begin();
    while (the_iterator != m_Cards.end()) {
       if ((*the_iterator)->GetValue() == 1) {
           cout<<"You have an ace! What is the value of the ace: 1 or 11?";
           do
           cin>>ace;
           while (ace!=1 || ace!=11);
           total +=ace;
       } else
    total = (*the_iterator)->GetValue();
    ++the_iterator;
    }
    return total;
}
};



int main () {
    ArrayInt A(3);
    A.push_back(5);
    A.push_back(4);
    A.push_back(3);
    A.insertBefore(1,1);
    A.printArrayInt();
    A.sort();
    A.printArrayInt();

    vector<int>myVector {5,5,7,5,4,7,7,7};
    int sum = 0;
    vector<int>::iterator the_iterator;
    sort (myVector.begin(), myVector.begin()+8);
  for (std::vector<int>::iterator it=myVector.begin(); it!=myVector.end(); ++it) {
  if (*it != *(it+1))
    sum++;
  }
  cout<<"The number of different elements: "<<sum<<endl;
    return 0;
}