#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lengthUtils.h"
#include <stdlib.h>
#include <unistd.h>

char *name = "PATH";
char *path;

char command[100];
char arguments[100];

char commandList[20][20] = {"echo", "exit", "type", "cd"};
int commandArrayIndex;

char envPaths[8][40];

char fileLocation[100];

void echo(char echoArgrument[]);
void breakout();
void type(char typeArguments[]);
bool checkValue(char input[100]);
void separatePaths();
bool fileExist(char name[]);
void cd();

int main() {
    path = getenv(name);
    //printf("%s", path);
    separatePaths();
    printf("$ ");
    fflush(stdout);
    char input[100];

    while (1) {
        fgets(input, 100, stdin);
        input[strlen(input) - 1] = '\0';

        /*
        if (strcmp(input, "exit 0") == 0) {
            break;
        }*/


        if (checkValue(input)){
            switch(commandArrayIndex){
                case 0:
                    echo(arguments);
                    break;
                case 1:
                    breakout();
                    break;
                case 2:
                    type(arguments);
                    break;
                case 3:
                    chdir(arguments);
                    cd();
                    break;
                default:
                    printf("%s: not found:first \n", command);
                    break; 
            }

        }else{
            if(fileExist(command)){


                if (strcmp(fileLocation, "not real") == 0){
                    printf("%s: not found \n", command);
                }

                if (strlen(arguments) > 1){
                    char cmd[100];

                    snprintf(cmd, sizeof(cmd), "%s %s" , command, arguments);

                    system(cmd);

                }else{
                    system(command);
                }

            }else{
                printf("%s: not found\n", command);
            }

        }
            printf("$ ");
            fflush(stdout);
   }

    return 0;
}

void cd (){
    if (arguments[0] == '~'){
        char *home = getenv("HOME");
        chdir(home);

        
        char rest[sizeof(arguments)];

        for(int i = 1; i < ArrayLength(arguments); i++){
            rest[i-1] = arguments[i];
        }

        rest[sizeof(arguments)] = '\0';

        printf("rest: %s\n", rest);

        strcat(home, rest);
        chdir(home);
    }
}

void separatePaths(){
    int pathIndex = 0;
    int resetIndex = 0;

    for (int i = 0; i < strlen(path); i++) {
        if (path[i] == ':'){
            pathIndex++;
            resetIndex = 0;
            continue;
        }
        envPaths[pathIndex][resetIndex] = path[i];
        resetIndex++;
    }
}

void breakout(){
    exit(0);
}
void echo(char echoArgrument[]){
    printf("%s\n", echoArgrument);
}


bool fileExist(char name[10]){
    for(int i = 0; i < ArrayLength(envPaths); i++){
        FILE *file;
        char path[256];

        // Create the file path
        snprintf(path, sizeof(path), "%s/%s", envPaths[i], name);

        // Open the file
        file = fopen(path, "r");
        // Check if the file was successfully opened
        if (file == NULL) {
            strcpy(fileLocation, "not real");
        } else {
            strcpy(fileLocation, path);
            fclose(file);
        }

        // If the file was found, return true
        if (strcmp(fileLocation, "not real") != 0) {
            return true;
        }
    }
    // If the file was not found in any path, return false
    return false;
}

void type(char typeArguments[]){
    //get argument
    //check if arguments is in the command array
    //if yes, get index, copy the main switch
    //if no return -1
    

    int* commandIndex = malloc(4);

    for (int i = 0; i < ArrayLength(commandList); i++){
        if (strcmp(typeArguments, commandList[i]) == 0){
            *commandIndex = i;
            break;
        }else{
            *commandIndex = -1;
        }
    }

    printf("%d\n", *commandIndex);
    switch (*commandIndex) {

        case 0:
            printf("%s is a shell builtin\n", typeArguments);
            break;
        case 1:
            printf("%s is a shell builtin\n", typeArguments);
            break;
        case 2:
            break;
        default:
            if(fileExist(typeArguments)){
 

                if (strcmp(fileLocation, "not real") == 0){
                    printf("%s: not found\n", typeArguments);

                    break;

                }

                printf("%s is %s\n", typeArguments, fileLocation);
                break;

            }
            printf("%s: not found\n", typeArguments);
            break;

    }
    free(commandIndex);

}

bool checkValue(char input[100]){
    //split string but first space
    
    //command is first word
    //second is argument
    
    int commandIndex = 0;
    bool commandFound = false;
    int agrumentIndex = 0;

    for (int i = 0; i < strlen(input); i++) {
        
        if (input[i] == ' ' && !commandFound){
            commandFound = true;
        }else if (commandFound){
            arguments[agrumentIndex] = input[i];
            agrumentIndex++;
        }else{
            command[commandIndex] = input[i];
            commandIndex++;

        }
    }

    command[commandIndex] = '\0';
    arguments[agrumentIndex] = '\0';

    for (int i = 0; i < ArrayLength(commandList); i++) {
        if (strcmp(command, commandList[i]) ==0){
            commandArrayIndex = i;
            return true;
        }
    }
    
    return false;
}

