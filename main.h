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

#define DEFAULT_SCREEN_W    1366
#define DEFAULT_SCREEN_H    768
#define FPS_LIMIT           60

#define CURRENT     0
#define MIN         0
#define MAX         1
#define _W           0
#define _H           1

#define MAX_TEXTURES        16
#define MAX_TEX_WEAPONS     8

#define MAX_CONST_CHAR      128
#define MAX_CELLS           0x10000
#define MAX_DECORATION      0x10000
#define MAX_CELLSPROT       16
#define MAX_SPRITE_CELL     16
#define MAX_DECPROT         8

#define MAX_FRACTION        4



const float cf_camera_speed = 10.0;

const char name_game[] = "PROJECT-E";
const char c_tex_dev_unit[] = "sprites/dev_warrior.png";
const char c_dir_hud_order[] = "sprites/hud_order.png";
const char c_main_font[] = "pala.ttf";

const char c_could_not_open[] = "Could not open ";
const char c_error[] = "ERROR: ";
const char c_loading[] = "Loading: ";

const int  ci_move_ms = 500;
const float cf_offset_move_order = 10.0;

int random(int min, int max);
int random(unsigned int min, unsigned int max);
double random(double min, double max);
void strclear(char* str);
bool CheckFordable(Vector2i _vector);
Vector2i GetPosition(const Vector2f _vector);
void DrawCells(RenderWindow* window);
void DrawDecorations(RenderWindow* window);
void DrawInventory(RenderWindow* window);
void DrawWarriors(RenderWindow* window);

#endif // MAIN

