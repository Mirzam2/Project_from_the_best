#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
#include <typeinfo>
#include <cstring>
#include <cstdlib>
#include <memory>
using namespace std;

enum stavka
{
    number = 0,
    color,
    range,
    even
}; // тип ставки в рулетке

struct rouletevalue
{                 // значение рулетки
    int value;    // выпавшее число
    bool iszero;  // ноль или нет
    bool iseven;  // четное/нечетное
    bool isblack; // черное/красное
    stavka playerbet;
};

class Tmen
{ // родительский класс для ведущего и игрока
protected:
    string name; // имя

public:
    virtual void SetName(){}; // метод установки имени

    string GetName()
    { // возвращение имени
        return name;
    }
};

class Host : public Tmen
{ // ведущий
private:
    int Bets = 0;                                          // сумма собранных ставок
    string croupiernames[3] = {"Petya", "Vasya", "Sasha"}; // массив имен ведущего

public:
    void SetName() override;

    void BidsCollect(int a); // сбор ставок

    int Giveprize(); // выдача приза победителю
};

class Player : public Tmen
{ // игрок
private:
    int bank;             // банк игрока
    int bet;              // ставка игрока
    int prizesumm;        // выйгрыш
    int summaryprize = 0; // суммарный выйгрыш
    int summarybet = 0;   // суммарная ставка
    bool Iswinner;        // победитель/проигравший

public:
    void SetintBank(); // установка банка перед началом игры

    void SetBet(); // установка ставки

    void setcurrbank(); // установка банка после ставки

    void SetoutBank(); // установка банка по окончании игры

    int getbet(); // возвращает ставку

    int getprize(); // возвращает приз

    int getbank(); // возвращает банк
    void SetName() override;

    void setwin(bool a); // устанавливает победу

    bool getwin(); // возвращает победитель или проигравший

    void setsummarybet(int a); // устанавливает суммарную ставку

    void SetPrize(int a); // устанавливает приз

    int getsummarybet(); // возвращает суммарную ставку

    int getsummaryprize(); // возвращает суммарный приз

    int getcurrprize(); // возвращает приз за 1 игру

    void setcurrbank_by_value(int val);

    void SetoutBank_by_value(int val);
};

class Game
{
protected:
std::unique_ptr<Player[]> Players;
    Host Croupier;
    int numofplayers=5;

public:
    // игровой процесс
    virtual bool isequal();    // проверка на одинаковость ставок
    virtual bool isbankrupt(); // проверка обанкротился ли кто то из игроков
    Game(std::unique_ptr<Player[]> Players, Host Croupier, int numofplayers);
    Game();
};

class Dices : public Game
{ // игра в кости
private:
    std::unique_ptr<int[]> playerpoints; // массив с суммами очков каждого игрока
    int maxpoints;

public:
    Dices(); // конструктор по умолчанию
    Dices(std::unique_ptr<Player[]> Players, Host Croupier, int numofplayers);
    Dices(std::unique_ptr<int[]> playerpointss)
    { // кончтруктор
        this->playerpoints = std::move(playerpointss);
    };
    //bool isbankrupt(); //
    int RollofDice();  // бросок костей

    void initplayerpoints(int a); // создание массива сумм очков

    void setpoints(int a); // присваивание очков

    void coutpoints(int index); // вывод очков на экран

    void setmaxpoints(int a);

    int getmaxpoints();

    void game_process();

    int getpoints(int a); // возвращает сумму очков по индексу

    ~Dices()
    { // деструктор
    }
};

class Roulete : public Game
{ // игра в рулетку
private:
    rouletevalue computerval;   // значение выпавшее с рулетки
    rouletevalue *playervalues; // массив со значениями на которые поставили игроки

public:
    Roulete();
    Roulete(std::unique_ptr<Player[]> Players, Host Croupier, int numofplayers);

    Roulete(rouletevalue computerval, rouletevalue *playervalues)
    {
        this->computerval = computerval;
        this->playervalues = playervalues;
    }
    void game_process(int &Casinobank); //процесс игры
    void initplayervalues(); // создание массива ставок

    void setplayervalnum(int index, int a); // присваивание числового значения по индексу в массив

    void setplayervalisblack(int index, bool color); // присваивание цвета по индексу

    void setplayervaliseven(int index, bool even); // присваивание чет/нечте по индексу

    void setplayervaliszero(int index, bool zero);

    void setplayerbet(int index, stavka stavka); // присваивание в массив на какой тип ставит игрок

    int getplayervalnum(int index); // возвращение числовго значения по индексу

    bool getplayervalisblack(int index); // возвращение цвета по индексу

    bool getplayervaliseven(int index); // возвращение чет/нечет по индексу

    bool getplayervaliszero(int index); // возвращение ноль/не ноль по индексу

    stavka getplayerstavka(int index); // возвращение типа ставки по индексу

    void RollofRoulete(); // олучение значений рулетки

    int getcompnum(); // возвращение числового значения рулетки

    bool getcompblack(); // цвет значения рулетки

    bool getcompeven(); // четное нечетное

    bool getcompzero(); // ноль/не ноль
    void lose(int index, int& Casinobank);//выводит в случае проигрыша
    void win(int index, int& Casinobank, int multy);
    ~Roulete()
    {
        delete[] playervalues;
    }
};

class Casino
{
private:
    int Casinobank = 10000000; // банк казино
    int numofplayers;          // количество игроков
    Host Croupier;             // крупье
    std::unique_ptr<Player[]> Players;           // массив игроков

public:
    void Setnumofplayers(); // устанавливает количество игроков

    int Getnumofplayers(); // возвращает количество игроков

    void Initplayers(); // создает массив игроков

    void game(); // игровой процесс
    ~Casino()
    {
    }
};

bool anser();

struct Card
{
public:
    friend std::ostream &operator<<(std::ostream &out, const Card &obj); // оператор вывода карты
    Card();                                                              // конструктор по умолчанию
    Card(std::string suit, std::string dignity);                         // конструктор
    int get_nominal();
    std::string get_suit();
    std::string get_dignity();
    int nominal;
    Card& operator=(const Card& other);

private:
    std::string suit;
    std::string dignity;
};

std::ostream& operator<<(std::ostream& out, const Card& obj);

std::vector<Card> make_deck(int number_of_decks);

struct Hand{
public:
    Hand(); //конструктор по умолчанию

    Hand(std::vector<Card>& deck_of_cards); //конструктор от колоды

    std::vector<Card> hand; //массив карт на руках

    void getcard(std::vector<Card>& deck_of_cards); //добавление карты в руку

    Hand& operator=(const Hand& other);

    int handpoint();

    void make_hand(std::vector<Card>& deck_of_cards);
        
    void drop_card();
    
    void print_card();

    friend std::ostream& operator<<(std::ostream& out, const Card& obj);
};

std::ostream& operator<<(std::ostream& out, const Hand& obj);

class BlackJack : public Game{
public:
    BlackJack();
    BlackJack(std::unique_ptr<Player[]> Players, Host Croupier, int numofplayers);
    void game_process();
    bool Isace();
    void split(int i);
    void double_down(int i);
    void surrender(int i);
    void insurance(int i);
    void isBlackJAck(int i);
    void even_money(int i);
    void Croupier_take();
private:
    Hand** hands;
    int** bets;
    std::vector<Card> deck_of_cards_6 = make_deck(6);
    Hand Croupier_hand;
};