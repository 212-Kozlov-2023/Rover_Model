#include "Rover.h"

class Processor{
    public:
    bool rover_step(Rover & rover, Point Final_Destination){};
    bool sensor_check(){
        rover.fill_sensor();
        double max_z = rover.center_gravity_location.z_cord, min_z = rover.center_gravity_location.z_cord;
        for (int i = -1; i <=1 ; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if(rover.get_point_centerdxdy(i, j).z_cord <= min_z){
                    min_z = rover.get_point_centerdxdy(i, j).z_cord;
                }
                if(rover.get_point_centerdxdy(i, j).z_cord >= max_z){
                    max_z = rover.get_point_centerdxdy(i, j).z_cord;
                }
            }
            
        }
        if(rover.direction == 1 || rover.direction == -1 || rover.direction == 10 || rover.direction == -10){
            for (size_t i = 0; i < 5; i++)
            {
                if(min_z + rover.radius_of_wheels_in_pixels*NET_STEP < rover.first_pixels_row_to_rover[i].z_cord) return 0;
                if(max_z - rover.radius_of_wheels_in_pixels*NET_STEP > rover.first_pixels_row_to_rover[i].z_cord) return 0;
            }
            for (size_t i = 0; i < 7; i++)
            {
                if(min_z + rover.radius_of_wheels_in_pixels*NET_STEP < rover.second_pixels_row_to_rover[i].z_cord) return 0;
                if(max_z - rover.radius_of_wheels_in_pixels*NET_STEP > rover.second_pixels_row_to_rover[i].z_cord) return 0;
            }
            for (size_t i = 0; i < 9; i++)
            {
                if(min_z + rover.radius_of_wheels_in_pixels*NET_STEP < rover.third_pixels_row_to_rover[i].z_cord) return 0;
                if(max_z - rover.radius_of_wheels_in_pixels*NET_STEP > rover.third_pixels_row_to_rover[i].z_cord) return 0;
            }
        }
        else{
            for (size_t i = 0; i < 8; i++)
            {
                if(min_z + rover.radius_of_wheels_in_pixels*NET_STEP < rover.first_pixels_corner_to_rover[i].z_cord) return 0;
                if(max_z - rover.radius_of_wheels_in_pixels*NET_STEP > rover.first_pixels_corner_to_rover[i].z_cord) return 0;
            }
            for (size_t i = 0; i < 10; i++)
            {
                if(min_z + rover.radius_of_wheels_in_pixels*NET_STEP < rover.second_pixels_corner_to_rover[i].z_cord) return 0;
                if(max_z - rover.radius_of_wheels_in_pixels*NET_STEP > rover.second_pixels_corner_to_rover[i].z_cord) return 0;
            }
            for (size_t i = 0; i < 12; i++)
            {
                if(min_z + rover.radius_of_wheels_in_pixels*NET_STEP < rover.third_pixels_corner_to_rover[i].z_cord) return 0;
                if(max_z - rover.radius_of_wheels_in_pixels*NET_STEP > rover.third_pixels_corner_to_rover[i].z_cord) return 0;
            }
        }
        return true;
    }
}