#include "extra_functions.h"
class Stone
{
    friend class Surface;
    double x_cord;
    double y_cord;
    double radius_stone;
    public:
    Stone(const double & x = 0.0, const double & y = 0, const double & radius = 0);
    double get_stone_height(const double & x = 0.0, const double & y = 0.0);
};