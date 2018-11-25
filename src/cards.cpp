#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

#include "cards.hpp"

using namespace Cards;

static auto rng = std::default_random_engine {};

std::vector<Card> Cards::get_full_shuffled_deck() {
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::vector<Card> deck;
    for (const Color c : AllColors) {
        for (const Rank r : AllRanks) {
            deck.emplace_back(c, r);
        }
    }
    std::shuffle(deck.begin(), deck.end(), rng);
    return deck;
}

int Cards::get_card_points(std::vector<Card> const& cards) {
    int sum = 0;
    for (auto card: cards) {
        sum += rank_points.find(card.rank)->second;
    }
    return sum;
}

int Cards::get_suit_base_value(Card const& card) {
    return color_base_values.find(card.color)->second;
}

int Cards::get_suit_base_value(Color const& color) {
    return color_base_values.find(color)->second;
}

std::ostream& Cards::operator<< (std::ostream& os, Card const& card) {
    os << color_symbols.find(card.color)->second << rank_symbols.find(card.rank)->second;
    return os;
}

std::ostream& Cards::operator<< (std::ostream& os, std::vector<Card> const& cards) {
    int i = 0;
    for (auto card : cards) {
        os << std::to_string(i+1) << ". " << card;
        if (i++ < cards.size()-1) {
            os << ", ";
        }
    }
    return os;
}