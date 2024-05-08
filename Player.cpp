#include <iostream>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "Dice.cpp"

using std::string;

class Player {
  public:
    int score = 0;
    int roll[6] = {};
    Dice dice[6] = {Dice(), Dice(), Dice(), Dice(), Dice(), Dice()};
    int turnScore = 0;
    string username;
    bool ignore;

    Player() {}
    Player(string name) : username(name) { }

    void startTurn() {
      #ifdef _WIN32
      Sleep(2000);
      system("cls");
      #else
      sleep(2);
      //std::cout << "\033[2J\033[1;1H";
      #endif
      turnScore = 0;
      string _upperName = username;
      transform(_upperName.begin(), _upperName.end(), _upperName.begin(), ::toupper);
      std::cout << std::endl << std::endl << _upperName << "\nBegin turn!\n";
      play();
    }

    void exitTurn() {
      score += turnScore;
      string _upperName = username;
      transform(_upperName.begin(), _upperName.end(), _upperName.begin(), ::toupper);
      std::cout << std::endl << std::endl << std::endl << _upperName << "\nTurn ended!\n" << turnScore << " points this turn\n" << "Total Score: " << score << std::endl << std::endl;
      turnScore = 0;
      #ifdef _WIN32
      Sleep(2000);
      #else
      sleep(2);
      #endif
    }

    void play() {
      std::cout << "\nDo you want to roll (Y) or skip turn (N)?\n";
      char _turn = ' ';
      try { std::cin >> _turn; } catch(...) { return; }
      
      if (_turn == 'y') {
        for (int i = 0; i < 6; i++) { dice[i].active = true; }
        std::cout << std::endl << std::endl;
        while (turn() == 1) { }
      }
      else if (_turn == 'n') {
        exitTurn();
      }
      else {
        _turn = 'n';
        std::cout << "\nInvalid\n";
        exitTurn();
      }
    }

    int modifyScore(int selection, int count, int n, int singleIncrease, int tripleIncrease) { // selected count to remove, how many rolls that number has actually had, physical number, singular value increase, 3 value increase
      if (selection > count) {
          std::cout << "You cannot select more than you have." << std::endl;
          return 0;
        }
        
        else if (selection < 0) {
          std::cout << "You must select a number between 1 and 6." << std::endl;
          return 0;
        }

        else if (selection == 0) {
          return 0;
        }

        else {
          int ret = 0;
          if (singleIncrease == 0) {
            if (selection < 3) {
              std::cout << "You cannot select less than 3 unless the number is 1 or 5." << std::endl;
              return 0;
            }
          }
          if (selection == 6) {
            turnScore += (tripleIncrease * 2);
            ret = tripleIncrease * 2;
          }
          else if (selection >= 3) {
            if (singleIncrease == 0) { selection = 3; }
            turnScore += tripleIncrease;
            selection -= 3;
            turnScore += singleIncrease * selection;
            ret = (tripleIncrease) + (singleIncrease * selection);
            selection += 3;
          }
          else {
            turnScore += singleIncrease * selection;
            ret = singleIncrease * selection;
          }

          std::cout << "Removing " << selection << " dice." << std::endl;

          int found = 0;
          for (int i = 0; i < 6; i++) {
            
            if (dice[i].active) {
              if (dice[i].holding == n) {
                if (found != selection) {
                  dice[i].active = false;
                  found++;
                }
              }
            }
            
          }

          std::cout << "New turn score: " << turnScore << std::endl << std::endl;

          return ret;
          
        }
    }

    int turn() {
      
      int _tempScore = 0;
      int _ones = 0, _twos = 0, _threes = 0, _fours = 0, _fives = 0, _sixes = 0;
      int diceCount = 0;
      for (int i = 0; i < 6; i++) {
        if (dice[i].active) { diceCount++; }
      }
      std::cout << std::endl << "Rolling " << diceCount << " dice." << std::endl;
      

      // Roll dice
      for (int i = 0; i < 6; i++) {
        if (not dice[i].active) { continue; }
        dice[i].roll();
        switch (dice[i].holding) {
          case 1:
            _ones++;
            break;
          case 2:
            _twos++;
            break;
          case 3:
            _threes++;
            break;
          case 4:
            _fours++;
            break;
          case 5:
            _fives++;
            break;
          case 6:
            _sixes++;
            break;
        }
      } std::cout << "Rolls:" << std::endl << _ones << " ones; " << _twos << " twos; " << _threes << " threes; " << _fours << " fours; " << _fives << " fives; " << _sixes << " sixes" << std::endl << std::endl;

      int selection;
      if (_ones > 0) {
        std::cout << "How many ones to use?" << std::endl;
        try { std::cin >> selection; } catch(...) { selection = 0; }
        _tempScore += modifyScore(selection, _ones, 1, 100, 1000);
      }
      if (_twos >= 3) {
        std::cout << "How many twos to use?" << std::endl;
        try { std::cin >> selection; }
        catch(...) { selection = 0; }
        _tempScore += modifyScore(selection, _twos, 2, 0, 200);
      }
      if (_threes >= 3) {
        std::cout << "How many threes to use?" << std::endl;
        try { std::cin >> selection; } catch(...) { selection = 0; }
        _tempScore += modifyScore(selection, _threes, 3, 0, 300);
      }
      if (_fours >= 3) {
        std::cout << "How many fours to use?" << std::endl;
        try { std::cin >> selection; } catch(...) { selection = 0; }
        _tempScore += modifyScore(selection, _fours, 4, 0, 400);
      }
      if (_fives > 0) {
        std::cout << "How many fives to use?" << std::endl;
        try { std::cin >> selection; } catch(...) { selection = 0; }
        _tempScore += modifyScore(selection, _fives, 5, 50, 500);
      }
      if (_sixes >= 3) {
        std::cout << "How many sixes to use?" << std::endl;
        try { std::cin >> selection; } catch(...) { selection = 0; }
        _tempScore += modifyScore(selection, _sixes, 6, 0, 600);
      }
      
      if (_tempScore == 0) {
        std::cout << std::endl << "FARKLE" << std::endl << std::endl;
        turnScore = 0;
        exitTurn();
        return 0;
      }

      else {
        string end = "n";
        bool hotDice = true;
        for (int i = 0; i < 6; i++) { if (dice[i].active) { hotDice = false; } }
        if (hotDice) {
          for (int i = 0; i < 6; i++) { dice[i].active = true; }
          std::cout << std::endl << "HOT DICE" << std::endl << std::endl;
        }
        std::cout << "End turn? (y/n)" << std::endl;
        std::cin >> end;
        if (end == "n") {
          std::cout << "\nContinuing turn!" << std::endl;
          return 1;
        }
        else {
          std::cout << "\nEnding turn." << std::endl;
          exitTurn();
          return 0;
        }
      }
        
      // MISTAKE: redo, if a dice doesnt count as a score then it can be reused, but one dice must be removed if there is a score, if zero of them score then the turn is dead, hot dice means you get all dice back
      // NEED TO REDO THE ENTIRE METHOD OH MY GOD!!!!!
      // Read 'Play' this time instead of just scoring AGHHHH
      // cool dice function though?
      // https://en.wikipedia.org/wiki/Farkle
      // you can exit a turn at any time
      // farkle still means that everything from that turn is dead, including hot dice

      return 1; // 0 = farkle/no score/end play; 1 = normal score/hot dice/continue play
    }
};