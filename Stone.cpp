#include "Stone.h"

Stone::Stone(const double & x, const double & y, const double & radius){
    x_cord = x;
    y_cord = y;
    radius_stone = radius;
}

double Stone::get_stone_hight(const double & x, const double & y)
{
    double z = get_sqr(radius_stone) - get_sqr(x_cord - x) - get_sqr(y_cord - y);
    if(z >= 0){
        return sqrt(z);
    }
    else{
        return 0;
    }
}