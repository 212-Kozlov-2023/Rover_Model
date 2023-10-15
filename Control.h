#include "Rover.h"

class Control{
    ofstream control_log_file;
    ofstream surf_gnu_file;
    ofstream rover_gnu_file;
    Surface *ptr_surface;
    Rover *rover;
    bool is_date = true;
    Cursor control_cursor;
    public:
    Control(bool date, string log_filename, string gnu_filename, string gnu_rover_filename){
        ofstream file;
        file.open("TEST2.txt");
        file << "Ghbdtn";
        is_date = date;
        _max_rand_hummocks = 0;
        _max_rand_logs = 0;
        _max_rand_stones = 0;
        // cout << log_filename << " " << gnu_filename << " " << gnu_rover_filename << "\n";
        control_log_file.open(log_filename);
        surf_gnu_file.open(gnu_filename);
        rover_gnu_file.open(gnu_rover_filename);
    };
    ~Control(){
        control_log_file.close();
    }

    bool surface_create(const double & surf_length, const double & surf_width, const double & surf_unevennes);
    bool set_cursor(const double & x, const double & y);
    bool surface_set_random_hummocks(const double & num);
    bool surface_set_random_stones(const double & num);
    bool surface_set_random_logs(const double & num);
    bool surface_create_hummock(const double & height, const double & sigma_x, const double & sigma_y, const double & rotation);
    bool surface_create_log(const double & x1, const double & y1, const double & x2, const double & y2, const double & radius);
    bool surface_create_stone(const double & radius);
    bool surface_count();
    void surface_delete(){
        delete ptr_surface;
        free(ptr_surface);
    };

    void rover_create(const int & dir, const int & length, const int & width, const int & rad, const double & crit_slope_side, const double & crit_slope_along, const double & start_point_x, const double & start_point_y){
        rover = new Rover(dir, length, width, rad, crit_slope_side, crit_slope_along, start_point_x, start_point_y, ptr_surface);
    };



    void close_files(){
        control_log_file.close();
        surf_gnu_file.close();
        rover_gnu_file.close();
    };
    bool rover_test(){
        Rover ostap  = Rover(-1, 20, 10, 20, 1, 1, 50, 32.4, ptr_surface);
        ostap.turn_180();
        int i = 0;
        while (1)
        {
            if(i == 50) break;
            if(ostap.drive_forward_speed_1() == 0){
                return 0;
            }
            i++;
        }
        i = 0;
        while (1)
        {
            if(i == 50) break;
            ostap.drive_forward_speed_1();
            if(ostap.drive_forward_speed_1() == 0){
                return 0;
            }
            i++;
        }
        i = 0;
        while (1)
        {
            if(i == 50) break;
            if(ostap.drive_forward_speed_1() == 0){
                return 0;
            }
            i++;
        }

        if(ostap.drive_forward_speed_1() == 0){
            return 0;
        }

            ostap.drive_north_east_speed_1();
        return 1;
    };
    void print_message_in_log(string message);
};