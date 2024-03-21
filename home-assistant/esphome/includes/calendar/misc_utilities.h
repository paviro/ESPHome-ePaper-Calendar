int find_max_in_array(int arr[], int size) {
    int max_value = arr[0];
    
    for(int i = 1; i < size; i++) {
        if(arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    
    return max_value;
}

long find_non_zero_min_in_array(long arr[], int size) {
    long min_value = 0;
    
    for(int i = 0; i < size; i++) {
        if(arr[i] > 0 && (min_value == 0 || arr[i] < min_value)) {
            min_value = arr[i];
        }
    }
    
    return min_value;
}