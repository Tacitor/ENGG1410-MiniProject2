#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define NAME_LEN 100
#define ADDRESS_LEN 200

/**
 * A Struct that hold almost everything needed for traking a user.
 */
typedef struct user
{
    double latitude;
    double longitude;
    double altitude;
    double time;
    char name[NAME_LEN];
} user_t;

/**
 * A Struct that holds the name of another user. And the distance to the main user (our_user)
 */
typedef struct distToUser
{
    char name[NAME_LEN];
    double dist;
} distToUser_t;

user_t scan_user(double, double, double, double, char *);
void getOur_user(user_t *);
void getInputAdress(char *);
int getNumberOtherUsers(char[]);
void populateOtherUsers(char[], int, user_t[]);
void calcDistances(user_t, int, user_t[], distToUser_t[]);

int main(void)
{

    user_t our_user;
    int numOtherUser;                            // the number of other users
    char inputFileAddress[ADDRESS_LEN] = {'\0'}; // set the adress to delimeters

    printf("Welcome to the GPS position calculator\n");

    // get the address of the file that has the other user data in it
    getInputAdress(inputFileAddress);

    // get the data for our_user
    getOur_user(&our_user);

    // open and read the file. Populate the number of of users in the file
    numOtherUser = getNumberOtherUsers(inputFileAddress);

    // setup the array for the other users
    user_t other_users[numOtherUser];
    // the array for the distances
    distToUser_t other_user_dists[numOtherUser];

    populateOtherUsers(inputFileAddress, numOtherUser, other_users);

    // debug and print off the users
    // for (int i = 0; i < numOtherUser; i++)
    // {
    //     printf("\nName: %s\nTime: %.0lf\nLat: %lg\nLong: %lg\nAlt: %lg\n", other_users[i].name, other_users[i].time, other_users[i].latitude, other_users[i].longitude, other_users[i].altitude);
    // }

    // get the distances
    calcDistances(our_user, numOtherUser, other_users, other_user_dists);

    return 0;
}

/**
 * Loop through the given array of structs, extract the position data and calculates the distance to out_user. Then is stores this distance in a new array of structs.
 */
void calcDistances(user_t our_user, int numOtherUsers, user_t otherUsers[numOtherUsers], distToUser_t other_user_dists[numOtherUsers])
{
    // local copies of the positions
    double lat = our_user.latitude, lon = our_user.longitude, alt = our_user.altitude;

    // loop through
    for (int i = 0; i < numOtherUsers; i++)
    {
        // calc the distance and save it
        other_user_dists[i].dist = sqrt(pow((lat - otherUsers[i].latitude), 2) + pow((lon - otherUsers[i].longitude), 2) + pow((alt - otherUsers[i].altitude), 2));
        // populate the name while we are here
        strcpy(other_user_dists[i].name, otherUsers[i].name);
    }
}

/**
 * Loop through a formatted data file that contains data entries for the GPS data of multiple other users.
 */
void populateOtherUsers(char address[ADDRESS_LEN], int numUsers, user_t other_users[numUsers])
{
    // make the file pointer
    FILE *dataFile = NULL;
    char fromFile_s[NAME_LEN]; // give it the max name length just in case

    // vars used in populating the array and making the structs
    char name[NAME_LEN];
    double time, lat, lon, alt;

    // try to open the file
    dataFile = fopen(address, "r");

    // check if it worked
    if (dataFile == NULL)
    {
        printf("\nERROR: FAILED to open the specified file while populating the array of other users\n");
    }
    else
    {
        // skip the first line
        fscanf(dataFile, "%*s");

        // loop through as many times as there are other users
        for (int i = 0; i < numUsers; i++)
        {
            // read the name
            fscanf(dataFile, "%s", name);
            // read the time
            fscanf(dataFile, "%lf", &time);
            // read the latitude
            fscanf(dataFile, "%lf", &lat);
            // read the longitude
            fscanf(dataFile, "%lf", &lon);
            // read the altitude
            fscanf(dataFile, "%lf", &alt);

            // add it to the other_users array
            other_users[i] = scan_user(lat, lon, alt, time, name);
        }
    }

    fclose(dataFile);
}

/**
 * Read the first line of a data file. This first line contains the number of entries following. Return said number.
 */
int getNumberOtherUsers(char address[ADDRESS_LEN]) // "Other Users/sample_users.txt"
{
    // make the file pointer
    FILE *dataFile = NULL;
    char fromFile;
    int numUser = -1;

    // try to open the file
    dataFile = fopen(address, "r");

    // check if it worked
    if (dataFile == NULL)
    {
        printf("\nERROR: FAILED to open the specified file while counting the number of users\n");
    }
    else
    {
        numUser = 0;                // reset to 0 now that we file confimed to work
        fromFile = fgetc(dataFile); // grab the first char

        // loop until the end of the first line
        while ((fromFile > 47 && fromFile < 58))
        {
            // sum it
            numUser += (fromFile - '0');

            fromFile = fgetc(dataFile); // update the char for the next iteration
            // shift over the decimal for the next iteration
            numUser *= 10;
        }

        // shift the decimal back once
        numUser /= 10;
    }

    fclose(dataFile);

    return numUser;
}

/**
 * Collect an file path from the user
 */
void getInputAdress(char *returnString)
{
    printf("\nPlease enter the file path of the file containing the other users:\n");
    fgets(returnString, ADDRESS_LEN, stdin);

    // take the linefeed off the end of the string
    returnString[strlen(returnString) - 1] = '\0';
}

/**
 * Prompt the user for input from the cli about their position, name, and time.
 */
void getOur_user(user_t *our_user)
{
    double lat, lon, alt, time;
    char name[NAME_LEN];

    printf("\nPlease enter your name: ");
    scanf("%s", &name);

    printf("Please enter your position (latitude, longitude, altitude): ");
    scanf("%lf, %lf, %lf", &lat, &lon, &alt);

    printf("Please enter your time in nano seconds: ");
    scanf("%lf", &time);

    // debug the user input
    printf("First Hi %s! Your position is (%lf, %lf, %lf) at %lf nanoseconds.\n", name, lat, lon, alt, time);

    // fill the struct
    *our_user = scan_user(lat, lon, alt, time, name);
}

user_t scan_user(double lat, double lon, double alt, double time, char *name)
{
    user_t returnUser = {lat, lon, alt, time, "\0"}; // create the struct
    strcpy(returnUser.name, name);

    return returnUser;
}