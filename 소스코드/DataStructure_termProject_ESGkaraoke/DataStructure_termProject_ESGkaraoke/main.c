#pragma warning(disable : 4996)
#pragma comment(lib,"winmm.lib")
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<mmsystem.h>
#include <process.h>
#include "lyric.h"
#define SINGER_SIZE 100

void search_number(tree* t, int* num);
void gotoxy(int x, int y);
void end_page();
void search_title(tree* t, int* num);
void coin_insert_page(int* num);
void main_page(int* num);
void search_singer(tree* t, int* num);
void popular_song(tree* t, int* num, song hotsong[3][13][100]);

int main(void)
{
	system("title CoronaKaraoke");
	system("color 3F");
	song hotSong[3][13][100];
	tree* t = createNewTree();
	readData(hotSong, t);
	char k;

	int x = 0, y = 0;
	int s;
	int num = 0;
	main_page(&num);
	while (1)
	{
		s = getch();
		if (s == '1') { num++; coin_insert_page(&num); }
		else if (s == '2') { search_singer(t, &num); }
		else if (s == '3') { search_title(t, &num); }
		else if (s == '4') { search_number(t, &num); }
		else if (s == '5') { popular_song(t, &num, hotSong); }
		else if (s == '6') { end_page(); break; }
	}
	gotoxy(x, y + 28); system("pause");

}


