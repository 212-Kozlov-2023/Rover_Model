#include "Control.h"

class Boundary{
    string log_file_name;
    ifstream bound_config_file;
    ofstream bound_log_file;
    bool is_log = false;
    bool is_surface = false;
    bool is_counted = false;
    bool is_date;
    int is_rand = 0;
    string buff;
    Control controller;
    
    public:
    Boundary(){
        read_config();
    };
    bool read_config();
};