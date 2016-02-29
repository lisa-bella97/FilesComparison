#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List
{
	char* value;
	unsigned int num;
	struct List *next;
} List;

void pushBack(List *&head, List *&end, List *p)
{
	p->next = NULL;
	if (head == NULL)
		head = end = p;
	else
	{
		end->next = p;
		end = p;
	}
}

List * pop(List *&head)
{
	if (head == 0) return 0;
	List *p = head;
	head = head->next;
	return p;
}

int main(int argc, char* argv[])
{
	char* fileName1 = new char[256];
	char* fileName2 = new char[256];
	FILE *pF1;
	FILE *pF2;
	List * head1 = NULL, *end1 = NULL, *p1;
	List * head2 = NULL, *end2 = NULL, *p2;
	unsigned int n1 = 0;
	unsigned int n2 = 0;

	if (argc != 3)
	{
	printf("Error: invalid number of parameters.\n");
	return 1;
	}

	sscanf_s(argv[1], "%s", fileName1);
	sscanf_s(argv[2], "%s", fileName2);

	pF1 = fopen(fileName1, "r");
	if (pF1 == NULL)
	{
	printf("Error: first file name is not correct.\n");
	return 1;
	}

	pF2 = fopen(fileName2, "r");
	if (pF2 == NULL)
	{
	printf("Error: second file name is not correct.\n");
	return 1;
	}

	while (!feof(pF1))
	{
	p1 = new List;
	p1->value = new char[100];
	fgets(p1->value, 100, pF1);
	if (p1->value[strlen(p1->value) - 1] == '\n')
	p1->value[strlen(p1->value) - 1] = '\0';
	p1->num = ++n1;
	pushBack(head1, end1, p1);
	}

	while (!feof(pF2))
	{
	p2 = new List;
	p2->value = new char[100];
	fgets(p2->value, 100, pF2);
	if (p2->value[strlen(p2->value) - 1] == '\n')
	p2->value[strlen(p2->value) - 1] = '\0';
	p2->num = ++n2;
	pushBack(head2, end2, p2);
	}

	for (p1 = head1; p1; p1 = p1->next)
	{
	for (p2 = head2; p2; p2 = p2->next)
	{
	if (strcmp(p1->value, p2->value) == 0)
	break;
	if (p2 == end2)
	printf("%s %d \"%s\"\n", fileName1, p1->num, p1->value);
	}
	}

	for (p2 = head2; p2; p2 = p2->next)
	{
	for (p1 = head1; p1; p1 = p1->next)
	{
	if (strcmp(p2->value, p1->value) == 0)
	break;
	if (p1 == end1)
	printf("%s %d \"%s\"\n", fileName2, p2->num, p2->value);
	}
	}

	fclose(pF1);
	fclose(pF2);

	while (p1 = pop(head1))
	{
	delete[]p1->value;
	delete p1;
	}

	while (p2 = pop(head2))
	{
	delete[]p2->value;
	delete p2;
	}

	delete[] fileName1;
	delete[] fileName2;

	system("pause");
	return 0;
}