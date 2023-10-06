#include "extra_functions.h"
#include "Log.h"
#include "Stone.h"
#include "Hummock.h"
#include "Cursor.h"

class Surface{
    friend class Log;
    friend class Stone;
    friend class Hummock;
    friend class Control;
    double length;
    double width;
    double unevenness_degree;
    vector<Hummock> hummocks;
    vector<Stone> stones;
    vector<Log> logs;
    Cursor cursor;
    public:
    Surface(const double & surf_len = 10, const double & surf_wid = 10, const double & surf_uneven = 0.1);
    double get_surface_hight(const double & x, const double & y);
    void Print_in_file(ofstream & file);
    bool add_hummock(const double & x = 0.0, const double & y = 0.0, const double & z = 0.0, const double & sig_x = 1.0, const double & sig_y = 1.0, const double & ax_rotat_angle = 0);
    bool add_stone(const double & x = 0.0, const double & y = 0.0, const double & radius = 0);
    bool add_log(const double & x1 = 0.0, const double & y1 = 0.0, const double & x2 = 0.0, const double & y2 = 0.0, const double & radius = 0.0);
};