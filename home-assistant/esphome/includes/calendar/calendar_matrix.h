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

// Convert a date to Julian Day Number
long date_to_jdn(int year, int month, int day) {
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    long jdn = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    return jdn;
}

// Parse a date string "YYYY-MM-DD" and convert to integers
void parse_date(const char *date_str, int *year, int *month, int *day) {
    char date_copy[11]; // Buffer to hold a copy of the date string
    strncpy(date_copy, date_str, 10); // Make a copy of the date string
    date_copy[10] = '\0'; // Ensure null-termination
    
    char *token = strtok(date_copy, "-"); // Split the string by '-'
    if (token) {
        *year = atoi(token);
        token = strtok(NULL, "-");
        if (token) {
            *month = atoi(token);
            token = strtok(NULL, "-");
            if (token) {
                *day = atoi(token);
            }
        }
    }
}

// Calculate the difference in days between two dates given in "YYYY-MM-DD" format
int days_between_dates(const char *start_date, const char *end_date) {
    int start_year, start_month, start_day;
    int end_year, end_month, end_day;
    
    // Parse start date
    parse_date(start_date, &start_year, &start_month, &start_day);
    
    // Parse end date
    parse_date(end_date, &end_year, &end_month, &end_day);
    
    long start_jdn = date_to_jdn(start_year, start_month, start_day);
    long end_jdn = date_to_jdn(end_year, end_month, end_day);
    return (int)(end_jdn - start_jdn);
}