void end_page()	//프로그램 종료 interface
{
	int x = 5;
	int y = 5;

	gotoxy(x + 13, y + 3); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	gotoxy(x + 13, y + 4); printf("▤                              ▤");
	gotoxy(x + 13, y + 5); printf("▤                              ▤");
	gotoxy(x + 13, y + 6); printf("▤    프로그램을 종료합니다^^   ▤");
	gotoxy(x + 13, y + 7); printf("▤     Press any button         ▤");
	gotoxy(x + 13, y + 8); printf("▤                              ▤");
	gotoxy(x + 13, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	Sleep(200);
}

void search_title(tree* t, int* num)	//제목 검색 interface
{
	system("cls");
	int song_number = 0;;
	int s;
	char o = NULL;
	int x = 0;
	int y = 0;
	char title_name[100];
	gotoxy(x, y + 0); printf("┌─────────────────┐\n");
	gotoxy(x, y + 1); printf("│＃가수 검색      │\n");
	gotoxy(x, y + 2); printf("└─────────────────┘\n");
	gotoxy(x + 10, y); printf("┌──────────────┐\n");
	gotoxy(x + 10, y + 1); printf("│＃메인 화면(1)│\n");
	gotoxy(x + 10, y + 2); printf("└──────────────┘\n");
	gotoxy(x + 18, y + 0); printf("┌──────────────┐\n");
	gotoxy(x + 18, y + 1); printf("│＃노래 시작(2)│\n");
	gotoxy(x + 18, y + 2); printf("└──────────────┘\n");
	gotoxy(x + 26, y + 0); printf("┌──────────────┐\n");
	gotoxy(x + 26, y + 1); printf("│＃재검색 (3)  │\n");
	gotoxy(x + 26, y + 2); printf("└──────────────┘\n");
	gotoxy(x, y + 3); printf("▶ 제목을 입력해 주세요: ");
	scanf("%s", title_name);
	int idx = 0;
	song* titleData[100];
	song* data = NULL;
	find_title(t, titleData, &idx, title_name);
	if (idx == 0)
	{
		gotoxy(x, y + 8); printf("Error");
	}
	int p = 0;

	while (1)
	{
		system("cls");
		gotoxy(x, y + 0); printf("┌─────────────────┐\n");
		gotoxy(x, y + 1); printf("│＃가수 검색      │\n");
		gotoxy(x, y + 2); printf("└─────────────────┘\n");
		gotoxy(x + 10, y); printf("┌──────────────┐\n");
		gotoxy(x + 10, y + 1); printf("│＃메인 화면(1)│\n");
		gotoxy(x + 10, y + 2); printf("└──────────────┘\n");
		gotoxy(x + 18, y + 0); printf("┌──────────────┐\n");
		gotoxy(x + 18, y + 1); printf("│＃노래 시작(2)│\n");
		gotoxy(x + 18, y + 2); printf("└──────────────┘\n");
		gotoxy(x + 26, y + 0); printf("┌──────────────┐\n");
		gotoxy(x + 26, y + 1); printf("│＃재검색 (3)  │\n");
		gotoxy(x + 26, y + 2); printf("└──────────────┘\n");
		gotoxy(x, y + 3); printf("▶ 제목을 입력해 주세요: %s", title_name);
		gotoxy(x, y + 5); printf("번호         제목                                가수\n\n");
		for (int i = p * 10; i < p * 10 + 10; i++) {
			if (i < idx) {
				printf(" %-5d%-40s%-20s\n\n", i + 1, titleData[i]->title, titleData[i]->singer);
			}
		}
		gotoxy(x + 17, y + 27); printf("%d/%d", p * 10 + 1, idx);
		s = getch();
		if (s == '1') { system("cls");  main_page(num); break; }
		else if (s == '2')
		{
			if (*num == 0) {
				gotoxy(x + 34, y + 1); printf("☆★코인을 충전해주세요☆★");
				Sleep(1000);
			}
			else {

				while (o != '-')
				{
					gotoxy(x + 36, y + 1); printf("▶ 시작할 노래 번호를 입력해 주세요: ");
					scanf(" %d", &song_number);
					data = titleData[song_number - 1];
					gotoxy(x + 36, y + 3); printf("▶노래시작 '-'");
					o = getch();
				}
				if (data)
				{
					(*num)--;
					if (play(data) == NULL)
					{
						system("cls");
						gotoxy(x + 20, y + 4); printf("아직 구현되어있지 않습니다!");
						gotoxy(x + 20, y + 6); printf("▶ 구현 목록\n");
						gotoxy(x + 20, y + 8); printf("  ☞ 흔들리는꽃들속에서네샴푸향이느껴진거야 - 장범준");
						gotoxy(x + 20, y + 10); printf("  ☞ 살짝설렜어(Non-Stop) - 오마이걸");
						gotoxy(x + 20, y + 12); printf("  ☞ 주저하는연인들을위해-잔나비");
						gotoxy(x + 20, y + 14); printf("  ☞ 다섯번째계절 - 오마이걸");
						gotoxy(x + 20, y + 16); printf("  ☞ 벚꽃엔딩 - 버스커버스커");
						gotoxy(x + 20, y + 18); printf("  ☞ 밤편지 - 아이유");
						gotoxy(x + 20, y + 20); printf("  ☞ 폰서트 - 10cm");
						gotoxy(x + 20, y + 22); printf("  ☞ TT - twice");
						Sleep(1900); system("cls"); main_page(num); break;
					}
					else {
						system("cls");
						main_page(num);
						break;
					}
				}
				else { printf("Error!"); }
			}
		}
		else if (s == 224)
		{
			s = getch();
			if (s == 75) ///좌
			{
				if (0 < p) p--;
			}
			else if (s == 77) //우
			{
				if ((p + 1) * 10 < idx)p++;
			}
		}
		else if (s == '3') {
			system("cls");
			search_title(t, num);
			break;
		}
	}
}
void search_number(tree* t, int* num)
{
	system("cls");
	int song_number = 0;
	char o = NULL;
	int s;
	int x = 0;
	int y = 0;
	gotoxy(x, y + 0); printf("┌─────────────────┐\n");
	gotoxy(x, y + 1); printf("│＃번호 검색      │\n");
	gotoxy(x, y + 2); printf("└─────────────────┘\n");
	gotoxy(x + 10, y); printf("┌──────────────┐\n");
	gotoxy(x + 10, y + 1); printf("│＃메인 화면(1)│\n");
	gotoxy(x + 10, y + 2); printf("└──────────────┘\n");
	gotoxy(x + 18, y + 0); printf("┌──────────────┐\n");
	gotoxy(x + 18, y + 1); printf("│＃노래 시작(2)│\n");
	gotoxy(x + 18, y + 2); printf("└──────────────┘\n");
	gotoxy(x, y + 3); printf("▶ 노래 번호를 입력해 주세요: ");
	scanf("%d", &song_number);
	int idx = 0;
	song* singerData[100];
	song* data = find_number(t, song_number);

	if (data == NULL)
	{
		gotoxy(x, y + 8); printf("Error");
		while (data == NULL)
		{
			gotoxy(x, y + 4); printf("▶ 노래 번호를 입력해 주세요: ");
			scanf(" %d", &song_number);
			data = find_number(t, song_number);
		}
	}
	gotoxy(x, y + 8); printf("번호         제목                                가수\n\n\n");
	printf("%-5d%-40s%-20s\n", data->key, data->title, data->singer);
	while (1)
	{
		s = getch();
		if (s == '1') { system("cls");  main_page(num); break; }
		else if (s == '2')
		{
			if (*num == 0) { gotoxy(x + 30, y); printf("☆★코인을 충전해주세요☆★"); }
			else {
				while (o != '-')
				{
					gotoxy(x + 30, y); printf("▶ 시작할 노래 번호를 입력해 주세요: ");
					scanf(" %d", &song_number);
					data = find_number(t, song_number);
					gotoxy(x + 30, y + 3); printf("▶노래시작 '-'");
					o = getch();
				}
				if (data)
				{
					(*num)--;
					if (play(data) == NULL)
					{
						system("cls");
						gotoxy(x + 20, y + 4); printf("아직 구현되어있지 않습니다!");
						gotoxy(x + 20, y + 6); printf("▶ 구현 목록\n");
						gotoxy(x + 20, y + 8); printf("  ☞ 흔들리는꽃들속에서네샴푸향이느껴진거야 - 장범준");
						gotoxy(x + 20, y + 10); printf("  ☞ 살짝설렜어(Non-Stop) - 오마이걸");
						gotoxy(x + 20, y + 12); printf("  ☞ 주저하는연인들을위해-잔나비");
						gotoxy(x + 20, y + 14); printf("  ☞ 다섯번째계절 - 오마이걸");
						gotoxy(x + 20, y + 16); printf("  ☞ 벚꽃엔딩 - 버스커버스커");
						gotoxy(x + 20, y + 18); printf("  ☞ 밤편지 - 아이유");
						gotoxy(x + 20, y + 20); printf("  ☞ 폰서트 - 10cm");
						gotoxy(x + 20, y + 22); printf("  ☞ TT - twice");


						Sleep(1900); system("cls"); main_page(num); break;
					}
					else {
						system("cls");
						main_page(num);
						break;
					}
				}
				else { printf("Error!"); }
			}
		}
	}

}

void search_singer(tree* t, int* num)
{
	system("cls");
	int song_number;
	char singer_name[100];
	char o = NULL;
	int s;
	int x = 0;
	int y = 0;
	gotoxy(x, y + 0); printf("┌─────────────────┐\n");
	gotoxy(x, y + 1); printf("│＃가수 검색      │\n");
	gotoxy(x, y + 2); printf("└─────────────────┘\n");
	gotoxy(x + 10, y); printf("┌──────────────┐\n");
	gotoxy(x + 10, y + 1); printf("│＃메인 화면(1)│\n");
	gotoxy(x + 10, y + 2); printf("└──────────────┘\n");
	gotoxy(x + 18, y + 0); printf("┌──────────────┐\n");
	gotoxy(x + 18, y + 1); printf("│＃노래 시작(2)│\n");
	gotoxy(x + 18, y + 2); printf("└──────────────┘\n");
	gotoxy(x + 26, y + 0); printf("┌──────────────┐\n");
	gotoxy(x + 26, y + 1); printf("│＃재검색 (3)  │\n");
	gotoxy(x + 26, y + 2); printf("└──────────────┘\n");
	gotoxy(x, y + 3); printf("▶ 가수 이름을 입력해 주세요: ");
	scanf("%s", singer_name);
	int idx = 0;
	song* singerData[100];
	song* data = NULL;
	find_singer(t, singerData, &idx, singer_name);
	if (idx == 0)
	{
		gotoxy(x, y + 8); printf("Error");
	}
	int p = 0;

	while (1)
	{
		system("cls");
		gotoxy(x, y + 0); printf("┌─────────────────┐\n");
		gotoxy(x, y + 1); printf("│＃가수 검색      │\n");
		gotoxy(x, y + 2); printf("└─────────────────┘\n");
		gotoxy(x + 10, y); printf("┌──────────────┐\n");
		gotoxy(x + 10, y + 1); printf("│＃메인 화면(1)│\n");
		gotoxy(x + 10, y + 2); printf("└──────────────┘\n");
		gotoxy(x + 18, y + 0); printf("┌──────────────┐\n");
		gotoxy(x + 18, y + 1); printf("│＃노래 시작(2)│\n");
		gotoxy(x + 18, y + 2); printf("└──────────────┘\n");
		gotoxy(x + 26, y + 0); printf("┌──────────────┐\n");
		gotoxy(x + 26, y + 1); printf("│＃재검색 (3)  │\n");
		gotoxy(x + 26, y + 2); printf("└──────────────┘\n");
		gotoxy(x, y + 3); printf("▶ 가수 이름을 입력해 주세요: %s", singer_name);
		gotoxy(x, y + 5); printf("번호         제목                                가수\n\n");
		for (int i = p * 10; i < p * 10 + 10; i++) {
			if (i < idx) {
				printf(" %-5d%-40s%-20s\n\n", i + 1, singerData[i]->title, singerData[i]->singer);
			}
		}
		gotoxy(x + 17, y + 27); printf("%d/%d", p * 10 + 1, idx);
		s = getch();
		if (s == '1') { system("cls");  main_page(num); break; }
		else if (s == '2')
		{
			if (*num == 0) {
				gotoxy(x + 34, y + 4); printf("☆★코인을 충전해주세요☆★");
				Sleep(1000);
			}
			else {

				while (o != '-')
				{
					gotoxy(x + 36, y + 1); printf("▶ 시작할 노래 번호를 입력해 주세요: ");
					scanf(" %d", &song_number);
					data = singerData[song_number - 1];
					gotoxy(x + 36, y + 3); printf("▶노래시작 '-'");
					o = getch();
				}
				if (data)
				{
					(*num)--;
					if (play(data) == NULL)
					{
						system("cls");
						gotoxy(x + 20, y + 4); printf("아직 구현되어있지 않습니다!");
						gotoxy(x + 20, y + 6); printf("▶ 구현 목록\n");
						gotoxy(x + 20, y + 8); printf("  ☞ 흔들리는꽃들속에서네샴푸향이느껴진거야 - 장범준");
						gotoxy(x + 20, y + 10); printf("  ☞ 살짝설렜어(Non-Stop) - 오마이걸");
						gotoxy(x + 20, y + 12); printf("  ☞ 주저하는연인들을위해-잔나비");
						gotoxy(x + 20, y + 14); printf("  ☞ 다섯번째계절 - 오마이걸");
						gotoxy(x + 20, y + 16); printf("  ☞ 벚꽃엔딩 - 버스커버스커");
						gotoxy(x + 20, y + 18); printf("  ☞ 밤편지 - 아이유");
						gotoxy(x + 20, y + 20); printf("  ☞ 폰서트 - 10cm");
						gotoxy(x + 20, y + 22); printf("  ☞ TT - twice");
						Sleep(1900); system("cls"); main_page(num); break;
					}
					else {
						system("cls");
						main_page(num);
						break;
					}
				}
				else { printf("Error!"); }
			}
		}
		else if (s == 224)
		{
			s = getch();
			if (s == 75) ///좌
			{
				if (0 < p) p--;
			}
			else if (s == 77) //우
			{
				if ((p + 1) * 10 < idx)p++;
			}
		}
		else if (s == '3') {
			system("cls");
			search_singer(t, num);
			break;
		}
	}
}

void main_page(int* num)
{
	int x = 0;
	int y = 0;
	printf("□■□■□■□■□■□■□■□■□■□■□\n");
	printf("■                                      □\n");
	printf("□           이시국 코인 노래방         ■\n");
	printf("■              ver.2020                □\n");
	printf("□                                      ■\n");
	printf("□■□■□■□■□■□■□■□■□■□■□\n\n");
	printf("┌───────────────────────────────────────┐\n");
	printf("│ ♩♪♬ Menu ♩♪♬                    │\n");
	printf("│                                       │\n");
	printf("│ >1.코인 추가하기                      │\n");
	printf("│                                       │\n");
	printf("│ >2.가수 검색                          │\n");
	printf("│                                       │\n");
	printf("│ >3.제목 검색                          │\n");
	printf("│                                       │\n");
	printf("│ >4.번호 검색                          │\n");
	printf("│                                       │\n");
	printf("│ >5.인기 차트                          │\n");
	printf("│                                       │\n");
	printf("│ >6.프로그램 종료                      │\n");
	printf("└───────────────────────────────────────┘\n");

	gotoxy(x + 38, y + 12); printf("○●○●○● quick gide ○●○●○●\n");
	gotoxy(x + 38, y + 13); printf("●                                ○\n");
	gotoxy(x + 38, y + 14); printf("○    Push '1' -> insert coin     ●\n");
	gotoxy(x + 38, y + 15); printf("●                                ○\n");
	gotoxy(x + 38, y + 16); printf("○    Push '2' -> search singer   ●\n");
	gotoxy(x + 38, y + 17); printf("●                                ○\n");
	gotoxy(x + 38, y + 18); printf("○    Push '3' -> search title    ●\n");
	gotoxy(x + 38, y + 19); printf("●                                ○\n");
	gotoxy(x + 38, y + 20); printf("○●○●○●○●○●○●○●○●○●\n");
	if (*num >= 10)
	{
		gotoxy(x + 43, y + 0); printf("□■□■□■□\n");
		gotoxy(x + 43, y + 1); printf("■coin: %d  □\n", *num);
		gotoxy(x + 43, y + 2); printf("■□■□■□■\n");

	}
	else
	{
		gotoxy(x + 43, y + 0); printf("□■□■□■\n");
		gotoxy(x + 43, y + 1); printf("■coin: %d □\n", *num);
		gotoxy(x + 43, y + 2); printf("■□■□■□\n");

	}
	return 0;
}
void coin_insert_page(int* num)
{

	int x = 5;
	int y = 5;

	gotoxy(x + 12, y + 3); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	gotoxy(x + 12, y + 4); printf("▤                              ▤");
	gotoxy(x + 12, y + 5); printf("▤  ○●○●○●○●○●○●○  ▤");
	gotoxy(x + 12, y + 6); printf("▤  | 코인이 추가되었습니다! |  ▤");
	gotoxy(x + 12, y + 7); printf("▤  ●○●○●○●○●○●○●  ▤");
	gotoxy(x + 12, y + 8); printf("▤                              ▤");
	gotoxy(x + 12, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	Sleep(200);
	system("cls");
	main_page(num);

}

void popular_song(tree* t, int* num, song hotsong[3][13][100])
{
	system("cls");
	int song_number = 0;
	int date = 28;
	int year = date / 12;
	int month = date % 12 + 1;
	int s;
	int p = 0;
	char o = NULL;
	int x = 0;
	int y = 0;
	char title_name[100];
	song* data = NULL;
	gotoxy(x, y + 0); printf("┌─────────────────┐\n");
	gotoxy(x, y + 1); printf("│＃인기 차트      │\n");
	gotoxy(x, y + 2); printf("└─────────────────┘\n");
	gotoxy(x + 10, y + 0); printf("┌──────────────┐\n");
	gotoxy(x + 10, y + 1); printf("│＃메인 화면(1)│\n");
	gotoxy(x + 10, y + 2); printf("└──────────────┘\n");
	gotoxy(x + 38, y + 1); printf("○●○●○● quick gide ○●○●○●○●\n");
	gotoxy(x + 38, y + 2); printf("●                                    ○\n");
	gotoxy(x + 38, y + 3); printf("○  Push '↑' or '↓' ->  '월 이동'   ●\n");
	gotoxy(x + 38, y + 4); printf("●                                    ○\n");
	gotoxy(x + 38, y + 5); printf("○  Push '←' or '→' -> '페이지이동' ●\n");
	gotoxy(x + 38, y + 6); printf("●                                    ○\n");
	gotoxy(x + 38, y + 7); printf("○●○●○●○●○●○●○●○●○●○●\n");
	gotoxy(x, y + 3); printf("┌───────────────────────────────────────┐");
	gotoxy(x, y + 4); printf("│☆★%d년도 %d월의 인기 차트입니다.☆★│", year + 2018, month);
	gotoxy(x, y + 5); printf("└───────────────────────────────────────┘");
	gotoxy(x, y + 8); printf("순위         제목                                가수\n\n");
	for (int i = p * 10; i < p * 10 + 10; i++) { printf("%d위.   %-40s%-20s\n\n", i + 1, hotsong[year][month][i].title, hotsong[year][month][i].singer); }
	while (1)
	{
		s = getch();
		system("cls");
		if (s == '1') {
			system("cls");  main_page(num); break;
		}
		else {
			if (s == 224)
			{
				s = getch();
				if (s == 75) ///좌
				{
					if (0 < p) p--;
				}
				else if (s == 77) //우
				{
					if (p < 9)p++;
				}
				else if (s == 72)   //위
				{
					if (date < 28) date++;
					p = 0;
				}
				else if (s == 80)   //아래
				{
					if (4 < date) date--;
					p = 0;
				}
			}
			year = date / 12;
			month = date % 12 + 1;
			gotoxy(x, y + 0); printf("┌─────────────────┐\n");
			gotoxy(x, y + 1); printf("│＃인기 차트      │\n");
			gotoxy(x, y + 2); printf("└─────────────────┘\n");
			gotoxy(x + 10, y + 0); printf("┌──────────────┐\n");
			gotoxy(x + 10, y + 1); printf("│＃메인 화면(1)│\n");
			gotoxy(x + 10, y + 2); printf("└──────────────┘\n");
			gotoxy(x + 38, y + 1); printf("○●○●○● quick gide ○●○●○●○●\n");
			gotoxy(x + 38, y + 2); printf("●                                    ○\n");
			gotoxy(x + 38, y + 3); printf("○  Push '↑' or '↓' ->  '월 이동'   ●\n");
			gotoxy(x + 38, y + 4); printf("●                                    ○\n");
			gotoxy(x + 38, y + 5); printf("○  Push '←' or '→' -> '페이지이동' ●\n");
			gotoxy(x + 38, y + 6); printf("●                                    ○\n");
			gotoxy(x + 38, y + 7); printf("○●○●○●○●○●○●○●○●○●○●\n");
			gotoxy(x, y + 3); printf("┌───────────────────────────────────────┐");
			gotoxy(x, y + 4); printf("│☆★%d년도 %d월의 인기 차트입니다.☆★│", year + 2018, month);
			gotoxy(x, y + 5); printf("└───────────────────────────────────────┘");
			gotoxy(x, y + 8); printf("순위         제목                                가수\n\n");
			for (int i = p * 10; i < p * 10 + 10; i++) { printf("%d위.   %-40s%-20s\n\n", i + 1, hotsong[year][month][i].title, hotsong[year][month][i].singer); }
		}
	}
}


/*
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "DB.h"


// DB.h 파일은 무조건 읽어야함.
// AVLtree.h파일은 DB에서 쓰기 때문에, 헤더에 넣어줘야함.


/* 필수 입력사항.

	#include "DB.h"

	int main(){
		song hotSong[3][13][100]; -> 바로 밑에 설명
		tree* t = createNewTree();
		readData(hotSong, t);
	}

*/


/*
	typedef struct {
		int key;
		char singer[100];
		char title[100];
		}song;
*/


/* hotSong[3][13][100] 설명

	[3] -> 0: 2018년 , 1:2019년 , 2:2020년
	[13] ->[1~12]월
	[100] -> [0~99]등

*/

/* 함수 사용법

	1. 번호 검색 / find_number
		song* data = find_number(t, 번호);
			--> 못찾으면 NULL 반환

	2. 가수 검색 / find_singer
		int singerDataIdx = 0;
		song* singerData[100];
		find_singer(t, singerData, &singerDataIdx, "가수 문자열");
			--> 못찾으면, singerDataIdx=0 임.

	3. 제목검색 / find_title
		int titleDataIdx = 0;
		song* titleData[100];
		find_title(t, titleData, &titleDataIdx, "제목 문자열");
			--> 못찾으면, titleDataIdx=0 임.

*/

// y년 m월 인기곡은, 따로 hotSong데이터가 있으므로, 함수를 따로 만들지 않음. 직접 접근해서 쓰면됩니다. 
/*
int main() {
	song hotSong[3][13][100];
	tree* t = createNewTree();
	readData(hotSong, t);

	while (1) {
		int n; printf("\n\n0 번호 검색 , 1 가수검색 , 2제목검색\n입력 : "); scanf("%d", &n);


		//곡검색, 성공시 song* 반환 , 실패시 NULL 반환
		if (n == 0) {
			int num=0; printf("\n번호 입력 : "); scanf("%d", &num);

			song* data = find_number(t, num);

			if (data != NULL) printf("\n%s-%s", data->title, data->singer);
			else printf("못찾음.");
		}


		//가수 검색, song* 배열에 채워놓음. singerDataIDx==0 일경우, 찾기 실패.
		else if (n == 1) {
			char s[100]; printf("\n가수 입력 : "); scanf("%s", s);

			int singerDataIdx = 0;
			song* singerData[100];
			find_singer(t, singerData, &singerDataIdx, s);

			for (int i = 0; i < singerDataIdx; i++) printf("\n%s-%s", singerData[i]->title, singerData[i]->singer);
		}


		//제목 검색. 가수검색과 동일.
		else if (n == 2) {
			char ti[100]; printf("\n제목 입력 : ");scanf("%s", ti);

			int titleDataIdx = 0;
			song* titleData[100];
			find_title(t, titleData, &titleDataIdx, ti);

			for (int i = 0; i < titleDataIdx; i++) printf("\n%s-%s", titleData[i]->title, titleData[i]->singer);
		}
		else break;
	}
}

*/