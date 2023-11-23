#include "extra_functions.h"
#include "Surface.h"

class Rover{
    int direction; // координаты единичного вектора записанные подряд Например: 10 - {1, 0} - направление вдоль оси ox
    int length_in_pixels = 3;
    int width_in_pixels = 3;
    int radius_of_wheels_in_pixels;
    int straight_speed = 1;
    // int sideways_speed = 2;
    Point center_gravity_location;
    const Surface *rover_surface;
    double tilt_to_the_side;
    double tilt_along;
    double critical_side_tilt;
    double critical_along_tilt;
    Point first_pixels_row_to_rover[5];
    Point second_pixels_row_to_rover[7];
    Point third_pixels_row_to_rover[9];

    public:
    // Rover(const int & dir, const int & length, const int & width, const int & rad, const double & crit_slope_side, const double & crit_slope_along, const double & start_point_x, const double & start_point_y, const int & str_speed, const int & side_speed, const Surface * surf);
    Rover(const int & dir, const int & rad, const double & crit_slope_side, const double & crit_slope_along, const double & start_point_x, const double & start_point_y, const Surface * surf);

    bool check_condition();
    double get_max_side_tilt();
    double get_max_along_tilt();

    bool turn_45_clockwise();
    bool turn_45_counterclockwise();
    bool turn_90_clockwise();
    bool turn_90_counterclockwise();
    void turn_180();

    bool drive_forward_speed_1();
    // bool drive_north_east_speed_1();
    // bool drive_north_west_speed_1();

    // bool drive_forward_speed_2();
    // bool drive_NNE_speed_2();//north north east
    // bool drive_NEE_speed_2();
    // bool drive_NNW_speed_2();
    // bool drive_NWW_speed_2();

    Point get_location();
    void change_cords(const int & dx, const int & dy);
    void BOOM();

    void fill_n_print_sensor()();
    Point get_point_centerdxdy(const int & dx, const int & dy);
};