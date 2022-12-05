#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;
using time_stamp = time_point<system_clock, microseconds>;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int MergeSort(int arr[], int size, int kth) {
    sort(arr, arr + size);
    return arr[kth - 1];
}


int partition(int arr[], int left, int right);
int QuickSortIterative(int arr[], int low, int high, int kth) {
    if (kth > 0 && kth <= high - low + 1) {
        int position = partition(arr, low, high);
        if (position - low == kth - 1) {
            return arr[position];
            low = position + 1;
        }
        else if (position - low > kth - 1) {
            return QuickSortIterative(arr, low, position - 1, kth);
            high = position - 1;
        }
        else return QuickSortIterative(arr, position + 1, high, kth - position);
    }
    cout << "\nERROR in QuickSortIterative\n";
    return 0;
}
int QuickSortRecursive(int arr[], int left, int right, int kth) {
    if (kth > 0 && kth <= right - left + 1) {
        int position = partition(arr, left, right);
        if (position - left == kth - 1) return arr[position];
        else if (position - left > kth - 1) return QuickSortRecursive(arr, left, position - 1, kth);
        else return QuickSortRecursive(arr, position + 1, right, kth - position - 1 + left);
    }
    cout << "\nERROR in QuickSortRecursive\n";
    return 0;
}
int partition(int arr[], int left, int right) {
    int i = left;
    int g = arr[right];
    for (int h = left; h <= right - 1; h++) {
        if (arr[h] <= g) {
            swap(&arr[i], &arr[h]);
            i++;
        }
    }
    swap(&arr[i], &arr[right]);
    return i;
}


int partition(int arr[], int left, int right, int kth);
int findMedian(int arr[], int size) {
    sort(arr, arr + size);
    return arr[size/2];
}
int MMRecursive(int arr[], int left, int right, int kth) {
    if (kth > 0 && kth <= right - left + 1) {
        int i;
        int size = right - left + 1;
        int median[(10 + 4) / 5];
        for (i = 0; i < size / 10; i++) median[i] = findMedian(arr + left + i * 5, 10);
        if (i * 5 < size) {
            median[i] = findMedian(arr + left + i * 5, size % 10);
            i++;
        }

        int newMed = (i == 1) ? median[i - 1] : MMRecursive(median, 0, i - 1, i / 2);
        if (i == 1) newMed = median[i - 1];
        else newMed = MMRecursive(median, 0, i - 1, i / 2);

        int position = partition(arr, left, right, newMed);
        if (position - left == kth-1) return arr[position];
        if (position - left > kth-1) return MMRecursive(arr, left, position - 1, kth);
        return MMRecursive(arr, position + 1, right, kth - position - 1 + left);
    }
    cout << "\nERROR in MMRecursive\n";
    return 0;
}
int partition(int arr[], int left, int right, int kth) {
    int i;
    for (i = left; i < right; i++) if (arr[i] == kth) break;
    swap(&arr[i], &arr[right]);
    
    i = left;
    for (int g = left; g <= right - 1; g++) {
        if (arr[g] <= kth) {
            swap(&arr[i], &arr[g]);
            i++;
        }
    }
    swap(&arr[i], &arr[right]);
    return i;
}


double runAlgorithm() {
    int n[] = {10, 50, 100, 500, 1000};
    for (int n = 2; n <= sizeof(n); n++) {
        int k[] = {1, n / 4, n / 2, 3 * n / 4, n};
        int tests = sizeof(k);

        vector<double> durations;
        for (int i = 0; i < tests; i++) {
            cout << "k: " << k[i] << "\n";
            int arr[] = {4, 2, 7, 5, 8, 200, 6, 42, 9};
            int size = sizeof(arr) / sizeof(arr[0]);

            /*time_stamp start = time_point_cast<microseconds>(system_clock::now());

            MergeSort(arr, size, k[i]); //run algorithm dynamically instead of hard-coding

            time_stamp end = time_point_cast<microseconds>(system_clock::now());
            duration<double> elapsed_microseconds = end - start;

            durations.push_back(elapsed_microseconds.count());*/
            //cout << "Duration: " << elapsed_microseconds.count() << " microseconds" << "\n";
        }
        double sum = 0.0;
        for (int i = 0; i < tests; i++) sum += durations[i];
        double avg = sum / tests;
        cout << "Average Duration: " << avg << " microseconds" << "\n";
        return avg;
    }
    return 0.0;
}


int main() {
    while (true) {
        int arr[] = {4, 2, 7, 5, 8, 200, 6, 42, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int kth;
        cout << "Enter kth (or 0 to exit): ";
        cin >> kth;
        if (kth == 0) break;
        if (kth <= 0 || kth > size) cout << "Please choose an integer between 1 and " << size << " (Inclusive)\n";
        else {
            cout << "MergeSort ------------ kth smallest element: " << MergeSort(arr, size, kth) << "\n";
            cout << "QuickSortIterative --- kth smallest element: " << QuickSortIterative(arr, 0, size - 1, kth) << "\n";
            cout << "QuickSortRecursive --- kth smallest element: " << QuickSortRecursive(arr, 0, size - 1, kth) << "\n";
            cout << "MMRecursive ---------- kth smallest element: " << MMRecursive(arr, 0, size - 1, kth) << "\n";
        }
    }
    return 0;
}

//g++ -g Comparing-Sorting-Algorithms/sort.cpp -o a.out