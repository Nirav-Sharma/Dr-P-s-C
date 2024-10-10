#include <stdio.h>

// Define the months using an enum
typedef enum {
    January = 1, February, March, April, May, June, July, August, September, October, November, December
} Month;

// Define a struct for Date
typedef struct {
    Month month;
    int day;
} Date;

// Function to return the number of days in a month, assuming February has 28 days
int daysInMonth(Month month) {
    switch (month) {
        case January: case March: case May: case July: case August: case October: case December:
            return 31;
        case April: case June: case September: case November:
            return 30;
        case February:
            return 28;
        default:
            return 0;
    }
}
// Function to print the date
void printdate(Date date) {
    char *monthNames[] = { "", "January", "February", "March", "April", "May", "June",
                           "July", "August", "September", "October", "November", "December" };
    printf("%s %d\n", monthNames[date.month], date.day);
}

// Function to compute the next day
Date nextday(Date date) {
    // Check if the current day is the last day of the month
    if (date.day < daysInMonth(date.month)) {
        date.day += 1; // Increment the day
    } else {
        // Move to the next month
        if (date.month == December) {
            date.month = January; // Wrap around to January if it's December
        } else {
            date.month += 1;
        }
        date.day = 1; // Set the day to the first of the new month
    }
    return date;
}
int main() {
    Date today = {January, 31};
    printdate(today);
    // Get next day
    Date tomorrow = nextday(today);
    printdate(tomorrow);
    return 0;
}
