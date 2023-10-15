#include "extra_functions.h"
#include "Surface.h"

class Rover{
    int direction; // координаты единичного вектора записанные подряд Например: 10 - {1, 0} - направление вдоль оси ox
    int length_in_pixels;
    int width_in_pixels;
    int radius_of_wheels_in_pixels;
    Point center_gravity_location;
    const Surface *rover_surface;
    double tilt_to_the_side;
    double tilt_along;
    double critical_side_tilt;
    double critical_along_tilt;
    // ofstream rover;
    public:
    Rover(const int & dir, const int & length, const int & width, const int & rad, const double & crit_slope_side, const double & crit_slope_along, const double & start_point_x, const double & start_point_y, const Surface * surf){
        // rover.open("rover.txt");
        length_in_pixels = length;
        width_in_pixels = width;
        radius_of_wheels_in_pixels = rad;
        critical_along_tilt = crit_slope_along;
        critical_side_tilt = crit_slope_side;
        rover_surface = surf;
        center_gravity_location = Point(start_point_x, start_point_y, rover_surface->pixels[int(start_point_x/NET_STEP)][int(start_point_y/NET_STEP)].z_cord);
        direction = dir;
        
        // cout << "\n A " << length_in_pixels << " " << crit_slope_along << " \n";
        if(dir != 10 && dir != 1 && dir != -10 && dir != -1){ 
            cout << "Incorrect direction value \n";
            exit(-1);
        }
        if(crit_slope_along > M_PI_2 || crit_slope_side > M_PI_2 || crit_slope_along < EPS || crit_slope_side < EPS){
            cout << "Incorrect critical slope value";
            exit(-1);
        }
    };

