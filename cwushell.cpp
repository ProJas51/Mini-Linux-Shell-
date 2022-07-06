// Kolby Miller 
// CS470 Lab 1 
// Mini Linux Shell 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream> 
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib> 
#include <cstring> 
#include <iostream>
#include <vector> 
#include <string> 



// max number of commands to be supported
#define MAXLIST 100
 
using namespace std; 

// method that splits strings into tokens separated by spaces 
void tokenString(string input, vector<string> &comm) { 

     string tempString = ""; 
     
     for (int i = 0; i < input.length(); ++i) { 

         if (input[i] == ' ') { 
             // vector.push_back adds a new element after the previously added element. reference can be found at: 
             // https://www.cplusplus.com/reference/vector/vector/push_back/
             comm.push_back(tempString); 
             tempString = ""; 
         }

         else { 
             tempString.push_back(input[i]); 
         }
     }

     comm.push_back(tempString); 
}

// helper method used for printing the vector string 
void printVector(vector<string> comm) { 

    for (int i = 0; i < comm.size(); ++i) { 
        cout << comm[i] << endl; 

    }
    cout << "\n"; 
}


int main() { 

    int exitCode = 0; 
    
    string line = ""; 
    // this default prompt will can be changed to a new prompt if commanded. 
    string defaultPrompt = "cwushell> "; 
    bool helpFlag = false; 
    bool isValid = true; 

    // the shell will run within a while loop until 'exit' command is inputted 
    while(isValid) { 
        // string vector to hold the command 
        vector<string> command; 
        cout << defaultPrompt; 
        // getline will take the input and store it into a string
        getline(cin, line); 
        //calls the tokenizer and splits the input into the command vector 
        tokenString(line, command); 

        // this exits the cwushell with the system command "exit" if "exit" is the typed command
        if (command[0] == "exit" || command[0] == "Exit") { 

            cout << "exiting shell with exit code: " << exitCode << endl; 
            // system command to terminate the shell 
            exit(0); 
             
        }

        // cpu switches
        
        else if (command[0] == "cpuinfo") { 

            string line; 
            // reads the cpuinfo file found on windows PCs 
            ifstream cpu_info("/proc/cpuinfo");

            
            if (command[1] == "-c" || command[1] == "-C") { 

                // this for loop grabs the specific information for the right switch 
                for (int i = 0; i < 8; i++) { 

                    getline(cpu_info, line);
                     
                }
                cout << line << endl;
            }

            else if (command[1] == "-n" || command[1] == "-N") { 

                     for (int i = 0; i < 13; i++) { 

                    getline(cpu_info, line);
                    
                }
                cout << line << endl; 

            }

            else if (command[1] == "-t" || command[1] == "-T") { 

                     for (int i = 0; i < 5; i++) { 

                    getline(cpu_info, line);
                    
                }
                cout << line << endl; 
            }


        }

        // meminfo switches 
        else if (command[0] == "meminfo") { 

            string line; 
            // reads the file for memory information found on Windows PCs 
            ifstream mem_info("/proc/meminfo");

            
            if (command[1] == "-t" || command[1] == "-T") { 

                for (int i = 0; i < 3; i++) { 

                    getline(mem_info, line);
                     
                }
                cout << line << endl;
            }

            else if (command[1] == "-u" || command[1] == "-U") { 

                     for (int i = 0; i < 12; i++) { 

                    getline(mem_info, line);
                     
                }
                cout << line << endl;
            }

            else if (command[1] == "-c" || command[1] == "-C") { 

                 for (int i = 0; i < 5; i++) { 

                    getline(mem_info, line);
                     
                }
                cout << line << endl;
            }


        }

        // opens up a help menu to give description of commands and what they do 
        else if (command[0] == "-help" || command[0] == "-Help" || command[0] == "-h" || command[0] == "-H") { 
            
            helpFlag = true; 

            while (helpFlag) { 

                system("man man");
                helpFlag = false;  
            }
                    
            
        }

        // if user writes 'prompt [user]', then the default prompt will be changed to the user inputed prompt,
        // or change back to default prompt if just 'prompt' is entered. 
        else if (command[0] == "prompt" || command[0] == "Prompt") { 

                if (command.size() == 1) { 

                    defaultPrompt = "cwushell> "; 

                }

                else { 
                    defaultPrompt = command[1];
                    defaultPrompt += "> ";  
                }
            

        }

        
        // prints out Linux System commands or displays error if command does not exist or is spelled wrong.
        else { 
            
            char char_arr[100]; 
            strcpy(char_arr, line.c_str()); 
            system(char_arr); 
            continue; 
        }
        


    }
    return exitCode; 

    
}