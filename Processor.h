#include "Rover.h"

class Processor{
    Point final_point;
    public:
    Processor(Point Final_Destination){
        final_point = Final_Destination;
    }
    bool rover_step(Rover & rover){
        return rover.rover_drive_to_point(final_point);
    };
}