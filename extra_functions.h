#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <chrono>
#define _USE_MATH_DEFINES
#define EPS 1e-14
#define MAX_HUMMOCK_HIGHT 13
#define MAX_STONE_HIGHT 10
#define MAX_LOGS_HIGHT 3
#define NET_STEP 0.5
using namespace std;

double get_random(double min, double max);
double get_sqr(const double & num);
bool is_extra_symbol_after_semicolon(string str);
bool is_substr(string str, string substr);
void printer_with_time(string message, ofstream & file);

extern size_t _max_rand_hummocks;
extern size_t _max_rand_stones;
extern size_t _max_rand_logs;