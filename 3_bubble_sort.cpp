#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter " << n << " elements: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "\nBefore Sorting: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    // Parallel Odd-Even Sort
    for(int i = 0; i < n; i++) {

        // Even phase
        #pragma omp parallel for
        for(int j = 0; j < n - 1; j += 2) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }

        // Odd phase
        #pragma omp parallel for
        for(int j = 1; j < n - 1; j += 2) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    cout << "\nAfter Sorting: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}