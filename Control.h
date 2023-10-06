#include "Surface.h"

class Control{
    ofstream cnrtl_log_file;
    ofstream gnu_file;
    Surface A;
    bool is_date_at_log = true;
    Cursor cntrl_cursor;
    public:
    Control(string gnu_filename = "TEST.txt"){
        _max_rand_hummocks = 0;
        _max_rand_logs = 0;
        _max_rand_stones = 0;
        cnrtl_log_file.open("Log_control.txt");
        gnu_file.open(gnu_filename);
    }
    bool create_surface(const double & surf_length, const double & surf_width, const double & surf_unevennes);
    bool set_cursor(const double & x, const double & y);
    bool set_random_hummocks(const size_t & num);
    bool set_random_stones(const size_t & num);
    bool set_random_logs(const size_t & num);
    bool create_hummock(const double & hight, const double & sigma_x, const double & sigma_y, const double & rotation);
    bool create_log(const double & x1, const double & y1, const double & x2, const double & y2, const double & radius);
    bool create_stone(const double & radius);
    bool count_surface();
};