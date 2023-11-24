#include "Rover.h"

// Rover::Rover(const int & dir, const int & length, const int & width, const int & rad, const double & crit_slope_side, const double & crit_slope_along, const double & start_point_x, const double & start_point_y, const int & str_speed, const int & side_speed, const Surface * surf){
Rover::Rover(const int & dir, const int & rad, const double & crit_slope_side, const double & crit_slope_along, const double & start_point_x, const double & start_point_y, const Surface * surf){
    // length_in_pixels = length;
    // width_in_pixels = width;
    radius_of_wheels_in_pixels = rad;
    critical_along_tilt = crit_slope_along;
    critical_side_tilt = crit_slope_side;
    rover_surface = surf;
    // straight_speed = str_speed;
    // sideways_speed = side_speed;
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
}

bool Rover::check_condition(){
    // cout << "\n " << center_gravity_location.x_cord << " " << center_gravity_location.y_cord << " " << center_gravity_location.z_cord; 
    if(center_gravity_location.x_cord - NET_STEP < 0 || center_gravity_location.y_cord - NET_STEP < 0 || center_gravity_location.x_cord + NET_STEP > rover_surface->length || center_gravity_location.y_cord + NET_STEP > rover_surface->width) return 0;
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
    if(get_max_side_tilt() > critical_side_tilt) {
        cout << "TILT SIDE";
        return 0;
    }
    if(get_max_along_tilt() > critical_along_tilt) {
        cout << "EUJK";
        return 0;
    }
    // cout << "\n Check height: \n";
    // cout << fabs(min_z - max_z);
    if(fabs(min_z-max_z) >= radius_of_wheels_in_pixels*NET_STEP) return 0;
    return 1;
}

double Rover::get_max_side_tilt(){
    if(direction == 1 || direction == -1){ 
        left_tilt = acos(fabs((1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-get_point_centerdxdy(1, 0).z_cord)))));
        right_tilt = acos(fabs((-1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-get_point_centerdxdy(-1, 0).z_cord)))));
    }
    else if(direction == 10 || direction == -10){
        left_tilt = acos(fabs((1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-get_point_centerdxdy(0, 1).z_cord)))));
        right_tilt = acos(fabs((-1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-get_point_centerdxdy(0, -1).z_cord)))));
        // cout << left_tilt << " " << right_tilt << "\n";
    }
    else if(direction == 11 || direction == 101){
        left_tilt = acos(fabs((2 * NET_STEP)/(sqrt(2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(1, -1).z_cord)) * sqrt(2))));
        right_tilt = acos(fabs((-2 * NET_STEP)/(sqrt( 2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(-1, 1).z_cord)) * sqrt(2))));
        // cout << left_tilt << " " << right_tilt << "\n";
    }
    else if(direction == -11 || direction == 1101){
        left_tilt = acos(fabs((2 * NET_STEP)/(sqrt(2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(-1, -1).z_cord)) * sqrt(2))));
        right_tilt = acos(fabs((-2 * NET_STEP)/(sqrt( 2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(1, 1).z_cord)) * sqrt(2))));
        cout << left_tilt << " " << right_tilt << "\n";
    }
    // cout << left_tilt << " " << right_tilt << "\n";
    // cout << left_tilt << " " << right_tilt << " ";
    if(fabs(left_tilt) > fabs(right_tilt)) return fabs(left_tilt);
    else return fabs(right_tilt);
}

double Rover::get_max_along_tilt(){
    double left_tilt, right_tilt;
    if(direction == 10 || direction == -10){ 
        left_tilt = acos(fabs((1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+1)][int(center_gravity_location.y_cord/NET_STEP)].z_cord)))));
        right_tilt = acos(fabs((-1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-1)][int(center_gravity_location.y_cord/NET_STEP)].z_cord)))));
    }
    else if(direction == 1 || direction == -1){
        left_tilt = acos(fabs((1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP+1)].z_cord)))));
        right_tilt = acos(fabs((-1*NET_STEP)/(1*sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord-rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP-1)].z_cord)))));
    }
    else if(direction == -11 || direction == 1101){
        left_tilt = acos(fabs((2 * NET_STEP)/(sqrt(2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(1, 1).z_cord)) * sqrt(2))));
        right_tilt = acos(fabs((-2 * NET_STEP)/(sqrt( 2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(-1, -1).z_cord)) * sqrt(2))));
        // cout << left_tilt << " " << right_tilt << "\n";
    }
    else if(direction == 11 || direction == 101){
        left_tilt = acos(fabs((2 * NET_STEP)/(sqrt(2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(-1, -1).z_cord)) * sqrt(2))));
        right_tilt = acos(fabs((-2 * NET_STEP)/(sqrt( 2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(1, 1).z_cord)) * sqrt(2))));
        // cout << left_tilt << " " << right_tilt << "\n";
    }
    
    // cout << left_tilt << " " << right_tilt << " ";
    if(fabs(left_tilt) > fabs(right_tilt)) return fabs(left_tilt);
    else return fabs(right_tilt);
}

