#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {
	int time;
	char lyric[100];
}lyricData;


typedef struct {
	lyricData data;
	struct Qnode* next;
	struct Qnode* pre;
}Qnode;

typedef struct {
	Qnode* head;
	Qnode* tail;
	int size;
}queue;


Qnode* creatNewQnode(lyricData* ld) {
	Qnode* newQnode = (Qnode*)malloc(sizeof(Qnode));
	newQnode->next = NULL;
	newQnode->pre = NULL;
	newQnode->data.time = ld->time;
	strcpy(newQnode->data.lyric, ld->lyric);
	return newQnode;
}

queue* create() {
	queue* new = (queue*)malloc(sizeof(queue));
	new->head = NULL;
	new->tail = NULL;
	new->size = 0;
}


void enqueue(queue* l, lyricData* newdata) {
	Qnode* newQnode = creatNewQnode(newdata);
	if (l->head == NULL) {
		l->head = newQnode;
		l->tail = newQnode;
	}
	else {
		l->tail->next = newQnode;
		newQnode->pre = l->tail;
		l->tail = newQnode;
	}
	l->size++;
}

Qnode* dequeue(queue* l) {
	Qnode* delQnode = l->head;
	if (l->tail == NULL) {
		return NULL;
	}
	else {
		if (l->head->next == NULL && l->tail->pre == NULL) {
			l->head = NULL;
			l->tail = NULL;
		}
		else {
			Qnode* nextQnode = l->head->next;
			l->head->next = NULL;
			nextQnode->pre = NULL;
			l->head = nextQnode;
		}
		l->size--;
		return delQnode;
	}
}

Qnode* peek(queue* l) {
	return l->head;
}

int isEmptyQ(queue* l) {
	if (l->head != NULL) {
		return 0;
	}
	else {
		return 1;
	}
}

void clearQ(queue* l) {
	Qnode* tmp;
	while (l->head != NULL) {
		tmp = l->head;
		l->head = tmp->next;
		free(tmp);
		tmp = NULL;
	}
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}

void deleteHead(queue* l) {
	if (l->tail == NULL) {
		return NULL;
	}
	else {
		if (l->head->next == NULL && l->tail->pre == NULL) {
			l->head = NULL;
			l->tail = NULL;
		}
		else {
			Qnode* nextQnode = l->head->next;
			l->head->next = NULL;
			nextQnode->pre = NULL;
			l->head = nextQnode;
		}
		l->size--;
		return;
	}
}

int get_size(queue* q) {
	return q->size;
}
