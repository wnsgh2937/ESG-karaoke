#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "AVLtree.h"

// DB.h ������ ������ �о����.
// AVLtree.h������ DB���� ���� ������, ����� �־������.


/* �ʼ� �Է»���.

#include "DB.h"

int main(){
	song hotSong[3][13][100];
	tree* t = createNewTree();
	readData(hotSong, t);
}

*/

/*

	hotSong[3][13][100]
	[3] -> 0: 2018�� , 1:2019�� , 2:2020��
	[13] -> 1~12��
	[100] -> 1~100��

*/

/* �Լ� ����

1. ��ȣ �˻� ( find_number )
song* data = find_number(t, ��ȣ);
--> ��ã���� NULL ��ȯ

2. ���� �˻� ( find_singer )
int singerDataIdx = 0;
song* singerData[100];
find_singer(t, singerData, &singerDataIdx, "���� ���ڿ�");
--> ��ã����, singerDataIdx=0 ��.

3. ����˻� ( find_title )
int titleDataIdx = 0;
song* titleData[100];
find_title(t, titleData, &titleDataIdx, "���� ���ڿ�");
--> ��ã����, titleDataIdx=0 ��.

*/

song* find_number(tree* t, int num) {
	node* findNode;
	if (find(t->head, num, &findNode) == 1) {
		return &(findNode->data);
	}
	else {
		return NULL;
	}
}


void find_singer_DFS(node* iter, song** arr, int* idx, char* singer) {
	song data = iter->data;
	if (strstr(data.singer, singer) != NULL) {
		arr[*idx] = &(iter->data);
		*idx += 1;
	}
	if (iter->left != NULL) find_singer_DFS(iter->left, arr, idx, singer);
	if (iter->right != NULL) find_singer_DFS(iter->right, arr, idx, singer);
}

void find_singer(tree* t, song** arr, int* idx, char* singer) {
	find_singer_DFS(t->head, arr, idx, singer);
}

void find_title_DFS(node* iter, song** arr, int* idx, char* title) {
	song data = iter->data;
	if (strstr(data.title, title) != NULL) {
		arr[*idx] = &(iter->data);
		*idx += 1;
	}
	if (iter->left != NULL) find_title_DFS(iter->left, arr, idx, title);
	if (iter->right != NULL) find_title_DFS(iter->right, arr, idx, title);
}

void find_title(tree* t, song** arr, int* idx, char* title) {
	find_title_DFS(t->head, arr, idx, title);
}

void readData(song(*hotSong)[13][100], tree* t) {
	int allIdx = 0;
	song* all = (song*)malloc(sizeof(song) * 500);
	FILE* fin;
	for (int y = 2018; y <= 2020; y++) {
		for (int m = 1; m <= 12; m++) {
			char path[64] = "src\\songData\\";
			char year[64];
			if (y == 2020 && m == 12) {
				strcat(path, "user\\userSong.txt");
			}
			else {
				sprintf(year, "%d", y);
				strcat(path, year);
				strcat(path, "\\");

				char month[64];
				sprintf(month, "%d", m);
				strcat(path, month);
				strcat(path, ".txt");
			}
			if (0 == fopen_s(&fin, path, "rt")) {
				for (int i = 0; i < 100; i++) {

					if (y == 2020 && m == 6 && i == 67) break;
					if (y == 2020 && m == 12 && i == 4) break;


					char tmp[100];
					char title[100];
					fgets(title, 99, fin);
					fgets(tmp, 99, fin);
					title[strlen(title) - 2] = '\0';
					char singer[100];
					int idx = 1;
					while (tmp[idx] != '\0') {
						singer[idx - 1] = tmp[idx++];
					}
					singer[idx - 1] = '\0';
					if (singer[idx - 2] == '\n') singer[idx - 2] = '\0';


					strcpy(hotSong[y - 2018][m][i].title, title);
					strcpy(hotSong[y - 2018][m][i].singer, singer);


					int isThere = 0;
					for (int i = 0; i < allIdx; i++) {
						if (strcmp(all[i].singer, singer) == 0 && strcmp(all[i].title, title) == 0) {
							isThere = 1;
							break;
						}
					}
					if (isThere == 0) {
						strcpy(all[allIdx].singer, singer);
						strcpy(all[allIdx].title, title);
						all[allIdx].key = allIdx++;
					}

				}
				fclose(fin);
			}
		}
	}

	for (int i = 0; i < allIdx; i++) {
		node* newNode = createNewNode(i);
		newNode->data.key = i;
		strcpy(newNode->data.singer, all[i].singer);
		strcpy(newNode->data.title, all[i].title);

		if (isEmpty(t)) t->head = newNode;
		else {
			node* findNode;
			if (find(t->head, i, &findNode) == 0) {
				add_node(t, findNode, newNode);
			}
			else {
				printf("�ߺ��� ����Դϴ�.\n");
			}
		}
	}
	free(all);
}
