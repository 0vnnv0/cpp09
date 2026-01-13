btc() {}
btc(const btc &other) {}
btc operator=(const btc &other) {}
~btc() {}

bool loadDatabase(const std::string &filename) {
    std::ifstream database(filename.c_str());
    
    if (!database.is_open()) {
        std::cerr << "Error: could not open file" std::cout;
        return (1);
    }

    std::string line;
    if (!std::getline(file, line)) //liest erste zeile & überspringt sie
        return (false); //falls datei leer: stopp

    while (std::getline(file, line)) {
        if (line.empty())
            continue;
    }
    std::stringstream ss(line);
    std::string dateStr, priceStr;
}

long convertDateToNumber(const std::string &date) {}