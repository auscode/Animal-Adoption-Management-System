#include "bitmap.h"

/*
The addAnimal function adds a new animal to an array of animals. It first checks if there is enough space to add a new animal.
Then it initializes the new animal with a default name, age, and animal type. Finally, it adds the new animal to the array of
animals and increments the number of animals in the array.
*/
void addAnimal(Animal *animals, int *numAnimals)
{
    // Check if there is enough space to add a new animal
    if (*numAnimals >= MAX_ANIMALS)
    {
        return;
    }

    // Initialize the new animal
    Animal newAnimal;
    memset(&newAnimal, 0, sizeof(Animal));

    // Get the animal's name
    char name[MAX_NAME_LENGTH];
    strncpy(name, "Unknown", MAX_NAME_LENGTH);
    if (strlen(name) > 0)
    {
        strncpy(newAnimal.name, name, strlen(name));
    }

    // Get the animal's age
    int age = DEFAULT_AGE;
    if (age >= 0 && age <= MAX_AGE)
    {
        newAnimal.age = age;
    }

    // Get the animal's type
    char typeString[MAX_TYPE_LENGTH];
    strncpy(typeString, "CAT", MAX_TYPE_LENGTH);
    if (strcmp(typeString, "CAT") == 0)
    {
        newAnimal.type = CAT;
    }
    else if (strcmp(typeString, "DOG") == 0)
    {
        newAnimal.type = DOG;
    }
    else if (strcmp(typeString, "BIRD") == 0)
    {
        newAnimal.type = BIRD;
    }
    else
    {
        newAnimal.type = CAT;
    }

    // Add the new animal to the array
    animals[*numAnimals] = newAnimal;
    (*numAnimals)++;
}

/*
The searchAnimal function takes an array of Animal structs, the number of animals in the array, and a name to search for.
It loops through the array of animals, checking if each animal's name matches the search name. If it finds a match,
it returns a pointer to the matching animal's details. If no match is found, it returns NULL.
*/
Animal *searchAnimal(Animal *animals, int numAnimals, const char *name)
{
    // Check for NULL inputs
    if (!animals || !name)
    {
        return NULL;
    }

    // Loop through the array of animals
    for (int i = 0; i < numAnimals; i++)
    {
        // Check if the current animal's name matches the search name
        if (strcmp(animals[i].name, name) == 0)
        {
            // Return a pointer to the matching animal's details
            return &animals[i];
        }
    }

    // If no match was found, return NULL
    return NULL;
}

/*
The function deleteAnimal searches an array of Animal structures for an animal with a given name and deletes it from the array if found.
It returns true if the animal was successfully deleted, or false if it was not found or if the array is empty.
*/

bool deleteAnimal(Animal *animals, int *numAnimals, const char *nameToDelete)
{
    // Check if there are any animals in the array
    if (*numAnimals == 0)
    {
        return false; // Cannot delete an animal from an empty array
    }

    // Find the index of the animal with the given name, if it exists
    int animalIndexToDelete = -1; // Default value for not found
    for (int i = 0; i < *numAnimals; i++)
    {
        if (strcmp(animals[i].name, nameToDelete) == 0)
        {
            animalIndexToDelete = i;
            break; // Stop searching as soon as we find a match
        }
    }

    // Check if the animal was found
    if (animalIndexToDelete == -1)
    {
        return false; // Animal with given name was not found in the array
    }

    // Shift all animals after the deleted animal back by one index
    for (int i = animalIndexToDelete; i < *numAnimals - 1; i++)
    {
        animals[i] = animals[i + 1];
    }

    // Decrement the number of animals in the array
    (*numAnimals)--;

    return true; // Animal was successfully deleted
}

/*
The updateAnimal function updates the details of an animal in an array of animals.
It checks for valid input parameters, searches for the animal to update by name,
and returns a status code indicating whether the update was successful or not.
*/
FunctionStatus updateAnimal(Animal *animals, int numAnimals, char *name, int age, AnimalType type)
{
    // Check for valid input parameters
    if (name == NULL || age < DEFAULT_AGE || age > MAX_AGE || (type != CAT && type != DOG && type != BIRD))
    {
        return INVALID_INPUT;
    }

    // Search for the animal to update
    int index = -1;
    for (int i = 0; i < numAnimals; i++)
    {
        if (strcmp(animals[i].name, name) == 0)
        {
            index = i;
            break;
        }
    }

    // If animal is not found, return failure
    if (index == -1)
    {
        return FAILURE;
    }

    // Update animal's details
    strcpy(animals[index].name, name);
    animals[index].age = age;
    animals[index].type = type;

    return SUCCESS;
}

