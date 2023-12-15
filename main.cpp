#include "Boundary.h"


int main(void){
    double x, y;
    int checker;
    int temp = 0;
    string config_name;
    cout << "This program is an off-road rover model, the rover can be controlled manually via a command file or independently to the destination point. Print the name of the configuration file!\n";
    cin >> config_name;
    cout << "\nEnter the destination point\n";
    cin >> x >> y;
    Boundary a(config_name, x, y, checker);
    while (checker == 0)
    {
        temp++;
        Boundary a(config_name, x, y, checker);
        if(temp >= 5){
            cout << "\nThe point is unattainable!";
            return 0;}
    }
    cout << "The rover has successfully arrived!";
    return 0;
}