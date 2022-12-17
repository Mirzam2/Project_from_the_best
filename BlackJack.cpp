#include "casino.h"
#include <sstream>
#include <string>

/* Diamonds Бубы
   Hearts Черви
   Clubs Трефы
   Spades Пики
   Ace Туз
   Jack Валет
   Queen Дама
   King Король*/

Card::Card() : suit(""), dignity(""), nominal(0) {}
Card::Card(std::string suit, std::string dignity) : suit(suit), dignity(dignity) {
    int tmp_dignity = atoi(dignity.c_str());
    for (int i = 2; i <= 10; i++) {
        if (i == tmp_dignity) {
            nominal = i;
            break;
        }
    }
    if (dignity == "Jack" || dignity == "Queen" || dignity == "King") {
        nominal = 10;
    }
    if (dignity == "Ace") {
        nominal = 11;
    }
}

int Card::get_nominal() {
    return nominal;
}

std::string Card::get_suit() {
    return suit;
}

std::string Card::get_dignity() {
    return dignity;
}

Card& Card::operator=(const Card& other) {
    if (this == &other)
        return *this;
    this->dignity = other.dignity;
    this->suit = other.suit;
    this->nominal = other.nominal;
    return *this;
}
std::ostream& operator<<(std::ostream& out, const Card& obj) {
    out << obj.suit << " " << obj.dignity << '\n';
    return out;
}


std::string toString(int val) {
    std::string s = std::to_string(val);
    return s;
}

std::vector<Card> make_deck(int number_of_decks) {
    std::vector<Card> deck_of_cards(52 * number_of_decks);
    std::string dignities[13];
    for (int i = 2; i <= 10; i++) {
        dignities[i - 2] = toString(i);
    }
    dignities[12] = "Ace";
    dignities[11] = "King";
    dignities[10] = "Queen";
    dignities[9] = "Jack";
    int it = 0;
    std::string suits[4] = { "Diamond", "Heart", "Club", "Spade" };
    for (int k = 0; k < number_of_decks; k++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                deck_of_cards[it] = Card(suits[i], dignities[j]);
                it++;
            }
        }
    }
    srand(time(0));
    for (int i = 0; i < (52 * number_of_decks); ++i) {
        std::swap(deck_of_cards[i], deck_of_cards[std::rand() % (52 * number_of_decks)]);
    }
    return deck_of_cards;
}

Hand::Hand() = default;

Hand::Hand(std::vector<Card>& deck_of_cards) {
    getcard(deck_of_cards);
    getcard(deck_of_cards);
}

void Hand::getcard(std::vector<Card>& deck_of_cards) {
    hand.push_back(deck_of_cards[deck_of_cards.size() - 1]);
    deck_of_cards.pop_back();
}

void Hand::make_hand(std::vector<Card>& deck_of_cards) {
    getcard(deck_of_cards);
    getcard(deck_of_cards);
}

int Hand::handpoint() {
    int sum = 0;
    int num_of_ace = 0;
    for (auto it : hand) {
        if (it.get_dignity() == "Ace") {
            num_of_ace++;
        }
        sum += it.nominal;
    }
    if (sum > 21) {
        while (num_of_ace > 0 && sum > 21) {
            num_of_ace--;
            sum -= 10;
        }
    }
    return sum;
}

void Hand::drop_card() {
    hand.pop_back();
}

void Hand::print_card() {
    std::cout << hand.front();
    std::cout << "XXXXXXXXXX" << '\n';
}
std::ostream& operator<<(std::ostream& out, const Hand& obj) {
    for (auto item : obj.hand)
    {
        out << item;
    }
    return out;
}

BlackJack::BlackJack() : Game() {}

BlackJack::BlackJack(Player* Players, Host Croupier, int numofplayers) : Game(Players, Croupier, numofplayers){
    deck_of_cards_6 = make_deck(6);

    bets = new int* [numofplayers];
    for (int i = 0; i < numofplayers; ++i) {
        bets[i] = new int[2];
    }

    Hand* hands = new Hand[numofplayers];

    for (int i = 0; i < numofplayers; i++)
    
    {
        cout << Players[i].GetName() << ' ';
        Players[i].SetintBank();
    }

    for (int i = 0; i < numofplayers; ++i) {
        cout << Players[i].GetName() << ' ';
        Players[i].SetBet();
        Players[i].setcurrbank();
        bets[i][0] = Players[i].getbet();
    }

    for (int i = 0; i < numofplayers; i++) {
        hands[i].make_hand(deck_of_cards_6);
        std::cout << Players[i].GetName() << '\n' << hands[i] << '\n' << '\n';
    }

    Hand Croupier_hand(deck_of_cards_6);

    Croupier_hand.print_card();
}

void BlackJack::game_process() {
    std::cout << "not now" << '\n';
}