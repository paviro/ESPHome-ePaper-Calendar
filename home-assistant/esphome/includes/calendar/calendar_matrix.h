#include <stdio.h>
#include <string.h>

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void get_calendar_matrix(int year, int month, char cal[7][7][3]) {
    // Determine the number of days in the month
    int days_in_month[] = {31, 28 + is_leap_year(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int num_days = days_in_month[month - 1];
    
    // Determine the day of the week for the first day of the month (using Zeller's Congruence)
    if (month < 3) {
        month = month + 12;
        year = year - 1;
    }
    int day_of_week = (1 + (13 * (month + 1)) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
    
    // Adjust day of week to start from 0 for Sunday
    day_of_week = (day_of_week + 5) % 7;
    
    // Fill in the weekdays
    char weekdays[7][3] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
    for (int i = 0; i < 7; i++) {
        strcpy(cal[0][i], weekdays[i]);
    }
    
    // Fill in the days
    int current_day = 1 - day_of_week; // Adjust the starting day of the month
    for (int week_num = 1; week_num < 7; week_num++) {
        for (int day_num = 0; day_num < 7; day_num++) {
            if (current_day > 0 && current_day <= num_days) {
                sprintf(cal[week_num][day_num], "%d", current_day); // Fill in the day
            } else {
                strcpy(cal[week_num][day_num], ""); // Empty string for days before the first day or after the last day
            }
            current_day++;
        }
    }
}