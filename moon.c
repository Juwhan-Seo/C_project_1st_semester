#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void create_note();
void read_note();
void list_notes();
void edit_note();
void delete_note();

char notes[10][1000];
char tags[10][50];
char timestamps[10][50];
int note_count = 0;

int main() {
    int choice;
    system("color 0A");

    while (1) {
        system("cls");
        printf("=================================\n");
        printf("=           �޸��� �޴�           =\n");
        printf("=================================\n");
        printf("= 1. �� �޸� �ۼ�                =\n");
        printf("= 2. �޸� �ҷ�����               =\n");
        printf("= 3. �޸� ����                  =\n");
        printf("= 4. �޸� ����                  =\n");
        printf("= 5. ���α׷� ����                    =\n");
        printf("=================================\n");
        printf("����: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            create_note();
            break;
        case 2:
            read_note();
            break;
        case 3:
            edit_note();
            break;
        case 4:
            delete_note();
            break;
        case 5:
            exit(0);
        default:
            printf("�߸��� �����Դϴ�.\n");
        }
    }

    return 0;
}

void create_note() {
    char content[1000];
    char tag[50];
    size_t index = 0;

    time_t t;
    struct tm* tm_info;

    time(&t);
    tm_info = localtime(&t);
    strftime(timestamps[note_count], 50, "%Y�� %m�� %d�� %H�� %M��", tm_info);

    printf("�±� �Է� (#�±�): ");
    fgets(tag, 50, stdin);
    tag[strcspn(tag, "\n")] = 0;
    strcpy(tags[note_count], tag);

    printf("�޸� �ۼ� ('END' �Է����� ����):\n");
    while (1) {
        fgets(content + index, 1000 - index, stdin);
        if (strstr(content + index, "END")) {
            content[index + strlen(content + index) - 4] = '\0';
            break;
        }
        index += strlen(content + index);
    }

    strcpy(notes[note_count], content);
    note_count++;

    printf("\n�޸� ����Ǿ����ϴ�. (%s)\n", timestamps[note_count - 1]);
}

void read_note() {
    list_notes();

    int note_number;
    printf("�ҷ��� �޸� ��ȣ�� �����ϼ���: ");
    scanf("%d", &note_number);
    getchar();

    if (note_number > 0 && note_number <= note_count) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD savedAttributes;

        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        savedAttributes = consoleInfo.wAttributes;

        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED);

        printf("�±�: %s\n", tags[note_number - 1]);
        printf("�ð�: %s\n", timestamps[note_number - 1]);
        printf("����:\n%s\n", notes[note_number - 1]);

        SetConsoleTextAttribute(hConsole, savedAttributes);
    }
    else {
        printf("�߸��� ��ȣ�Դϴ�.\n");
    }
}

void edit_note() {
    list_notes();

    int note_number;
    printf("������ �޸� ��ȣ�� �����ϼ���: ");
    scanf("%d", &note_number);
    getchar();

    if (note_number > 0 && note_number <= note_count) {
        printf("���� ����:\n%s\n", notes[note_number - 1]);

        size_t index = 0;
        printf("���ο� ������ �Է��ϼ��� ('END' �Է����� ����):\n");
        while (1) {
            fgets(notes[note_number - 1] + index, 1000 - index, stdin);
            if (strstr(notes[note_number - 1] + index, "END")) {
                notes[note_number - 1][index + strlen(notes[note_number - 1] + index) - 4] = '\0';
                break;
            }
            index += strlen(notes[note_number - 1] + index);
        }

        printf("\n�޸� �����Ǿ����ϴ�.\n");
    }
    else {
        printf("�߸��� ��ȣ�Դϴ�.\n");
    }
}

void delete_note() {
    list_notes();

    int note_number;
    printf("������ �޸� ��ȣ�� �����ϼ���: ");
    scanf("%d", &note_number);
    getchar();

    if (note_number > 0 && note_number <= note_count) {
        for (int i = note_number - 1; i < note_count - 1; i++) {
            strcpy(notes[i], notes[i + 1]);
            strcpy(tags[i], tags[i + 1]);
            strcpy(timestamps[i], timestamps[i + 1]);
        }
        note_count--;

        printf("�޸� �����Ǿ����ϴ�.\n");
    }
    else {
        printf("�߸��� ��ȣ�Դϴ�.\n");
    }
}

void list_notes() {
    printf("����� �޸� ���:\n");
    for (int i = 0; i < note_count; i++) {
        printf("%d. %s (%s)\n", i + 1, tags[i], timestamps[i]);
    }
}

