# https://www.codeeval.com/open_challenges/91/
# This is obviously trivial to do in Python library calls.
# Implementing it by hand is an exercise more in keeping with the spirit
# of the question.

import sys

def partition(array, left, right, pivotIndex):
    pivotValue = array[pivotIndex]
    temp = array[pivotIndex]
    array[pivotIndex] = array[right]
    array[right] = temp
    storeIndex = left
    for i in range(left,right):
        if array[i] <= pivotValue:
            temp = array[i]
            array[i] = array[storeIndex]
            array[storeIndex] = temp
            storeIndex += 1
    temp = array[storeIndex]
    array[storeIndex] = array[right]
    array[right] = temp
    return storeIndex
            

def quicksort_imp(l,left,right):
    if left < right:
        pivotIndex = (left+right)//2
        pivotNewIndex = partition(l,left,right,pivotIndex)
        quicksort_imp(l, left, pivotNewIndex-1)
        quicksort_imp(l, pivotNewIndex+1, right)
    return l

def quicksort(l):
    return quicksort_imp(l,0,len(l)-1)

def main():
    with open(sys.argv[1],'r') as f:
        for line in f:
            nums = [float(e) for e in line.split(' ')]
            numsSorted = quicksort(nums)
            print(' '.join(["{:.3f}".format(e) for e in numsSorted]))

if __name__ == '__main__':
    main()
