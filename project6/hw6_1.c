#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    unsigned int thread_id;
    int l;
    int r;
} ThreadData;

// global variables
int *list;

void merge(int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1; // size of left subarray
    int n2 = r - m;     // size of right subarray

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = list[l + i];
    for (j = 0; j < n2; j++)
        R[j] = list[m + 1 + j];

    // Merge the temporary arrays back into list[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j]) // Change this to L[i] > R[j] for descending order
        {
            list[k] = L[i];
            i++;
        }
        else
        {
            list[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        list[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        list[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2; // Same as (l+r)/2, but avoids overflow for large l and r
        merge_sort(l, m);
        merge_sort(m + 1, r);
        merge(l, m, r);
    }
}

void *multi_thread_merge_sort(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    merge_sort(data->l, data->r);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <testcase_file> <output_file>\n", argv[0]);
        exit(1);
    }

    // Open the testcase file and read the list line by line
    FILE *testcase = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    do
    {
        list = (int *)malloc(sizeof(int) * 10000);
        int list_size = 0;
        // read until the end of the line
        do
        {
            fscanf(testcase, "%d", &list[list_size++]);
        } while (getc(testcase) != '\n' && !feof(testcase));

        if (feof(testcase))
            break;

        // Split the list into two halves and sort them in parallel
        pthread_t threads[2];
        ThreadData thread_data[2];

        thread_data[0].thread_id = 0;
        thread_data[0].l = 0;
        thread_data[0].r = list_size / 2 - 1;
        pthread_create(&threads[0], NULL, multi_thread_merge_sort, &thread_data[0]);

        thread_data[1].thread_id = 1;
        thread_data[1].l = list_size / 2;
        thread_data[1].r = list_size - 1;
        pthread_create(&threads[1], NULL, multi_thread_merge_sort, &thread_data[1]);

        // Wait for the two halves to be sorted
        pthread_join(threads[0], NULL);
        pthread_join(threads[1], NULL);

        // Merge the two sorted halves
        merge(0, list_size / 2 - 1, list_size - 1);

        // Write the sorted list to the output file
        for (int i = 0; i < list_size; i++)
        {
            fprintf(output, "%d ", list[i]);
        }
        fprintf(output, "\n");
        free(list);
    } while (!feof(testcase));
}