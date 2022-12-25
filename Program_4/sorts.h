#ifndef SORTS_H
#define SORTS_H
#include <iostream>
#include <vector>
using namespace std;

void BubbleSort(vector<int> &items, int start, int last);
void InsertionSort(vector<int> &items, int start, int last);
void QuickSort(vector<int> &items, int start, int last);
void MergeSort(vector<int> &items, int start, int last);
void Merge(vector<int> &items, int first, int mid, int last);
void IterativeMergeSort(vector<int> &items, int start, int last);
void IterativeMerge(vector<int> &items, int temp[], int first, int mid, int last);
void ShellSort(vector<int> &items, int first, int last);
void PrintVector(vector<int>& item_vector);

void BubbleSort(vector<int> &items, int first, int last){
    if (first > last || first < 0 || last < 0 || last > items.size()){
    cerr<<"not valid sort"<<endl;
    return;
    }
    bool sorted = false; // False when swaps occur
    int pass = 1;
    int n = (last - first) + 1;
    while (!sorted && (pass < n)){
    sorted = true;
    for ( int index = first; index < last; index++){ //only swap within range
    int nextIndex = index + 1;
        if (items[index] > items[nextIndex]){
            swap(items[index], items[nextIndex]);
            sorted = false; 
        } 
    } 
    pass++;
    }
}
//function defs
void InsertionSort(vector<int> &items, int first, int last){
if (first > last || first < 0 || last < 0 || last > items.size()){
cerr<<"not valid sort"<<endl;
return;
}
for (int i = first+1; i<= last; i++){ //stay within range
        int next = items[i];
        int location = i-1;
        while(location>=first && items[location] > next){
            items[location+1] = items[location];
            --location;
        }
        items[location+1] = next;
    }
}

void QuickSort(vector<int> &items, int first, int last){
    if (first > last || first < 0 || last < 0 || last > items.size()){
        cerr<<"not valid sort"<<endl;
        return;
    }
    if (last - first < 4){
        InsertionSort(items, first, last);
        return;
    }
    int mid = (first + last) / 2;
    if (items[first] > items[last]){
        swap(items[first], items[last]);
    }
    if (items[first] > items[mid]){
        swap(items[first], items[mid]);
    }
    else if (items[mid] > items[last]){
        swap(items[mid], items[last]);
    }
    int pivot = items[mid]; 
    swap(items[mid], items[last - 1]);
    int left = first + 1;
    int right = last - 2;
    bool done = false;
    while (! done){
        while (items[left] < pivot){
            left++;
        }
        while (items[right] > pivot) {
            right--;
        }
        if (right > left){
            swap(items[left], items[right]);
            right--;
            left++;
        }else{
            done = true;
        }
    }
    swap(items[left], items[last - 1]);
    QuickSort(items, first, left - 1);
    QuickSort(items, left + 1, last);
}

void MergeSort(vector<int> &items, int first, int last){
    if (first > last || first < 0 || last < 0 || last > items.size()){
        cerr<<"not valid sort"<<endl;
        return;
    }
    if (first < last){
        int mid = (first + last) /2;
        MergeSort(items, first, mid);
        MergeSort(items, mid+1, last);
        Merge(items,first,mid,last);
    }
}
void Merge(vector<int>& vec, int first, int mid, int last)
{
    int size = last - first + 1;
    int* tmp_arr;
    tmp_arr = new int[size];
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int index = 0;
    while ((first1 <= last1) && (first2 <= last2))
    {
        if (vec[first1] < vec[first2])
        {
            tmp_arr[index] = vec[first1];
            first1++;
        }
        else
        {
            tmp_arr[index] = vec[first2];
            first2++;
        }
        index++;
    }
    
    while (first1 <= last1)
    {
        tmp_arr[index] = vec[first1];
        first1++;
        index++;
    }
    while (first2 <= last2)
    {
        tmp_arr[index] = vec[first2];
        first2++;
        index++;
    }
    for (index = 0; index < size; index++)
    {
        vec[first] = tmp_arr[index];
        first++;
    }
    delete[] tmp_arr;
}

void IterativeMergeSort(vector<int> &items, int first, int last){
    if (first > last || first < 0 || last < 0 || last > items.size()){
        cerr<<"not valid sort"<<endl;
        return;
    }
    int size = last-first; 
    int left, pairs;
    int temp[size + 1]; //temp array
    for (pairs=1; pairs<=size; pairs = 2*pairs){
       for (left = first; left<last; left += 2*pairs){
           int mid = min(left + pairs - 1, last);
           int right = min(left + 2*pairs - 1, last);
           IterativeMerge(items, temp, left, mid, right);
       }
   }
}

void IterativeMerge(vector<int>& items, int temp[], int first, int mid, int last){
    int size = (last - first) + 1;
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int index = 0;
    while ((first1 <= last1) && (first2 <= last2))
    {
        if (items[first1] < items[first2])
        {
            temp[index] = items[first1];
            first1++;
        }
        else
        {
            temp[index] = items[first2];
            first2++;
        }
        index++;
    }
    
    while (first1 <= last1)
    {
        temp[index] = items[first1];
        first1++;
        index++;
    }
    while (first2 <= last2)
    {
        temp[index] = items[first2];
        first2++;
        index++;
    }
    for (index = 0; index < size; index++)
    {
        items[first] = temp[index];
        first++;
    }
}
//shell sort gap is determined by #ofElements/2 then second /2.2 until you reach 1
void ShellSort(vector<int>& items, int first, int last){ 
    if (first > last || first < 0 || last < 0 || last > items.size()){
        cerr<<"not valid sort"<<endl;
        return;
    }
    int size = (last - first) + 1;
    for (int gap = size / 2; gap > 0; gap = (gap == 2) ? 1 : int(gap / 2.2)){
        for (int i = gap + first; i <= last; i++){ //in order to establish start of range we do gap + first as i
            int tmp = items[i];
            int j = i;
            for ( ; (j >= gap + first) && (tmp < items[j - gap]); j -= gap){
                items[j] = items[j - gap];
            }
            items[j] = tmp;
        }
    }
}
#endif