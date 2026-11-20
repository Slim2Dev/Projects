# Bubble sort - Visual presentation 

## What is a bubble sort? 

**Bubble sort** is often referred to as sinking sort, its a simple sorting algorithm that repeatedle steps through the input list element by element, comparing the current element with the one after it, swapping their values if needed ( From smallest to largest or the other way around ). 
These passes through the list are repeated until no swaps have to be performed during a pass, meaning that the list was completly sorted.
## Performance

**Bubble sort** has worst-case and average complexity of *O(n²)*, where *n* is the number of items being sorted.
Most practical sorting algorithms have substantially better worst-case or average complexity, often *O(n log n)*. Even other *O(n²)* sorting algorithms, such as insertion sort, generally run faster than bubble sort, and are no more complex. For this reason bubble sort is rarely used in practice.


## Video 

https://github.com/user-attachments/assets/df003a4f-07b2-42f6-afab-192478f6694c

### Code i wrote for the *bubble sort*

```
#include <iostream>
using namespace std;

void printArray(int tab[])
{
    for(int i=0; i<6; i++)
    {
        cout << " " << tab[i] << ", ";
    }
}

int main()
{

    int tab[6] = {9,7,2,5,11,4};
    int temp = 0;
    bool swapped = true;

    cout << "\n";
    printArray(tab);

    while(swapped==true)
    {
        swapped = false;
        for(int i=0; i<5; i++)
        {
            if(tab[i]>tab[i+1])
            {
                temp = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = temp;
                swapped = true;
            }
        }
    }

    cout << "\n";
    printArray(tab);

    return 0;

}
```

## Sources 

[Wikipedia](https://en.wikipedia.org/wiki/Bubble_sort)

