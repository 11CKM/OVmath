#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"

#define QUEUR_SIZE 7

typedef struct Queur
{
	uint8_t data[QUEUR_SIZE];
	uint8_t head;// 队头指针(出队位置)
	uint8_t tail;
    uint8_t size;
} Queur;

void Queur_Init(Queur *queur);

void Queur_Push(Queur *queur, uint8_t data);

uint8_t Queur_Pop(Queur *queur);

bool Queur_IsEmpty(Queur *queur);

bool Queur_IsFull(Queur *queur);

uint8_t Queur_GetSize(Queur *queur);
