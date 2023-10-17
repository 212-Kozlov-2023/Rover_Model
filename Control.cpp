#include "Control.h"  
#include "extra_functions.h"  

Control::Control(bool date, string log_filename, string gnu_surf_filename, string gnu_rover_filename, string gnu_load){
    gnu_load_filename = gnu_load;
    is_date = date;
    _max_rand_hummocks = 0;
    _max_rand_logs = 0;
    _max_rand_stones = 0;
    // cout << log_filename << " " << gnu_filename << " " << gnu_rover_filename << "\n";
    control_log_file.open(log_filename);
    surf_gnu_file.open(gnu_surf_filename);
    rover_gnu_file.open(gnu_rover_filename);
};

Control::~Control(){
    surface_delete();
    close_files();
    delete rover;
    delete ptr_surface;
}


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


void Control::rover_create(const int & dir, const int & length, const int & width, const int & rad, const double & crit_slope_side, const double & crit_slope_along, const double & start_point_x, const double & start_point_y, const int & str_speed, const int & side_speed){
    rover = new Rover(dir, length, width, rad, crit_slope_side, crit_slope_along, start_point_x, start_point_y, str_speed, side_speed, ptr_surface);
    rover_print_current_loc();
};

bool Control::rover_drive_forward_1(){
    
    if(rover->drive_forward_speed_1()){
        print_message_in_log("The rover successfully drove forward at a speed of 1 ");
        rover_print_current_loc();
        return 1;
    }
    else{
        print_message_in_log("The rover broke down ");
        return 0;
    }
}
bool Control::rover_drive_NW_1(){
    if(rover->drive_north_west_speed_1()){
        print_message_in_log("The rover successfully drove to the northwest at a speed of 1 ");
        rover_print_current_loc();
        return 1;
    }
    else{
        print_message_in_log("The rover broke down ");
        return 0;
    }
}
bool Control::rover_drive_NE_1(){
    if(rover->drive_north_east_speed_1()){
        print_message_in_log("The rover successfully drove to the northeast at a speed of 1 ");
        rover_print_current_loc();
        return 1;
    }
    else{
        print_message_in_log("The rover broke down ");
        return 0;
    }
}
bool Control::rover_drive_forward_2(){
    if(rover->drive_forward_speed_2()){
        print_message_in_log("The rover successfully drove forward at a speed of 2 ");
        rover_print_current_loc();
        return 1;
    }
    else{
        print_message_in_log("The rover broke down ");
        return 0;
    }
}
bool Control::rover_drive_NNE_2(){
    if(rover->drive_NNE_speed_2()){
        print_message_in_log("The rover successfully drove to the north + northeast at a speed of 2 ");
        rover_print_current_loc();
        return 1;
    }
    else{
        print_message_in_log("The rover broke down ");
        return 0;
    }
}
bool Control::rover_drive_NNW_2(){
    if(rover->drive_NNW_speed_2()){
        print_message_in_log("The rover successfully drove to the north + northwest at a speed of 2 ");
        rover_print_current_loc();
        return 1;
    }
    else{
        print_message_in_log("The rover broke down ");
        return 0;
    }
}
bool Control::rover_drive_NWW_2(){
    if(rover->drive_NWW_speed_2()){
        print_message_in_log("The rover successfully drove to the northwest + west at a speed of 2 ");
        rover_print_current_loc();
        return 1;
    }
    else{
        print_message_in_log("The rover broke down ");
        return 0;
    }
}
bool Control::rover_drive_NEE_2(){
    if(rover->drive_NEE_speed_2()){
        print_message_in_log("The rover successfully drove to the northeast + east at a speed of 2 ");
        rover_print_current_loc();
        return 1;
    }
    else{
        print_message_in_log("The rover broke down ");
        return 0;
    }
}
bool Control::rover_turn_90_clock(){
    if(rover->turn_90_clockwise()){
        print_message_in_log("The rover successfully turned 90 clockwise ");
        rover_print_current_loc();
        return 1;
    }
    else{
        print_message_in_log("The rover broke down ");
        return 0;
    }
}
bool Control::rover_turn_90_counterclock(){
    if(rover->turn_90_counterclockwise()){
        print_message_in_log("The rover successfully turned 90 counterclockwise ");
        rover_print_current_loc();
        return 1;
    }
    else{
        print_message_in_log("The rover broke down ");
        return 0;
    }
}
void Control::rover_turn_180(){
    rover->turn_180();
    print_message_in_log("The rover successfully turned 180 ");
    rover_print_current_loc();
}

void Control::close_files(){
    control_log_file.close();
    surf_gnu_file.close();
    rover_gnu_file.close();
}

void Control::rover_print_current_loc(){
    Point point = rover->get_location();
    rover_gnu_file << point.x_cord << " " << point.y_cord << " " << point.z_cord << "\n";
}

void Control::surface_delete(){
    delete ptr_surface;
    free(ptr_surface);
};