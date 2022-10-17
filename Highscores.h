#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

class Highscores {
 public:
  std::string fname;
  int numScores;
  int *scores;
  int highscore;


  Highscores();

  void calcHighscore();
  void read();
  void write(int score);

};

#endif