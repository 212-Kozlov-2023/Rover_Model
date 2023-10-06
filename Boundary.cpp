#include "Boundary.h"

bool Boundary::read_config(){
    bound_config_file.open("config.txt");
    if(getline(bound_config_file, buff)){
        if(is_substr(buff, "print date")){
            if(is_substr(buff, "YES")){
                is_date = true;
            }
            else if(is_substr(buff, "NO")){
                is_date = false;
            }
            else{
                cout << "Error! Wrong command to set date in log file! Check how it spells in sample config file! \n";
                return 0;
            }
        }
        else{
            cout << "Error! The first line should have date setting like in sample config file! Try again.\n";
        }
    }
    else{
        cout << "Error! Config file is empty!!!\n";
    }
    while(getline(bound_config_file, buff) && !is_counted){
        if(!is_log && is_substr(buff,"log file name")){
            int i = 0;
            for (i = 0; i < 256; i++)
            {
                if(buff[i] == '"'){
                    break;
                }
            }
            i++;
            for (i; i < 256 && buff[i] != '"'; i++)
            {
                log_file_name += buff[i];
            }
            bound_log_file.open(log_file_name);
            if(bound_log_file.is_open() == 0){
                cout << "Ошибка\n";
                return 0;
            }
            else{
                is_log = true;
                if(is_date){
                    printer_with_time("log is open! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "log is open! Date: ";
                }
            } 
        }
        
        else if(is_log && is_substr(buff, "Random hummocks")){
            double temp;
            if(sscanf(buff.c_str(), "%*[^=]=%lf;", &temp) == 1 && !is_extra_symbol_after_semicolon(buff)){
                if(is_date){
                    printer_with_time("Command to define number of random hummocks has been read! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "Command to define number of random hummocks has been read!\n";
                }
                controller.set_random_hummocks(temp);
                is_rand += 1;
            }
            else{
                if(is_date){
                    printer_with_time("ERROR! Wrong command to set number of random hummocks. You need to write 1 number as described in config sample and don`t write something after semicolon! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "ERROR! Wrong command to set number of random hummocks. You need to write 1 number as described in config sample and don`t write something after semicolon! \n";
                }
                return 0;
            }
        }
        else if(is_log && is_substr(buff, "Random stones")){
            double temp;
            if(sscanf(buff.c_str(), "%*[^=]=%lf;", &temp) == 1 && is_extra_symbol_after_semicolon(buff) == 0){
                if(is_date){
                    printer_with_time("Command to define number of random stones has been read! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "Command to define number of random stones has been read!\n";
                }
                controller.set_random_stones(temp);
                is_rand += 1;
            }
            else{
                if(is_date){
                    printer_with_time("ERROR! Wrong command to set number of random stones. You need to write 1 number as described in config sample and don`t write something after semicolon! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "ERROR! Wrong command to set number of random stones. You need to write 1 number as described in config sample and don`t write something after semicolon! \n";
                }
                return 0;
            }
        }
        else if(is_log && is_substr(buff, "Random logs")){
            double temp;
            if(sscanf(buff.c_str(), "%*[^=]=%lf;", &temp) == 1 && is_extra_symbol_after_semicolon(buff) == 0){
                if(is_date){
                    printer_with_time("Command to define number of random logs has been read! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "Command to define number of random logs has been read!\n";
                }
                controller.set_random_logs(temp);
                is_rand += 1;
            }
            else{
                if(is_date){
                    printer_with_time("ERROR! Wrong command to set number of random logs. You need to write 1 number as described in config sample and don`t write something after semicolon! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "ERROR! Wrong command to set number of random logs. You need to write 1 number as described in config sample and don`t write something after semicolon! \n";
                }
                return 0;
            }
        }
        else if(is_rand == 3 && is_substr(buff, "Create surface A: ")){
            double temp1, temp2, temp3;

            if(sscanf(buff.c_str(), "%*[^=]=%lf,%*[^=]=%lf,%*[^=]=%lf;", &temp1, &temp2, &temp3) == 3 && is_extra_symbol_after_semicolon(buff) == 0){
                if(is_date){
                    printer_with_time("Command to create surface has been read! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "Command to create surface has been read!\n";
                }
                controller.create_surface(temp1, temp2, temp3);
                is_surface = true;
            }
            else{
                if(is_date){
                    printer_with_time("ERROR! Wrong command to create surface. You need to write 3 numbers as described in config sample and don`t write something after semicolon! ", bound_log_file);
                }
                else{
                    bound_log_file << "ERROR! Wrong command to create surface. You need to write 3 numbers as described in config sample and don`t write something after semicolon! \n";
                }
                return 0;
            }   
        }
        else if(is_log && is_surface && is_substr(buff,"Set cursor")){
            double temp1, temp2;
            if(sscanf(buff.c_str(), "%*[^(](%lf, %lf)", &temp1, &temp2) == 2 && is_extra_symbol_after_semicolon(buff) == 0){ 
                if(is_date){
                    printer_with_time("Command to define cursor location has been read! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "Command to define cursor location has been read!\n";
                }
                controller.set_cursor(temp1, temp2);
            }    
            else{
                if(is_date){
                    printer_with_time("ERROR! Wrong command to set cursor location. You need to write 2 numbers in parentheses separated by commas as described in config sample and don`t write something after semicolon! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "ERROR! Wrong command to set cursor location. You need to write 2 numbers in parentheses separated by commas as described in config sample and don`t write something after semicolon!\n";
                }
                return 0;
            }
        }
        else if(is_log && is_surface && is_substr(buff,"Create hummock(")){
            double temp1, temp2, temp3, temp4;
            if(sscanf(buff.c_str(), "%*[^(](%lf, %lf, %lf, %lf);", &temp1, &temp2, &temp3, &temp4) == 4 && is_extra_symbol_after_semicolon(buff) == 0){
                if(is_date){
                    printer_with_time("Command to create hummock has been read! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "Command to create hummock has been read!\n";
                }
                controller.create_hummock(temp1, temp2, temp3, temp4);
            }
            else{
                if(is_date){
                    printer_with_time("ERROR! Wrong command to create hummock. You need to write 4 numbers in parentheses separated by commas as described in config sample and don`t write something after semicolon! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "ERROR! Wrong command to create hummock. You need to write 4 numbers in parentheses separated by commas as described in config sample and don`t write something after semicolon!\n";
                }
                return 0;
            }
        }
        else if(is_log && is_surface && is_substr(buff,"Create stone")){
            double temp;
            if(sscanf(buff.c_str(), "%*[^(](%lf);", &temp) == 1 && is_extra_symbol_after_semicolon(buff) == 0){
                if(is_date){
                    printer_with_time("Command to create stone has been read! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "Command to create stone has been read!\n";
                }
                controller.create_stone(temp);
            }
            else{
                if(is_date){
                    printer_with_time("ERROR! Wrong command to create stone. You need to write 1 number in parentheses as described in config sample and don`t write something after semicolon! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "ERROR! Wrong command to create stone. You need to write 1 number in parentheses as described in config sample and don`t write something after semicolon!\n";
                }
                return 0;
            }
        }
        else if(is_log && is_surface && is_substr(buff,"Create log")){
            double temp1, temp2, temp3, temp4, temp5;
            if(sscanf(buff.c_str(), "%*[^(](%lf, %lf, %lf, %lf, %lf);", &temp1, &temp2, &temp3, &temp4, &temp5) == 5 && is_extra_symbol_after_semicolon(buff) == 0){
                if(is_date){
                    printer_with_time("Command to create log has been read! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "Command to create log has been read!\n";
                }
                controller.create_log(temp1, temp2, temp3, temp4, temp5);
            }
            else{
                if(is_date){
                    printer_with_time("ERROR! Wrong command to create log. You need to write 5 numbers in parentheses separated by commas as described in config sample and don`t write something after semicolon! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "ERROR! Wrong command to create log. You need to write 5 numbers in parentheses separated by commas as described in config sample and don`t write something after semicolon!\n";
                }
                return 0;
            }
        }
        else if(is_log && is_surface && is_substr(buff,"Count surface;")){
            if(is_extra_symbol_after_semicolon(buff) == 0){
                if(is_date){
                    printer_with_time("Command to count surface has been read! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "Command to count surface has been read!\n";
                }
                controller.count_surface();
                is_counted = true;
            }
            else{
                if(is_date){
                    printer_with_time("ERROR! Wrong command to count surface! Try delete extra symbols after semicolon! Date: ", bound_log_file);
                }
                else{
                    bound_log_file << "ERROR! Wrong command to count surface! Try delete extra symbols after semicolon!\n";
                    return 0;
                }
            }
        }
        else if(is_counted == 1){
            if(is_date){
                printer_with_time("ERROR! YOU CANNOT CHANGE SURFACE AFTER COUNTING", bound_log_file);
            }
            else{
                bound_log_file << "ERROR! UNKNOWN COMMAND!\n";
            }
            return 0;
        }
        else{
            if(is_date){
                printer_with_time("ERROR! UNKNOWN COMMAND!", bound_log_file);
            }
            else{
                bound_log_file << "ERROR! UNKNOWN COMMAND!\n";
            }
            return 0;
        }
    }
    return 1;   
}