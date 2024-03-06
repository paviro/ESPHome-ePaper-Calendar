# Dictionary to map calendar keys to their corresponding names
# One word calandars don't need to be added calendar.jobs would map to Jobs by default without adding it here
# calendar.hello_world should be added on the other hand
CALENDAR_NAMES = {"calendar.x": "X", "calendar.Y": "Y"}
# Day names (which are displayed in the calendar event list) can be translated here if required
DAY_NAMES = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]
# How many entries to send to the ESPHome device
MAX_ENTRIES = 8

def convert_calendar_format(data):
    # Initialize a dictionary to store events grouped by date
    events_by_date = {}
    entrie_count = 0
    
    # Iterate through calendar keys and events
    for calendar_key, events_list in data.items():
        for event in events_list['events']:
            if 'description' in event:
                event.pop('description')
                
            # Extract date from start time
            event_date = event['start'].split("T")[0]
            
            # Add calendar name to event
            # If calendar key exists in CALENDAR_NAMES, use its value, otherwise capitalize the second part of the key
            event['calendar_name'] = CALENDAR_NAMES.get(calendar_key, calendar_key.split(".")[1].capitalize())
            
            # Parse location_name and location_address
            if 'location' in event:
                # Split the 'location' string into lines based on the newline character
                location_lines = event['location'].split('\n')
                if len(location_lines) >= 2:
                    # If there are at least two lines, consider the first line as 'location_name' and the second line as 'location_address'
                    event['location_name'] = location_lines[0]
                    # event['location_address'] = location_lines[1]
                elif len(location_lines) == 1:
                    # If there's only one line, consider it as 'location_name'
                    event['location_name'] = location_lines[0]
                    
                # Remove the 'location' key from the event since it's been parsed into 'location_name' and 'location_address'
                event.pop('location')
                    
            # Add event to events_by_date dictionary
            if event_date in events_by_date:
                events_by_date[event_date].append(event)
            else:
                events_by_date[event_date] = [event]
                
    # Sort events by date
    sorted_dates = sorted(events_by_date.keys())
    
    # Initialize a list to store the final date objects
    result = []
    
    # Iterate through sorted dates
    for date in sorted_dates:
        all_day_events = []
        other_events = []
        for event in events_by_date[date]:
            if entrie_count == MAX_ENTRIES:
                break
            
            # Check if the event lasts for the whole day
            start_date = event['start']
            end_date = event['end']
            if 'T' not in event['start']:
                all_day_events.append(event)
            else:
                other_events.append(event)
                
            entrie_count = entrie_count + 1
            
        if all_day_events or other_events:
            # Sort other_events by start time
            other_events.sort(key=lambda item:dt_util.parse_datetime(item['start']), reverse=False)
            
            # Construct dictionary for the date
            # is_today cast to int because a bool somehow crashes my esphome config
            day_item = {
                'date': date,
                'day': dt_util.parse_datetime(date).day,
                'is_today': int(date == dt_util.now().isoformat().split("T")[0]),
                'day_name': DAY_NAMES[dt_util.parse_datetime(date).weekday()],
                'all_day': all_day_events,
                'other': other_events
            }
            result.append(day_item)
        
    return result

# Access the data received from the Home Assistant service call
input_data = data["calendar"]

# Convert the received data into the format expected by the epaper display
calendar_entries = convert_calendar_format(input_data)

# Pass the output back to Home Assistant
output["entries"] = calendar_entries