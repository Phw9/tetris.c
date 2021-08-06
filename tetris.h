#ifndef __TETRIS_H__
#define __TETRIS_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACEBAR 32
#define p 112
#define P 80
#define ESC 27


#define TRUE 1
#define FALSE 0

int key_down(char key);
void move_B(int* cen, char k);
void show_screen(char*** s);
void block_coord_rel(int** coor, int a_R, int a_C, int b_R, int b_C, int c_R, int c_C, int d_R, int d_C);
void make_block_coord(int** coor, int B_type, int B_spin);
int B_rotate(int spin);
int Brev_rotate(int spin);
void put_coord(int** c, int** n);
void make_block(char*** s, int** rel_coor, int M, int N);
void del_block(char*** s, int** rel_coor, int M, int N);
int put_block(char*** s, int** rel_coor, int* cen);
int fin_row(char*** s, int R);
void del_row(char*** s);


#endif