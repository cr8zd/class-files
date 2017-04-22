/* Name: Jennifer Frase
   CSS 344 adventure game assignment
   creates a directory and stores 7 rooms which are randomly picked from 10
   possible rooms. They are each given at least 3 connections to other rooms
   where connections go both way. There is one start room, and one end room,
   the goal is to get from the start to the end by traversing through the
   rooms. The current room and the possible connections for that room are
   given on the console. The user types in a connection they want to go to,
   if the connection is valid they enter the room. When they enter the end
   room, the game is over and it will give the number of steps as well as
   the route taken.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

/* Room structure used to create the room files */
struct room{
	char* name;/* name of the room*/
	int used;/* says whether or not the room has already been created */
	int connections;/* counts the number of connections the room already has */
	int connected[7]; /* used if the room is picked for the layout to tell
	                     which rooms it is connect to */
};

struct room createLayout();
void play(struct room);

int main(){

    int procID = getpid(); /* get processId to make the file unique */
    char  idBuff[BUFSIZ]; /* create a string buffer to store the process Id as
                             a string in, since mkdir needs a string */
    int check; /* used to check if a file/folder was successfully made */
    char dirname[40] = "frasej.rooms."; /* stores the name of the new directory
                                           where room file will be created */
    srand(time(0));


    sprintf(idBuff, "%d", procID); /* change the integer process id into a string
                                      so mkdir can use it */
    strcat(dirname, idBuff); /* appends onto dirname the string version of the
                                process ID */
    check = mkdir(dirname, 0777); /* creates the directory and stores the return value
                               so that we can make sure it worked */

    /* check if mkdir worked, if not exit with an error */
    if (!check){
        chdir(dirname);
        struct room curRoom = createLayout(); /* create the layout/game files */
        play(curRoom); /* play the game ps. made this a seperate function in
                          order to allow for replaying */

    }
    else{
        printf("Unable to create directory\n");
        exit(1);
    }

    exit(0);
}

/* creates 7 room files with random ordering and connections
   returns the start room so that the program doesn't have to search for it */
struct room createLayout(){

    /* list of room names */
    char* roomNames[10] = {"beach", "mountain", "cave", "city", "ocean", "sunset",
                           "jungle", "arctic", "volcano", "village"};
    struct room rooms[10]; /* takes the room names and makes a room out of them
                              using the struct: allows the program to see if the
                              room name has already been used */
    int check; /* used to check if a file/folder was successfully made */
    int i, j; /* for loop variables */
    int arrIndex; /* used with randomly generated index */
    FILE* current; /* used to open/create files */
    struct room layout[7]; /* creates a layout array, which allows for easier
                              access of the rooms being used and referencing how
                              many connections are made */
    srand(time(0));

    /* generate the room structs */
    for(i = 0; i < 10; i++){
        rooms[i].name = roomNames[i];
        rooms[i].connections = 0;
        rooms[i].used = 0;
        for(j = 0; j < 7; j++){ rooms[i].connected[j] = 0; }
    }

    /* choose seven rooms and make the files */
    for(i = 0; i < 7; i++){
        check = 0;
        /* pick a random room and assign it to the layout array if the room has
           not been used already otherwise pick a different room*/
        do{
            arrIndex = rand() % 10; /* choose a random number from 0-9
                                       representing the indexes of the room
                                       names */
            if(!rooms[arrIndex].used){
                char fileName[15];
                strcpy(fileName, rooms[arrIndex].name); /* make the name of the
                                                    room the name of the file */
                strcat(fileName, ".room"); /* attach the .room so that it is
                                              mostly unique to this program */
                current = fopen(fileName, "w"); /* create the file and allow for
                                                writing so we can add content */

                /* if current wasn't able to open, exit */
                if(!current){
                    printf("Unable to open file %s\n", fileName);
                    exit(1);
                }

                /* add the name of the room to the file */
                fprintf(current, "ROOM NAME: %s\n", rooms[arrIndex].name);
                fclose(current);
                layout[i] = rooms[arrIndex];
                rooms[arrIndex].used = 1; /* mark that the room was used already */
                check = 1; /* mark that a file was created so can exit loop */
            }
        }while(!check);
    }


    /* for each of the rooms make at least 3 connections between rooms */
    for(i = 0; i < 7; i++){
        /* if a room already has 3 connections skip it */
        while(layout[i].connections < 3){
            layout[i].connected[i] = 1; /* mark the current room as not having
                                           access to itself */
            arrIndex = rand() % 7;

            /* if layout[i] room isn't already connected to layout[arrIndex],
               connect them */
            if(!layout[i].connected[arrIndex]){

                /* create the file names for the used rooms so that the files
                   can be appended to */
                char file1Name[15];
                strcpy(file1Name, layout[i].name);
                strcat(file1Name, ".room");
                char file2Name[15];
                strcpy(file2Name, layout[arrIndex].name);
                strcat(file2Name, ".room");

                /* mark the rooms connect array so that the room doesn't try
                   to connect to each other again*/
                layout[i].connected[arrIndex] = 1;
                layout[arrIndex].connected[i] = 1;
                /*increase the number of connections so that fprintf will print
                  the right connection number to the file and the while doesn't
                  become infinite*/
                layout[i].connections++;
                layout[arrIndex].connections++;

                /* open both files and append the connection */
                current = fopen(file1Name, "a");
                /* if current wasn't able to open, exit */
                if(!current){
                    printf("Unable to open file %s\n", file1Name);
                    exit(1);
                }
                fprintf(current, "CONNECTION %d: %s\n", layout[i].connections,
                        layout[arrIndex].name);
                fclose(current);
                current = fopen(file2Name, "a");
                /* if current wasn't able to open, exit */
                if(!current){
                    printf("Unable to open file %s\n", file2Name);
                    exit(1);
                }
                fprintf(current, "CONNECTION %d: %s\n", layout[arrIndex].connections,
                        layout[i].name);
                fclose(current);
            }
        }
    }

