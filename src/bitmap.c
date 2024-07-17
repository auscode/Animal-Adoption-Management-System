#include "bitmap.h"

/*
The addAnimal function adds a new animal to an array of animals. It first checks if there is enough space to add a new animal. 
Then it initializes the new animal with a default name, age, and animal type. Finally, it adds the new animal to the array of 
animals and increments the number of animals in the array.
*/
void addAnimal(Animal *animals, int *numAnimals)
{
}

/*
The searchAnimal function takes an array of Animal structs, the number of animals in the array, and a name to search for. 
It loops through the array of animals, checking if each animal's name matches the search name. If it finds a match, 
it returns a pointer to the matching animal's details. If no match is found, it returns NULL.
*/
Animal *searchAnimal(Animal *animals, int numAnimals, const char *name)
{
}

/*
The function deleteAnimal searches an array of Animal structures for an animal with a given name and deletes it from the array if found. 
It returns true if the animal was successfully deleted, or false if it was not found or if the array is empty.
*/

bool deleteAnimal(Animal *animals, int *numAnimals, const char *nameToDelete)
{
 }

/*
The updateAnimal function updates the details of an animal in an array of animals. 
It checks for valid input parameters, searches for the animal to update by name, 
and returns a status code indicating whether the update was successful or not.
*/
FunctionStatus updateAnimal(Animal *animals, int numAnimals, char *name, int age, AnimalType type)
{
}


/*This function sorts an array of Animal structures by either name(n), age(a) or type(t), based on the sortBy parameter. 
It first checks if the sortBy parameter is valid, then allocates memory for a copy of the original array, 
and sorts the copy using bubble sort, selection sort, or insertion sort depending on the sortBy parameter. 
It then returns a pointer to the sorted copy. If any errors occur during the sorting process, it returns NULL.
*/
Animal *sortAnimals(Animal *animals, int numAnimals, char sortBy)
{
}

/*
This function counts the number of animals in an array by animal type (CAT, DOG, and BIRD). 
It returns an array of AnimalCount structures, where each structure contains the count for one animal type. 
The function dynamically allocates memory for the array using malloc and returns NULL if the allocation fails.
*/
AnimalCount *countAnimalsByType(Animal *animals, int numAnimals)
{
}
