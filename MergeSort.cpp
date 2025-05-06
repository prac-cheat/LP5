#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void displayArray(const vector<int>& nums) {
    cout << "Array: [ ";
    for (int x : nums) {
        cout << x << " ";
    }
    cout << "]" << endl;
}

void merge(vector<int>& nums, int left, int mid, int right) {
    int n = right - left + 1;
    vector<int> temp(n);
    
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        temp[k++] = (nums[i] <= nums[j]) ? nums[i++] : nums[j++];
    }
    while (i <= mid) temp[k++] = nums[i++];
    while (j <= right) temp[k++] = nums[j++];

    for (int i = 0; i < n; i++) {
        nums[left + i] = temp[i];
    }
}

void mergeSort(vector<int>& nums, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(nums, left, mid);
            
            #pragma omp section
            mergeSort(nums, mid + 1, right);
        }
        
        merge(nums, left, mid, right);
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "\nParallel Merge Sort:" << endl;
    cout << "Before Sorting: ";
    displayArray(nums);

    mergeSort(nums, 0, n - 1);

    cout << "After Sorting: ";
    displayArray(nums);

    return 0;
}