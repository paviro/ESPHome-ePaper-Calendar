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


long seconds_until_midnight(const esphome::ESPTime& time) {
    long total_seconds_day = 86400;
    long seconds_passed_today = (time.hour * 3600) + (time.minute * 60) + time.second;
    
    return total_seconds_day - seconds_passed_today;
}

long seconds_until_closest_event_end(const esphome::ESPTime& time, unsigned long event_end) {
    unsigned long current_time = time.timestamp;
    // Check if the event has already ended
    if (current_time >= event_end) {
        // Event has already ended
        return 0;
    } else {
        // Calculate and return the seconds until the event ends
        return event_end - current_time;
    }
}

long seconds_until_night_end(const esphome::ESPTime& time, int night_time_end) {
    long seconds_until_night_end = 0;

    if (time.hour < night_time_end) {
        // Before end of night today
        seconds_until_night_end = (night_time_end - time.hour - 1) * 3600 + (59 - time.minute) * 60 + (60 - time.second);
    } else {
        // After start of night, calculate time until night end next day
        seconds_until_night_end = ((24 - time.hour + night_time_end) - 1) * 3600 + (59 - time.minute) * 60 + (60 - time.second);
    }
    
    return seconds_until_night_end;
}