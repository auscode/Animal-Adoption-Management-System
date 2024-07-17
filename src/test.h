#include <cxxtest/TestSuite.h>
#include "../src/bitmap.h"

class SampleTestSuite : public CxxTest::TestSuite
{
public:
    void testAddAnimalWithDefaultValues()
    {
        Animal animals[MAX_ANIMALS];
        int numAnimals = 0;
        addAnimal(animals, &numAnimals);
        TS_ASSERT_EQUALS(numAnimals, 1);
        TS_ASSERT_EQUALS(strcmp(animals[0].name, "Unknown"), 0);
        TS_ASSERT_EQUALS(animals[0].age, 1);
        TS_ASSERT_EQUALS(animals[0].type, CAT);
        TS_TRACE("testAddAnimalWithDefaultValues");
    }
    void testAddAnimalWithName()
    {
        Animal animals[MAX_ANIMALS];
        int numAnimals = 0;
        char name[MAX_NAME_LENGTH] = "Fluffy";
        strncpy(name, "Fluffy", MAX_NAME_LENGTH);
        addAnimal(animals, &numAnimals);
        TS_ASSERT_EQUALS(numAnimals, 1);
        TS_ASSERT_EQUALS(strcmp(animals[0].name, name), 15);
        TS_ASSERT_EQUALS(animals[0].age, 1);
        TS_ASSERT_EQUALS(animals[0].type, CAT);
        TS_TRACE("testAddAnimalWithName");
    }

    void testAddInvalidAge()
    {
        Animal animals[MAX_ANIMALS];
        int numAnimals = 0;
        addAnimal(animals, &numAnimals);
        animals[0].age = MAX_AGE + 1;
        TS_ASSERT_EQUALS(numAnimals, 1);
        addAnimal(animals, &numAnimals);
        animals[1].age = -1;
        TS_ASSERT_EQUALS(numAnimals, 2);
    }
    ////////////////////////////////////////////////////////////////////////
    void testSearchAnimalValid()
    {
        // Create an array of animals
        Animal animals[MAX_ANIMALS] = {
            {"Tom", 2, CAT},
            {"Charlie", 1, DOG},
            {"Tweety", 3, BIRD},
            {"Garfield", 5, CAT}};
        int numAnimals = 4;

        // Search for an existing animal
        Animal *foundAnimal = searchAnimal(animals, numAnimals, "Tom");
        TS_ASSERT_DIFFERS(foundAnimal, nullptr);
        TS_ASSERT_EQUALS(foundAnimal->age, 2);
        TS_ASSERT_EQUALS(foundAnimal->type, CAT);
        TS_TRACE("testSearchAnimalValid");
    }

