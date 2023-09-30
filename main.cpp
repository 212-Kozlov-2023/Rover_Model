#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#define _USE_MATH_DEFINES
#define EPS 1e-14
#define MAX_HUMMOCK_HIGHT 13
#define MAX_HUMMOCKES_NUMBER 10
#define MAX_STONE_HIGHT 3
#define MAX_STONES_NUMBER 0
#define MAX_LOGS_NUMBER 0
#define MAX_LOGS_HIGHT 3
#define NET_STEP 0.1

using namespace std;

double get_random(double min, double max);
double get_sqr(const double & num){
    return num*num;
}

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

class Hummock : public Point //212-Козлов-Илья Класс бугорка(ямки) - является наследником точки, тк основывается на точке и sigma_x и sigma_y, которые представляют собой дисперсии по разным осям
//formula - строка, в которой хранится то, как задается уравнение данного бугорка
{
    friend class Surface;
    double sigma_y, sigma_x;
    double rotation_angle;
    public:
    Hummock(const double & x = 0, const double & y = 0, const double & z = 0, const double & sig_x = 1, const double & sig_y = 1, const double & ax_rotat_angle = 0);
    double get_hummock_hight(const double & x, const double & y);
};

class Stone : public Point
{
    friend class Surface;
    double radius_stone;
    public:
    Stone(const double & x = 0.0, const double & y = 0, const double & radius = 0);
    double get_stone_hight(const double & x = 0.0, const double & y = 0.0);
};

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


class Surface{
    friend class Log;
    friend class Stone;
    friend class Hummock;
    double length;
    double width;
    double unevenness_degree;
    vector<Hummock> hummocks;
    vector<Stone> stones;
    vector<Log> logs;
    public:
    Surface(const double & surf_len = 10, const double & surf_wid = 10, const double & surf_uneven = 0.1);
    double get_surface_hight(const double & x, const double & y);
    void Print_in_file(ofstream & file);
    bool add_hummock(const double & x = 0.0, const double & y = 0.0, const double & z = 0.0, const double & sig_x = 1.0, const double & sig_y = 1.0, const double & ax_rotat_angle = 0);
    bool add_stone(const double & x = 0.0, const double & y = 0.0, const double & radius = 0);
    bool add_log(const double & x1 = 0.0, const double & y1 = 0.0, const double & x2 = 0.0, const double & y2 = 0.0, const double & radius = 0.0);
};




int main(void){
    Surface A(50, 50, 15);
    ofstream file("GNUplot.txt");
    A.add_log(10, 5, 10, 25, 5);
    A.Print_in_file(file);
    file.close();
    return 0;
}




Surface::Surface(const double & surf_len, const double & surf_wid, const double & surf_uneven){
    length = surf_len;
    width = surf_wid;
    unevenness_degree = surf_uneven;
    double random_x, random_y, random_z, random_sig_y, random_sig_x, random_radius, random_rotation, random_x2, random_y2;
    srand(time(NULL));
    for (size_t i = 0; i < MAX_HUMMOCKES_NUMBER; i++)
    {
        random_x = get_random(length/10, length*9/10);
        random_y = get_random(width/10, width*9/10);
        random_z = get_random(-MAX_HUMMOCK_HIGHT/2, MAX_HUMMOCK_HIGHT);
        random_sig_x = get_random(surf_uneven/5, surf_uneven);
        random_sig_y = get_random(surf_uneven/5, surf_uneven);
        random_rotation = get_random(0, 2*3.1415);

        hummocks.push_back(Hummock(random_x, random_y, random_z, random_sig_x, random_sig_y, random_rotation));
    }
    for (size_t i = 0; i < MAX_STONES_NUMBER; i++)
    {
        random_x = get_random(length/10, length*9/10);
        random_y = get_random(width/10, width*9/10);
        random_z = get_random(-MAX_HUMMOCK_HIGHT/2, MAX_HUMMOCK_HIGHT);
        random_radius = get_random(0, MAX_STONE_HIGHT);

        stones.push_back(Stone(random_x, random_y, random_radius));
    }
    for (size_t i = 0; i < MAX_LOGS_NUMBER; i++)
    {
        random_x = get_random(length/10, length*9/10);
        random_x2 = get_random(length/10, length*9/10);
        random_y = get_random(width/10, width*9/10);
        random_y2 = get_random(width/10, width*9/10);
        random_radius = get_random(0, MAX_LOGS_HIGHT);
        
        logs.push_back(Log(random_x, random_y, random_x2, random_y2, random_radius));
    }
}

