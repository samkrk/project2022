#include "Highscores.h"

#include <fstream>
#include <iostream>

Highscores::Highscores() {
  fname = "highscores.txt";
  read();
}

void Highscores::calcHighscore() {
  highscore = scores[0];
  for (int i = 0; i < numScores; i++) {
    if (scores[i] < highscore) {
      highscore = scores[i];
    }
  }
}

void Highscores::read() {
  numScores = 0;
  std::fstream myfile;
  myfile.open(fname, std::ios::in);
  int input = 1;
  while (1) {
    myfile >> input;
    if (input == -1) {
      break;
    }
    numScores++;
  }
  myfile.close();
  myfile.open(fname, std::ios::in);
  scores = new int[numScores];
  for (int i = 0; i < numScores; i++) {
    myfile >> scores[i];
  }
  calcHighscore();
}

void Highscores::write(int score) {
  std::fstream myfile;
  myfile.open(fname, std::ios::out);
  for (int i = 0; i < numScores; i++)
  {
    myfile << scores[i] << "\n";
  }
  myfile << score << "\n";
  myfile << "-1\n";
  myfile.close();
}