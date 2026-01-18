#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

int main (int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Error. Couldn't open file." << std::endl;
        return (1);
    }
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return (1);
    }
	btc	Exchange;
	Exchange.loadDatabase("data.csv");
    return (0);
}