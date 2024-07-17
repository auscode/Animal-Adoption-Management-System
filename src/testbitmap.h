#include <cxxtest/TestSuite.h>
#include "../src/bitmap.h"

class SampleTestSuite : public CxxTest::TestSuite
{
public:
    void testAddOneAnimal()
    {
        Animal animals[MAX_ANIMALS];
        int numAnimals = 0;
        addAnimal(animals, &numAnimals);
        TS_ASSERT_EQUALS(numAnimals, 1);
    }
    void testAddMultipleAnimals()
    {
        Animal animals[MAX_ANIMALS];
        int numAnimals = 0;
        addAnimal(animals, &numAnimals);
        addAnimal(animals, &numAnimals);
        addAnimal(animals, &numAnimals);
        TS_ASSERT_EQUALS(numAnimals, 3);
    }

    void testAddMaxAnimals()
    {
        Animal animals[MAX_ANIMALS];
        int numAnimals = 0;
        for (int i = 0; i < MAX_ANIMALS; i++)
        {
            addAnimal(animals, &numAnimals);
        }
        TS_ASSERT_EQUALS(numAnimals, MAX_ANIMALS);
        addAnimal(animals, &numAnimals);
        TS_ASSERT_EQUALS(numAnimals, MAX_ANIMALS);
    }
    ////////////////////////////////////////////////////////////////////////

