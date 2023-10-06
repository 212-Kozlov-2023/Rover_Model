#include "Log.h"

Log::Log(const double & x1, const double & y1, const double & x2, const double & y2, const double & radius){
    x1_cord = x1;
    x2_cord = x2;
    y1_cord = y1;
    y2_cord = y2;
    log_radius = radius;
}

double Log::get_log_hight(const double & x, const double & y){
    
    if(fabs(x2_cord - x1_cord)>=EPS){
    
        double z = get_sqr(log_radius) - get_sqr(y-(x-x1_cord)*(y2_cord-y1_cord)/(x2_cord-x1_cord)-y1_cord);
        if(z>=0 && fabs(y-((x1_cord-x2_cord)*x/(y2_cord-y1_cord))-(y1_cord+y2_cord)/2+(x1_cord-x2_cord)*(x1_cord+x2_cord)/(2*(y2_cord-y1_cord))) <=sqrt(get_sqr(x1_cord-x2_cord)+get_sqr(y1_cord-y2_cord))/2){
            return sqrt(z);
        }
        else{
            return 0;
        }
    }
    if(fabs(y2_cord - y1_cord)>=EPS){
        double z = get_sqr(log_radius) - get_sqr(x-x1_cord);
        if( (z >= 0) && ((y2_cord > y1_cord && y < y2_cord && y > y1_cord) || (y1_cord >= y2_cord && y >= y2_cord && y <= y1_cord))){
            return sqrt(z);
        }
        else return 0;
    }
    else return 0;
}