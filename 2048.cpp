/**
 * anagrams.cpp
 *
 * Thomas Lextrait
 * thomas.lextrait@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for command-line flags

#include "anagrams.h"

// Global flags
bool f_printDictWordCount, f_wordStats;

// Dictionary
Dictionary* dict;

int main(int argc, char** argv)
{

    if(argc <= 1){
      printHelp();
      return 0;
    }

    // Flags
    f_printDictWordCount = false;
    f_wordStats = false;

    /*
      Parse command line flags with getopt()
      getopt also sets external (global) variables: 
      char* optarg, int optind, opterr, optopt
    */
    int c, index;
    while((c = getopt(argc, argv, "hwsx")) != -1){
      switch (c){
      case 'h':
        printHelp();
        break;
      case 'w':
        f_printDictWordCount = true;
        break;
      case 's':
        f_wordStats = true;
        break;
      case 'x':
        printBigO();
        break;
      default:
        fprintf(stderr, "Unknown option `-%c', use -h for help.\n", optopt);
        break;
      }
    }

    // Build dictionary
    dict = new Dictionary();
    dict->buildFromFile(); // builds automatically from file referenced in Macro

    if(f_printDictWordCount){
      printf("+ dictionary has %d words.\n", dict->getWordCount());
      printf("+ dictionary has %d character nodes.\n", dict->getTotalNodeCount());
      printf("+ dictionary requires %luMB.\n", sizeof(TTNode)*dict->getTotalNodeCount()/1000000);
    }

    // Parse non-flag arguments
    for(index = optind; index < argc; index++){
      //printf ("Non-option argument %s\n", argv[index]);
      displayAnagrams(argv[index]);
    }
}

/**
* Returns all anagrams for given word, including word itself
* @param word
*/
void displayAnagrams(char* word)
{
  int len = strlen(word);

  if(word && len > 0){

    printf("\n[%s]\n", word);

    int perm_count = factorial(len);
    int uperm_count = countUniquePermutations(word);

    // Display statistics
    if(f_wordStats){
      if(dict->hasWord(word)){
        printf("+ found in dictionary\n");
      }else{
        printf("+ not found in dictionary\n");
      }
      printf("+ %d permutations\n", perm_count);
      printf("+ %d distinct permutations\n", uperm_count);
    }

    Dictionary* perms = getWordPermutations(word);
    int count_valid_perms = 0;

    // Print all permutations
    while(perms->hasNextWord()){
      char* next = perms->getNextWord();
      if(next && dict->hasWord(next)){
        count_valid_perms++;
        printf("'%s'\n", next);
      }
    }

    if(f_wordStats){
      printf("+ %d anagrams in the dictionary\n", count_valid_perms);
    }
  }
}

/**
* Returns all the distinct permutations of given string in a dictionary
* this is essentially a driver function
* @param word
* @return dictionary
*/
Dictionary* getWordPermutations(char* word)
{
  Dictionary* dict = new Dictionary();
  getNextPermutations(dict, 0, strlen(word), word);
  return dict;
}

void getNextPermutations(Dictionary* dict, int start, int len, char* word)
{
  if(word){
    if(start == len-1){
      dict->addWord(word);
    }else{
      for(int i=start; i<len; i++){
        swap(word+start, word+i);
        getNextPermutations(dict, start+1, len, word);
        swap(word+start, word+i);
      }
    }
  }
}

/**
* Swaps two char pointers
*/
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/**
* Counts the number of unique permutations possible for given word, 
* this is case insensitive
* @param word
* @return number of permutations
*/
int countUniquePermutations(char* word)
{
  /*
    Theory:
    if there are n total chars in a string and
    the letter 'a' shows up n1 times, the letter 'b' shows up n2 times...
    then the total number of distinct permutations is :
    n!/(n1! * n2! * n3! ...)
  */
  if(word){

    int len = strlen(word);

    if(len > 0){

      // We need to count each character
      int* ASCII = new int[MAX_CHARSET];

      // Set all counts to zero
      for(int i=0; i<MAX_CHARSET; i++) ASCII[i] = 0;

      for(int i=0; i<len; i++){
        ASCII[(int)lowerCase(word[i])]++;
      }

      int top = factorial(len);
      int bottom = 1;

      for(int i=0; i<MAX_CHARSET; i++){
        if(ASCII[i] > 0){
          bottom *= factorial(ASCII[i]);
        }
      } 

      return top/bottom;

    }else{
      return 0;
    }
  }else{
    return 0;
  }
}

/**
* Computes a factorial iteratively
*/
int factorial(int n)
{
    int ret = 1;
    for(int i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}

/**
* Prints a help message
*/
void printHelp()
{
    printf("\nAnagrams is a C++ program that returns all English word anagrams for given words.\n");
    printf("author:\tThomas Lextrait, thomas.lextrait@gmail.com, Feb 2014\n");
    printf("usage:\t./anagrams [-h] [-s] [-w] [x] WORDS...\n");
    printf("\t-h\tDisplay help\n");
    printf("\t-s\tDisplay statistics for each word\n");
    printf("\t-w\tCount and display the number of words in the dictionary\n");
    printf("\t-x\tDisplay big O information\n\n");
}

/**
* Display Big O information
*/
void printBigO()
{
  printf("Coming soon...\n");
}
