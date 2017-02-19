#include "vc_shell.h"
#include <sstream>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <array>

using namespace std;
struct
{

    bool master;
    bool node;
    int ip_index;
    int specified;
    bool pub;
    int command_index;
    std::string extras;
    std::string msg;
    bool tmp_guard;
    bool tmp_agent;
    std::string host_name;
    bool hook;

} opts =
{
    // default values is master at present its 192.168.1.80 can change
    1,0,5,0,1,1,"","",false,false,"Dell Optiplex-755",false

};
std::string getLogPath(){
    return "sys.log";
}
std::string getMasterIp(){
    return "192.168.0.124";
}
std::string getHookCmd(){
    return "mosquitto_sub -h 192.168.0.80 -t vc_shell_gatekeeper_request_hook";
}
std::string system_control_func(int func_id ){
    std::string result="Initial Val:";
      if(func_id ==1){
        std::string command = "sensors";
        std::array<char, 128> buffer;
        std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get())==true) {
            if (fgets(buffer.data(), 128, pipe.get()) != NULL){
                result += buffer.data();
            }
      
        }

      }
      if(func_id ==2){
        std::string command = "/opt/vc/bin/vcgencmd measure_temp";
        std::array<char, 128> buffer;
        std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get())==true) {
            if (fgets(buffer.data(), 128, pipe.get()) != NULL){
                result += buffer.data();
            }
      
        }

      }
      return result;
}
void getCommands(){
    VC_Shell *shell = new VC_Shell;
    std::cout<<"[*] Available commands:\n";
    shell->VC_Shell_CommandSetup();
    int len = shell->getCommands().size();
    for(int i =0;i<len;i++){
        std::cout<<"      "<<(i+1)<<".) "<<shell->getCommands().at(i)<<"\n";
    }

}
void saveResetOpts(){
    opts.master = false;
    opts.node = true;
    opts.ip_index = 5;
    opts.specified = true;
    opts.pub =false;
    opts.command_index = 1;
    opts.extras ="";
    opts.msg ="";
    opts.tmp_guard = false;
    opts.tmp_agent = false;
}
void usage(){
    printf("remote_utils votechain_alpha.v.0.1 remote debugging utility:\n");
    printf("Usage: remote_utils <options>, where options are:\n");
    printf("    -h <host_name> (default is %s)\n", opts.host_name.c_str());
    printf("    -m <master> (default is %d)\n", opts.master);
    printf("    -n <node> (default is %d)\n", opts.node);
    printf("    -s <pub/sub?> (default is %d)\n", opts.pub);
    printf("    -buff additional command parameters defaul is none\n");
    printf("    -msg simple message default is empty \n");
    printf("    -tmp_guard cpu temperature surveillance\n");
    printf("    -tmp_agent cpu temperature agent (publish cpu temperature to broker)\n");
    printf("    -hook (catch remote RPC calls listens on predefined topic)\n");
    printf("    -ip_index <index of target ip> (default is 5)\n");
    printf("              1.) <192.168.0.150>\n");
    printf("              2.) <192.168.0.144>\n");
    printf("              3.) <192.168.0.129>\n");
    printf("              4.) <192.168.0.124>\n");
    printf("              5.) <192.168.0.80>\n");
   
    printf("\n");
    printf("    -cmd_index <command index> (default is %d)\n", opts.command_index);
    getCommands();
   
    exit(0);
}
// mosquitto_pub -h 192.168.0.80 -t vc_shell_gatekeeper_request_hook 
void getOpts(int argc, char* argv[])
{
    int count = 1;
    while (count < argc)
    {
        if (strcmp(argv[count], "-m") == 0)
        {
                opts.master=true;
                opts.specified =true;
        }
        else if (strcmp(argv[count], "-tmp_guard") == 0)
        {
             if(opts.tmp_agent ==true){
                    printf("remote_utils votechain_alpha.v.0.1 remote debugging utility:\nERROR: tmp_guard and tmp_agent selected remote_utils can only be in one mode\nSee usage for more");
                    usage();
             }
             else
                opts.tmp_guard =true;
        }
        else if (strcmp(argv[count], "-hook") == 0)
        {
              opts.hook =true;
        }
        else if (strcmp(argv[count], "-tmp_agent") == 0)
        {
             
             if(opts.tmp_guard ==true){
                    printf("remote_utils votechain_alpha.v.0.1 remote debugging utility:\nERROR: tmp_guard and tmp_agent selected remote_utils can only be in one mode\nSee usage for more");
                    usage();
             }
             else
                opts.tmp_agent =true;
        }
        else if (strcmp(argv[count], "-n") == 0)
        {
                if(opts.specified ==true){
                     printf("remote_utils votechain_alpha.v.0.1 remote debugging utility:\nError master and node option specified\nremote_utils cannot be a master and node at the same time!\nSee usage for more");
                    usage();
                }
                else{
                    opts.node =true;
                }
        }
        else if (strcmp(argv[count], "-ip_index") == 0)
        {
            if (++count < argc)
             opts.ip_index =atoi(argv[count]);
            else
                usage();
        }
        else if (strcmp(argv[count], "-h") == 0)
        {
            if (++count < argc)
             opts.host_name =argv[count];
            else
                usage();
        }
        else if (strcmp(argv[count], "-buff") == 0)
        {
            if (++count < argc)
             opts.extras = std::string(argv[count]);
            else
                usage();
        }
        else if (strcmp(argv[count], "-msg") == 0)
        {
            if (++count < argc)
             opts.msg = std::string(argv[count]);
            else
                usage();
        }
        else if (strcmp(argv[count], "-cmd_index") == 0)
        {
            if (++count < argc)
             opts.command_index=atoi(argv[count]);
            else
                usage();
        }
        else if (strcmp(argv[count], "-s") == 0)
        {
             opts.pub =false;
             opts.master =false;
        }
        count++;
    }

}