/*This function sorts an array of Animal structures by either name(n), age(a) or type(t), based on the sortBy parameter.
It first checks if the sortBy parameter is valid, then allocates memory for a copy of the original array,
and sorts the copy using bubble sort, selection sort, or insertion sort depending on the sortBy parameter.
It then returns a pointer to the sorted copy. If any errors occur during the sorting process, it returns NULL.
*/
Animal *sortAnimals(Animal *animals, int numAnimals, char sortBy)
{
    // Check for invalid sortBy parameter
    if (sortBy != 'n' && sortBy != 'a' && sortBy != 't')
    {
        return NULL;
    }

    // Allocate memory for a copy of the array
    Animal *sortedAnimals = (Animal *)malloc(numAnimals * sizeof(Animal));
    if (sortedAnimals == NULL)
    {
        return NULL;
    }

    // Copy the contents of the original array into the copy
    memcpy(sortedAnimals, animals, numAnimals * sizeof(Animal));

    // Sort the copy by the given attribute
    switch (sortBy)
    {
    case 'n':
        // Sort by name using bubble sort
        for (int i = 0; i < numAnimals - 1; i++)
        {
            for (int j = 0; j < numAnimals - i - 1; j++)
            {
                if (strcmp(sortedAnimals[j].name, sortedAnimals[j + 1].name) > 0)
                {
                    // Swap elements
                    Animal temp = sortedAnimals[j];
                    sortedAnimals[j] = sortedAnimals[j + 1];
                    sortedAnimals[j + 1] = temp;
                }
            }
        }
        break;
    case 'a':
        // Sort by age using selection sort
        for (int i = 0; i < numAnimals - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < numAnimals; j++)
            {
                if (sortedAnimals[j].age < sortedAnimals[minIndex].age)
                {
                    minIndex = j;
                }
            }
            // Swap elements
            Animal temp = sortedAnimals[i];
            sortedAnimals[i] = sortedAnimals[minIndex];
            sortedAnimals[minIndex] = temp;
        }
        break;
    case 't':
        // Sort by type using insertion sort
        for (int i = 1; i < numAnimals; i++)
        {
            Animal key = sortedAnimals[i];
            int j = i - 1;
            while (j >= 0 && sortedAnimals[j].type > key.type)
            {
                sortedAnimals[j + 1] = sortedAnimals[j];
                j--;
            }
            sortedAnimals[j + 1] = key;
        }
        break;
    default:
        // This case should never be reached, but included for completeness
        free(sortedAnimals);
        return NULL;
    }

    return sortedAnimals;
}

/*
This function counts the number of animals in an array by animal type (CAT, DOG, and BIRD).
It returns an array of AnimalCount structures, where each structure contains the count for one animal type.
The function dynamically allocates memory for the array using malloc and returns NULL if the allocation fails.
*/
AnimalCount *countAnimalsByType(Animal *animals, int numAnimals)
{
    // Allocate memory for the AnimalCount array
    AnimalCount *counts = (AnimalCount *)malloc(3 * sizeof(AnimalCount));

    if (counts == NULL)
    {
        // Failed to allocate memory
        return NULL;
    }

    // Initialize count values to 0 for each animal type
    counts[0].count = 0;
    counts[0].type = CAT;
    counts[1].count = 0;
    counts[1].type = DOG;
    counts[2].count = 0;
    counts[2].type = BIRD;

    // Count the number of animals for each type
    for (int i = 0; i < numAnimals; i++)
    {
        switch (animals[i].type)
        {
        case CAT:
            counts[0].count++;
            break;
        case DOG:
            counts[1].count++;
            break;
        case BIRD:
            counts[2].count++;
            break;
        default:
            // Invalid animal type
            free(counts);
            return NULL;
        }
    }

    return counts;
}
