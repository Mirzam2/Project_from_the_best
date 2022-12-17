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
        nominal = 1;
    }
}

int Card::get_nominal() {
    return nominal;
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

Hand& Hand::operator=(const Hand& other) {
    if (this == &other)
        return *this;
    hand.clear();
    this->hand = other.hand;
}

Hand& Hand::operator=(Hand&& other) {
    if (this == &other)
        return *this;
    hand.clear();
    this->hand = other.hand;
    other.hand.clear();
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
    for (int i = 0; i < numofplayers; i++) {
        Hand hand_tmp(deck_of_cards_6);
        hands[i] = hand_tmp;
    }
    Hand Croupier_hand;
    Croupier_hand.getcard(deck_of_cards_6);
}

void BlackJack::game_process() {

}