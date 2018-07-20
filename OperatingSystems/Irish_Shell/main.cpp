// Molly Pierce (mpierce3) & Andrew Bub (abub) - oPAIRating Systems
// CSE 30341 PreProject2
// Feburary 8, 2018

#include <iostream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <vector>
#include <map>
#include <errno.h>
#include <zmq.hpp>
#include <csignal>
#include <time.h>
#include <chrono>
#include <thread>
#include <algorithm>
#include <fstream>
#include <stdlib.h>

using namespace std;

// Global Variables ----------------------------------------------------------------------------------------------------
map<string, int> signalMap; // maps signal names to their respective ints

vector <int> processTable; // vector of all active child processes

// ZMQ setup for level 2
zmq::context_t context (1);
zmq::socket_t socket (context, ZMQ_REP);

string output; // for sending results of program back to client via ZMQ

vector<string> myargs;
// Prototypes -----------------------------------------------------------------------------------------------------------
void runProgram(int level); // function that runs all requirements of level 1
void levelTwo(); // function that binds server/client for level 2
void bg(char *[], int); // function that forks and execs commands in the bg
void fg(vector<string>); // function that brings processes to fg, and waits for them to terminate
void list(); // function that lists all live child processes
void signal(vector<string>); // function that sends given signals to given processes
void stop(vector<string>); // function that acts as alias for SIGSTOP signal
void cont(vector<string>); // function that acts as alias for SIGCONT signal
void help(); // function that displays help menu for irish shell
void quit(); // function that exits the irish shell

// Main Execution -------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
	// fill the global map of signals to their respective ints
	signalMap["SIGHUP"] = 1;
	signalMap["SIGINT"] = 2;
	signalMap["SIGQUIT"] = 3;
	signalMap["SIGSTOP"] = 19;
	signalMap["SIGKILL"] = 9;
	signalMap["SIGALRM"] = 14;
	signalMap["SIGCONT"] = 18;

	if (argc > 1) {
		string first = argv[1];
		string second = argv[2];
		if (first == "-level" && second == "1") {
			runProgram(1); // run level 1
		}
		else if (first == "-level" && second == "2") {
			levelTwo(); // run level 2
		}

		else {
			cout << "Incorrect syntax: input ./irish -level # to run program" << endl;
		}

	}
	else {
		cout << "Not enough input arguments" << endl;
	}

	return 0;
}


// Functions -------------------------------------------------------------------------------------------------------------

void runProgram(int level) {
	if (level == 1) {
		cout << "welcome to irish." << endl;	

		int size = 0;
		string line; // variable for reading in each line of input
		string s; // variable for each individual string of each line
	
		while(getline(cin, line)) // read in line by line of stdin
		{
			size = 0;

			// separate line of stdin into its individual arguments
			istringstream iss(line);
			while(getline(iss, s, ' '))
			{
				myargs.push_back(s);
				size++;
			}

			char *args[size]; // new array for keeping track of arguments
			// read in command line arguments into new array, args

			for (int i = 0; i < size; i++) {
				s = myargs[i];
				args[i] = (char *)s.c_str(); // convert each argument to c string for exec command
			}
				args[size] = NULL; // terminates end of args


			if (myargs[0] == "bg") { // fork if 'bg' 
				bg(args, size);
			}
			else if(myargs[0] == "quit") {
				quit();
			}
			else if(myargs[0] == "help") { // display Help Menu
				help();
			}
			else if (myargs[0] == "list") { // list all live child processes
				list();
			}
			else if(myargs[0] == "fg") { // wait for bg process to terminate; collect return code
				fg(myargs);
			}
			else if(myargs[0] == "signal") { // signal process handling
				signal(myargs);
			}
			else if(myargs[0] == "stop") { // alias for signal PID SIGSTOP
				stop(myargs);
			}
			else if(myargs[0] == "continue") { // alias for signal PID SIGCONT
				cont(myargs);
			}
			else { // if user enters a command that is not in the help menu
				cout << "This command does not exist. See help for list of valid commands" << endl;
			}
		
			myargs.clear(); // clear vector for next cycle
		}
	}

	else if (level == 2) {
		output = "Welcome to irish.\n"; // level 2 output to send through zmq to client
	}
}

