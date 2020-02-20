#include "processStruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void correctString(char* ptr, int sizeOfPtr)
{
	for (int i = 0; i < sizeOfPtr; ++i)
	{
		if (ptr[i] == '\n')
		{
			ptr[i] = '\0';
			break;
		}
	}
}

FILE* openFile()
{
	int val = 0;
	FILE* fp;
	char* address;
	do
	{
		++val;
		address = (char*)malloc(SIZEOFADDRESS * sizeof(char));
	} while (!address && val < 40);
	if (!address)
		exit(-1);
	val = 1;
	do
	{
		if (val)
		{
			printf("Enter address of text file\t");
			--val;
		}
		else
		{
			printf("Something went wrong. File was not opened. Try again\t");
		}
		fgets(address, SIZEOFADDRESS - 1, stdin);
		correctString(address, SIZEOFADDRESS);
		fp = fopen(address, "r");
	} while (!fp);
	free(address);
	return fp;
}

Student* copyDataToNewStructure(const Student* studentToCopy)
{
	if (!studentToCopy) return NULL;

	Student* tmp = (Student*)malloc(sizeof(Student));
	if (!tmp) return NULL;
	memcpy(tmp, studentToCopy, sizeof(Student));
	tmp->next = NULL;
	return tmp;
}

Student* readDataToNewStructure(FILE* fp, int* val)
{
	if (!fp) return NULL;
	Student* pTmp;
	pTmp = (Student*)malloc(sizeof(Student));
	if (!pTmp) return NULL;
	pTmp->next = NULL;

	if (getc(fp) == EOF)
	{
		*val = 0;
		return NULL;
	}
	else
	{
		fseek(fp, -1, SEEK_CUR);
	}
	fscanf(fp, "%s", pTmp->surName);
	fscanf(fp, "%s", pTmp->name);
	fscanf(fp, "%d.%d.%d", &(pTmp->dateOfBirth[0]), &(pTmp->dateOfBirth[1]), &(pTmp->dateOfBirth[2]));
	for (int i = 0; i < NUMOFMARKS; ++i)
	{
		fscanf(fp, "%d", &(pTmp->marks[i]));
	}
	pTmp->next = NULL;
	return pTmp;
}

void printAllStudents(const Student* pHead)
{
	if (!pHead) return;
	Student* pTmp = pHead;
	while (1)
	{
		printStudent(pTmp);
		if (pTmp->next)
		{
			pTmp = pTmp->next;
		}
		else { break; }
	}
}

void printStudent(const Student* student)
{
	if (!student) return;
	printf("|%-20s|%-20s|%2d.%2d.%4d   |", student->surName, student->name,
		student->dateOfBirth[0], student->dateOfBirth[1], student->dateOfBirth[2]);
	for (int i = 0; i < NUMOFMARKS; ++i)
	{
		printf("%2d|", student->marks[i]);
	}printf("\n");
}

int checkForExcellentMarks(const Student* student)
{
	if (!student) return -1;
	int returnVal = 1;
	for (int i = 0; i < NUMOFMARKS; ++i)
	{
		if (student->marks[i] != 5)
		{
			returnVal = 0;
			break;
		}
	}
	return returnVal;
}
void freeList(Student** pHead)
{
	if (!(*pHead)) return;
	Student* pTmp = *pHead;
	while (1)
	{
		if (pTmp->next)
		{
			while (1)
			{
				if (pTmp->next->next)
					pTmp = pTmp->next;
				else
				{
					free(pTmp->next);
					pTmp->next = NULL;
					break;
				}
			}
		}
		else
		{
			free(pTmp);
			*pHead = NULL;
			break;
		}
	}
}

void deleteFromList(Student** pHead, Student* student)
{
	if (!(*pHead)||!student) return;
	Student* pTmp = *pHead;
	if (student==(*pHead))
	{
		*pHead = pTmp->next;
		free(student);
		return;
	}
	while (1)
	{
		if (pTmp->next == student)
		{
			pTmp->next = student->next;
			free(student);
			return;
		}
		pTmp = pTmp->next;
	}
}

int compareAvarage(const Student* student, float expectedAverage)
{
	if (!student) return 0;
	float avarage = 0;
	for (int i = 0; i < NUMOFMARKS; ++i)
	{
		avarage = avarage + student->marks[i];
	}
	avarage /= NUMOFMARKS;
	return avarage < expectedAverage ? 1 : 0;
}

void addToList(Student** pHead, Student* ptr)
{
	if (!ptr|| !pHead) return;
	if (!((*pHead)->next))
	{
		while (1)
		{
			if (ptr->dateOfBirth[2] < (*pHead)->dateOfBirth[2])
			{
				(*pHead)->next = ptr;
				break;
			}
			if (ptr->dateOfBirth[2] > (*pHead)->dateOfBirth[2])
			{
				ptr->next = (*pHead);
				(*pHead) = ptr;
				break;
			}
			if (ptr->dateOfBirth[1] < (*pHead)->dateOfBirth[1])
			{
				(*pHead)->next = ptr;
				break;
			}
			if (ptr->dateOfBirth[1] > (*pHead)->dateOfBirth[1])
			{
				ptr->next = (*pHead);
				(*pHead) = ptr;
				break;
			}
			if (ptr->dateOfBirth[0] < (*pHead)->dateOfBirth[0])
			{
				(*pHead)->next = ptr;
				break;
			}
			if (ptr->dateOfBirth[0] > (*pHead)->dateOfBirth[0])
			{
				ptr->next = (*pHead);
				(*pHead) = ptr;
				break;
			}
			if (ptr->dateOfBirth[0] == (*pHead)->dateOfBirth[0])
			{
				(*pHead)->next = ptr;
				break;
			}
		}
	}
	else {
		Student* pTmp = (*pHead);

		while (1)
		{
			if (ptr->dateOfBirth[2] < pTmp->next->dateOfBirth[2])
			{
				if (pTmp->next->next)
				{
					pTmp = pTmp->next;
					break;
				}
				else
				{
					pTmp->next->next = ptr;
					break;
				}
			}
			if (ptr->dateOfBirth[2] > pTmp->next->dateOfBirth[2])
			{
				ptr->next = pTmp->next;
				pTmp->next = ptr;
				break;
			}
			if (ptr->dateOfBirth[1] < pTmp->next->dateOfBirth[1])
			{
				if (pTmp->next->next)
				{
					pTmp = pTmp->next;
					break;
				}
				else
				{
					pTmp->next->next = ptr;
					break;
				}
			}
			if (ptr->dateOfBirth[1] > pTmp->next->dateOfBirth[1])
			{
				ptr->next = pTmp->next;
				pTmp->next = ptr;
				break;
			}
			if (ptr->dateOfBirth[0] < pTmp->next->dateOfBirth[0])
			{
				if (pTmp->next->next)
				{
					pTmp = pTmp->next;
					break;
				}
				else
				{
					pTmp->next->next = ptr;
					break;
				}
			}
			if (ptr->dateOfBirth[0] > pTmp->next->dateOfBirth[0])
			{
				ptr->next = pTmp->next;
				pTmp->next = ptr;
				break;
			}
			if (ptr->dateOfBirth[0] == pTmp->next->dateOfBirth[0])
			{
				if (pTmp->next->next)
				{
					pTmp = pTmp->next;
					break;
				}
				else
				{
					pTmp->next->next = ptr;
					break;
				}
			}
		}
	}
}