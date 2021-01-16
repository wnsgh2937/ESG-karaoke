#pragma once
#pragma warning(disable : 4996)
#pragma comment(lib,"winmm.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <mmsystem.h>
#include <string.h>
#include <time.h>
#include "DB.h"
#include "queue.h"

/*
	사용법 :

	play(song* data)
	-> 성공시, 아무것도 반환 안함.
	-> 실패시, NULL  반환

*/

void gotoxy(int x, int y)
{
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void* set_lyricData(char* lyricPath) {
	FILE* fin;
	queue* data = create();
	int runtime;
	if (0 == fopen_s(&fin, lyricPath, "rt")) {
		char* tmp = (char*)malloc(sizeof(char) * 100);
		fgets(tmp, 99, fin);
		sscanf(tmp, "%d", &runtime);
		free(tmp);
		while (1) {
			lyricData newdata;
			char tmp[10];
			fgets(tmp, 9, fin);
			fgets(newdata.lyric, 99, fin);
			if (strcmp(tmp, "EOF") == 0 || strcmp(newdata.lyric, "EOF") == 0) {
				newdata.time = runtime;
				strcpy(newdata.lyric, " ");
				enqueue(data, &newdata);
				break;
			}
			sscanf(tmp, "%d", &(newdata.time));
			enqueue(data, &newdata);
		}
		return data;
	}
	else {
		free(data);
		return NULL;
	}

}

void stop_lyric(void* isDone) {
	int* done = (int*)isDone;
	while (1) {
		*done = getch();
		if (*done) break;
	}
}

void start(char* mp3Path, queue* data, song* songData) {
	PlaySound(TEXT(mp3Path), NULL, SND_FILENAME | SND_ASYNC);

	int start = clock();
	system("cls");
	int x = 0;
	int y = 0;
	gotoxy(x + 20, y + 10); printf("%d / %s - %s\n", songData->key, songData->title, songData->singer);
	int order = 0;
	int isDone = 0;
	_beginthread(stop_lyric, 0, (void*)&isDone);
	if (peek(data)->data.time > 3000) {
		gotoxy(x + 15, y + 20); printf("☆ %s", peek(data)->data.lyric);
		Sleep(peek(data)->data.time - 3000);
		gotoxy(x + 15, y + 19); printf("3!");
		Sleep(1000);
		gotoxy(x + 15, y + 19); printf("2!");
		Sleep(1000);
		gotoxy(x + 15, y + 19); printf("1!");
		Sleep(1000);
		system("cls");
	}
	else {
		gotoxy(x + 15, y + 20); printf("☆ %s", peek(data)->data.lyric);
		gotoxy(x + 15, y + 19); printf("3!");
		Sleep(peek(data)->data.time / 3);
		gotoxy(x + 15, y + 19); printf("2!");
		Sleep(peek(data)->data.time / 3);
		gotoxy(x + 15, y + 19); printf("1!");
		Sleep(peek(data)->data.time / 3);
		system("cls");
	}
	while (1) {
		Qnode* tmp = dequeue(data);
		lyricData* crnt = &(tmp->data);
		if (isDone) break;

		char* line[2];
		int time;

		if (get_size(data) == 1) isDone = 1;
		time = peek(data)->data.time + start - clock();
		gotoxy(x + 20, y + 10); printf("%d / %s - %s\n", songData->key, songData->title, songData->singer);
		if (order == 0) {
			line[0] = crnt->lyric;
			line[1] = peek(data)->data.lyric;
			gotoxy(x + 15, y + 20); printf("★ %s", line[0]);
			gotoxy(x + 25, y + 22); printf("☆ %s", line[1]);
		}
		else if (order == 1) {
			line[0] = peek(data)->data.lyric;
			line[1] = crnt->lyric;
			gotoxy(x + 15, y + 20); printf("☆ %s", line[0]);
			gotoxy(x + 25, y + 22); printf("★ %s", line[1]);
		}
		Sleep(time);
		free(tmp);
		system("cls");
		order = (order + 1) % 2;
		if (isDone) break;
	}
	system("cls");
	PlaySound(NULL, 0, 0);
}
void* play(song* songData) {
	char* title = songData->title;
	char* singer = songData->singer;
	char mp3Path[100] = "src\\mp3\\"; strcat(mp3Path, title); strcat(mp3Path, "-"); strcat(mp3Path, singer);
	char lyricPath[100] = "src\\lyric\\"; strcat(lyricPath, title); strcat(lyricPath, "-"); strcat(lyricPath, singer); strcat(lyricPath, ".txt");
	queue* data = set_lyricData(lyricPath);
	if (data == NULL) {//가사 불러오기 실패.
		return NULL;
	}
	else {
		start(mp3Path, data, songData);
		clearQ(data);
		free(data);
		return (void*)songData;
	}
}