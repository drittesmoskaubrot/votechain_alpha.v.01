#include "vc_shell.h"
#include <sstream>

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

} opts =
{
    // default values is master at present its 192.168.1.80 can change
    1,0,5,0,1,1,"",""

};
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
}
void usage(){
    printf("remote_utils votechain_alpha.v.0.1 remote debugging utility:\n");
    printf("Usage: remote_utils <options>, where options are:\n");
    printf("  -m <master> (default is %d)\n", opts.master);
    printf("  -n <node> (default is %d)\n", opts.node);
    printf("  -s <pub/sub?> (default is %d)\n", opts.pub);
    printf("  -ip_index <indes of target ip> (default is 5)\n");
    printf("       1.) 192.168.0.150\n");
    printf("       2.) 192.168.0.144\n");
    printf("       3.) 192.168.0.129\n");
    printf("       4.) 192.168.0.124\n");
    printf("       5.) 192.168.0.80\n");
    printf("\n");
    printf("  -cmd_index <command index> (default is %d)\n", opts.command_index);
    getCommands();
    printf("  -buff ""\n");
    printf(" -msg simple message ""\n");
    exit(0);
}

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
        else if (strcmp(argv[count], "-n") == 0)
        {
                if(opts.specified ==true){
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

    
    if(argc == 1){
        usage();
    } 
    if(strcmp(argv[1], "-d") == 0){
        std::cout<<"\n[*] falling back to default options"<<std::endl;
    }
    else{
       getOpts(argc,argv);
    }
     VC_Shell *remote = new VC_Shell("~/git/votechain_alpha.v.01/src/VoteChainCoin");
    remote->VC_Shell_CommandSetup();
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
