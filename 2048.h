/**
 * anagrams.h
 *
 * Thomas Lextrait
 * thomas.lextrait@gmail.com
 */

#include "dictionary.h"

/**
* Returns all anagrams for given word, including word itself
* @param word
*/
void displayAnagrams(char* word);

Dictionary* getWordPermutations(char* word);

void getNextPermutations(Dictionary* dict, int start, int len, char* word);

/**
* Swaps two char pointers
*/
void swap(char *x, char *y);

/**
* Counts the number of unique permutations possible for given word
* @param word
* @return number of permutations
*/
int countUniquePermutations(char* word);

/**
* Computes a factorial iteratively
*/
int factorial(int n);

/**
* Prints a help message
*/
void printHelp();

/**
* Display Big O information
*/
void printBigO();
