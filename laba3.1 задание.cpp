#define _CRT_SECURE_NO_WARNINGS
#include "StdAfx.h"
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "string.h"


struct node
{
	char inf[256];  // полезная информация
	struct node* next; // ссылка на следующий элемент 
};

struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
int dlinna = 0;


struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите строку: \n");   // вводим данные
	scanf("%s", s);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

struct node *find(char *name)
{
	int ch = 1;
	struct node *struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			printf("Номер слова в списке: %d\n", ch);
			return 0;
		}
		struc = struc->next;
		ch++;
	}
	printf("Элемент не найден\n");
	return NULL;
}

/* Удаление элемента по содержимому. */
void del(char *name)
{
	struct node *struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node *prev;// указатель на предшествующий удаляемому элемент
	int flag = 0;      // индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) // если удаляемый элемент - первый
	{
		flag = 1;
		head = struc->next; // установливаем голову на следующий элемент
		free(struc);  // удаляем первый элемент
		struc = head; // устанавливаем указатель для продолжения поиска
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}

	while (struc) // проход по списку и поиск удаляемого элемента
	{
		if (strcmp(name, struc->inf) == 0) // если нашли, то
		{
			flag = 1;         // выставляем индикатор
			if (struc->next)  // если найденный элемент не последний в списке
			{
				prev->next = struc->next; // меняем указатели
				free(struc);		    // удаляем  элемент
				struc = prev->next; // устанавливаем указатель для продолжения поиска
			}
			else			// если найденный элемент последний в списке
			{
				prev->next = NULL; // обнуляем указатель предшествующего элемента
				free(struc);	// удаляем  элемент
				return;
			}
		}
		else	// если не нашли, то
		{
			prev = struc; // устанавливаем указатели для продолжения поиска
			struc = struc->next;
		}
	}

	if (flag == 0)				// если флаг = 0, значит нужный элемент не найден
	{
		printf("Элемент не найден\n");
		return;
	}


}


void spstore(void)
{
	struct node* p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else
	{
		struct node* curr = head;
		struct node* prev = NULL;

		while (curr != NULL && strlen(curr->inf) < strlen(p->inf)) {
			prev = curr;
			curr = curr->next;
		}
		if (prev == NULL) {
			p->next = head;
			head = p;
		}
		else {
			prev->next = p;
			p->next = curr;
		}
		if (p->next == NULL) {
			last = p;
		}
	}
	return;
}


/* Просмотр содержимого списка. */
void review(void)
{
	int  flag = 0;
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		flag++;
		printf("%d) %s \n", flag, struc->inf);
		struc = struc->next;
	}
	return;
}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	int choice;
	char word[256];

	while (true)
	{	
		printf("\n1. Добавить элемент в список\n");
		printf("2. Просмотр списка\n");
		printf("3. Поиск содержанию в списке\n");
		printf("4. Удаление содержанию в списке\n");
		printf("Выберите действие: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			spstore(); // Добавление элемента
			break;
		case 2:
			review(); // Просмотр списка
			break;
		case 3:
			printf("Введите, что нужно найти: ");
			scanf("%s",word);
			find(word);
			break;
		case 4:
			printf("Введите, что нужно удалить: ");
			scanf("%s", word);
			del(word);
			break;

		}
	}
}