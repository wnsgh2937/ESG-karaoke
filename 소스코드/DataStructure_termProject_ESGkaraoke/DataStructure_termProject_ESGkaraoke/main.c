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


void end_page()	//���α׷� ���� interface
{
	int x = 5;
	int y = 5;

	gotoxy(x + 13, y + 3); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
	gotoxy(x + 13, y + 4); printf("��                              ��");
	gotoxy(x + 13, y + 5); printf("��                              ��");
	gotoxy(x + 13, y + 6); printf("��    ���α׷��� �����մϴ�^^   ��");
	gotoxy(x + 13, y + 7); printf("��     Press any button         ��");
	gotoxy(x + 13, y + 8); printf("��                              ��");
	gotoxy(x + 13, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
	Sleep(200);
}

void search_title(tree* t, int* num)	//���� �˻� interface
{
	system("cls");
	int song_number = 0;;
	int s;
	char o = NULL;
	int x = 0;
	int y = 0;
	char title_name[100];
	gotoxy(x, y + 0); printf("��������������������������������������\n");
	gotoxy(x, y + 1); printf("�������� �˻�      ��\n");
	gotoxy(x, y + 2); printf("��������������������������������������\n");
	gotoxy(x + 10, y); printf("��������������������������������\n");
	gotoxy(x + 10, y + 1); printf("�������� ȭ��(1)��\n");
	gotoxy(x + 10, y + 2); printf("��������������������������������\n");
	gotoxy(x + 18, y + 0); printf("��������������������������������\n");
	gotoxy(x + 18, y + 1); printf("�����뷡 ����(2)��\n");
	gotoxy(x + 18, y + 2); printf("��������������������������������\n");
	gotoxy(x + 26, y + 0); printf("��������������������������������\n");
	gotoxy(x + 26, y + 1); printf("������˻� (3)  ��\n");
	gotoxy(x + 26, y + 2); printf("��������������������������������\n");
	gotoxy(x, y + 3); printf("�� ������ �Է��� �ּ���: ");
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
		gotoxy(x, y + 0); printf("��������������������������������������\n");
		gotoxy(x, y + 1); printf("�������� �˻�      ��\n");
		gotoxy(x, y + 2); printf("��������������������������������������\n");
		gotoxy(x + 10, y); printf("��������������������������������\n");
		gotoxy(x + 10, y + 1); printf("�������� ȭ��(1)��\n");
		gotoxy(x + 10, y + 2); printf("��������������������������������\n");
		gotoxy(x + 18, y + 0); printf("��������������������������������\n");
		gotoxy(x + 18, y + 1); printf("�����뷡 ����(2)��\n");
		gotoxy(x + 18, y + 2); printf("��������������������������������\n");
		gotoxy(x + 26, y + 0); printf("��������������������������������\n");
		gotoxy(x + 26, y + 1); printf("������˻� (3)  ��\n");
		gotoxy(x + 26, y + 2); printf("��������������������������������\n");
		gotoxy(x, y + 3); printf("�� ������ �Է��� �ּ���: %s", title_name);
		gotoxy(x, y + 5); printf("��ȣ         ����                                ����\n\n");
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
				gotoxy(x + 34, y + 1); printf("�١������� �������ּ���١�");
				Sleep(1000);
			}
			else {

				while (o != '-')
				{
					gotoxy(x + 36, y + 1); printf("�� ������ �뷡 ��ȣ�� �Է��� �ּ���: ");
					scanf(" %d", &song_number);
					data = titleData[song_number - 1];
					gotoxy(x + 36, y + 3); printf("���뷡���� '-'");
					o = getch();
				}
				if (data)
				{
					(*num)--;
					if (play(data) == NULL)
					{
						system("cls");
						gotoxy(x + 20, y + 4); printf("���� �����Ǿ����� �ʽ��ϴ�!");
						gotoxy(x + 20, y + 6); printf("�� ���� ���\n");
						gotoxy(x + 20, y + 8); printf("  �� ��鸮�²ɵ�ӿ����׼�Ǫ���̴������ž� - �����");
						gotoxy(x + 20, y + 10); printf("  �� ��¦������(Non-Stop) - �����̰�");
						gotoxy(x + 20, y + 12); printf("  �� �����ϴ¿��ε�������-�ܳ���");
						gotoxy(x + 20, y + 14); printf("  �� �ټ���°���� - �����̰�");
						gotoxy(x + 20, y + 16); printf("  �� ���ɿ��� - ����Ŀ����Ŀ");
						gotoxy(x + 20, y + 18); printf("  �� ������ - ������");
						gotoxy(x + 20, y + 20); printf("  �� ����Ʈ - 10cm");
						gotoxy(x + 20, y + 22); printf("  �� TT - twice");
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
			if (s == 75) ///��
			{
				if (0 < p) p--;
			}
			else if (s == 77) //��
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
	gotoxy(x, y + 0); printf("��������������������������������������\n");
	gotoxy(x, y + 1); printf("������ȣ �˻�      ��\n");
	gotoxy(x, y + 2); printf("��������������������������������������\n");
	gotoxy(x + 10, y); printf("��������������������������������\n");
	gotoxy(x + 10, y + 1); printf("�������� ȭ��(1)��\n");
	gotoxy(x + 10, y + 2); printf("��������������������������������\n");
	gotoxy(x + 18, y + 0); printf("��������������������������������\n");
	gotoxy(x + 18, y + 1); printf("�����뷡 ����(2)��\n");
	gotoxy(x + 18, y + 2); printf("��������������������������������\n");
	gotoxy(x, y + 3); printf("�� �뷡 ��ȣ�� �Է��� �ּ���: ");
	scanf("%d", &song_number);
	int idx = 0;
	song* singerData[100];
	song* data = find_number(t, song_number);

	if (data == NULL)
	{
		gotoxy(x, y + 8); printf("Error");
		while (data == NULL)
		{
			gotoxy(x, y + 4); printf("�� �뷡 ��ȣ�� �Է��� �ּ���: ");
			scanf(" %d", &song_number);
			data = find_number(t, song_number);
		}
	}
	gotoxy(x, y + 8); printf("��ȣ         ����                                ����\n\n\n");
	printf("%-5d%-40s%-20s\n", data->key, data->title, data->singer);
	while (1)
	{
		s = getch();
		if (s == '1') { system("cls");  main_page(num); break; }
		else if (s == '2')
		{
			if (*num == 0) { gotoxy(x + 30, y); printf("�١������� �������ּ���١�"); }
			else {
				while (o != '-')
				{
					gotoxy(x + 30, y); printf("�� ������ �뷡 ��ȣ�� �Է��� �ּ���: ");
					scanf(" %d", &song_number);
					data = find_number(t, song_number);
					gotoxy(x + 30, y + 3); printf("���뷡���� '-'");
					o = getch();
				}
				if (data)
				{
					(*num)--;
					if (play(data) == NULL)
					{
						system("cls");
						gotoxy(x + 20, y + 4); printf("���� �����Ǿ����� �ʽ��ϴ�!");
						gotoxy(x + 20, y + 6); printf("�� ���� ���\n");
						gotoxy(x + 20, y + 8); printf("  �� ��鸮�²ɵ�ӿ����׼�Ǫ���̴������ž� - �����");
						gotoxy(x + 20, y + 10); printf("  �� ��¦������(Non-Stop) - �����̰�");
						gotoxy(x + 20, y + 12); printf("  �� �����ϴ¿��ε�������-�ܳ���");
						gotoxy(x + 20, y + 14); printf("  �� �ټ���°���� - �����̰�");
						gotoxy(x + 20, y + 16); printf("  �� ���ɿ��� - ����Ŀ����Ŀ");
						gotoxy(x + 20, y + 18); printf("  �� ������ - ������");
						gotoxy(x + 20, y + 20); printf("  �� ����Ʈ - 10cm");
						gotoxy(x + 20, y + 22); printf("  �� TT - twice");


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
	gotoxy(x, y + 0); printf("��������������������������������������\n");
	gotoxy(x, y + 1); printf("�������� �˻�      ��\n");
	gotoxy(x, y + 2); printf("��������������������������������������\n");
	gotoxy(x + 10, y); printf("��������������������������������\n");
	gotoxy(x + 10, y + 1); printf("�������� ȭ��(1)��\n");
	gotoxy(x + 10, y + 2); printf("��������������������������������\n");
	gotoxy(x + 18, y + 0); printf("��������������������������������\n");
	gotoxy(x + 18, y + 1); printf("�����뷡 ����(2)��\n");
	gotoxy(x + 18, y + 2); printf("��������������������������������\n");
	gotoxy(x + 26, y + 0); printf("��������������������������������\n");
	gotoxy(x + 26, y + 1); printf("������˻� (3)  ��\n");
	gotoxy(x + 26, y + 2); printf("��������������������������������\n");
	gotoxy(x, y + 3); printf("�� ���� �̸��� �Է��� �ּ���: ");
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
		gotoxy(x, y + 0); printf("��������������������������������������\n");
		gotoxy(x, y + 1); printf("�������� �˻�      ��\n");
		gotoxy(x, y + 2); printf("��������������������������������������\n");
		gotoxy(x + 10, y); printf("��������������������������������\n");
		gotoxy(x + 10, y + 1); printf("�������� ȭ��(1)��\n");
		gotoxy(x + 10, y + 2); printf("��������������������������������\n");
		gotoxy(x + 18, y + 0); printf("��������������������������������\n");
		gotoxy(x + 18, y + 1); printf("�����뷡 ����(2)��\n");
		gotoxy(x + 18, y + 2); printf("��������������������������������\n");
		gotoxy(x + 26, y + 0); printf("��������������������������������\n");
		gotoxy(x + 26, y + 1); printf("������˻� (3)  ��\n");
		gotoxy(x + 26, y + 2); printf("��������������������������������\n");
		gotoxy(x, y + 3); printf("�� ���� �̸��� �Է��� �ּ���: %s", singer_name);
		gotoxy(x, y + 5); printf("��ȣ         ����                                ����\n\n");
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
				gotoxy(x + 34, y + 4); printf("�١������� �������ּ���١�");
				Sleep(1000);
			}
			else {

				while (o != '-')
				{
					gotoxy(x + 36, y + 1); printf("�� ������ �뷡 ��ȣ�� �Է��� �ּ���: ");
					scanf(" %d", &song_number);
					data = singerData[song_number - 1];
					gotoxy(x + 36, y + 3); printf("���뷡���� '-'");
					o = getch();
				}
				if (data)
				{
					(*num)--;
					if (play(data) == NULL)
					{
						system("cls");
						gotoxy(x + 20, y + 4); printf("���� �����Ǿ����� �ʽ��ϴ�!");
						gotoxy(x + 20, y + 6); printf("�� ���� ���\n");
						gotoxy(x + 20, y + 8); printf("  �� ��鸮�²ɵ�ӿ����׼�Ǫ���̴������ž� - �����");
						gotoxy(x + 20, y + 10); printf("  �� ��¦������(Non-Stop) - �����̰�");
						gotoxy(x + 20, y + 12); printf("  �� �����ϴ¿��ε�������-�ܳ���");
						gotoxy(x + 20, y + 14); printf("  �� �ټ���°���� - �����̰�");
						gotoxy(x + 20, y + 16); printf("  �� ���ɿ��� - ����Ŀ����Ŀ");
						gotoxy(x + 20, y + 18); printf("  �� ������ - ������");
						gotoxy(x + 20, y + 20); printf("  �� ����Ʈ - 10cm");
						gotoxy(x + 20, y + 22); printf("  �� TT - twice");
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
			if (s == 75) ///��
			{
				if (0 < p) p--;
			}
			else if (s == 77) //��
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
	printf("����������������������\n");
	printf("��                                      ��\n");
	printf("��           �̽ñ� ���� �뷡��         ��\n");
	printf("��              ver.2020                ��\n");
	printf("��                                      ��\n");
	printf("����������������������\n\n");
	printf("����������������������������������������������������������������������������������\n");
	printf("�� �ۢܢ� Menu �ۢܢ�                    ��\n");
	printf("��                                       ��\n");
	printf("�� >1.���� �߰��ϱ�                      ��\n");
	printf("��                                       ��\n");
	printf("�� >2.���� �˻�                          ��\n");
	printf("��                                       ��\n");
	printf("�� >3.���� �˻�                          ��\n");
	printf("��                                       ��\n");
	printf("�� >4.��ȣ �˻�                          ��\n");
	printf("��                                       ��\n");
	printf("�� >5.�α� ��Ʈ                          ��\n");
	printf("��                                       ��\n");
	printf("�� >6.���α׷� ����                      ��\n");
	printf("����������������������������������������������������������������������������������\n");

	gotoxy(x + 38, y + 12); printf("�ۡܡۡܡۡ� quick gide �ۡܡۡܡۡ�\n");
	gotoxy(x + 38, y + 13); printf("��                                ��\n");
	gotoxy(x + 38, y + 14); printf("��    Push '1' -> insert coin     ��\n");
	gotoxy(x + 38, y + 15); printf("��                                ��\n");
	gotoxy(x + 38, y + 16); printf("��    Push '2' -> search singer   ��\n");
	gotoxy(x + 38, y + 17); printf("��                                ��\n");
	gotoxy(x + 38, y + 18); printf("��    Push '3' -> search title    ��\n");
	gotoxy(x + 38, y + 19); printf("��                                ��\n");
	gotoxy(x + 38, y + 20); printf("�ۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡ�\n");
	if (*num >= 10)
	{
		gotoxy(x + 43, y + 0); printf("��������\n");
		gotoxy(x + 43, y + 1); printf("��coin: %d  ��\n", *num);
		gotoxy(x + 43, y + 2); printf("��������\n");

	}
	else
	{
		gotoxy(x + 43, y + 0); printf("�������\n");
		gotoxy(x + 43, y + 1); printf("��coin: %d ��\n", *num);
		gotoxy(x + 43, y + 2); printf("�������\n");

	}
	return 0;
}
void coin_insert_page(int* num)
{

	int x = 5;
	int y = 5;

	gotoxy(x + 12, y + 3); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
	gotoxy(x + 12, y + 4); printf("��                              ��");
	gotoxy(x + 12, y + 5); printf("��  �ۡܡۡܡۡܡۡܡۡܡۡܡ�  ��");
	gotoxy(x + 12, y + 6); printf("��  | ������ �߰��Ǿ����ϴ�! |  ��");
	gotoxy(x + 12, y + 7); printf("��  �ܡۡܡۡܡۡܡۡܡۡܡۡ�  ��");
	gotoxy(x + 12, y + 8); printf("��                              ��");
	gotoxy(x + 12, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
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
	gotoxy(x, y + 0); printf("��������������������������������������\n");
	gotoxy(x, y + 1); printf("�����α� ��Ʈ      ��\n");
	gotoxy(x, y + 2); printf("��������������������������������������\n");
	gotoxy(x + 10, y + 0); printf("��������������������������������\n");
	gotoxy(x + 10, y + 1); printf("�������� ȭ��(1)��\n");
	gotoxy(x + 10, y + 2); printf("��������������������������������\n");
	gotoxy(x + 38, y + 1); printf("�ۡܡۡܡۡ� quick gide �ۡܡۡܡۡܡۡ�\n");
	gotoxy(x + 38, y + 2); printf("��                                    ��\n");
	gotoxy(x + 38, y + 3); printf("��  Push '��' or '��' ->  '�� �̵�'   ��\n");
	gotoxy(x + 38, y + 4); printf("��                                    ��\n");
	gotoxy(x + 38, y + 5); printf("��  Push '��' or '��' -> '�������̵�' ��\n");
	gotoxy(x + 38, y + 6); printf("��                                    ��\n");
	gotoxy(x + 38, y + 7); printf("�ۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡ�\n");
	gotoxy(x, y + 3); printf("����������������������������������������������������������������������������������");
	gotoxy(x, y + 4); printf("���١�%d�⵵ %d���� �α� ��Ʈ�Դϴ�.�١ڦ�", year + 2018, month);
	gotoxy(x, y + 5); printf("����������������������������������������������������������������������������������");
	gotoxy(x, y + 8); printf("����         ����                                ����\n\n");
	for (int i = p * 10; i < p * 10 + 10; i++) { printf("%d��.   %-40s%-20s\n\n", i + 1, hotsong[year][month][i].title, hotsong[year][month][i].singer); }
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
				if (s == 75) ///��
				{
					if (0 < p) p--;
				}
				else if (s == 77) //��
				{
					if (p < 9)p++;
				}
				else if (s == 72)   //��
				{
					if (date < 28) date++;
					p = 0;
				}
				else if (s == 80)   //�Ʒ�
				{
					if (4 < date) date--;
					p = 0;
				}
			}
			year = date / 12;
			month = date % 12 + 1;
			gotoxy(x, y + 0); printf("��������������������������������������\n");
			gotoxy(x, y + 1); printf("�����α� ��Ʈ      ��\n");
			gotoxy(x, y + 2); printf("��������������������������������������\n");
			gotoxy(x + 10, y + 0); printf("��������������������������������\n");
			gotoxy(x + 10, y + 1); printf("�������� ȭ��(1)��\n");
			gotoxy(x + 10, y + 2); printf("��������������������������������\n");
			gotoxy(x + 38, y + 1); printf("�ۡܡۡܡۡ� quick gide �ۡܡۡܡۡܡۡ�\n");
			gotoxy(x + 38, y + 2); printf("��                                    ��\n");
			gotoxy(x + 38, y + 3); printf("��  Push '��' or '��' ->  '�� �̵�'   ��\n");
			gotoxy(x + 38, y + 4); printf("��                                    ��\n");
			gotoxy(x + 38, y + 5); printf("��  Push '��' or '��' -> '�������̵�' ��\n");
			gotoxy(x + 38, y + 6); printf("��                                    ��\n");
			gotoxy(x + 38, y + 7); printf("�ۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡܡۡ�\n");
			gotoxy(x, y + 3); printf("����������������������������������������������������������������������������������");
			gotoxy(x, y + 4); printf("���١�%d�⵵ %d���� �α� ��Ʈ�Դϴ�.�١ڦ�", year + 2018, month);
			gotoxy(x, y + 5); printf("����������������������������������������������������������������������������������");
			gotoxy(x, y + 8); printf("����         ����                                ����\n\n");
			for (int i = p * 10; i < p * 10 + 10; i++) { printf("%d��.   %-40s%-20s\n\n", i + 1, hotsong[year][month][i].title, hotsong[year][month][i].singer); }
		}
	}
}


/*
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "DB.h"


// DB.h ������ ������ �о����.
// AVLtree.h������ DB���� ���� ������, ����� �־������.


/* �ʼ� �Է»���.

	#include "DB.h"

	int main(){
		song hotSong[3][13][100]; -> �ٷ� �ؿ� ����
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


/* hotSong[3][13][100] ����

	[3] -> 0: 2018�� , 1:2019�� , 2:2020��
	[13] ->[1~12]��
	[100] -> [0~99]��

*/

/* �Լ� ����

	1. ��ȣ �˻� / find_number
		song* data = find_number(t, ��ȣ);
			--> ��ã���� NULL ��ȯ

	2. ���� �˻� / find_singer
		int singerDataIdx = 0;
		song* singerData[100];
		find_singer(t, singerData, &singerDataIdx, "���� ���ڿ�");
			--> ��ã����, singerDataIdx=0 ��.

	3. ����˻� / find_title
		int titleDataIdx = 0;
		song* titleData[100];
		find_title(t, titleData, &titleDataIdx, "���� ���ڿ�");
			--> ��ã����, titleDataIdx=0 ��.

*/

// y�� m�� �α����, ���� hotSong�����Ͱ� �����Ƿ�, �Լ��� ���� ������ ����. ���� �����ؼ� ����˴ϴ�. 
/*
int main() {
	song hotSong[3][13][100];
	tree* t = createNewTree();
	readData(hotSong, t);

	while (1) {
		int n; printf("\n\n0 ��ȣ �˻� , 1 �����˻� , 2����˻�\n�Է� : "); scanf("%d", &n);


		//��˻�, ������ song* ��ȯ , ���н� NULL ��ȯ
		if (n == 0) {
			int num=0; printf("\n��ȣ �Է� : "); scanf("%d", &num);

			song* data = find_number(t, num);

			if (data != NULL) printf("\n%s-%s", data->title, data->singer);
			else printf("��ã��.");
		}


		//���� �˻�, song* �迭�� ä������. singerDataIDx==0 �ϰ��, ã�� ����.
		else if (n == 1) {
			char s[100]; printf("\n���� �Է� : "); scanf("%s", s);

			int singerDataIdx = 0;
			song* singerData[100];
			find_singer(t, singerData, &singerDataIdx, s);

			for (int i = 0; i < singerDataIdx; i++) printf("\n%s-%s", singerData[i]->title, singerData[i]->singer);
		}


		//���� �˻�. �����˻��� ����.
		else if (n == 2) {
			char ti[100]; printf("\n���� �Է� : ");scanf("%s", ti);

			int titleDataIdx = 0;
			song* titleData[100];
			find_title(t, titleData, &titleDataIdx, ti);

			for (int i = 0; i < titleDataIdx; i++) printf("\n%s-%s", titleData[i]->title, titleData[i]->singer);
		}
		else break;
	}
}

*/