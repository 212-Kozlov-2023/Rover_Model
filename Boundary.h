#include "Control.h"

class Boundary{
        bool is_counted = false;
        bool is_date = false;

        Control *controller;

        string boundary_log_filename;
        string rover_command_filename;
        string surface_command_filename;
        string controller_log_filename;
        string gnu_surf_filename;
        string gnu_rover_filename;

        ofstream boundary_log_file;

        ifstream rover_command_file;
        ifstream config_file;

    public:
        Boundary(const string & config_filename){
            if(read_config(config_filename) == 0){
                cout << "\nIncorrect config\n";
            }
            // cout << boundary_log_filename << " " << rover_command_filename << " " << surface_command_filename << " " << controller_log_filename << " " << gnu_surf_filename << " " << gnu_rover_filename; 
            boundary_log_file.open(boundary_log_filename);
            controller = new Control(is_date, controller_log_filename, gnu_surf_filename, gnu_rover_filename);
            read_surface_config();
            boundary_log_file.close();
            controller->close_files();
            // controller->surface_delete();
            // free(controller);
            // controller->rover_test();
        };
        bool read_config(const string & conf_name);
        bool read_rover_config();
        bool read_surface_config();
        void print_message_in_log(const string & message);
        bool fill_filename(const string & line, string & filename);
};