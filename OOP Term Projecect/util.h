#pragma once
#include "main.h"

#ifndef KEY_CODE
#define KEY_CODE

// 키보드 값
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SUBMIT 13
#define BACKSPACE 8

#endif

void init();
void gotoxy(int, int);
int randQuarter();
int keyControl();
void titleDraw();
int menuDraw();
bool* optionDraw(bool*);
void infoDraw();
int randSpeed();