    /* append the room type to each file */
    for(i = 0; i < 7; i++){
        char fileName[15];
        strcpy(fileName, layout[i].name);
        strcat(fileName, ".room");
        current = fopen(fileName, "a");

        /* if current was able to open, exit */
        if(!current){
            printf("Unable to open file %s\n", fileName);
            exit(1);
        }

        /*append on the appropriate room type. Since the rooms were assigned
          to layout randomly, the first room picked is always the start and the
          last picked is always the end */
        if (i == 0)
            fprintf(current, "ROOM TYPE: START_ROOM\n");
        else if (i == 6)
            fprintf(current, "ROOM TYPE: END_ROOM\n");
        else
            fprintf(current, "ROOM TYPE: MID_ROOM\n");

        fclose(current);
    }

    return layout[0];
}

/* plays one round of the game based on the files in the current directory */
/* takes the start room as a parameter */
void play(struct room startRoom){
    int done = 0; /* bool to see if the end room is found so the game can end */
    int steps = -1; /* used to count the number of steps; the first room is not
                       counted so starts at -1 since it is incremented if the
                       file successfully opens */
    char pathThr[100]; /* storage for any successfully opened room name;
                          seperated by new line characters */
    char location[10]; /* storage for the name of the current file */
    char fileName[15]; /* takes the desired file to open (either from startRoom
                          or gets, and makes a file name out of it */
    char prevFileName[15]; /* stores the previously valid room file name;
                              if the end result of fileName doesn't exist, then
                              reverts to this */

    char posConnect[100]; /* stores the possible connections for the room */
    FILE* current; /* the currently open file */
    strcpy(fileName, startRoom.name); /* make the name of the start room the name
                                         of the file */


    do{
        int notFound = 1; /* used to test if a requested file is a possible connection */
        char* wordSt; /* used with strtok */
        strcpy(location, fileName); /* makes location the filename without the .room,
                                       so that if the file opens then the name of the
                                       room gets added to the pathThr */
        strcat(fileName, ".room"); /* attach the .room so that it is mostly unique to
                                      this program */
        current = fopen(fileName, "r"); /* create the file and allow for reading*/

        /* if steps is > 0, then make sure that the requested location is actually
           connected to the previous room */
        if(steps > 0){
            wordSt = strtok(posConnect, " ,");
            while( wordSt != NULL){
                /* found the requested room, so set notFound to false; ! symbol is used
                   because strcmp returns 0 if they are the same*/
                if(!strcmp(wordSt, location))
                    notFound = 0;
                wordSt = strtok(NULL, " ,");
            }
        }
        else
            notFound = 0;

        /* checks if current was opened, if not or the requested room isn't valid
           reverts to last valid file name */
        if(!current || notFound){
            printf("HUH? I DON\'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n", prevFileName);
            strcpy(fileName, prevFileName);
            current = fopen(fileName, "r"); /* create the file and allow for reading */
        }
        /* increment steps and if steps > 0, add the room name to pathThr */
        else{
            steps++;
            if(steps > 0){
                if(steps == 1)
                    strcpy(pathThr, location);
                else
                    strcat(pathThr, location);
                strcat(pathThr, "\n");
            }
        }

        strcpy(prevFileName, fileName);
        char line[100];

        /* get the name of the file*/
        fgets(line, 100, current);
        strtok(line, ":");
        wordSt = strtok(NULL, " :");
        strtok(wordSt, "\n");
        strcpy(location, wordSt);

        /* get the first connection and set posConnect to the room's name */
        fgets(line, 100, current);
        strtok(line, ":");
        wordSt = strtok(NULL, " :");
        strtok(wordSt, "\n");
        strcpy(posConnect, wordSt);
        fgets(line, 100, current);

        /* get the rest of the lines and print the appropriate response for the
           current room */
        do{
            strtok(line, ":");

            /* check if the first character of the line is a C, if so then the
               line is a connection, so strip it down to the room name and add
               it to posConnect */
            if(line[0] == 'C'){
                strcat(posConnect, ", ");
                wordSt = strtok(NULL, " :");
                strtok(wordSt, "\n");
                strcat(posConnect, wordSt);
            }
            else{
                strcat(posConnect, "."); /* don't have any more connections to add
                                            a '.' to posConnect */
                wordSt = strtok(NULL, " :"); /* get the type of the room */
                strtok(wordSt, "\n");

                /* if the room is the end room then print the results */
                if(wordSt[0] == 'E'){
                    done = 1;
                    printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
                    printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n%s", steps,
                           pathThr);
                }
                /* didn't find the end, so print the locations content and ask for a
                   new room to go to */
                else{
                    printf("CURRENT LOCATION: %s\n", location);
                    printf("POSSIBLE CONNECTIONS: %s\n", posConnect);
                    printf("WHERE TO? ");
                    gets(fileName);
                    printf("\n");
                }
            }
        }while(fgets(line, 100, current));

        fclose(current);
    }while(!done);
}
