#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define VECTOR_SIZE 10000
#define NUM_THREADS 8

// Define the vectors
int *vector1, *vector2;

int inner_product = 0;

pthread_mutex_t mutex;

// Structure to hold thread-specific data
typedef struct {
    unsigned int thread_id;
    unsigned int start;
    unsigned int end;
} ThreadData;

// Function to calculate the inner product for a portion of the vectors
void* calculate_inner_product(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    int temp_inner_product = 0;
    for (int i = data->start; i < data->end; i++) {
        temp_inner_product += vector1[i] * vector2[i];
    }

    // Lock the mutex before updating the global inner product
    pthread_mutex_lock(&mutex);
    inner_product += temp_inner_product;
    pthread_mutex_unlock(&mutex);


    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Initialize the vectors
    vector1 = (int *)malloc(sizeof(int)*10000);
    vector2 = (int *)malloc(sizeof(int)*10000);
    for(int i = 0; i < VECTOR_SIZE; i++) { 
        vector1[i] = 1;
        vector2[i] = 2;
    }

    int elements_per_thread = VECTOR_SIZE / NUM_THREADS;
    int remaining_elements = VECTOR_SIZE % NUM_THREADS;

    // Create threads and calculate inner product in parallel
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].start = i * elements_per_thread;
        thread_data[i].end = (i + 1) * elements_per_thread;
        if (i == NUM_THREADS - 1) {
            // Include remaining elements in the last thread
            thread_data[i].end += remaining_elements;
        }

        pthread_create(&threads[i], NULL, calculate_inner_product, &thread_data[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Inner Product: %d\n", inner_product);

    return 0;
}
