#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>

class btc {
    public: 
        btc();
        btc(const btc &other);
        btc operator=(const btc &other);
        ~btc();

        bool loadDatabase(const std::string &filename);

        std::map<long, double> data;

    private:
        long convertDateToNumber(const std::string &date);
};

#endif