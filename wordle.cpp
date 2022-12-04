// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
//by reference 
std::set<std::string> wordleHelper(
  std::set<std::string>& usefulWords,
  std::string& possibleWords,
  std::string& floatLetters,
  const std::set<std::string>& dict,
  int pos,
  int spaces);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> usefulWords;
    std::string possibleWords = in;
    std:: string floatYellow = floating;
    int spaces = 0;

    //get the # of spaces 
    for(unsigned int i = 0; i < (unsigned int)in.size(); i++){
      if(in[i] == '-'){
        spaces++;
      }
    }
    //recurse and return usefulWords set
    wordleHelper(usefulWords, possibleWords, floatYellow, dict, 0, spaces);
    return usefulWords;
}

std::set<std::string> wordleHelper(
  std::set<std::string>& usefulWords,
  std::string& possibleWords,
  std::string& floatLetters,
  const std::set<std::string>& dict,
  int pos,
  int spaces)
  {
    //base case,  all spaces are full and possibly word is valid 
    if(pos == (int)possibleWords.size()){
      //word is valid 
      if(dict.find(possibleWords) != dict.end()){
        usefulWords.insert(possibleWords);
      }
      return usefulWords;
    }
    //backtracking implementation
    if(possibleWords[pos] != '-'){
      wordleHelper(usefulWords, possibleWords, floatLetters, dict, pos+1, spaces);
      return usefulWords;
    }
    //floating letter is present 
    if(spaces <= (int)floatLetters.size()){
      //iterate through floating letters and check with that particualr letter 
      for(unsigned int i = 0; i < (unsigned int)floatLetters.size();i++){
        std::string temp = floatLetters;
        possibleWords[pos] = floatLetters[i];
        floatLetters.erase(floatLetters.find(floatLetters[i]), 1);
        wordleHelper(usefulWords, possibleWords, floatLetters, dict, pos, spaces-1);
          floatLetters = temp;
      }
      //reverse back to '-' after done 
      possibleWords[pos] = '-';
    }
    else if(spaces > (int)floatLetters.size()){
      //Go through entire alphabet and recurse 
      for(char letter = 'a';letter <= 'z';letter++){
        possibleWords[pos] = letter;
        //letter is in the floating letters 
        if(floatLetters.find(letter) != floatLetters.npos){
          std::string temp = floatLetters;
          floatLetters.erase(floatLetters.find(letter),1);
          wordleHelper(usefulWords,possibleWords,floatLetters, dict, pos, spaces-1);
          floatLetters = temp;
        }
        //keep recursing since letter is not in floating letters
        else{
          wordleHelper(usefulWords, possibleWords, floatLetters, dict, pos, spaces-1);
        }
      }
      //reverse back to '-' after done
      possibleWords[pos] = '-';
    }
    return usefulWords;
  }
//the user will provide you an input of how many letters the word is
//what letters have already been guessed in their correct location
//what letters have already been guessed in their correct location

