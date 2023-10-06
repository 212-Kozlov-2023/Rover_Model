#include "Boundary.h"

class Point//212-Козлов-Илья Класс точки: в нем *_cord соответственно x, y, z координаты точки
{
    protected:
    double x_cord;
    double y_cord;
    double z_cord;
    public:
    Point(const double & x = 0, const double & y = 0, const double & z = 0){
        x_cord = x, y_cord = y, z_cord = z;
    };
};


int main(void){
    ofstream file("GNUplot.txt");
    Boundary();
    file.close();
    return 0;
}