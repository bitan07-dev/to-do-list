#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXLINE 1024

typedef struct{
    char *work;
    char time[20];
    char status[8];
} todo;

todo recieve(char *data) {
    todo job;
    job.work = strtok(data,",");
    strcpy(job.time,strtok(NULL,","));
    strcpy(job.status,strtok(NULL,","));
    return job;
}

void help() {
    printf("-h or --help\n\tDisplay help text and exit\n"
           "-s or --setup\n\tRun initial setup and exit\n"
           "-c or --check\n\tDisplay current list and exit\n"
           "-a \e[4m\"work\"\e[0m or --add \e[4m\"work\"\e[0m\n\tAdd new work to do and exit\n"
           "-d \e[4mindex\e[0m or --delete \e[4mindex\e[0m\n\tdelete a work on index provided and exit\n"
           "-t \e[4mindex\e[0m or --toggle \e[4mindex\e[0m\n\ttoggle a work as done or pending on index provided and exit\n"
           "-r or --clear\n\tClears current list after confirmation (use -y to bypass) and exit\n");
}

int setup(char* filename,int flag) {
    if (flag) {
        FILE *chk = fopen(filename,"r");
        if (chk != NULL) {
            printf("File already exists no need to create again\n");
            fclose(chk);
            return 1;
        }
    }
    FILE *fptr = fopen(filename,"w");
    fclose(fptr);
    printf("File succesfully created\n");
    return 0;
}


int check(char* filename) {
    FILE *fptr = fopen(filename,"r");
    if (fptr == NULL) {
        printf("File does not exist, run todo -s or todo --setup\n");
        fclose(fptr);
        return 1;
    }
    char data[MAXLINE];
    int index = 1;
    printf("=Sl.no= | =======================Work======================= | =======Time======== | =Status=\n");
    while (fgets(data, MAXLINE,fptr) != NULL) {
        todo job = recieve(data);
        printf(" %3d   | %-50s | %s | %8s", index++, job.work, job.time, job.status);
    }
    if (index == 1) {
        printf("EMPTY");
    }
    fclose(fptr);
    return 0;
}

int add(char* filename, char* work) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    todo new_job;
    new_job.work = work;
    strftime(new_job.time, 20, "%d/%m/%Y-%H:%M:%S", t);
    strcpy(new_job.status,"Pending");
    FILE *fptr = fopen(filename,"a");
    if (fptr == NULL) {
        printf("ERROR running program\\n");
        fclose(fptr);
        return 1;
    }
    fprintf(fptr,"%s,%s,%s\n",new_job.work,new_job.time,new_job.status);
    return 0;
}

int del(char* filename, int index) {
    FILE *fptr = fopen(filename,"r");
    FILE *fptrTemp = fopen("temp.csv","w");
    if (fptr == NULL) {
        printf("File does not exist, run todo -s or todo --setup\n");
        fclose(fptr);
        return 1;
    }
    int currentLine = 1;
    char data[MAXLINE];
    while (fgets(data, MAXLINE,fptr) != NULL) {
        if (currentLine++ != index) {
            fprintf(fptrTemp,data);
        }
        else {
            todo job = recieve(data);
            printf("Deleting... || %d | %s | %s | %s", index, job.work, job.time, job.status);
        }
    }
    if (currentLine <= index) {
        printf("Element at index %d doensn't exist\n",index);
        return 1;
    }
    fclose(fptr);
    fclose(fptrTemp);
    remove(filename);
    rename("temp.csv",filename);
    return 0;
}
int toggle(char* filename, int index) {
    FILE *fptr = fopen(filename,"r");
    FILE *fptrTemp = fopen("temp.csv","w");
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    if (fptr == NULL) {
        printf("File does not exist, run todo -s or todo --setup\n");
        fclose(fptr);
        return 1;
    }
    int currentLine = 1;
    char data[MAXLINE];
    while (fgets(data, MAXLINE,fptr) != NULL) {
        if (currentLine++ != index) {
            fprintf(fptrTemp,data);
        }
        else {
            todo job = recieve(data);
            if (strcmp(job.status,"Pending")) {
                printf("Marking as Done... ");
                strcpy(job.status,"Done");
            }
            else {
                printf("Marking as Pending... ");
                strcpy(job.status,"Pending");
            }
            printf("|| %d | %s ||\n", index, job.work);
            strftime(job.time, 20, "%d/%m/%Y-%H:%M:%S", t);
            fprintf(fptrTemp,"%s,%s,%s\n",job.work,job.time,job.status);
        }
    }
    if (currentLine <= index) {
        printf("Element at index %d doensn't exist\n",index);
        return 1;
    }
    fclose(fptr);
    fclose(fptrTemp);
    remove(filename);
    rename("temp.csv",filename);
    return 0;
}

int clear(char* filename) {
    FILE *fptr = fopen(filename,"w");
    if (fptr == NULL) {
        printf("Error clearing!");
        return 1;
    }
    fclose(fptr);
    return 0;
}