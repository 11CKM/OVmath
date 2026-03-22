#include "useQueur.h"

void Queur_Init(Queur *queur)
{
	queur->head = 0;
	queur->tail = 0;
    queur->size = 0;
}
//入队操作
void Queur_Push(Queur *queur, uint8_t data)
{
	if (Queur_IsFull(queur)) {
		return; // 队列已满,不执行入队
	}
	queur->data[queur->tail] = data;
	queur->tail = (queur->tail + 1) % QUEUR_SIZE;
	queur->size++;
}

//出队操作
uint8_t Queur_Pop(Queur *queur)
{
	if (Queur_IsEmpty(queur)) {
		return 0; // 队列为空,返回0(或可根据需求返回错误码)
	}
	uint8_t data = queur->data[queur->head];
	queur->head = (queur->head + 1) % QUEUR_SIZE;
	queur->size--;
	return data;
}
//判断队列是否为空
bool Queur_IsEmpty(Queur *queur)
{
	return queur->size == 0;
}
//判断队列是否已满
bool Queur_IsFull(Queur *queur)
{
	return queur->size == QUEUR_SIZE;
}
//获取队列当前元素数量
uint8_t Queur_GetSize(Queur *queur)
{
	return queur->size;
}


