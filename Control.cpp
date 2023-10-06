#include "Control.h"  
#include "extra_functions.h"  

bool Control::create_surface(const double & surf_length, const double & surf_width, const double & surf_unevennes){
    A = Surface(surf_length, surf_width, surf_unevennes);
    auto now = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(now);
    cnrtl_log_file << "Surface was generated:" << " length - " << surf_length << ", width - " << surf_width << ", unevennes degree - " << surf_unevennes << ctime(&end_time);
    set_cursor(surf_length/2, surf_width/2);
    return 1;
}
bool Control::set_cursor(const double & x, const double & y){
    cntrl_cursor = Cursor(x, y);
    printer_with_time("Cursor was located ", cnrtl_log_file);
    return 1;
}
bool Control::set_random_hummocks(const size_t & num){
    _max_rand_hummocks = num;
    printer_with_time("Number of random hummocks was setted ", cnrtl_log_file);
    return 1;
}
bool Control::set_random_stones(const size_t & num){
    _max_rand_stones = num;
    printer_with_time("Number of random stones was setted ", cnrtl_log_file);
    return 1;
}
bool Control::set_random_logs(const size_t & num){
    _max_rand_logs = num;
    printer_with_time("Number of random logs was setted ", cnrtl_log_file);
    return 1;
}
bool Control::create_hummock(const double & hight, const double & sigma_x, const double & sigma_y, const double & rotation){
    A.add_hummock(cntrl_cursor.x_cord, cntrl_cursor.y_cord, hight, sigma_x, sigma_y);
    printer_with_time("Hummock was created ", cnrtl_log_file);
    return 1;
}
bool Control::count_surface(){
    A.Print_in_file(gnu_file);
    printer_with_time("Surface was counted", cnrtl_log_file);
    return 1;
}

bool Control::create_stone(const double & radius){
    A.add_stone(cntrl_cursor.x_cord, cntrl_cursor.y_cord, radius);
    printer_with_time("Stone was created ", cnrtl_log_file);
    return 1;
}

bool Control::create_log(const double & x1, const double & y1, const double & x2, const double & y2, const double & radius){
    A.add_log(x1, y1, x2, y2, radius);
    printer_with_time("Log was created ", cnrtl_log_file);
    return 1;
}