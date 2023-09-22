#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#define MAX_HIGH 10
#define MAX_POINTS_NUMBER 10

using namespace std;

double my_rand(double min, double max);

class Point{
    protected:
    double x_cord;
    double y_cord;
    double z_cord;
    public:
    Point(const double & x = 0, const double & y = 0, const double & z = 0){
        x_cord = x, y_cord = y, z_cord = z;
    };
};

class Hummock : public Point{
    friend class Surface;
    // double deviation;
    double sigma_y, sigma_x;
    string formula;
    public:
    Hummock(const double & x = 0, const double & y = 0, const double & z = 0, const double & sig_x = 1, const double & sig_y = 1, const double & ax_rotat_angle = 0);
    // Hummock(Point = Point(0, 0, 0), double sigma_x, double sigma_y);
    double get_hummock_hight(const double & x, const double & y);
};

class Surface{
    double length;
    double width;
    double unevenness_degree;
    Hummock * points[MAX_POINTS_NUMBER];
    public:
    Surface(const double & surf_len = 10, const double & surf_wid = 10, const double & surf_uneven = 0.1);
    double get_surface_hight(const double & x, const double & y);
    // int Print_in_file(FILE*file, Point *points);
};





int main(void){
    Surface A(10, 10, 10);
    // ofstream file;
    // double x = A.get_surface_hight(1, 1);
    // cout << x;
    return 0;
}







double my_rand(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

Surface::Surface(const double & surf_len, const double & surf_wid, const double & surf_uneven){
    length = surf_len;
    width = surf_wid;
    unevenness_degree = surf_uneven;
    double random_x, random_y, random_z, random_sig_y, random_sig_x;
    srand(time(NULL));
    for (size_t i = 0; i < MAX_POINTS_NUMBER; i++)
    {
        random_x = my_rand(0, length);
        random_y = my_rand(0, width);
        random_z = my_rand(-MAX_HIGH/2, MAX_HIGH);
        random_sig_x = my_rand(surf_uneven/5, surf_uneven);
        random_sig_y = my_rand(surf_uneven/5, surf_uneven);

        points[i] = new Hummock(random_x, random_y, random_z, random_sig_x, random_sig_y);
        cout << points[i]->formula << " + ";
    }
}

Hummock::Hummock(const double & x, const double & y, const double & z, const double & sig_x, const double & sig_y, const double & ax_rotat_angle){
        x_cord = x;
        y_cord = y;
        z_cord = z;
        sigma_x = sig_x;
        sigma_y = sig_y;
        formula = "(" + to_string(z) + "*" + "exp(" + "(-1)*((x-(" + to_string(x) + "))**2" + "/" + to_string(sigma_x) + " + " + "((y-(" + to_string(y) + "))**2)" + "/" + to_string(sigma_y) + ")))";
    };

// Surface::Print_in_file(FILE*file, Point *points){
    
//     return 0;
// }

double Hummock::get_hummock_hight(const double & x, const double & y){
    double z = 12;// Формула
    return z;
}

double Surface::get_surface_hight(const double & x, const double & y){
    double z = 0;
    for (size_t i = 0; i < MAX_POINTS_NUMBER; i++)
    {
        z += points[i]->get_hummock_hight(x, y);

    }
    return z;
}