void bg(char *args[], int size)
{
	// Update args without 'bg'
	for (int i = 1; i < size + 1; i++) {
		args[i-1] = args[i];
	} 
	int rc = fork();
	int child_pid;
	if (rc < 0) {
		// error handling
		fprintf(stderr, "forked failed\n"); // fork failed
		exit(1); // exit
	}
	else if (rc == 0) {
		// child
		child_pid = (int) getpid();
		cout << "Process " << child_pid << " started in background" << endl;
		output = "Process " + to_string(child_pid) + " started in background\n";
		execvp(args[0], args); // goes out and runs command
		cout << "Command failed or does not exist. Process terminated" << endl;
		output = "Command failed or does not exist. Process terminated\n";
		kill(child_pid, 9); // won't get here unless exec failed
	}
	else {
		// parent
		child_pid = rc;
		output = "Process " + to_string(child_pid) + " started in background\n";
		processTable.push_back(child_pid);
	}

}

void fg(vector<string> myargs)
{
	int s = myargs.size();
	if(s > 1) // check that user gave a PID argument with input
	{
		s = processTable.size();
		for(int i = 0; i < s; i++) 
		{
			// check that given PID is valid
			if(processTable[i] == stoi(myargs[1]))
			{
				int rc = stoi(myargs[1]);
				pid_t id = wait(&rc); // wait for given process to terminate
				cout << "Process " << id << " terminated with return code " << rc << "." << endl;
				output = "Process " + to_string(id) + " terminated with return code " + to_string(rc) + ".\n";
				processTable.erase(processTable.begin() + i); // remove process from Process Table
				return;
			}
		}
		// if given PID is not valid
		cout << "Error: no such process" << endl;
		output = "Error: no such process\n";
	} else {
		cout << "ERROR: no process given to move to foreground" << endl;
		output = "ERROR: no process given to move to foreground\n";
	}
}

void list()
{
	// if no child processes	
	if (processTable.empty()) {
		cout << "No subprocesses" << endl;
		output.append("No subprocesses\n");
	}				
	// if there are child processes running
	else {
	int s = processTable.size();
	for (int i = 0; i < s; i++) {
		// format appropriate output
		cout << "(" << i+1 << ") ";
		output.append("(" + to_string(i+1) + ") ");

		// Determine state of each PID and output result
		siginfo_t status;
		status.si_pid = (pid_t)0;
		int result = waitid(P_PID, processTable[i], &status, WEXITED | WSTOPPED | WCONTINUED | WNOHANG | WNOWAIT);

		if (status.si_code == CLD_EXITED) { // exit status
			cout << "PID=" << processTable[i] << " State=Exited" << endl;
			output.append("PID=" + to_string(processTable[i]) + " State=Exited\n");
		}
		else if (status.si_code == CLD_KILLED) { // killed status 
			cout << "PID=" << processTable[i] << " State=Terminated" << endl;
			output.append("PID=" + to_string(processTable[i]) + " State=Terminated\n");
		}
		else if (status.si_code == CLD_STOPPED) { // stopped status
			cout << "PID=" << processTable[i] << " State=Stopped" << endl;
			output.append("PID=" + to_string(processTable[i]) + " State=Stopped\n");
		}
		else if (status.si_code == CLD_CONTINUED) { // continued status
			cout << "PID=" << processTable[i] << " State=Continued" << endl;
			output.append("PID=" + to_string(processTable[i]) + " State=Continued\n");
		}
		else if (result == 0) { // result will return 0 if process is still running
			cout << "PID=" << processTable[i] << " State=Running" << endl;
			output.append("PID=" + to_string(processTable[i]) + " State=Running\n");
		}
		else if(result == -1) { // error checking
			cout << "PID= " << processTable[i] << " ERROR" << endl;
			output.append("PID=" + to_string(processTable[i]) + " ERROR\n");
		}
	}
	}


}

