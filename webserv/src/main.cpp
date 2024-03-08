#include "../inc/Webserv.hpp"
#include "../inc/ServerManager.hpp"

void sigpipeHandle(int sig) { if(sig) {}}

int main(int argc, char **argv) 
{
	if (argc == 1 || argc == 2) {
		try 
		{
			std::string		config; 
			ConfigParser	cluster;
        	ServerManager 	master;
			signal(SIGPIPE, sigpipeHandle); 
		
			config = (argc == 1 ? "configs/default.conf" : argv[1]);
			cluster.createCluster(config); 
			
			master.setupServers(cluster.getServers()); 
			master.runServers();
		}
		catch (std::exception &e) { 
			std::cerr << e.what() << std::endl; 
			return (1);
		}
    }
    else 
	{
		Logger::logMsg(RED, CONSOLE_OUTPUT, "Error: wrong arguments"); 
		return (1); 
	}
    return (0);
}

