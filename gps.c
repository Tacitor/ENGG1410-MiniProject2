#include <stdio.h>
#include <string.h>

#define NAME_LEN 100

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

int main(void)
{

    user_t our_user;
    user_t other_users[2];
    char inputFileAddress[100] = {'\0'}; // set the adress to delimeters

    printf("Welcome to the GPS position calculator\n");

    // get the data for our_user
    getOur_user(&our_user);

    getInputAdress(inputFileAddress);
    printf("Address: %s\n", inputFileAddress);

    return 0;
}

void getInputAdress(char *returnString)
{
    printf("\nPlease enter the file path of the file containing the other users:\n");
    scanf("%s", returnString);
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