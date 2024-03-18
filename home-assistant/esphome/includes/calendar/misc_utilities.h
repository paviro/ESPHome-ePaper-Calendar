int find_max_in_array(int arr[], int size) {
    int max_value = arr[0];
    
    for(int i = 1; i < size; i++) {
        if(arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    
    return max_value;
}