#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024 // Max line length
#define INITIAL_CAPACITY 10  // Initial array capacity

int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] <= pivot) {
      i++;
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  int temp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = temp;

  return i + 1;
}

void quickSort(int arr[], int low, int high) {
  if (low < high) {
    int pivotIndex = partition(arr, low, high);
    quickSort(arr, low, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, high);
  }
}

int main(int argc, char *argv[]) {
  FILE *file = fopen("input.txt", "r");
  if (file == NULL) {
    perror("Failed to open file");
    return EXIT_FAILURE;
  }

  // Dynamic array allocation
  int *col1 = malloc(INITIAL_CAPACITY * sizeof(int));
  int *col2 = malloc(INITIAL_CAPACITY * sizeof(int));
  if (col1 == NULL || col2 == NULL) {
    perror("Memory allocation failed");
    fclose(file);
    return EXIT_FAILURE;
  }

  size_t capacity = INITIAL_CAPACITY;
  size_t size = 0;
  char line[MAX_LINE_LENGTH];

  // Read and parse integers from lines
  while (fgets(line, sizeof(line), file)) {
    int num1, num2;
    if (sscanf(line, "%d %d", &num1, &num2) != 2) {
      fprintf(stderr, "Invalid format: %s", line);
      continue;
    }

    // Resize arrays if needed
    if (size >= capacity) {
      capacity *= 2;
      int *new_col1 = realloc(col1, capacity * sizeof(int));
      int *new_col2 = realloc(col2, capacity * sizeof(int));
      if (new_col1 == NULL || new_col2 == NULL) {
        perror("Memory reallocation failed");
        free(col1);
        free(col2);
        fclose(file);
        return EXIT_FAILURE;
      }
      col1 = new_col1;
      col2 = new_col2;
    }

    col1[size] = num1;
    col2[size] = num2;
    size++;
  }

  fclose(file);

  int low = 0;
  int high = size - 1;

  // Sort both arrays independently
  quickSort(col1, low, high);
  quickSort(col2, low, high);

  // Calculate total distance
  int tot_dist = 0;
  for (int k = 0; k < size; k++) {
    int dist = abs(col1[k] - col2[k]);
    tot_dist += dist;
  }

  printf("The total distance is: %d\n", tot_dist);

  free(col1);
  free(col2);
  return EXIT_SUCCESS;
}