    bool check_condition(){
        cout << "\n " << center_gravity_location.x_cord << " " << center_gravity_location.y_cord << " " << center_gravity_location.z_cord; 
        if(center_gravity_location.x_cord - length_in_pixels*NET_STEP/2 < 0 || center_gravity_location.y_cord - length_in_pixels*NET_STEP/2 < 0 || center_gravity_location.x_cord + length_in_pixels * NET_STEP/2 > rover_surface->length || center_gravity_location.y_cord + length_in_pixels*NET_STEP/2 > rover_surface->width) return 0;
        double max_z = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP)].z_cord;
        double min_z = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP)].z_cord;
        double z = 0;
        if(direction == 1 || direction == -1){
            for (int i = -length_in_pixels/2; i <= length_in_pixels/2; i++)
            {
                for (int j = -width_in_pixels/2; j <= width_in_pixels/2; j++){
                    z = rover_surface->pixels[int((center_gravity_location.x_cord+i*NET_STEP)/NET_STEP)][int((center_gravity_location.y_cord+j*NET_STEP)/NET_STEP)].z_cord;
                    if(z > max_z) max_z = z;
                    if(z < min_z) min_z = z;
                }
            }
        }
        else{
            for (int i = -width_in_pixels/2; i <= width_in_pixels/2; i++)
            {
                for (int j = -length_in_pixels/2; j <= length_in_pixels/2; j++){
                    z = rover_surface->pixels[int((center_gravity_location.x_cord+i*NET_STEP)/NET_STEP)][int((center_gravity_location.y_cord+j*NET_STEP)/NET_STEP)].z_cord;
                    if(z > max_z) max_z = z;
                    if(z < min_z) min_z = z;
                }
            }
        }
        // cout << "Angel check: \n";
        if(get_max_side_tilt() > critical_side_tilt) return 0;
        if(get_max_along_tilt() > critical_along_tilt) return 0;
        // cout << "\n Check height: \n";
        // cout << fabs(min_z - max_z);
        if(fabs(min_z-max_z) >= radius_of_wheels_in_pixels*NET_STEP) return 0;
        return 1;
    };

    double get_max_side_tilt(){
        double left_tilt, right_tilt;
        if(direction == 1 || direction == -1){ 
            left_tilt = acos(fabs((1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+1)][int(center_gravity_location.y_cord/NET_STEP)].z_cord)))));
            right_tilt = acos(fabs((-1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-1)][int(center_gravity_location.y_cord/NET_STEP)].z_cord)))));
        }
        else{
            left_tilt = acos(fabs((1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP+1)].z_cord)))));
            right_tilt = acos(fabs((-1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP-1)].z_cord)))));
        }
        // cout << left_tilt << " " << right_tilt << " ";
        if(fabs(left_tilt) > fabs(right_tilt)) return fabs(left_tilt);
        else return fabs(right_tilt);
    };
    double get_max_along_tilt(){
        double left_tilt, right_tilt;
        if(direction == 10 || direction == -10){ 
            left_tilt = acos(fabs((1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+1)][int(center_gravity_location.y_cord/NET_STEP)].z_cord)))));
            right_tilt = acos(fabs((-1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-1)][int(center_gravity_location.y_cord/NET_STEP)].z_cord)))));
        }
        else{
            left_tilt = acos(fabs((1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP+1)].z_cord)))));
            right_tilt = acos(fabs((-1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP-1)].z_cord)))));
        }
        // cout << left_tilt << " " << right_tilt << " ";
        if(fabs(left_tilt) > fabs(right_tilt)) return fabs(left_tilt);
        else return fabs(right_tilt);
    };

    bool turn_90_clockwise(){
        switch (direction)
        {
        case 1:
            direction = 10;
            break;
        case 10:
            direction = -1;
            break;
        case -1:
            direction = -10;
            break;
        case -10:
            direction = 1;
            break;
        default:
            break;
        }
        if(check_condition() == 0){
            BOOM();
            return 0;
        }
        else return 1;
    }

    bool turn_90_counterclockwise(){
        switch (direction)
        {
        case 1:
            direction = -10;
            break;
        case -10:
            direction = -1;
            break;
        case -1:
            direction = 10;
            break;
        case 10:
            direction = 1;
            break;
        default:
            break;
        }
        if(check_condition() == 0){
            BOOM();
            return 0;
        }
        else return 1;
    }

    void turn_180(){
        direction = -direction;
    }

    bool drive_forward_speed_1(){
        switch (direction)
        {
        case 1:
            // center_gravity_location.y_cord+NET_STEP;
            // center_gravity_location.z_cord = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP)].z_cord;
            // cout << " \n" << int(center_gravity_location.y_cord/NET_STEP)+1 << " - x \n";
            center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP)+2];
            // cout << " \n" << int(center_gravity_location.y_cord/NET_STEP) << " - x` \n";
            // cout << "\n Поехали 1\n";
            break;
        case -1:
            center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP-1)];
            // cout << "\n Поехали -1\n";
            break;
        case 10:
            center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+1)][int(center_gravity_location.y_cord/NET_STEP)];
            // cout << "\n Поехали 10\n";
            break;
        case -10:
            center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-1)][int(center_gravity_location.y_cord/NET_STEP)];
            // cout << "\n Поехали -10\n";
            break;
        default:
            break;
        }
        if(check_condition() == 0){
            BOOM();
            return 0;
        }
        else return 1;
    };

    bool drive_north_east_speed_1(){
        switch (direction)
        {
        case 1:
            center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+1)][int(center_gravity_location.y_cord/NET_STEP+1)];
            break;
        case -1:
            center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-1)][int(center_gravity_location.y_cord/NET_STEP-1)];
            break;
        case 10:
            center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+1)][int(center_gravity_location.y_cord/NET_STEP-1)];
            break;
        case -10:
            center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-1)][int(center_gravity_location.y_cord/NET_STEP+1)];
            break;
        default:
            break;
        }
        if(check_condition() == 0){
            BOOM();
            return 0;
        }
        else return 1;
    }

    bool drive_north_west_speed_1(){
        switch (direction)
        {
        case 1:
            center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-1)][int(center_gravity_location.y_cord/NET_STEP+1)];
            break;
        case -1:
            center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+1)][int(center_gravity_location.y_cord/NET_STEP-1)];
            break;
        case 10:
            center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+1)][int(center_gravity_location.y_cord/NET_STEP+1)];
            break;
        case -10:
            center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-1)][int(center_gravity_location.y_cord/NET_STEP-1)];
            break;
        default:
            break;
        }
        if(check_condition() == 0){
            BOOM();
            return 0;        
        }
        else return 1;
    }

    void BOOM(){
        cout << "\nBOOOOOOOM\n";
    }
    };