    void testSearchAnimalNullInputs()
    {
        Animal *foundAnimal = searchAnimal(nullptr, 0, nullptr);
        TS_ASSERT_EQUALS(foundAnimal, nullptr);
        TS_TRACE("testSearchAnimalNullInputs");
    }
    void testSearchAnimalValid1()
    {
        Animal animals[MAX_ANIMALS];
        animals[0] = {"Fluffy", 2, CAT};
        animals[1] = {"Max", 3, DOG};
        animals[2] = {"Tweety", 1, BIRD};
        int numAnimals = 3;

        Animal *result = searchAnimal(animals, numAnimals, "Fluffy");

        TS_ASSERT_DIFFERS(result, nullptr);
        TS_ASSERT_EQUALS(strcmp(result->name, "Fluffy"), 0);
        TS_ASSERT_EQUALS(result->age, 2);
        TS_ASSERT_EQUALS(result->type, CAT);
    }
    void testSearchAnimalInvalid1()
    {
        Animal animals[MAX_ANIMALS];
        animals[0] = {"Fluffy", 2, CAT};
        animals[1] = {"Max", 3, DOG};
        int numAnimals = 2;

        Animal *result = searchAnimal(animals, numAnimals, "Tweety");

        TS_ASSERT_EQUALS(result, nullptr);
    }
    void testSearchAnimalNullAnimals1()
    {
        Animal *result = searchAnimal(nullptr, 0, "Fluffy");
        TS_ASSERT_EQUALS(result, nullptr);
    }
    void testSearchAnimalNullName1()
    {
        Animal animals[MAX_ANIMALS];
        animals[0] = {"Fluffy", 2, CAT};
        int numAnimals = 1;

        Animal *result = searchAnimal(animals, numAnimals, nullptr);
        TS_ASSERT_EQUALS(result, nullptr);
    }
    void testSearchAnimalEmptyName1()
    {
        Animal animals[MAX_ANIMALS];
        animals[0] = {"Fluffy", 2, CAT};
        int numAnimals = 1;

        Animal *result = searchAnimal(animals, numAnimals, "");
        TS_ASSERT_EQUALS(result, nullptr);
    }
    ////////////////////////////////////////////////////////////////////
    void testDeleteAnimalOnlyAnimal()
    {
        Animal animals[MAX_ANIMALS] = {{"Fluffy", 2, CAT}};
        int numAnimals = 1;
        bool result = deleteAnimal(animals, &numAnimals, "Fluffy");
        TS_ASSERT_EQUALS(result, true);
        TS_ASSERT_EQUALS(numAnimals, 0);
    }
    void testDeleteAnimalFirst()
    {
        Animal animals[MAX_ANIMALS] = {{"Fluffy", 2, CAT}, {"Rufus", 1, DOG}, {"Tweety", 3, BIRD}};
        int numAnimals = 3;
        bool result = deleteAnimal(animals, &numAnimals, "Fluffy");
        TS_ASSERT_EQUALS(result, true);
        TS_ASSERT_EQUALS(numAnimals, 2);
        TS_ASSERT_EQUALS(strcmp(animals[0].name, "Rufus"), 0);
        TS_ASSERT_EQUALS(strcmp(animals[1].name, "Tweety"), 0);
    }
    void testDeleteAnimalLast()
    {
        Animal animals[MAX_ANIMALS];
        animals[0] = {"Tom", 3, CAT};
        animals[1] = {"Jerry", 2, MOUSE};
        int numAnimals = 2;

        bool result = deleteAnimal(animals, &numAnimals, "Jerry");

        TS_ASSERT_EQUALS(result, true);
        TS_ASSERT_EQUALS(numAnimals, 1);
        TS_ASSERT_EQUALS(strcmp(animals[0].name, "Tom"), 0);
        TS_TRACE("testDeleteAnimalLast");
    }
    /////////////////////////////////////////////////////////////
    void testUpdateAnimalNonexistent()
    {
        Animal animals[MAX_ANIMALS] = {{"Fluffy", 2, CAT}, {"Rex", 3, DOG}};
        int numAnimals = 2;
        char name[] = "Whiskers";
        int age = 1;
        AnimalType type = CAT;
        FunctionStatus result = updateAnimal(animals, numAnimals, name, age, type);
        TS_ASSERT_EQUALS(result, FAILURE);
    }
    void testUpdateAnimalNullName()
    {
        Animal animals[MAX_ANIMALS] = {{"Fluffy", 2, CAT}, {"Rex", 3, DOG}};
        int numAnimals = 2;
        char *name = NULL;
        int age = 1;
        AnimalType type = CAT;
        FunctionStatus result = updateAnimal(animals, numAnimals, name, age, type);
        TS_ASSERT_EQUALS(result, INVALID_INPUT);
    }
    void testUpdateAnimalValid1()
    {
        Animal animals[MAX_ANIMALS] = {{"Tommy", 2, CAT}, {"Buddy", 3, DOG}};
        int numAnimals = 2;
        char name[] = "Tommy";
        int age = 3;
        AnimalType type = BIRD;
        FunctionStatus result = updateAnimal(animals, numAnimals, name, age, type);
        TS_ASSERT_EQUALS(result, SUCCESS);
        TS_ASSERT_EQUALS(animals[0].age, 3);
        TS_ASSERT_EQUALS(animals[0].type, BIRD);
    }
    /////////////////////////////////////////////////////////////////
    void testSortAnimalsByInvalidAttribute()
    {
        Animal animals[MAX_ANIMALS];
        animals[0] = (Animal){"Charlie", 3, CAT};
        animals[1] = (Animal){"Bella", 1, DOG};
        animals[2] = (Animal){"Lola", 2, CAT};
        int numAnimals = 3;
        Animal *sortedAnimals = sortAnimals(animals, numAnimals, 'z');
        TS_ASSERT(sortedAnimals == NULL);
        TS_TRACE("testSortAnimalsByInvalidAttribute");
    }
    void testSortAnimalsByAge1()
    {
        Animal animals[MAX_ANIMALS];
        int numAnimals = 3;
        strcpy(animals[0].name, "cat");
        animals[0].age = 2;
        animals[0].type = CAT;
        strcpy(animals[1].name, "dog");
        animals[1].age = 4;
        animals[1].type = DOG;
        strcpy(animals[2].name, "bird");
        animals[2].age = 1;
        animals[2].type = BIRD;
        Animal *sortedAnimals = sortAnimals(animals, numAnimals, 'a');
        TS_ASSERT_EQUALS(sortedAnimals[0].type, BIRD);
        TS_ASSERT_EQUALS(sortedAnimals[1].type, CAT);
        TS_ASSERT_EQUALS(sortedAnimals[2].type, DOG);

        free(sortedAnimals);
    }
    void testSortAnimalsByType1()
    {
        Animal animals[MAX_ANIMALS];
        int numAnimals = 3;
        strcpy(animals[0].name, "cat");
        animals[0].age = 2;
        animals[0].type = CAT;
        strcpy(animals[1].name, "dog");
        animals[1].age = 4;
        animals[1].type = DOG;
        strcpy(animals[2].name, "bird");
        animals[2].age = 1;
        animals[2].type = BIRD;
        Animal *sortedAnimals = sortAnimals(animals, numAnimals, 'n');
        TS_ASSERT_EQUALS(sortedAnimals[0].type, BIRD);
        TS_ASSERT_EQUALS(sortedAnimals[1].type, CAT);
        TS_ASSERT_EQUALS(sortedAnimals[2].type, DOG);

        free(sortedAnimals);
    }
    ///////////////////////////////////////////////////////////////////////////////////
    void testCountAnimalsByTypeDuplicateAnimalType()
    {
        Animal animals[MAX_ANIMALS] = {
            {"Tom", 2, CAT},
            {"Max", 3, DOG},
            {"Tweety", 1, BIRD},
            {"Jerry", 1, MOUSE},
            {"Minnie", 2, MOUSE},
            {"Garfield", 5, CAT},
        };
        int numAnimals = 6;
        AnimalCount *counts = countAnimalsByType(animals, numAnimals);
        TS_ASSERT(counts == NULL);
    }
    void testCountAnimalsByTypeMultipleSame()
    {
        Animal animals[5] = {
            {"Simba", 5, CAT},
            {"Nala", 3, CAT},
            {"Pongo", 2, DOG},
            {"Perdita", 1, DOG},
            {"Tweety", 1, BIRD}};
        int numAnimals = 5;
        AnimalCount *counts = countAnimalsByType(animals, numAnimals);
        TS_ASSERT_EQUALS(counts[0].count, 2);
        TS_ASSERT_EQUALS(counts[0].type, CAT);
        TS_ASSERT_EQUALS(counts[1].count, 2);
        TS_ASSERT_EQUALS(counts[1].type, DOG);
        TS_ASSERT_EQUALS(counts[2].count, 1);
        TS_ASSERT_EQUALS(counts[2].type, BIRD);
        free(counts);
    }
    void testCountAnimalsByTypeAllSame()
    {
        Animal animals[4] = {
            {"Garfield", 5, CAT},
            {"Tom", 2, CAT},
            {"Sylvester", 3, CAT},
            {"Felix", 1, CAT}};
        int numAnimals = 4;
        AnimalCount *counts = countAnimalsByType(animals, numAnimals);
        TS_ASSERT_EQUALS(counts[0].count, 4);
        TS_ASSERT_EQUALS(counts[0].type, CAT);
        TS_ASSERT_EQUALS(counts[1].count, 0);
        TS_ASSERT_EQUALS(counts[1].type, DOG);
        TS_ASSERT_EQUALS(counts[2].count, 0);
        TS_ASSERT_EQUALS(counts[2].type, BIRD);
        free(counts);
    }
};