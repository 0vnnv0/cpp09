#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>

btc::btc() {
	loadDatabase("data.csv");
}

btc::btc(const btc &other) {
	_rates = other._rates;
}

btc &btc::operator=(const btc &other) {
	if (this != &other) {
		_rates = other._rates;
	}
	return *this;
}

btc::~btc() {}

bool btc::loadDatabase(const std::string &filename) {
    std::ifstream database(filename.c_str());
    
    if (!database.is_open()) {
        std::cerr << "Error: could not open data file" << std::endl;
        return (1);
    }

    std::string line;
    if (!std::getline(database, line)) //liest erste zeile & überspringt sie
        return (false); //falls datei leer: stopp

    while (std::getline(database, line)) {
        if (line.empty())
            continue;

		std::stringstream ss(line);
		std::string dateStr, priceStr;

		if (!std::getline(ss, dateStr, ',') || !std::getline(ss, priceStr)) {
		//	std::cerr << "Error: bad database line => " << std::endl;
			continue;
			}
	
		long dateNum = convertDateToNumber(dateStr);
		double price = atof(priceStr.c_str());
		_rates[dateNum] = price;
	}
	return (true);
}

long btc::convertDateToNumber(const std::string &date) {
	long result = 0;

    for (std::string::const_iterator it = date.begin(); it != date.end(); ++it)
    {
        if (*it >= '0' && *it <= '9')
        {
            result = result * 10 + (*it - '0');
        }
    }
    return result;
}

void btc::processInputFile(std::ifstream &input) {
    std::string line;


    while (std::getline(input, line)) {
        if (line.empty())
            continue;

		size_t pipePos = line.find('|');
        if (pipePos == std::string::npos) {
        std::cerr << "Error: bad input => " << line << std::endl;
        continue;
        }

        std::string dateStr = line.substr(0, pipePos);
        std::string valueStr = line.substr(pipePos + 1);
		
        while (!dateStr.empty() && dateStr[dateStr.size() - 1] == ' ') {
            dateStr.erase(dateStr.size() - 1);
		while (!valueStr.empty() && valueStr[0] == ' ')
            valueStr.erase(0, 1);
        if (!isValidDate(dateStr)) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
		double value;
		if (!isValidValue(valueStr, value))
			continue;

		long dateNum = convertDateToNumber(dateStr);
		double rate = detExchangeRate(dateNum);

		std::cout << dateStr << " => " << value << " = " << value * rate << std::endl;
    }
}

bool btc::isValidDate(std::string dateStr) {
    if (dateStr.size() != 10)
        return (false);
    if (dateStr[4] != '-' || dateStr[7] != '-')
        return (false);

    for (unsigned int i = 0; i < dateStr.length(); i++) {
        if (i == 4 || i == 7) {
			if (dateStr[i] != '-')
				return(false);
	    }
		else {
			if (!std::isdigit(dateStr[i]))
				return (false);
		}
    }
	int month = std::atoi(dateStr.substr(5, 2).c_str());
	if (month < 1 || month > 12)
		return (false);

	int day = std::atoi(dateStr.substr(8, 2).c_str());
		if (day < 1 || day > 31)
			return (false),

	return (true);
}

bool btc::isValidValue(const std::string &valueStr, double &value) {
	int flag = 0;

	for (unsigned int i = 0; i < valueStr.length(); i++) {
		if (valueStr[i] == '.') {
			flag++;
			if (flag > 1)
				return (false);
		}
		else if (!std::isdigit(valueStr[i])) {
			if (valueStr[i] == '-' && i == 0)
				continue;
			return (false);
		}
	}
	double value = std::atof(valueStr.c_str());
	if (value < 0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (value > 1000) {
		std::cerr << "Error: too large a number." << std::endl;
		return (false);
	}
	return (true);
}

double btc:: getExchangeRate(long dateNum) {
    std::map<long, double>::const_iterator it = _rates.lower_bound(dateNum);

	if (it != _rates.end() && it->first == dateNum)
		return it->second;

	if (it == _rates.begin())
		return it->second;

	--it;
	return it->second;
}