#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>

class btc {
	public: 
		btc();
		btc(const btc &other);
		btc &operator=(const btc &other);
		~btc();

		bool loadDatabase(const std::string &filename);
		void processInputFile(std::ifstream &input);

	private:
		std::map<long, double> _rates;

		long convertDateToNumber(const std::string &date);
		bool isValidDate(std::string dateStr);
		bool isValidValue(const std::string valueStr, double &value);
};

#endif