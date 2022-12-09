#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int MergeSort(vector<int> vec, int size, int kth) {
    sort(vec.begin(), vec.end());
    return vec[kth - 1];
}


int partition(vector<int> vec, int left, int right);
int QuickSortIterative(vector<int> vec, int low, int high, int kth) {
    if (kth > 0 && kth <= high - low + 1) {
        int position = partition(vec, low, high);
        if (position - low == kth - 1) {
            return vec[position];
            low = position + 1;
        }
        else if (position - low > kth - 1) {
            return QuickSortIterative(vec, low, position - 1, kth);
            high = position - 1;
        }
        else return QuickSortIterative(vec, position + 1, high, kth - position);
    }
    cout << "\nERROR in QuickSortIterative\n";
    return 0;
}
int QuickSortRecursive(vector<int> vec, int left, int right, int kth) {
    if (kth > 0 && kth <= right - left + 1) {
        int position = partition(vec, left, right);
        if (position - left == kth - 1) return vec[position];
        else if (position - left > kth - 1) return QuickSortRecursive(vec, left, position - 1, kth);
        else return QuickSortRecursive(vec, position + 1, right, kth - position - 1 + left);
    }
    cout << "\nERROR in QuickSortRecursive\n";
    return 0;
}
int partition(vector<int> vec, int left, int right) {
    int i = left;
    int g = vec[right];
    for (int h = left; h <= right - 1; h++) {
        if (vec[h] <= g) {
            swap(&vec[i], &vec[h]);
            i++;
        }
    }
    swap(&vec[i], &vec[right]);
    return i;
}


int partition(vector<int> vec, int left, int right, int kth);
int findMedian(vector<int> vec, int size) {
    sort(vec.begin(), vec.end());
    return vec[size/2];
}
int MMRecursive(vector<int> vec, int left, int right, int kth) {
    if (kth > 0 && kth <= right - left + 1) {
        int i;
        int size = right - left + 1;
        vector<int> median; //[(10 + 4) / 5]
        for (i = 0; i < size / 10; i++) {
            vector<int> temp;
            for (int k = left + i * 5; k < vec.size(); k++) temp.push_back(vec[k]);
            median[i] = findMedian(temp, 10);
        }
        if (i * 5 < size) {
            vector<int> temp;
            for (int k = left + i * 5; k < vec.size(); k++) temp.push_back(vec[k]);
            median[i] = findMedian(temp, size % 10);
            i++;
        }

        int newMed = (i == 1) ? median[i - 1] : MMRecursive(median, 0, i - 1, i / 2);
        if (i == 1) newMed = median[i - 1];
        else newMed = MMRecursive(median, 0, i - 1, i / 2);

        int position = partition(vec, left, right, newMed);
        if (position - left == kth-1) return vec[position];
        if (position - left > kth-1) return MMRecursive(vec, left, position - 1, kth);
        return MMRecursive(vec, position + 1, right, kth - position - 1 + left);
    }
    cout << "\nERROR in MMRecursive\n";
    return 0;
}
int partition(vector<int> vec, int left, int right, int kth) {
    int i;
    for (i = left; i < right; i++) if (vec[i] == kth) break;
    swap(&vec[i], &vec[right]);
    
    i = left;
    for (int g = left; g <= right - 1; g++) {
        if (vec[g] <= kth) {
            swap(&vec[i], &vec[g]);
            i++;
        }
    }
    swap(&vec[i], &vec[right]);
    return i;
}