void signal(vector<string> myargs)
{
	int s = myargs.size();
	if(s > 2) // check to make sure correct amount of input arguments
	{
		int sig = signalMap[myargs[2]];
		int result;

		switch(sig)
		{
			// SIGHUP
			case 1:		result = kill(stoi(myargs[1]), sig);
					if(result != 0)
					{
						cout << "Error while signaling the process: " << strerror(errno) << endl;
						output = "Error while signaling the process: Error " + to_string(errno) + "\n";
					} else {
						cout << "Process " << stoi(myargs[1]) << " sent " << sig << endl;
						output = "Process " + myargs[1] + " sent " + to_string(sig) + "\n";
					}
					break;
			// SIGINT
			case 2:		result = kill(stoi(myargs[1]), sig);
					if(result != 0)
					{
						cout << "Error while signaling the process: " << strerror(errno) << endl;
						output = "Error while signaling the process: Error " + to_string(errno);
					} else {
						cout << "Process " << stoi(myargs[1]) << " sent " << sig << endl;
						output = "Process " + myargs[1] + " sent " + to_string(sig) + "\n";
					}
					break;
			// SIGQUIT
			case 3:		result = kill(stoi(myargs[1]), sig);
					if(result != 0)
					{
						cout << "Error while signaling the process: " << strerror(errno) << endl;
						output = "Error while signaling the process: Error " + to_string(errno) + "\n";
					} else {
						cout << "Process " << stoi(myargs[1]) << " sent " << sig << endl;
						output = "Process " + myargs[1] + " sent " + to_string(sig) + "\n";
					}
					break;
			// SIGSTOP
			case 19:	result = kill(stoi(myargs[1]), sig);
					if(result != 0)
					{
						cout << "Error while signaling the process: " << strerror(errno) << endl;
						output = "Error while signaling the process: Error " + to_string(errno) + "\n";
					} else {
						cout << "Process " << stoi(myargs[1]) << " sent " << sig << endl;
						output = "Process " + myargs[1] + " sent " + to_string(sig) + "\n";
					}
					break;
			// SIGKILL
			case 9:		result = kill(stoi(myargs[1]), sig);
					if(result != 0)
					{
						cout << "Error while signaling the process: " << strerror(errno) << endl;
					} else {
						cout << "Process " << stoi(myargs[1]) << " sent " << sig << endl;
						output = "Process " + myargs[1] + " sent " + to_string(sig) + "\n";
					}
					break;
			// SIGALARM
			case 14:	result = kill(stoi(myargs[1]), sig);
					if(result != 0)
					{
						cout << "Error while signaling the process: " << strerror(errno) << endl;
						output = "Error while signaling the process: Error " + to_string(errno);
					} else {
						cout << "Process " << stoi(myargs[1]) << " sent " << sig << endl;
						output = "Process " + myargs[1] + " sent " + to_string(sig) + "\n";
					}
					break;
			// SIGCONT
			case 18:	result = kill(stoi(myargs[1]), sig);
					if(result != 0)
					{
						cout << "Error while signaling the process: " << strerror(errno) << endl;
						output = "Error while signaling the process: Error " + to_string(errno);
					} else {
						cout << "Process " << stoi(myargs[1]) << " sent " << sig << endl;
						output = "Process " + myargs[1] + " sent " + to_string(sig) + "\n";
					}
					break;
			// if not one of the above signals
			default:	cout << "Error: input signal not compatible" << endl;
					output = "Error: input signal not compatible\n";
					break;			
		}
	} else {
		cout << "Error: invalid input" << endl;
		output = "Error: invalid input\n";
	}
}

// stop function
void stop(vector<string> myargs)
{
	int s = myargs.size();
	if(s > 1)
	{
		int result = kill(stoi(myargs[1]), 19);
		if(result != 0)
		{
			cout << "Error while signaling the process: " << strerror(errno) << endl;
			output = "Error while signaling the process: Error " + to_string(errno) + "\n";
		} else {
			cout << "Process " << stoi(myargs[1]) << " sent 19" << endl;
			output = "Process " + myargs[1] + " sent 19\n";
		}
	} else {
		cout << "ERROR: no process given to stop" << endl;
		output = "ERROR: no process given to stop\n";
	}
}

