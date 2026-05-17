#include <iostream>
#include <omp.h>

using namespace std;

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];

    cout << "Enter " << n << " elements: ";

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int sum = 0;
    int min = arr[0];
    int max = arr[0];

    // Sum
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++) {
        sum += arr[i];
    }

    // Minimum
    #pragma omp parallel for reduction(min:min)
    for(int i = 0; i < n; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }

    // Maximum
    #pragma omp parallel for reduction(max:max)
    for(int i = 0; i < n; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }

    float avg = (float)sum / n;

    cout << "\nSum = " << sum << endl;
    cout << "Minimum = " << min << endl;
    cout << "Maximum = " << max << endl;
    cout << "Average = " << avg << endl;

    return 0;
}