void runAlgorithm1(int baseArr[]) {
    int ns[] = {10, 50, 100, 500, 1000};
    for (int n = 2; n <= sizeof(n); n++) {
        int k[] = {1, n / 4, n / 2, 3 * n / 4, n};
        int tests = sizeof(k);

        vector<double> durations;
        for (int i = 0; i < tests; i++) {
            cout << "k: " << k[i] << "\n";
            vector<int> vec;
            for (int i = 0; i < sizeof(baseArr); i++) vec.push_back(baseArr[i]); //Fill vector with values from initial array
            int size = sizeof(vec) / sizeof(vec[0]);

            uint64_t start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            cout << "MergeSort ------------ kth smallest element: " << MergeSort(vec, size, k[i]) << "\n";
            uint64_t end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            long long elapsed_microseconds = end - start;
            
            cout << "time: " << elapsed_microseconds << " \n";
        }
        double sum = 0.0;
        for (int i = 0; i < tests; i++) sum += durations[i];
        double avg = sum / tests;
        cout << "Average Duration: " << avg << " microseconds" << "\n";
    }
}
void runAlgorithm2(int baseArr[]) {
    int ns[] = {10, 50, 100, 500, 1000};
    for (int n = 2; n <= sizeof(n); n++) {
        int k[] = {1, n / 4, n / 2, 3 * n / 4, n};
        int tests = sizeof(k);

        vector<double> durations;
        for (int i = 0; i < tests; i++) {
            cout << "k: " << k[i] << "\n";
            vector<int> vec;
            for (int i = 0; i < sizeof(baseArr); i++) vec.push_back(baseArr[i]); //Fill vector with values from initial array
            int size = sizeof(vec) / sizeof(vec[0]);

            uint64_t start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            cout << "QuickSortIterative --- kth smallest element: " << QuickSortIterative(vec, 0, size - 1, k[i]) << "\n";
            uint64_t end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            long long elapsed_microseconds = end - start;
            
            cout << "time: " << elapsed_microseconds << " \n";
        }
        double sum = 0.0;
        for (int i = 0; i < tests; i++) sum += durations[i];
        double avg = sum / tests;
        cout << "Average Duration: " << avg << " microseconds" << "\n";
    }
}
void runAlgorithm3(int baseArr[]) {
    int ns[] = {10, 50, 100, 500, 1000};
    for (int n = 2; n <= sizeof(n); n++) {
        int k[] = {1, n / 4, n / 2, 3 * n / 4, n};
        int tests = sizeof(k);

        vector<double> durations;
        for (int i = 0; i < tests; i++) {
            cout << "k: " << k[i] << "\n";
            vector<int> vec;
            for (int i = 0; i < sizeof(baseArr); i++) vec.push_back(baseArr[i]); //Fill vector with values from initial array
            int size = sizeof(vec) / sizeof(vec[0]);

            uint64_t start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            cout << "QuickSortRecursive --- kth smallest element: " << QuickSortRecursive(vec, 0, size - 1, k[i]) << "\n";
            uint64_t end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            long long elapsed_microseconds = end - start;
            
            cout << "time: " << elapsed_microseconds << " \n";
        }
        double sum = 0.0;
        for (int i = 0; i < tests; i++) sum += durations[i];
        double avg = sum / tests;
        cout << "Average Duration: " << avg << " microseconds" << "\n";
    }
}
void runAlgorithm4(int baseArr[]) {
    int ns[] = {10, 50, 100, 500, 1000};
    for (int n = 2; n <= sizeof(n); n++) {
        int k[] = {1, n / 4, n / 2, 3 * n / 4, n};
        int tests = sizeof(k);

        vector<double> durations;
        for (int i = 0; i < tests; i++) {
            cout << "k: " << k[i] << "\n";
            vector<int> vec;
            for (int i = 0; i < sizeof(baseArr); i++) vec.push_back(baseArr[i]); //Fill vector with values from initial array
            int size = sizeof(vec) / sizeof(vec[0]);

            uint64_t start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            cout << "MMRecursive ---------- kth smallest element: " << MMRecursive(vec, 0, size - 1, k[i]) << "\n";
            uint64_t end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            long long elapsed_microseconds = end - start;
            
            cout << "time: " << elapsed_microseconds << " \n";
        }
        double sum = 0.0;
        for (int i = 0; i < tests; i++) sum += durations[i];
        double avg = sum / tests;
        cout << "Average Duration: " << avg << " microseconds" << "\n";
    }
}


int main() {
    while (true) {
        int arr[5000];
        for (int i = 0; i < 5000; i++) arr[i] = 5000 - i; //Fill initial array
        /*int size = sizeof(arr) / sizeof(arr[0]);
        int kth;*/
        runAlgorithm1(arr);
        runAlgorithm2(arr);
        runAlgorithm3(arr);
        runAlgorithm4(arr);
        /*cout << "Enter kth (or 0 to exit): ";
        cin >> kth;
        if (kth == 0) break;
        if (kth <= 0 || kth > size) cout << "Please choose an integer between 1 and " << size << " (Inclusive)\n";
        else {
            cout << "MergeSort ------------ kth smallest element: " << MergeSort(arr, size, kth) << "\n";
            cout << "QuickSortIterative --- kth smallest element: " << QuickSortIterative(arr, 0, size - 1, kth) << "\n";
            cout << "QuickSortRecursive --- kth smallest element: " << QuickSortRecursive(arr, 0, size - 1, kth) << "\n";
            cout << "MMRecursive ---------- kth smallest element: " << MMRecursive(arr, 0, size - 1, kth) << "\n";
        }*/
    }
    return 0;
}