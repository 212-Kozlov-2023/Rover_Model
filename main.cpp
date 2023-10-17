#include "Boundary.h"


int main(void){
    string config_name;
    cout << "Print the name of the configuration file!\n";
    cin >> config_name;
    Boundary a(config_name);
    return 0;
}