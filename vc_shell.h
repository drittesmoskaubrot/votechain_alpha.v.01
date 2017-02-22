#ifndef VC_SHELL
#define VC_SHELL
#include <string>
#include <vector>
#include <iostream>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <stdio.h>
#include <time.h>

class VC_Shell{

public: 

    VC_Shell(std::string executable);
    VC_Shell();
    std::vector<std::string> getCommands(){
        return commands;
    }
    std::string getClientRequestCommand(int value){
        /*"start","stop","help","getblockcount","getconnectioncount",  
         "getpeerinfo","getdifficulty","getnetworkhashps","getgenerate",         
         "setgenerate","gethashespersec","getinfo","getmininginfo",       
         "getnewaddress","getaccountaddress","setaccount","getaccount",          
         "getaddressesbyaccount","sendtoaddress","getreceivedbyaddress",
         "getreceivedbyaccount","listreceivedbyaddress","listreceivedbyaccount"
         "backupwallet","keypoolrefill","walletpassphrase","walletpassphrasechange",
         "walletlock","encryptwallet","validateaddress","getbalance","move",                
         "sendfrom","sendmany","addmultisigaddress","getrawmempool",       
         "getblock","getblockhash","gettransaction","listtransactions","signmessage",         
         "verifymessage","getwork","getworkex","listaccounts","settxfee",            
         "setmininput","getblocktemplate","listsinceblock","dumpprivkey",         
         "importprivkey","listunspent","getrawtransaction","createrawtransaction",
         "decoderawtransaction","signrawtransaction","sendrawtransaction",
        */
        switch(value){
            // start
            case  1: return getCurrentExecutable()+" &";
            // stop
            case  2: return getCurrentExecutable()+" "+getCommands().at(1)+" "+getCommandExtras();
            //  help
            case 3: return getCurrentExecutable()+" "+getCommands().at(2)+" "+getCommandExtras();
            //  getblockcount
            case  4: return getCurrentExecutable()+" "+getCommands().at(3)+" "+getCommandExtras();
            // getconnectioncount
            case  5: return getCurrentExecutable()+" "+getCommands().at(4)+" "+getCommandExtras();
            //  getpeerinfo
            case  6: return getCurrentExecutable()+" "+getCommands().at(5)+" "+getCommandExtras();
            // getdifficulty
            case  7: return getCurrentExecutable()+" "+getCommands().at(6)+" "+getCommandExtras();
            // getnetworkhashps
            case  8: return getCurrentExecutable()+" "+getCommands().at(7)+" "+getCommandExtras();
            // getgenerate
            case  9: return getCurrentExecutable()+" "+getCommands().at(8)+" "+getCommandExtras();
            // setgenerate
            case 10: return getCurrentExecutable()+" "+getCommands().at(9)+" "+getCommandExtras();
            // gethashespersec
            case 11: return getCurrentExecutable()+" "+getCommands().at(10)+" "+getCommandExtras();
            // getinfo
            case 12: return getCurrentExecutable()+" "+getCommands().at(11)+" "+getCommandExtras();
            // getmininginfo
            case 13: return getCurrentExecutable()+" "+getCommands().at(12)+" "+getCommandExtras();
            // getnewaddress
            case 14: return getCurrentExecutable()+" "+getCommands().at(13)+" "+getCommandExtras();
            // getaccountaddress
            case 15: return getCurrentExecutable()+" "+getCommands().at(14)+" "+getCommandExtras();
            // setaccount
            case 16: return getCurrentExecutable()+" "+getCommands().at(15)+" "+getCommandExtras();
            // getaccount
            case 17: return getCurrentExecutable()+" "+getCommands().at(16)+" "+getCommandExtras();
            // getaddressesbyaccount
            case 18: return getCurrentExecutable()+" "+getCommands().at(17)+" "+getCommandExtras();
            // sendtoaddress
            case 19: return getCurrentExecutable()+" "+getCommands().at(18)+" "+getCommandExtras();
            // getreceivedbyaddress
            case 20: return getCurrentExecutable()+" "+getCommands().at(19)+" "+getCommandExtras();
            // getreceivedbyaccount
            case 21: return getCurrentExecutable()+" "+getCommands().at(20)+" "+getCommandExtras();
            // listreceivedbyaddress
            case 22: return getCurrentExecutable()+" "+getCommands().at(21)+" "+getCommandExtras();
            // listreceivedbyaccount
            case 23: return getCurrentExecutable()+" "+getCommands().at(22)+" "+getCommandExtras();
            // backupwallet
            case 24: return getCurrentExecutable()+" "+getCommands().at(23)+" "+getCommandExtras();
            // keypoolrefill
            case 25: return getCurrentExecutable()+" "+getCommands().at(24)+" "+getCommandExtras();
            // walletpassphrase
            case 26: return getCurrentExecutable()+" "+getCommands().at(25)+" "+getCommandExtras();
            // walletpassphrasechange
            case 27: return getCurrentExecutable()+" "+getCommands().at(26)+" "+getCommandExtras();
            // walletlock
            case 28: return getCurrentExecutable()+" "+getCommands().at(27)+" "+getCommandExtras();
            // encryptwallet
            case 29: return getCurrentExecutable()+" "+getCommands().at(28)+" "+getCommandExtras();
            // validateaddress
            case 30: return getCurrentExecutable()+" "+getCommands().at(29)+" "+getCommandExtras();
            // getbalance
            case 31: return getCurrentExecutable()+" "+getCommands().at(30)+" "+getCommandExtras();
            // move
            case 32: return getCurrentExecutable()+" "+getCommands().at(31)+" "+getCommandExtras();
            // sendfrom
            case 33: return getCurrentExecutable()+" "+getCommands().at(32)+" "+getCommandExtras();
            // sendmany
            case 34: return getCurrentExecutable()+" "+getCommands().at(33)+" "+getCommandExtras();
            // addmultisigaddress
            case 35: return getCurrentExecutable()+" "+getCommands().at(34)+" "+getCommandExtras();
            // getrawmempool
            case 36: return getCurrentExecutable()+" "+getCommands().at(35)+" "+getCommandExtras();
            // getblock
            case 37: return getCurrentExecutable()+" "+getCommands().at(36)+" "+getCommandExtras();
            // getblockhash
            case 38: return getCurrentExecutable()+" "+getCommands().at(37)+" "+getCommandExtras();
            // gettransaction
            case 39: return getCurrentExecutable()+" "+getCommands().at(38)+" "+getCommandExtras();
            // listtransactions
            case 40: return getCurrentExecutable()+" "+getCommands().at(39)+" "+getCommandExtras();
            // signmessage
            case 41: return getCurrentExecutable()+" "+getCommands().at(40)+" "+getCommandExtras();
            // verifymessage
            case 42: return getCurrentExecutable()+" "+getCommands().at(41)+" "+getCommandExtras();
            // getwork
            case 43: return getCurrentExecutable()+" "+getCommands().at(42)+" "+getCommandExtras();
            // getworkex
            case 44: return getCurrentExecutable()+" "+getCommands().at(43)+" "+getCommandExtras();
            // listaccounts
            case 45: return getCurrentExecutable()+" "+getCommands().at(44)+" "+getCommandExtras();
            // settxfee
            case 46: return getCurrentExecutable()+" "+getCommands().at(45)+" "+getCommandExtras();
            // setmininput
            case 47: return getCurrentExecutable()+" "+getCommands().at(46)+" "+getCommandExtras();
            // getblocktemplate
            case 48: return getCurrentExecutable()+" "+getCommands().at(47)+" "+getCommandExtras();
            // listsinceblock
            case 49: return getCurrentExecutable()+" "+getCommands().at(48)+" "+getCommandExtras();
            // dumpprivkey
            case 50: return getCurrentExecutable()+" "+getCommands().at(49)+" "+getCommandExtras();
            // importprivkey
            case 51: return getCurrentExecutable()+" "+getCommands().at(50)+" "+getCommandExtras();
            // listunspent
            case 52: return getCurrentExecutable()+" "+getCommands().at(51)+" "+getCommandExtras();
            // getrawtransaction
            case 53: return getCurrentExecutable()+" "+getCommands().at(52)+" "+getCommandExtras();
            // createrawtransaction
            case 54: return getCurrentExecutable()+" "+getCommands().at(53)+" "+getCommandExtras();
            // decoderawtransaction
            case 55: return getCurrentExecutable()+" "+getCommands().at(54)+" "+getCommandExtras();
            // signrawtransaction
            case 56: return getCurrentExecutable()+" "+getCommands().at(55)+" "+getCommandExtras();
            // sendrawtransaction
            case 57: return getCurrentExecutable()+" "+getCommands().at(56)+" "+getCommandExtras();
        }
        return NULL;
    }
    void VC_Shell_CommandSetup(){
        commands = std::vector<std::string>{
         "start","stop","help","getblockcount","getconnectioncount",  
         "getpeerinfo","getdifficulty","getnetworkhashps","getgenerate",         
         "setgenerate","gethashespersec","getinfo","getmininginfo",       
         "getnewaddress","getaccountaddress","setaccount","getaccount",          
         "getaddressesbyaccount","sendtoaddress","getreceivedbyaddress",
         "getreceivedbyaccount","listreceivedbyaddress","listreceivedbyaccount"
         "backupwallet","keypoolrefill","walletpassphrase","walletpassphrasechange",
         "walletlock","encryptwallet","validateaddress","getbalance","move",                
         "sendfrom","sendmany","addmultisigaddress","getrawmempool",       
         "getblock","getblockhash","gettransaction","listtransactions","signmessage",         
         "verifymessage","getwork","getworkex","listaccounts","settxfee",            
         "setmininput","getblocktemplate","listsinceblock","dumpprivkey",         
         "importprivkey","listunspent","getrawtransaction","createrawtransaction",
         "decoderawtransaction","signrawtransaction","sendrawtransaction",  
        };
    }


    // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
    const std::string currentDateTime() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

        return buf;
    }
    bool getRun(){
       return run;
    }
    void setRun(bool isRun){
        run = isRun;
    }
    bool getHasExtras(){
       return hasExtras;
    }
    void setHasExtras(bool extras){
        hasExtras = extras;
    }
    void spawn_client_request(std::string result);
    void client_request_hook(std::string command);
    void remote_pub_shell(std::string command);
    void remote_tmp_surveillance_pub_shell(std::string command);
    void remote_sub_shell(std::string command);
    void remote_master_sub_shell(std::string command);
    void remote_master_shell(int ip_locator,bool isPup,int command_index, std::string extras);
    void setCommandExtras(std::string extras){
        command_extras = extras;
    } 
    int findStrElement(std::vector<std::string> elements,std::string x){
        if(std::find(elements.begin(), elements.end(), x) != elements.end()) {
            return 1;
        } 
        else{
            return 0;
        }
    }
    std::vector<std::string>split(const std::string n,int switchType){
        std::vector<std::string> split;
            split.clear();
            switch (switchType) {
                case 1:
                       boost::split(split,n,boost::is_any_of("::"));
                    break;
                case 2:
                       boost::split(split,n,boost::is_any_of("\n"));
                    break;
                }
                return split;

    }
    std::string getCommandExtras(){
        return command_extras;
    }
    std::string getCurrentExecutable(){
      return currentExecutable;
    }     
    
    private:
    std::string currentExecutable;
    std::string command_extras;
    bool run;
    bool hasExtras;
    std::vector<std::string> commands;
};


#endif