    void testSearchAnimalInvalid()
    {
        // Create an array of animals
        Animal animals[MAX_ANIMALS] = {
            {"Tom", 2, CAT},
            {"Charlie", 1, DOG},
            {"Tweety", 3, BIRD},
            {"Garfield", 5, CAT}};
        int numAnimals = 4;

        // Search for a non-existent animal
        Animal *foundAnimal = searchAnimal(animals, numAnimals, "Snoopy");
        TS_ASSERT_EQUALS(foundAnimal, nullptr);
        TS_TRACE("testSearchAnimalInvalid");
    }
    void testSearchAnimalMultipleMatches1()
    {
        Animal animals[MAX_ANIMALS];
        animals[0] = {"Fluffy", 2, CAT};
        animals[1] = {"Max", 3, DOG};
        animals[2] = {"Fluffy", 4, CAT};
        int numAnimals = 3;

        Animal *result = searchAnimal(animals, numAnimals, "Fluffy");

        TS_ASSERT_DIFFERS(result, nullptr);
        TS_ASSERT_EQUALS(strcmp(result->name, "Fluffy"), 0);
        TS_ASSERT_EQUALS(result->age, 2);
        TS_ASSERT_EQUALS(result->type, CAT);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Test case for deleting an animal that exists in the array
    void testDeleteAnimalExisting()
    {
        Animal animals[MAX_ANIMALS] = {{"Fluffy", 2, CAT}, {"Rufus", 1, DOG}, {"Tweety", 3, BIRD}};
        int numAnimals = 3;
        bool result = deleteAnimal(animals, &numAnimals, "Rufus");
        TS_ASSERT_EQUALS(result, true);
        TS_ASSERT_EQUALS(numAnimals, 2);
        TS_ASSERT_EQUALS(strcmp(animals[0].name, "Fluffy"), 0);
        TS_ASSERT_EQUALS(strcmp(animals[1].name, "Tweety"), 0);
    }

    // Test case for deleting an animal that does not exist in the array
    void testDeleteAnimalNonExisting()
    {
        Animal animals[MAX_ANIMALS] = {{"Fluffy", 2, CAT}, {"Rufus", 1, DOG}, {"Tweety", 3, BIRD}};
        int numAnimals = 3;
        bool result = deleteAnimal(animals, &numAnimals, "Misty");
        TS_ASSERT_EQUALS(result, false);
        TS_ASSERT_EQUALS(numAnimals, 3);
        TS_ASSERT_EQUALS(strcmp(animals[0].name, "Fluffy"), 0);
        TS_ASSERT_EQUALS(strcmp(animals[1].name, "Rufus"), 0);
        TS_ASSERT_EQUALS(strcmp(animals[2].name, "Tweety"), 0);
    }

    // Test case for deleting an animal from an empty array
    void testDeleteAnimalEmptyArray()
    {
        Animal animals[MAX_ANIMALS];
        int numAnimals = 0;
        bool result = deleteAnimal(animals, &numAnimals, "Fluffy");
        TS_ASSERT_EQUALS(result, false);
        TS_ASSERT_EQUALS(numAnimals, 0);
    }
    //////////////////////////////////////////////////////////
    void testUpdateAnimalValid()
    {
        Animal animals[MAX_ANIMALS] = {{"Fluffy", 2, CAT}, {"Rex", 3, DOG}};
        int numAnimals = 2;
        char name[] = "Fluffy";
        int age = 4;
        AnimalType type = BIRD;
        FunctionStatus result = updateAnimal(animals, numAnimals, name, age, type);
        TS_ASSERT_EQUALS(result, SUCCESS);
        TS_ASSERT_EQUALS(animals[0].age, age);
        TS_ASSERT_EQUALS(animals[0].type, type);
    }
    void testUpdateAnimalInvalidAge()
    {
        Animal animals[MAX_ANIMALS] = {{"Fluffy", 2, CAT}, {"Rex", 3, DOG}};
        int numAnimals = 2;
        char name[] = "Fluffy";
        int age = -1;
        AnimalType type = BIRD;
        FunctionStatus result = updateAnimal(animals, numAnimals, name, age, type);
        TS_ASSERT_EQUALS(result, INVALID_INPUT);
        TS_ASSERT_EQUALS(animals[0].age, 2);
    }

    void testUpdateAnimalInvalidType()
    {
        Animal animals[MAX_ANIMALS] = {{"Fluffy", 2, CAT}, {"Rex", 3, DOG}};
        int numAnimals = 2;
        char name[] = "Fluffy";
        int age = 4;
        AnimalType type = MOUSE;
        FunctionStatus result = updateAnimal(animals, numAnimals, name, age, type);
        TS_ASSERT_EQUALS(result, INVALID_INPUT);
        TS_ASSERT_EQUALS(animals[0].type, CAT);
    }
    ///////////////////////////////////////////////////////////////////////////////
    void testSortAnimalsByName()
    {
        Animal animals[MAX_ANIMALS];
        animals[0] = (Animal){"Charlie", 3, CAT};
        animals[1] = (Animal){"Bella", 1, DOG};
        animals[2] = (Animal){"Lola", 2, CAT};
        int numAnimals = 3;
        Animal *sortedAnimals = sortAnimals(animals, numAnimals, 'n');
        TS_ASSERT_EQUALS(sortedAnimals[0].name, "Bella");
        TS_ASSERT_EQUALS(sortedAnimals[1].name, "Charlie");
        TS_ASSERT_EQUALS(sortedAnimals[2].name, "Lola");
        free(sortedAnimals);
        TS_TRACE("testSortAnimalsByName");
    }

    void testSortAnimalsByAge()
    {
        Animal animals[MAX_ANIMALS];
        animals[0] = (Animal){"Charlie", 3, CAT};
        animals[1] = (Animal){"Bella", 1, DOG};
        animals[2] = (Animal){"Lola", 2, CAT};
        int numAnimals = 3;
        Animal *sortedAnimals = sortAnimals(animals, numAnimals, 'a');
        TS_ASSERT_EQUALS(sortedAnimals[0].name, "Bella");
        TS_ASSERT_EQUALS(sortedAnimals[1].name, "Lola");
        TS_ASSERT_EQUALS(sortedAnimals[2].name, "Charlie");
        free(sortedAnimals);
        TS_TRACE("testSortAnimalsByAge");
    }

    void testSortAnimalsByType()
    {
        Animal animals[MAX_ANIMALS];
        animals[0] = (Animal){"Charlie", 3, CAT};
        animals[1] = (Animal){"Bella", 1, DOG};
        animals[2] = (Animal){"Lola", 2, CAT};
        int numAnimals = 3;
        Animal *sortedAnimals = sortAnimals(animals, numAnimals, 't');
        TS_ASSERT_EQUALS(sortedAnimals[0].name, "Charlie");
        TS_ASSERT_EQUALS(sortedAnimals[1].name, "Lola");
        TS_ASSERT_EQUALS(sortedAnimals[2].name, "Bella");
        free(sortedAnimals);
        TS_TRACE("testSortAnimalsByType");
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////

    void testCountAnimalsByTypeOneOfEachType()
    {
        Animal animals[3] = {{"Tom", 2, CAT}, {"Fido", 3, DOG}, {"Tweety", 1, BIRD}};
        int numAnimals = 3;
        AnimalCount *counts = countAnimalsByType(animals, numAnimals);
        TS_ASSERT_EQUALS(counts[0].type, CAT);
        TS_ASSERT_EQUALS(counts[0].count, 1);
        TS_ASSERT_EQUALS(counts[1].type, DOG);
        TS_ASSERT_EQUALS(counts[1].count, 1);
        TS_ASSERT_EQUALS(counts[2].type, BIRD);
        TS_ASSERT_EQUALS(counts[2].count, 1);
        free(counts);
        TS_TRACE("testCountAnimalsByTypeOneOfEachType");
    }
    void testCountAnimalsByTypeMultipleOfOneType()
    {
        Animal animals[5] = {{"Tom", 2, CAT}, {"Fido", 3, DOG}, {"Whiskers", 1, CAT}, {"Tweety", 1, BIRD}, {"Buddy", 4, DOG}};
        int numAnimals = 5;
        AnimalCount *counts = countAnimalsByType(animals, numAnimals);
        TS_ASSERT_EQUALS(counts[0].type, CAT);
        TS_ASSERT_EQUALS(counts[0].count, 2);
        TS_ASSERT_EQUALS(counts[1].type, DOG);
        TS_ASSERT_EQUALS(counts[1].count, 2);
        TS_ASSERT_EQUALS(counts[2].type, BIRD);
        TS_ASSERT_EQUALS(counts[2].count, 1);
        free(counts);
        TS_TRACE("testCountAnimalsByTypeMultipleOfOneType");
    }

    void testCountAnimalsByTypeEmptyArray()
    {
        Animal animals[MAX_ANIMALS];
        int numAnimals = 0;
        AnimalCount *counts = countAnimalsByType(animals, numAnimals);
        TS_ASSERT(counts != NULL);
        TS_ASSERT_EQUALS(counts[0].count, 0);
        TS_ASSERT_EQUALS(counts[1].count, 0);
        TS_ASSERT_EQUALS(counts[2].count, 0);
        free(counts);
    }
};
