#ifndef MAIN
#define MAIN

#include <iostream>
#include <fstream>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <cstdio>
#include <cstring>

using namespace std;
using namespace sf;

#define DEFAULT_SCREEN_W    1280
#define DEFAULT_SCREEN_H    720
#define FPS_LIMIT           60

#define CURRENT     0
#define MAX         1

#define MAX_TEXTURES    16

#define MAX_CONST_CHAR  128
#define MAX_CELLS   0x10000
#define MAX_CELLSPROT   16
#define MAX_SPRITE_CELL 16

const char name_game[] = "PROJECT-E";

int random(int min, int max);
double random(double min, double max);
void strclear(char* str);
void DrawCells(RenderWindow* window);
#endif // MAIN

