#include "vc_shell.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


VC_Shell::VC_Shell(){
     
}
VC_Shell::VC_Shell(std::string executable){
    currentExecutable = executable;
    command_extras ="XX";
}
void VC_Shell::spawn_client_request(std::string result){
     std::cout<<"[*] before if stmt test "<<result<<"\n";
    if(split(result,1).at(1)!="XX" ){
        std::cout<<"[*] in if stmt test "<<result<<"\n";
        setCommandExtras(split(result,1).at(1));
    }
    std::cout<<"[*] in stmt test "<<result<<"\n";
    int value = atoi(split(result,1).at(0).c_str());
    std::string clientRequestCommand = getClientRequestCommand(value);
    system(clientRequestCommand.c_str()); 
}
void VC_Shell::remote_master_sub_shell(std::string command){
    setRun(true);
        std::cout<<"[*] in subscriber remote listening on: "<<command<<"\n";
        std::array<char, 128> buffer;
        std::string result="";
        std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get()) && getRun() ==true) {
            if (fgets(buffer.data(), 128, pipe.get()) != NULL){
                result = buffer.data();
                std::cout<<result;
            }
        }
        system("killall mosquitto_sub");
        exit(0);
}
void VC_Shell::remote_sub_shell(std::string command){
        setRun(true);
        std::cout<<"[*] in subscriber remote listening on: "<<command<<"\n";
        std::array<char, 128> buffer;
        std::string result="";
        std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get()) && getRun() ==true) {
            std::cout<<"[*] waiting for incoming messages\n";
            if (fgets(buffer.data(), 128, pipe.get()) != NULL){
                result = buffer.data();
                if(result =="EXIT\n"){
                    setRun(false);
                    // just in case 
                    break;
                }
                else{
                   std::cout<<"[*] incoming message "<<result<<"\n";
                   spawn_client_request(result);
                }
            }
      
        }
        system("killall mosquitto_sub");
        exit(0);
}
void VC_Shell::remote_master_shell(int ip_locator,bool isPup,int command_index, std::string extras){
    bool isExit =false;
    std::string current_ip ="";

    switch (ip_locator){
        case 1: current_ip = "192.168.0.150"; break;
        case 2: current_ip = "192.168.0.144"; break;
        case 3: current_ip = "192.168.0.129"; break;
        case 4: current_ip = "192.168.0.124"; break;
        case 5: current_ip = "192.168.0.80";  break;
    }
    if(isPup== true){
       std::string command ="";
       if(extras !=""){
         if(extras =="EXIT"){
            isExit =true;
         }
         setCommandExtras(extras);
       }
       if(isExit ==false){
         command="mosquitto_pub -h "+current_ip+ " -t vc_shell -m "+SSTR( command_index)+"::"+getCommandExtras();
       }
       else{
          command="mosquitto_pub -h "+current_ip+ " -t vc_shell -m "+getCommandExtras();
       }
       remote_pub_shell(command);
    }
    else{
        std::string command = "mosquitto_sub -h localhost -t vc_shell";
         remote_sub_shell(command);
    }
}
void VC_Shell::remote_pub_shell(std::string command){
        std::cout<<command<<"\n";
        std::string mqtt_pub_command = command;
        std::array<char, 128> buffer;
        std::string result="";
        std::shared_ptr<FILE> pipe(popen(mqtt_pub_command.c_str(), "r"), pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get())) {
            if (fgets(buffer.data(), 128, pipe.get()) != NULL){
                result += buffer.data();
                std::cout<<result<<"\n";
            }
        }
}
