#include "RemoveDups.hpp"
#include "CppUTest/TestHarness.h"

TEST_GROUP(RemoveDupsTests)
{
   const char* testStrings [9] = 
   {
      "AB",
      "AAA  BBB AAA",
      "A",
      "AA",
      "AAA",
      "AA  ",
      "ABC DEF",
      "A A A A  A  A A A ",
      "ABC CCCCCCCCCDCCDDCCAABDDDS"
   };

   const char* expectedOutput[9] = 
   {
      "AB",
      "A B A",
      "A",
      "A",
      "A",
      "A ",
      "ABC DEF",
      "A A A A A A A A ",
      "ABC CDCDCABDS",
   };
};

TEST(RemoveDupsTests, Test)
{
   for(int i = 0; i < 9; i++)
   {
      char buffer[32]{};
      strncpy(buffer, testStrings[i], strlen(testStrings[i]));
      removeDups(buffer);
      STRCMP_EQUAL(expectedOutput[i], buffer);
   }
}
