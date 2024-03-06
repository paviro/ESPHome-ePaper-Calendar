#include <stdio.h>
#include <string.h>

// Code from https://community.home-assistant.io/t/centering-text-when-using-multiple-printf/491205/14

std::array<int, 2> get_text_bounds(esphome::display::Display* it, esphome::font::Font *font, const char *buffer){
    int x1 = 0;     // A pointer to store the returned x coordinate of the upper left corner in. 
    int y1 = 0;     // A pointer to store the returned y coordinate of the upper left corner in.
    int width = 0;  // A pointer to store the returned text width in.
    int height = 0; // A pointer to store the returned text height in. 
    it->get_text_bounds(0, 0, buffer, font, TextAlign::BOTTOM_CENTER, &x1, &y1, &width, &height);
    return {width, height};
}

int get_text_width(esphome::display::Display* it, esphome::font::Font *font, const char* formatting, const char *raw_text){
    char temp_buffer[80];
    sprintf(temp_buffer, formatting, raw_text);
    return get_text_bounds(it, font, temp_buffer)[0];
}

int get_text_width(esphome::display::Display* it, esphome::font::Font *font, const char* formatting, const int raw_int){
    char temp_buffer[80];
    sprintf(temp_buffer, formatting, raw_int);
    return get_text_bounds(it, font, temp_buffer)[0];
}

int get_text_width(esphome::display::Display* it, esphome::font::Font *font, const char* formatting, const float raw_float){
    char temp_buffer[80];
    sprintf(temp_buffer, formatting, raw_float);
    return get_text_bounds(it, font, temp_buffer)[0];
}

// Calculate the width of time format
int get_text_width(esphome::display::Display* it, esphome::font::Font *font, const char* formatting, esphome::ESPTime time){
    auto c_tm = time.to_c_tm();
    size_t buffer_length = 80;
    char temp_buffer[buffer_length];
    strftime(temp_buffer, buffer_length, formatting, &c_tm);
    return get_text_bounds(it, font, temp_buffer)[0];
}

int get_text_height(esphome::display::Display* it, esphome::font::Font *font, const char* formatting, const char *raw_text){
    char temp_buffer[80];
    sprintf(temp_buffer, formatting, raw_text);
    return get_text_bounds(it, font, temp_buffer)[1];
}

int get_text_height(esphome::display::Display* it, esphome::font::Font *font, const char* formatting, const int raw_int){
    char temp_buffer[80];
    sprintf(temp_buffer, formatting, raw_int);
    return get_text_bounds(it, font, temp_buffer)[1];
}

int get_text_height(esphome::display::Display* it, esphome::font::Font *font, const char* formatting, const float raw_float){
    char temp_buffer[80];
    sprintf(temp_buffer, formatting, raw_float);
    return get_text_bounds(it, font, temp_buffer)[1];
}

// Calculate the width of time format
int get_text_height(esphome::display::Display* it, esphome::font::Font *font, const char* formatting, esphome::ESPTime time){
    auto c_tm = time.to_c_tm();
    size_t buffer_length = 80;
    char temp_buffer[buffer_length];
    strftime(temp_buffer, buffer_length, formatting, &c_tm);
    return get_text_bounds(it, font, temp_buffer)[1];
}

std::string extract_time(const char* datetime) {
    // Assume datetime is in the format "YYYY-MM-DDTHH:MM:SS+XX:XX"
    std::string datetimeStr(datetime);
    size_t pos = datetimeStr.find('T'); // Find the position of 'T' which separates date and time
    if (pos != std::string::npos && pos + 3 < datetimeStr.size()) {
        // Extract the time part after 'T'
        std::string timeStr = datetimeStr.substr(pos + 1, 5); // Assuming time format is "HH:MM"
        return timeStr;
    }
    return "";
}