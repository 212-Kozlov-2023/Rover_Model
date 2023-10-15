#include "extra_functions.h"

class Hummock //212-Козлов-Илья Класс бугорка(ямки) - является наследником точки, тк основывается на точке и sigma_x и sigma_y, которые представляют собой дисперсии по разным осям
//formula - строка, в которой хранится то, как задается уравнение данного бугорка
{
    friend class Surface;
    double x_cord;
    double y_cord;
    double z_cord;
    double sigma_y, sigma_x;
    double rotation_angle;
    public:
    Hummock(const double & x = 0, const double & y = 0, const double & z = 0, const double & sig_x = 1, const double & sig_y = 1, const double & ax_rotat_angle = 0);
    double get_hummock_height(const double & x, const double & y);
};
