#include "extra_functions.h"

double get_random(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

bool is_extra_symbol_after_semicolon(string str){
    size_t pos = str.find(";");
    if (pos != std::string::npos) { // символ ";" найден
        // извлечение подстроки после ";"
        string substr = str.substr(pos + 1);

        // проверка наличия символов после ";"
        if (substr.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
            return true;
        }
        else return false;
    }
    else return false;
}



bool is_substr(string str, string substr){
    return (str.find(substr) != string::npos);
}

void printer_with_time(string message, ofstream & file)
{
    auto now = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(now);
    file << message << ctime(&end_time);
}

double get_sqr(const double & num){
    return num*num;
}