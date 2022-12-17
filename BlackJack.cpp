#include "casino.h"
#include <sstream>
#include <string>
#include <memory>

/* Diamonds ����
   Hearts �����
   Clubs �����
   Spades ����
   Ace ���
   Jack �����
   Queen ����
   King ������*/

bool anser() {
    int a = 0;
    std::cin >> a;
    if (a == 1) {
        return true;
    }
    return false;
}
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

Hand& Hand::operator=(const Hand& other) {
    if (this == &other)
        return *this;
    this->hand = other.hand;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Hand& obj) {
    for (auto item : obj.hand)
    {
        out << item;
    }
    return out;
}

BlackJack::BlackJack() : Game() {}

BlackJack::BlackJack(std::unique_ptr<Player[]> Players, Host Croupier, int numofplayers) : Game(std::move(Players), Croupier, numofplayers){
   deck_of_cards_6 = make_deck(6);
    bets = new int* [numofplayers];
    for (int i = 0; i < numofplayers; ++i) {
        bets[i] = new int[2];
    }

    for (int i = 0; i < numofplayers; ++i) {
        bets[i][1] = 0;
    }

    hands = new Hand* [numofplayers];
    for (int i = 0; i < numofplayers; ++i) {
        hands[i] = new Hand[2];
    }
}

bool BlackJack::Isace() {
    if (Croupier_hand.hand.front().get_nominal() == 11) {
        return true;
    }
    return false;
}

void BlackJack::split(int i) {
    bets[i][1] = bets[i][0];
    Players[i].setcurrbank();
    hands[i][1].drop_card();
    hands[i][1].drop_card();
    hands[i][1].getcard(hands[i][0].hand);
}

void BlackJack::double_down(int i) {
    Players[i].setcurrbank_by_value(bets[i][0]);
    bets[i][0] *= 2;
}

void BlackJack::surrender(int i) {
    hands[i][0].drop_card();
    hands[i][0].drop_card();
    hands[i][1].drop_card();
    hands[i][1].drop_card();
    Players[i].SetoutBank_by_value(bets[i][0] / 2);
    bets[i][0] = 0;
}

void BlackJack::insurance(int i) {
    if (Isace()) {
        bets[i][1] = bets[i][0] / 2;
        Players[i].setcurrbank_by_value(bets[i][1]);
    }
}

void BlackJack::isBlackJAck(int i) {
    if (hands[i][0].handpoint() == 21) {
        if (Isace()) {
            int a = 0;
            std::cout << "Do you want to get even money? 1)Yes 2)No" << '\n';
            std::cin >> a;
            if (a == 1) {
                even_money(i);
            }
        }
        Players[i].SetoutBank_by_value(bets[i][0] * 5 / 2);
    }
}

void BlackJack::even_money(int i)
{
    Players[i].SetoutBank_by_value(bets[i][0] * 2);
    bets[i][0] = 0;
}

void BlackJack::Croupier_take() {
    while (Croupier_hand.handpoint() < 17) {
        Croupier_hand.getcard(deck_of_cards_6);
    }
}

void BlackJack::game_process() {
    bool gamecontinue = true;


    for (int i = 0; i < numofplayers; i++) {
        std::cout << Players[i].GetName() << ' ';
        Players[i].SetintBank();
    }

    do
    {
    for (int i = 0; i < numofplayers; ++i) {
        std::cout << Players[i].GetName() << ' ';
        Players[i].SetBet();
        Players[i].setcurrbank();
        bets[i][0] = Players[i].getbet();
    }

    for (int i = 0; i < numofplayers; i++) {
        hands[i][0].make_hand(deck_of_cards_6);
        hands[i][1] = hands[i][0];
        std::cout << Players[i].GetName() << '\n' << hands[i][0] << '\n' << '\n';
    }

    Croupier_hand.make_hand(deck_of_cards_6);

    Croupier_hand.print_card();

    for (int i = 0; i < numofplayers; ++i) {
        bool ans = true;
        std::cout << '\n' << Players[i].GetName() << " Your turn" << '\n';
        std::cout << "Your cards:" << '\n';
        std::cout << hands[i][0] << '\n';
        while (ans && hands[i][0].handpoint() < 21) {
            std::cout << Players[i].GetName() << " Would you like to take card? 1)Yes 2)No" << '\n';
            ans = anser();
            if (ans) {
                hands[i][0].getcard(deck_of_cards_6);
            }
            std::cout << hands[i][0] << '\n' << hands[i][0].handpoint() << '\n';
        }
        std::cout << '\n';
    }

    Croupier_take();
    std::cout << Croupier.GetName() << '\n' << Croupier_hand << '\n';

    for (int i = 0; i < numofplayers; ++i) {
        if (hands[i][0].handpoint() > 21) {
            std::cout << Players[i].GetName() << " You lose" << '\n';
            bets[i][0] = 0;
        }
        else if (Croupier_hand.handpoint() > 21) {
            std::cout << Players[i].GetName() << " You win" << '\n';
            Players[i].SetoutBank_by_value(bets[i][0] * 2);
        }
        else if (Croupier_hand.handpoint() > hands[i][0].handpoint()) {
            std::cout << Players[i].GetName() << " You lose" << '\n';
            bets[i][0] = 0;
        }
        else if (hands[i][0].handpoint() > Croupier_hand.handpoint()) {
            std::cout << Players[i].GetName() << "You win" << '\n';
            Players[i].SetoutBank_by_value(bets[i][0] * 2);
        }
    }
    std::cout << '\n';
    std::cout << "Do you want to play again? " << '\n';
    std::cout << "0) No " << '\n';
    std::cout << "1) Yes " << '\n';
    std::cin >> gamecontinue;
    } while (gamecontinue && isbankrupt() == false && deck_of_cards_6.size() > numofplayers);
    std::cout << "not now" << '\n';
}