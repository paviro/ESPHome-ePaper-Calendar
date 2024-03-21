long parse_time_to_seconds(String time_string) {
    long seconds = 0; // Variable to store the total seconds
    int num_start = 0; // Start of the numeric part
    int num_end = 0;
    
    // Iterate over each character in the string to find where the numeric part ends
    for (num_end = 0; num_end < time_string.length(); num_end++) {
        if (!isDigit(time_string[num_end])) {
            break; // Non-digit found, break the loop
        }
    }
    
    // Extract the numeric part from the string
    long num = time_string.substring(num_start, num_end).toInt();
    
    // Determine the unit (h, min, s) and calculate the seconds accordingly
    if (time_string[num_end] == 'h') {
        seconds = num * 3600; // 1 hour = 3600 seconds
    } else if (time_string.substring(num_end).startsWith("min")) {
        seconds = num * 60; // 1 minute = 60 seconds
    } else if (time_string[num_end] == 's') {
        seconds = num; // Directly in seconds
    } else {
        // Since we use this function for converting the deep sleep string return a default
        seconds = 600;
        ESP_LOGD("parse_time_to_seconds", "Unrecognised time unit: Returning default of 600 seconds.");
    }
    
    return seconds;
}


long seconds_until_midnight(int current_hour, int current_minute, int current_second) {
    long total_seconds_day = 86400;
    long seconds_passed_today = (current_hour * 3600) + (current_minute * 60) + current_second;
    
    return total_seconds_day - seconds_passed_today;
}

long seconds_until_closest_event_end(unsigned long current_time, unsigned long event_end) {
    // Check if the event has already ended
    if (current_time >= event_end) {
        // Event has already ended
        return 0;
    } else {
        // Calculate and return the seconds until the event ends
        return event_end - current_time;
    }
}