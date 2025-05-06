#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void displayArray(const vector<int>& nums) {
    cout << "Array: [ ";
    for (int x : nums) cout << x << " ";
    cout << "]" << endl;
}

void bubbleSort(vector<int>& nums) {
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        #pragma omp parallel for
        for (int j = 0; j < n - 1 - i; j++) {
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "\nParallel Bubble Sort:" << endl;
    cout << "Before Sorting: ";
    displayArray(nums);

    bubbleSort(nums);

    cout << "After Sorting: ";
    displayArray(nums);

    return 0;
}