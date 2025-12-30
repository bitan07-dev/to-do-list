#include "functions.h"

#define filename "list.csv"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Enter valid arguements, run todo -s or todo --setup for initial setup\n"
               "OR run todo -h or todo --help for help\n");
        exit(1);
    }
    else if (argc >= 2) {
        char* flag = argv[1];
        if (!strcmp(flag,"-h") || !strcmp(flag,"--help")) {
            help();
        }
        else if (!strcmp(flag,"-s") || !strcmp(flag,"--setup")) {
            exit(setup(filename,1));
        }
        else if (!strcmp(flag,"-c") || !strcmp(flag,"--check")) {
            exit(check(filename));
        }
        else if (!strcmp(flag,"-a") || !strcmp(flag,"--add")) {
            char *work; 
            if (argc == 2) {
                do {
                    printf("Enter work to do:\n");
                    fgets(work,1024,stdin);
                } while (*work == '\n');
                work[strcspn(work, "\n")] = '\0';
            }
            else {
                strcpy(work,argv[2]);
            }
            exit(add(filename,work));
        }
        else if (!strcmp(flag,"-d") || !strcmp(flag,"--delete")) {
            int index; 
            if (argc == 2) {
                printf("Enter index to toggle:");
                if (scanf("%d",&index) == 0 || index <= 0) {
                    printf("Enter valid number!");
                    exit(1);
                }
            }
            else {
                index = atoi(argv[2]);
                if (index <= 0) {
                    printf("Enter valid number!");
                    exit(1);
                }
            }
            exit(del(filename,index));
        }
        else if (!strcmp(flag,"-t") || !strcmp(flag,"--toggle")) {
            int index; 
            if (argc == 2) {
                printf("Enter index to toggle:");
                if (scanf("%d",&index) == 0 || index <= 0) {
                    printf("Enter valid number!");
                    exit(1);
                }
            }
            else {
                index = atoi(argv[2]);
                if (index <= 0) {
                    printf("Enter valid number!");
                    exit(1);
                }
            }
            exit(toggle(filename,index));
        }
        else if (!strcmp(flag,"-r") || !strcmp(flag,"--clear")) {
            if (argc == 2) {
                printf("Do you want to CLEAR all data (Y/n): ");
                char choice = getchar();
                if (choice == 'Y' || choice == 'y') {
                    exit(clear(filename));
                }
            }
            else if (!strcmp(argv[2],"-y")){
                exit(clear(filename));
            }
            printf("Exitted without clearing!");
        }
    }
}