Hummock::Hummock(const double & x, const double & y, const double & z, const double & sig_x, const double & sig_y, const double & ax_rotat_angle){
        x_cord = x;
        y_cord = y;
        z_cord = z;
        sigma_x = sig_x;
        sigma_y = sig_y;
        rotation_angle = ax_rotat_angle;
}

Stone::Stone(const double & x, const double & y, const double & radius){
    x_cord = x;
    y_cord = y;
    radius_stone = radius;
}

Log::Log(const double & x1, const double & y1, const double & x2, const double & y2, const double & radius){
    x1_cord = x1;
    x2_cord = x2;
    y1_cord = y1;
    y2_cord = y2;
    log_radius = radius;
}


void Surface::Print_in_file(ofstream& file){
    for (double i = 0.0; i <= length; i += NET_STEP)
    {
        for (double j = 0.0; j <= width; j += NET_STEP)
        {
            file << i << " " << j << " " << get_surface_hight(i, j) << "\n";
        }
    }
    
}
bool Surface::add_hummock(const double & x, const double & y, const double & z, const double & sig_x, const double & sig_y, const double & ax_rotat_angle){
    if(x > -EPS && y > -EPS && x < length && y < width){
        hummocks.push_back(Hummock(x, y, z, sig_x, sig_y, ax_rotat_angle));
        return true;
    }
    else{
        return false;
    }
}

bool Surface::add_log(const double & x1, const double & y1, const double & x2, const double & y2, const double & radius)
{
    if(x1 > -EPS && y1 > -EPS && x1 < length && y1 < width && x2 > -EPS && y2 > -EPS && x2 < length && y2 < width){
        logs.push_back(Log(x1, y1, x2, y2, radius));
        return true;
    }
    else{ 
        return false;
    }
}

bool Surface::add_stone(const double &x, const double &y, const double &radius)
{
    if(x > -EPS && y > -EPS && x < length && y < width){
        stones.push_back(Stone(x, y, radius));
        return true;
    }
    else{
        return false;
    }
}

double Log::get_log_hight(const double & x, const double & y){
    
    if(fabs(x2_cord - x1_cord)>=EPS){
    
        double z = get_sqr(log_radius) - get_sqr(y-(x-x1_cord)*(y2_cord-y1_cord)/(x2_cord-x1_cord)-y1_cord);
        cout << z << "\n";
        if(z>=0 && fabs(y-((x1_cord-x2_cord)*x/(y2_cord-y1_cord))-(y1_cord+y2_cord)/2+(x1_cord-x2_cord)*(x1_cord+x2_cord)/(2*(y2_cord-y1_cord))) <=sqrt(get_sqr(x1_cord-x2_cord)+get_sqr(y1_cord-y2_cord))/2){
            return sqrt(z);
        }
        else{
            return 0;
        }
    }
    if(fabs(y2_cord - y1_cord)>=EPS){
        double z = get_sqr(log_radius) - get_sqr(x-x1_cord);
        if((y2_cord > y1_cord && y < y2_cord && y > y1_cord) || (y1_cord >= y2_cord && y >= y2_cord && y <= y1_cord)){
            return sqrt(z);
        }
        else return 0;
    }
    else return 0;
}
double Hummock::get_hummock_hight(const double & x, const double & y){
    if(fabs(x_cord-x)<4*sigma_x || fabs(x_cord-x)<4*sigma_y || fabs(y_cord-y)<4*sigma_x || fabs(y_cord-y)<4*sigma_y){
        double z = z_cord*exp((-1)*(get_sqr(cos(rotation_angle)*(x-x_cord) + sin(rotation_angle)*(y-y_cord))/(sigma_x) + get_sqr(-sin(rotation_angle)*(x-x_cord) + cos(rotation_angle)*(y-y_cord))/sigma_y));
        return z;
    }
    else return 0;
}

double Stone::get_stone_hight(const double & x, const double & y)
{
    double z = get_sqr(radius_stone) - get_sqr(x_cord - x) - get_sqr(y_cord - y);
    if(z >= 0){
        return sqrt(z) + z_cord;
    }
    else{
        return 0;
    }
}

double Surface::get_surface_hight(const double & x, const double & y){
    double z = 0;
    for (size_t i = 0; i < hummocks.size(); i++)
    {
        z += hummocks[i].get_hummock_hight(x, y);
    }
    for (size_t i = 0; i < stones.size(); i++)
    {
        z += stones[i].get_stone_hight(x, y);
    }
    for (size_t i = 0; i < logs.size(); i++)
    {
        z += logs[i].get_log_hight(x, y);
    }
    return z;
}



double get_random(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}