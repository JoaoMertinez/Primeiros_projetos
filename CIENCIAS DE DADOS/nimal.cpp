#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_FEATURES 17
#define NUM_CATEGORIES 7
#define MAX_ANIMALS 150

typedef struct {
    char name[50];
    int features[NUM_FEATURES];
    int category;
} Animal;

double calculateDistance(int *features1, int *features2) {
    double distance = 0.0;
    for (int i = 0; i < NUM_FEATURES; ++i) {
        distance += pow(features1[i] - features2[i], 2);
    }
    return sqrt(distance);
}

int classify(Animal *animals, int numAnimals, int *unknownFeatures) {
    int k = 5; // You can adjust the value of k as needed
    double distances[MAX_ANIMALS];
    
    for (int i = 0; i < numAnimals; ++i) {
        distances[i] = calculateDistance(unknownFeatures, animals[i].features);
    }

    // Sort distances and get the indices
    int sortedIndices[MAX_ANIMALS];
    for (int i = 0; i < numAnimals; ++i) {
        sortedIndices[i] = i;
    }

    for (int i = 0; i < numAnimals - 1; ++i) {
        for (int j = i + 1; j < numAnimals; ++j) {
            if (distances[i] > distances[j]) {
                double tempDist = distances[i];
                distances[i] = distances[j];
                distances[j] = tempDist;

                int tempIndex = sortedIndices[i];
                sortedIndices[i] = sortedIndices[j];
                sortedIndices[j] = tempIndex;
            }
        }
    }

    // Count the occurrences of each category in the k nearest neighbors
    int categoryCount[NUM_CATEGORIES] = {0};
    for (int i = 0; i < k; ++i) {
        int index = sortedIndices[i];
        categoryCount[animals[index].category]++;
    }

    // Determine the most frequent category
    int maxCount = 0;
    int predictedCategory = 0;
    for (int i = 0; i < NUM_CATEGORIES; ++i) {
        if (categoryCount[i] > maxCount) {
            maxCount = categoryCount[i];
            predictedCategory = i;
        }
    }

    return predictedCategory;
}

int main() {
    FILE *file = fopen("teste.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    Animal animals[MAX_ANIMALS];
    int numAnimals = 0;

    // Read data from the file
    while (fscanf(file, "%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                  animals[numAnimals].name,
                  &animals[numAnimals].features[0],
                  &animals[numAnimals].features[1],
                  &animals[numAnimals].features[2],
                  &animals[numAnimals].features[3],
                  &animals[numAnimals].features[4],
                  &animals[numAnimals].features[5],
                  &animals[numAnimals].features[6],
                  &animals[numAnimals].features[7],
                  &animals[numAnimals].features[8],
                  &animals[numAnimals].features[9],
                  &animals[numAnimals].features[10],
                  &animals[numAnimals].features[11],
                  &animals[numAnimals].features[12],
                  &animals[numAnimals].features[13],
                  &animals[numAnimals].features[14],
                  &animals[numAnimals].features[15],
                  &animals[numAnimals].features[16],
                  &animals[numAnimals].category) == 18) {
        numAnimals++;
    }

    fclose(file);

    // Example of classifying an unknown animal
    int unknownFeatures[NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 4, 1, 0, 1, 1};
    int predictedCategory = classify(animals, numAnimals, unknownFeatures);

    printf("Predicted category for the unknown animal: %d\n", predictedCategory);

    return 0;
}

