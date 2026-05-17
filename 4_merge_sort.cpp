#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void merge(vector<int>& arr, int low, int mid, int high) {

    vector<int> temp(high + 1);

    int i = low;
    int j = mid + 1;
    int k = low;

    while(i <= mid && j <= high) {

        if(arr[i] < arr[j]) {
            temp[k] = arr[i];
            i++;
        }
        else {
            temp[k] = arr[j];
            j++;
        }

        k++;
    }

    while(i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while(j <= high) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for(int i = low; i <= high; i++) {
        arr[i] = temp[i];
    }
}

void mergesort(vector<int>& arr, int low, int high) {

    if(low < high) {

        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergesort(arr, low, mid);

            #pragma omp section
            mergesort(arr, mid + 1, high);
        }

        merge(arr, low, mid, high);
    }
}

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

    mergesort(arr, 0, n - 1);

    cout << "\nAfter Sorting: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}