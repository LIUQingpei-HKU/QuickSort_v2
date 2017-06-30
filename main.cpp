#include <iostream>
#include <algorithm>
#include "MergeSort.h"
#include "SortTestHelper.h"

using namespace std;

template<typename T>
int __partition(T arr[], int l,int r){
    swap(arr[l],arr[rand()%(r-l+1)+l]);

    T v = arr[l];

    //arr[l+1...j]<v;arr[j+1...i)>v
    int j=l;
    for(int i=l+1;i<=r;i++){
        if(arr[i]<v){
            swap(arr[j+1],arr[i]);
            j++;
        }
    }
    swap(arr[l],arr[j]);
    return j;
}

template <typename T>
void __quickSort(T arr[], int l, int r){
//    if(l>=r)
//        return;
    if(r-l<=15){
        insertionSort(arr,l,r);
        return;
    }
    int p = __partition(arr,l,r);
    __quickSort(arr, l,p-1);
    __quickSort(arr,p+1,r);

}

template <typename T>
void quickSort(T arr[], int n){
    srand(time(NULL));
    __quickSort(arr,0,n-1);
}

int main(){
    int n = 1000000;

    // 测试1 一般性测试
    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int* arr1 = SortTestHelper::generateRandomArray(n,0,n);
    int* arr2 = SortTestHelper::copyIntArray(arr1,n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);

    delete[] arr1;
    delete[] arr2;

    cout<<endl;


    // 测试2 测试近乎有序的数组
    // 但是对于近乎有序的数组, 我们的快速排序算法退化成了O(n^2)级别的算法
    // 思考一下为什么对于近乎有序的数组, 快排退化成了O(n^2)的算法? :)
    int swapTimes = 100;
    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);

    delete[] arr1;
    delete[] arr2;
    return 0;
}