int main(int argc, char *argv[])
{

    VC_Shell *remote;
    if(argc == 1){
        usage();
    } 
    if(strcmp(argv[1], "-d") == 0){
        std::cout<<"\n[*] falling back to default options"<<std::endl;
    }
    else{
       getOpts(argc,argv);
       remote = new VC_Shell("~/git/votechain_alpha.v.01/src/VoteChainCoin");
       remote->VC_Shell_CommandSetup();
       std::cout<<"[*] hook is: "<<opts.hook;
       // check is it temperature surveillance mode
       if(opts.hook == true){
          // just warning user hook is selected all other selections are void:
          std::cout<<"\n[*] Client Request hook selected:\n   falling back to default settings all selections are VOID"<<std::endl;
          // resetting the node options just in case someone tries weird stuff here:
          saveResetOpts();
          remote->client_request_hook(getHookCmd());
       }
     
       if(opts.tmp_guard == true){
        // does not matter weather its a master or remote node all publishing to same broker
        // master broker will be DELL Optiplex but for initial test is Acer
        std::string command = "mosquitto_sub -h localhost -t vc_shell_gatekeeper";
        remote->remote_master_sub_shell(command); // the chosen one listens for temperature updates
       }
       if(opts.tmp_agent == true){
        // does not matter weather its a master or remote node all publishing to same broker
        // master broker will be DELL Optiplex but for initial test is Acer
        std::string time= remote->currentDateTime();
        std::string data ="\n\n**********************Start**********************\n\n";
        data+="   [*] "+opts.host_name+"\n";
        data+="   [*] "+time+"\n\n";
        if(opts.host_name == "Raspberry Pi" || opts.host_name == "Raspberry Pi\n"){
          data+=system_control_func(2)+"\n";
        }
        else{
          data+=system_control_func(1)+"\n";
        }
        data+="***********************EOF***********************\n\n";
        ofstream outputFile;
        outputFile.open(getLogPath().c_str(),ios::out | ios::app);
        outputFile<<data;
        outputFile.close();                     // change later for master
        std::string command = "mosquitto_pub -h 192.168.0.80 -t vc_shell_gatekeeper -m \""+data+"\"";
        remote->remote_pub_shell(command);// the slave node update the chosen one :-)
        return 0;
       }
        // request a remote master debugging utility
        if(opts.master == true){  
           remote->remote_master_shell(opts.ip_index,opts.pub,opts.command_index,std::string(opts.extras));
        return 0;
        }
        // is a node remote node accepting incoming message for execution 
        else if(opts.node = true){
           // resetting the node options just in case someone tries weird stuff here:
           saveResetOpts();
           remote->remote_master_shell(opts.ip_index,opts.pub,opts.command_index,std::string(opts.extras));
        }
    }
}
