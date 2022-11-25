#include <stdio.h>

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

user_t scan_user(double, double, double, double, char[]);

int main(void)
{

    user_t our_user;
    user_t other_users[2];

    printf("Welcome to the GPS position calculator\n");

    return 0;
}

user_t scan_user(double lat, double lon, double alt, double time, char name[NAME_LEN])
{
    user_t returnUser = {lat, lon, alt, time, name}; // create the

    return returnUser;
}