// continue function
void cont(vector<string> myargs)
{
	int s = myargs.size();
	if(s > 1)
	{
		int result = kill(stoi(myargs[1]), 18);
		if(result != 0)
		{
			cout << "Error while signaling the process: " << strerror(errno) << endl;
			output = "Error while signaling the process: Error " + to_string(errno) + "\n";
		} else {
			cout << "Process " << stoi(myargs[1]) << " sent 18" << endl;
			output = "Process " + myargs[1] + " sent 18\n";
		}
	} else {
		cout << "ERROR: no process given to continue" << endl;
		output = "ERROR: no process given to continue\n";
	}
}

void help()
{
	cout << "----------------------------------------------- HELP MENU ----------------------------------------------------" << endl;
	cout << "bg <COMMAND>		execute external command asynchronously in the background." << endl;
	cout << "list			print a list of active child processes." << endl;
	cout << "fg <PID>		wait for previously running command in background to terminate and collect return code." << endl;
	cout << "signal <PID> <SIGNAL>	sinals process PID an arbitrary SIGNAL" << endl;
	cout << "stop <PID>		signals process PID to stop" << endl;
	cout << "continue <PID> 	signals process PID to continue" << endl;
	cout << "quit			exit irish shell" << endl;
	cout << "help			print help menu" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------" << endl;

	output = "----------------------------------------------- HELP MENU ----------------------------------------------------\n"
		 "bg <COMMAND>		execute external command asynchronously in the background.\n"
		 "list			print a list of active child processes.\n"
		 "fg <PID>		wait for previously running command in background to terminate and collect return code.\n"
		 "signal <PID> <SIGNAL>	sinals process PID an arbitrary SIGNAL\n"
		 "stop <PID>		signals process PID to stop\n"
		 "continue <PID> 	signals process PID to continue\n"
		 "quit			exit irish shell\n"
		 "help			print help menu\n"
		 "--------------------------------------------------------------------------------------------------------------\n";
}

void quit()
{
	cout << "Goodbye!" << endl;
	output = "Goodbye!\n";
	exit(EXIT_SUCCESS); // exit shell if "quit" command
}

// run level two program with ZMQ
void levelTwo() {
	socket.bind("tcp://*:60800");
	while (true) {
		zmq::message_t request;
		socket.recv (&request);
		string rqst  = string (static_cast<char*>(request.data()), request.size());
		cout << "> " << rqst << endl;
		int size = 0;
		string r, s;

	
		// separate line of stdin into its individual arguments
		istringstream iss(rqst);
		while(getline(iss, s, ' '))
		{
			myargs.push_back(s);
			size++;
		}
		char *args[size]; // new array for keeping track of arguments

		// read in command line arguments into new array, args
		for (int i = 0; i < size; i++) {
			s = myargs[i];
			args[i] = (char *)s.c_str();
		}
		args[size] = NULL; // terminates end of args


		if (myargs[0] == "bg") { // fork if 'bg' 
			bg(args, size);
			r = output;
		}
		else if(myargs[0] == "quit") {
			quit();
			r = output;
		}
		else if(myargs[0] == "help") { // display Help Menu
			help();
			r = output;
		}
		else if (myargs[0] == "list") { // list all live child processes
			int n = output.size();
			output.erase(0, n);
			list();
			r = output;
		}
		else if(myargs[0] == "fg") { // wait for bg process to terminate; collect return code
			fg(myargs);
			r = output;
		}
		else if(myargs[0] == "signal") { // signal process handling
			signal(myargs);
			r = output;
		}
		else if(myargs[0] == "stop") { // alias for signal PID SIGSTOP
			stop(myargs);
			r = output;
		}
		else if(myargs[0] == "continue") { // alias for signal PID SIGCONT
			cont(myargs);
			r = output;
		}
		else { // if user enters a command that is not in the help menu
			r = "This command does not exist. See help for list of valid commands\n";
		}

		int l;
		l = r.size();
		zmq::message_t reply (l+1);
		snprintf(static_cast<char*>(reply.data()), l+1, "%s", r.c_str());
		socket.send(reply);

		myargs.clear();
		
	}
}
