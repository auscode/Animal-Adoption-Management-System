#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_AGE 20
#define DEFAULT_AGE 1
#define MAX_ANIMALS 100
#define MAX_NAME_LENGTH 50
#define MAX_TYPE_LENGTH 10

// Enum for animal type
typedef enum
{
    CAT,
    DOG,
    BIRD,
    MOUSE
} AnimalType;

typedef enum
{
    SUCCESS,
    FAILURE,
    INVALID_INPUT
} FunctionStatus;

typedef struct
{
    int count;
    AnimalType type;
} AnimalCount;

typedef struct
{
    char name[50];
    int age;
    AnimalType type;
} Animal;

void addAnimal(Animal *animals, int *numAnimals);

Animal *searchAnimal(Animal *animals, int numAnimals, const char *name);

bool deleteAnimal(Animal *animals, int *numAnimals, const char *nameToDelete);

FunctionStatus updateAnimal(Animal *animals, int numAnimals, char *name, int age, AnimalType type);

Animal *sortAnimals(Animal *animals, int numAnimals, char sortBy);

AnimalCount *countAnimalsByType(Animal *animals, int numAnimals);