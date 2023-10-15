#include "Hummock.h"


Hummock::Hummock(const double & x, const double & y, const double & z, const double & sig_x, const double & sig_y, const double & ax_rotat_angle){
        x_cord = x;
        y_cord = y;
        z_cord = z;
        sigma_x = sig_x;
        sigma_y = sig_y;
        rotation_angle = ax_rotat_angle;
}

double Hummock::get_hummock_height(const double & x, const double & y){
    double z = 0;
    if(fabs(x_cord-x)<4*sigma_x || fabs(x_cord-x)<4*sigma_y || fabs(y_cord-y)<4*sigma_x || fabs(y_cord-y)<4*sigma_y){
        z = z_cord*exp((-1)*(get_sqr(cos(rotation_angle)*(x-x_cord) + sin(rotation_angle)*(y-y_cord))/(sigma_x) + get_sqr(-sin(rotation_angle)*(x-x_cord) + cos(rotation_angle)*(y-y_cord))/sigma_y));
        return z;
    }
    else return 0;
}