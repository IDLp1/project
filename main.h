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
#include <ctime>

using namespace std;
using namespace sf;

#define DEFAULT_SCREEN_W    1280
#define DEFAULT_SCREEN_H    720
#define FPS_LIMIT           60

#define CURRENT     0
#define MIN         0
#define MAX         1
#define _W           0
#define _H           1

#define MAX_TEXTURES        16

#define MAX_CONST_CHAR      128
#define MAX_CELLS           0x10000
#define MAX_DECORATION      0x10000
#define MAX_CELLSPROT       16
#define MAX_SPRITE_CELL     16
#define MAX_DECPROT         8

#define MAX_FRACTION        4
#define MAX_WARRIOR         64

const char name_game[] = "PROJECT-E";
const char c_tex_dev_unit[] = "sprites/dev_unit.png";

int random(int min, int max);
double random(double min, double max);
void strclear(char* str);
void DrawCells(RenderWindow* window);
void DrawDecorations(RenderWindow* window);
#endif // MAIN

