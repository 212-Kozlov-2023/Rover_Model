#include "Rover.h"

class Processor{
    public:
    bool rover_step(Rover & rover, Point Final_Destination){};
    bool sensor_check(Rover & rover){
        return rover.sensor_check();
    }
}