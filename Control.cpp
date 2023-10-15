#include "Control.h"  
#include "extra_functions.h"  

bool Control::surface_create(const double & surf_length, const double & surf_width, const double & surf_unevennes){
    if(surf_length < 0 || surf_width < 0) return 0;
    ptr_surface = new Surface(surf_length, surf_width, surf_unevennes);
    print_message_in_log("Surface was generated: length - " + to_string(surf_length) + ", width - " + to_string(surf_width) + ", unevennes degree - " + to_string(surf_unevennes) + " ");
    set_cursor(surf_length/2, surf_width/2);
    return 1;
}
bool Control::set_cursor(const double & x, const double & y){
    if(x < 0 || y < 0 || x > ptr_surface->length || y > ptr_surface->width) return 0;
    control_cursor = Cursor(x, y);
    print_message_in_log("Cursor was located ");
    return 1;
}
bool Control::surface_set_random_hummocks(const double & num){
    if(can_double_to_int(num) == 0 || num < 0) return 0;
    _max_rand_hummocks = int(num);
    print_message_in_log("Number of random hummocks was setted ");
    return 1;
}
bool Control::surface_set_random_stones(const double & num){
    if(can_double_to_int(num) == 0 || num < 0) return 0;
    _max_rand_stones = int(num);
    print_message_in_log("Number of random stones was setted ");
    return 1;
}
bool Control::surface_set_random_logs(const double & num){
    if(can_double_to_int(num) == 0 || num < 0) return 0;
    _max_rand_logs = int(num);
    print_message_in_log("Number of random logs was setted ");
    return 1;
}
bool Control::surface_create_hummock(const double & height, const double & sigma_x, const double & sigma_y, const double & rotation){
    ptr_surface->add_hummock(control_cursor.x_cord, control_cursor.y_cord, height, sigma_x, sigma_y, rotation);
    print_message_in_log("Hummock was created ");
    return 1;
}
bool Control::surface_count(){
    ofstream file;
    file.open("TEST.txt");
    ptr_surface->count_surface();
    ptr_surface->Print_in_file(surf_gnu_file);
    print_message_in_log("Surface was counted ");
    return 1;
}

bool Control::surface_create_stone(const double & radius){
    if(radius < 0) return 0;
    ptr_surface->add_stone(control_cursor.x_cord, control_cursor.y_cord, radius);
    print_message_in_log("Stone was created ");
    return 1;
}

bool Control::surface_create_log(const double & x1, const double & y1, const double & x2, const double & y2, const double & radius){
    if(x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0 || radius < 0 || x1 > ptr_surface->length || x2 > ptr_surface->length || y1 > ptr_surface->width || y2 > ptr_surface->width) return 0;
    ptr_surface->add_log(x1, y1, x2, y2, radius);
    print_message_in_log("Log was created ");
    return 1;
}

void Control::print_message_in_log(string message)
{
    if(is_date){
        printer_with_time(message, control_log_file);
    }
    else{
        control_log_file << message <<"\n";
    }
}