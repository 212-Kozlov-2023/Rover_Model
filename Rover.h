#include "extra_functions.h"
#include "Surface.h"

class Rover{
    friend class Processor;
    vector<Point> path;
    int direction;
    int radius_of_wheels_in_pixels;
    int straight_speed = 1;
    int type_of_crawl = 1;
    Point center_gravity_location;
    const Surface *rover_surface;
    double left_tilt, right_tilt;
    double tilt_to_the_side;
    double tilt_along;
    double critical_side_tilt;
    double critical_along_tilt;
    Point first_pixels_row_to_rover[5];
    Point second_pixels_row_to_rover[7];
    Point third_pixels_row_to_rover[9];
    Point first_pixels_corner_to_rover[7];
    Point second_pixels_corner_to_rover[9];
    Point third_pixels_corner_to_rover[11];

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

    Point get_location();
    void change_cords(const int & dx, const int & dy);
    void BOOM();
    bool sensor_check();
    bool rover_main_direct(Point Final_Destination);
    void rover_bypass();
    bool rover_drive_to_point(Point Final_Destination);
    void fill_sensor();
    Point get_point_centerdxdy(const int & dx, const int & dy);
    Point * return_path(int & path_size);
};