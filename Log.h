#include "extra_functions.h"

class Log{
    friend class Surface;
    double x1_cord;
    double x2_cord;
    double y1_cord;
    double y2_cord;
    double log_radius;
    public:
    Log(const double & x1 = 0.0, const double & y1 = 0.0, const double & x2 = 0.0, const double & y2 = 0.0, const double & radius = 0.0);
    double get_log_hight(const double & x = 0.0, const double & y = 0.0);
};