bool Rover::turn_90_clockwise(){
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
    case 11:
        direction = 1101;
        break;
    case 1101:
        direction = 101;
        break;
    case 101:
        direction = -11;
        break;
    case -11:
        direction = 11;
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

bool Rover::turn_45_counterclockwise(){
    switch (direction){
        case 1:
            direction = -11;
            break;
        case -11:
            direction = -10;
            break;
        case -10:
            direction = 101;
            break;
        case 101:
            direction = -1;
            break;
        case -1:
            direction = 1101;
            break;
        case 1101:
            direction = 10;
            break;
        case 10:
            direction = 11;
            break;
        case 11:
            direction = 1;
            break;
        default:
            break;
    }
    return 1;
}

bool Rover::turn_45_clockwise(){
    switch (direction)
    {
    case 1:
        direction = 11;
        break;
    case 11:
        direction = 10;
        break;
    case 10:
        direction = 1101;
        break;
    case 1101:
        direction = -1;
        break;
    case -1:
        direction = 101;
        break;
    case 101:
        direction = -10;
        break;
    case -10:
        direction = -11;
        break;
    case -11:
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

bool Rover::turn_90_counterclockwise(){
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
    case 11:
        direction = -11;
        break;
    case -11:
        direction = 101;
        break;
    case 101:
        direction = 1101;
        break;
    case 1101:
        direction = 11;
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

void Rover::turn_180(){
    if(direction == 1 ||direction == -1 || direction == 10 || direction == -10){
        direction = -direction;
    }
    else{
        switch (direction)
        {
        case -11:
            direction = 1101;
            break;
        case 1101:
            direction = -11;
            break;
        case 11:
            direction = 101;
            break;
        case 101:
            direction = 11;
            break;
        default:
            break;
        }
    }
}

bool Rover::drive_forward_speed_1(){
    switch (direction)
    {
    case 1:
        change_cords(0, straight_speed);
        // cout << rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP)+1].y_cord << " " << rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP)+1].z_cord << "\n";
        // cout << rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP)+2].y_cord << " " << rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP)+2].z_cord << "\n";
        // cout << rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP)+3].y_cord << " " << rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP)+3].z_cord << "\n\n";
        break;
    case -1:
        change_cords(0, -straight_speed);
        break;
    case 10:
        change_cords(straight_speed, 0);
        break;
    case -10:
        change_cords(-straight_speed, 0);
        break;
    case -11:
        change_cords(-straight_speed, straight_speed);
        break;
    case 101:
        change_cords(-straight_speed, -straight_speed);
        break;
    case 1101:
        change_cords(straight_speed, -straight_speed);
        break;
    case 11:
        change_cords(straight_speed, straight_speed);
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

// bool Rover::drive_north_east_speed_1(){
//     switch (direction)
//     {
//     case 1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+sideways_speed)][int(center_gravity_location.y_cord/NET_STEP+straight_speed)];
//         break;
//     case -1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-sideways_speed)][int(center_gravity_location.y_cord/NET_STEP-straight_speed)];
//         break;
//     case 10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+straight_speed)][int(center_gravity_location.y_cord/NET_STEP-sideways_speed)];
//         break;
//     case -10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-straight_speed)][int(center_gravity_location.y_cord/NET_STEP+sideways_speed)];
//         break;
//     default:
//         break;
//     }
//     if(check_condition() == 0){
//         BOOM();
//         return 0;
//     }
//     else return 1;
// }

// bool Rover::drive_north_west_speed_1(){
//     switch (direction)
//     {
//     case 1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-sideways_speed)][int(center_gravity_location.y_cord/NET_STEP+straight_speed)];
//         break;
//     case -1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+sideways_speed)][int(center_gravity_location.y_cord/NET_STEP-straight_speed)];
//         break;
//     case 10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+straight_speed)][int(center_gravity_location.y_cord/NET_STEP+sideways_speed)];
//         break;
//     case -10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-straight_speed)][int(center_gravity_location.y_cord/NET_STEP-sideways_speed)];
//         break;
//     default:
//         break;
//     }
//     if(check_condition() == 0){
//         BOOM();
//         return 0;        
//     }
//     else return 1;
// }

void Rover::BOOM(){
    cout << "\nBOOOOOOOM\n";
}

// bool Rover::drive_forward_speed_2(){
//     switch (direction)
//     {
//     case 1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP)+2*straight_speed];
//         break;
//     case -1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)][int(center_gravity_location.y_cord/NET_STEP-2*straight_speed)];
//         break;
//     case 10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP+2*straight_speed)][int(center_gravity_location.y_cord/NET_STEP)];
//         break;
//     case -10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP-2*straight_speed)][int(center_gravity_location.y_cord/NET_STEP)];
//         break;
//     default:
//         break;
//     }
//     if(check_condition() == 0){
//         BOOM();
//         return 0;
//     }
//     else return 1;
// }

// bool Rover::drive_NNE_speed_2(){ //north north east
// switch (direction)
//     {
//     case 1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP) + sideways_speed][int(center_gravity_location.y_cord/NET_STEP) + 2*straight_speed];
//         break;
//     case -1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP) - sideways_speed][int(center_gravity_location.y_cord/NET_STEP) - 2*straight_speed];
//         break;
//     case 10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP + 2*straight_speed)][int(center_gravity_location.y_cord/NET_STEP) - sideways_speed];
//         break;
//     case -10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP - 2*straight_speed)][int(center_gravity_location.y_cord/NET_STEP) + sideways_speed];
//         break;
//     default:
//         break;
//     }
//     if(check_condition() == 0){
//         BOOM();
//         return 0;
//     }
//     else return 1;
// }

// bool Rover::drive_NEE_speed_2(){
//     switch (direction)
//     {
//     case 1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP) + 2*sideways_speed][int(center_gravity_location.y_cord/NET_STEP) + 2*straight_speed];
//         break;
//     case -1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP) - 2*sideways_speed][int(center_gravity_location.y_cord/NET_STEP) - 2*straight_speed];
//         break;
//     case 10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP + 2*straight_speed)][int(center_gravity_location.y_cord/NET_STEP) - 2*sideways_speed];
//         break;
//     case -10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP - 2*straight_speed)][int(center_gravity_location.y_cord/NET_STEP) + 2*sideways_speed];
//         break;
//     default:
//         break;
//     }
//     if(check_condition() == 0){
//         BOOM();
//         return 0;
//     }
//     else return 1;
// }

// bool Rover::drive_NNW_speed_2(){ //north north east
// switch (direction)
//     {
//     case 1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP) - sideways_speed][int(center_gravity_location.y_cord/NET_STEP) + 2*straight_speed];
//         break;
//     case -1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP) + sideways_speed][int(center_gravity_location.y_cord/NET_STEP) - 2*straight_speed];
//         break;
//     case 10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP + 2*straight_speed)][int(center_gravity_location.y_cord/NET_STEP) + sideways_speed];
//         break;
//     case -10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP - 2*straight_speed)][int(center_gravity_location.y_cord/NET_STEP) - sideways_speed];
//         break;
//     default:
//         break;
//     }
//     if(check_condition() == 0){
//         BOOM();
//         return 0;
//     }
//     else return 1;
// }

// bool Rover::drive_NWW_speed_2(){
//     switch (direction)
//     {
//     case 1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP) - 2*sideways_speed][int(center_gravity_location.y_cord/NET_STEP) + 2*straight_speed];
//         break;
//     case -1:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP) + 2*sideways_speed][int(center_gravity_location.y_cord/NET_STEP) - 2*straight_speed];
//         break;
//     case 10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP + 2*straight_speed)][int(center_gravity_location.y_cord/NET_STEP) + 2*sideways_speed];
//         break;
//     case -10:
//         center_gravity_location = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP - 2*straight_speed)][int(center_gravity_location.y_cord/NET_STEP) - 2*sideways_speed];
//         break;
//     default:
//         break;
//     }
//     if(check_condition() == 0){
//         BOOM();
//         return 0;
//     }
//     else return 1;
// }

Point Rover::get_location(){
    return center_gravity_location;
}

void Rover::change_cords(const int & dx, const int & dy){
    center_gravity_location.y_cord += NET_STEP*dy;
    center_gravity_location.x_cord += NET_STEP*dx;
    center_gravity_location.z_cord = rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)+dx][int(center_gravity_location.y_cord/NET_STEP)+dy].z_cord;
}

void Rover::fill_n_print_sensor(){
    switch(direction){
        case 1:
            for (int i = -2; i <= 2; i++)
            {
                first_pixels_row_to_rover[i+2] = get_point_centerdxdy(i ,2);
            }
            for (int i = -3; i <= 3; i++)
            {
                second_pixels_row_to_rover[i+3] = get_point_centerdxdy(i ,3);
            }
            for (int i = -4; i <= 4; i++)
            {
                third_pixels_row_to_rover[i+4] = get_point_centerdxdy(i, 4);
            }
            break;
        case -1:
            for (int i = -2; i <= 2; i++)
            {
                first_pixels_row_to_rover[i+2] = get_point_centerdxdy(i ,-2);
            }
            for (int i = -3; i <= 3; i++)
            {
                second_pixels_row_to_rover[i+3] = get_point_centerdxdy(i ,-3);
            }
            for (int i = -4; i <= 4; i++)
            {
                third_pixels_row_to_rover[i+4] = get_point_centerdxdy(i, -4);
            }
            break;
        case 10:
            for (int i = -2; i <= 2; i++)
            {
                first_pixels_row_to_rover[i+2] = get_point_centerdxdy(2 ,i);
            }
            for (int i = -3; i <= 3; i++)
            {
                second_pixels_row_to_rover[i+3] = get_point_centerdxdy(3 ,i);
            }
            for (int i = -4; i <= 4; i++)
            {
                third_pixels_row_to_rover[i+4] = get_point_centerdxdy(4, i);
            }
            break;
        case -10:
            for(int i = -2; i <= 2; i++)
            {
                first_pixels_row_to_rover[i+2] = get_point_centerdxdy(-2, i);
            }
            for(int i = -3; i <= 3; i++)
            {
                second_pixels_row_to_rover[i+3] = get_point_centerdxdy(-3, i);
            }
            for(int i = -4; i <= 4; i++)
            {
                third_pixels_row_to_rover[i+4] = get_point_centerdxdy(-4, i);
            }
            break;
        case 11:
            for (int i = 0; i <=2; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, 2);
            for (int i = 0; i <=3; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, 3);
            for (int i = 0; i <=4; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, 4);
            
            for (int i = 3; i <=6; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(2, i - 4);
            for (int i = 4; i <=8; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(3, i - 5);
            for (int i = 5; i <=10; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(4, i - 6);
            break;
        case -11:
            for (int i = 0; i <=2; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, 2);
            for (int i = 0; i <=3; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 2, 3);
            for (int i = 0; i <=4; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 3, 4);
            
            for (int i = 3; i <=6; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(-2, i - 4);
            for (int i = 4; i <=8; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(-3, i - 5);
            for (int i = 5; i <=10; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(-4, i - 6);
            break;
        case 101:
            for (int i = 0; i <=2; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, -2);
            for (int i = 0; i <=3; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 2, -3);
            for (int i = 0; i <=4; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 3, -4);
            
            for (int i = 3; i <=6; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(-2, i - 5);
            for (int i = 4; i <=8; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(-3, i - 7);
            for (int i = 5; i <=10; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(-4, i - 9);
            break;
        case 1101:
            for (int i = 0; i <=2; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, -2);
            for (int i = 0; i <=3; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, -3);
            for (int i = 0; i <=4; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, -4);
            
            for (int i = 3; i <=6; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(2, i - 5);
            for (int i = 4; i <=8; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(3, i - 7);
            for (int i = 5; i <=10; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(4, i - 9);
            break;
        default:
            break; 
    }
}

void Rover::Project_IRA(Point Final_Destination){
    while(1){
        if(center_gravity_location.y_cord > Final_Destination.y_cord && center_gravity_location.x_cord > Final_Destination.x_cord){
            direction = 101;
            while(center_gravity_location.y_cord > Final_Destination && center_gravity_location.x_cord > Final_Destination.x_cord){
                drive_forward_speed_1();
                //sensor_check();
            }
            while(center_gravity_location.y_cord > Final_Destination.y_cord){
                direction = -1;
                drive_forward_speed_1();
                //sensor_check();
            }
            while (center_gravity_location.x_cord > Final_Destination.x_cord)
            {
                direction = -10;
                drive_forward_speed_1();
                //sensor_check();
            }
        }
        if(center_gravity_location.y_cord > Final_Destination.y_cord && center_gravity_location.y_cord < Final_Destination.x_cord){
            direction = 1101;
            while(center_gravity_location.y_cord > Final_Destination.y_cord && center_gravity_location.x_cord < Final_Destination.x_cord){
                drive_forward_speed_1();
                //sensor_check();
            }
            while(center_gravity_location.y_cord > Final_Destination.y_cord){
                direction = -1;
                drive_forward_speed_1();
                //sensor_check();
            }
            while (center_gravity_location.x_cord < Final_Destination.x_cord)
            {
                direction = 10;
                drive_forward_speed_1();
                //sensor_check();
            } 
        }
        if(center_gravity_location.y_cord > Final_Destination.y_cord && center_gravity_location.y_cord == Final_Destination.x_cord){
            while(center_gravity_location.y_cord > Final_Destination.y_cord){
                direction = -1;
                drive_forward_speed_1();
                //sensor_check();
            }
        }
        if(center_gravity_location.y_cord < Final_Destination.y_cord && center_gravity_location.y_cord < Final_Destination.x_cord){
            direction = 11;
            while(center_gravity_location.y_cord < Final_Destination.y_cord && center_gravity_location.x_cord < Final_Destination.x_cord){
                drive_forward_speed_1();
                //sensor_check();
            }
            while(center_gravity_location.y_cord < Final_Destination.y_cord){
                direction = 1;
                drive_forward_speed_1();
                //sensor_check();
            }
            while (center_gravity_location.x_cord < Final_Destination.x_cord)
            {
                direction = 10;
                drive_forward_speed_1();
                //sensor_check();
            } 
        }
        if(center_gravity_location.y_cord < Final_Destination.y_cord && center_gravity_location.y_cord > Final_Destination.x_cord){
            direction = -11;
            while(center_gravity_location.y_cord < Final_Destination.y_cord && center_gravity_location.x_cord > Final_Destination.x_cord){
                drive_forward_speed_1();
                //sensor_check();
            }
            while(center_gravity_location.y_cord < Final_Destination.y_cord){
                direction = 1;
                drive_forward_speed_1();
                //sensor_check();
            }
            while (center_gravity_location.x_cord > Final_Destination.x_cord)
            {
                direction = -10;
                drive_forward_speed_1();
                //sensor_check();
            } 
        }
        if(center_gravity_location.y_cord < Final_Destination.y_cord && center_gravity_location.y_cord == Final_Destination.x_cord){
            direction = 1;
            while(center_gravity_location.y_cord < Final_Destination.y_cord){
                drive_forward_speed_1();
                //sensor_check();
            }
        }
        if(Final_Destination.x_cord == center_gravity_location.x_cord && Final_Destination.y_cord == center_gravity_location.x_cord){
            break;
        }

}

void Rover::Project_MARINA(){
    
}


Point Rover::get_point_centerdxdy(const int & dx, const int & dy){
    // cout << rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)+1][int(center_gravity_location.y_cord/NET_STEP)].z_cord << " " << rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)+dx][int(center_gravity_location.y_cord/NET_STEP)+dy].z_cord << "\n";
    // cout << center_gravity_location.x_cord + NET_STEP*dx << " " << center_gravity_location.y_cord + NET_STEP*dy << " " << rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)+dx][int(center_gravity_location.y_cord/NET_STEP)+dy].z_cord << "\n";
    return Point(center_gravity_location.x_cord + NET_STEP*dx, center_gravity_location.y_cord + NET_STEP*dy, rover_surface->pixels[int(center_gravity_location.x_cord/NET_STEP)+dx][int(center_gravity_location.y_cord/NET_STEP)+dy].z_cord);
}