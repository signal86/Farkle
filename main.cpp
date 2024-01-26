#include <iostream>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "Player.cpp"

using std::string;


int main() {

  // Generating players
  int playerNumber = -1;
  string* _players = new string[100]; // temp variable | DONT CHANGE UNLESS CHANGING LINE 41
  string in;

  while (in != "end" && in != "exit") {
    playerNumber++;
    std::cout << "exit OR end TO STOP CREATING NEW PLAYERS" << std::endl;
    std::cout << "Player " << playerNumber + 1 << " Name:" << std::endl;
    getline(std::cin, in);
    if (playerNumber == 99) {
      std::cout << "Player limit reached" << std::endl;
      in = "end";
    }
    if (in != "end" && in != "exit") { _players[playerNumber] = in; }
    std::cout << std::endl;
  }

  Player players[playerNumber]; // the real list of players
  
  for (int i = 0; i < playerNumber; i++) { // swapping arrays to save memory without UD
    players[i] = Player(_players[i]);
  }
  delete[] _players; // LINE 20



  // Player listing / verification
  #ifdef _WIN32
  Sleep(1000);
  system("cls");
  std::cout << "\nPlayers:\n\n";
  #else
  sleep(1);
  std::cout << "\033[2J\033[1;1H\nPlayers:\n\n"; // clear terminal
  #endif
  
  for (int i = 0; i < playerNumber; i++) {
    std::cout << players[i].username << std::endl;
  }

  #ifdef _WIN32
  Sleep(3000);
  #else
  sleep(3);
  #endif



  // Game logic
  int player = 0;
  bool playing = true;

  while (playing) {
    
    if (player == 0) { // leaderboard system
      system("cls");
      //std::cout << "\033[2J\033[1;1H\nLEADERBOARD\n\n";
      std::cout << "\nLEADERBOARD\n\n";
      for (int i = 0; i < playerNumber; i++) {
        std::cout << players[i].username << " - " << players[i].score << std::endl;
      }
      #ifdef _WIN32
      Sleep(3000);
      #else
      sleep(3);
      #endif
    }

    
    try { // turns
      players[player].startTurn();
      if (player + 1 == playerNumber) {
        player = -1;
      } player++;
    }
    catch (...) { // extra exception handling, UD doesnt care though so
      player = 0;
      continue;
    }
  }
  
  return 0;
  
}