#include <stdio.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int total_size = nums1Size + nums2Size; 
    int last_two[2]; 
    int checked = 0;
    int index1 = 0, index2 = 0;
    while (index1 + index2 < (total_size / 2) + 1) {
        if (index1 < nums1Size && index2 < nums2Size) {
            if (nums1[index1] < nums2[index2]) {
                last_two[0] = last_two[1];
                last_two[1] = nums1[index1++]; 
            } else {
                last_two[0] = last_two[1];
                last_two[1] = nums2[index2++];
            }
        } else if (index1 < nums1Size) {
            last_two[0] = last_two[1];
            last_two[1] = nums1[index1++];
        } else {
            last_two[0] = last_two[1];
            last_two[1] = nums2[index2++];
        }
    }
    if (total_size % 2 == 0) { // even 
        printf("Even: [%d, %d]\n", last_two[0], last_two[1]);
        return ((double) (last_two[0] + last_two[1])) / 2; 
    } else { // odd
        printf("Odd: [%d, %d]\n", last_two[0], last_two[1]);
        return (double) last_two[1];
    }
}