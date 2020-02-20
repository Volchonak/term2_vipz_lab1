#include "processStruct.h"
#include <stdio.h>
#include <stdlib.h>



int main(void)
{
	int i, numOfStudents = 0, check;
	float expectedAverage = 0.0;
	FILE* fp;
	Student* pHead = NULL, *pTmp=NULL, *pTmp2=NULL;
	fp = openFile();
	pHead = readDataToNewStructure(fp, &check);
	if (!pHead) return -2;
	++numOfStudents;
	while (1)
	{
		addToList(&pHead, readDataToNewStructure(fp, &check));
		if (check)
		{
			++numOfStudents;
		}
		else
		{
			break;
		}
	}
	PRINTTABLESTART;
	PRINTHEADER;
	PRINTADDITIONLINE;
	printAllStudents(pHead);
	PRINTTABLEEND;
	pTmp = pHead;
	Student* pExcellentStudentHead = NULL;

	while (1)
	{
		if (checkForExcellentMarks(pTmp))
		{
			pExcellentStudentHead = copyDataToNewStructure(pTmp);

			break;
		}
		if (!pTmp->next) break;
		pTmp = pTmp->next;
	}

	while(1)
	{ 
		if (!pTmp->next) break;
			pTmp = pTmp->next;
		if (checkForExcellentMarks(pTmp))
		{
			addToList(&pExcellentStudentHead, copyDataToNewStructure(pTmp));
		}
	}
	printf("Students with excellent marks:\n");
	PRINTTABLESTART;
	printAllStudents(pExcellentStudentHead);
	PRINTTABLEEND;

	pTmp = pHead;

	printf("\nEnter passing avarage mark. Everyone who has arithmetic mean\n"
		"less than this mark, will be deleted from the list\t\t");
	scanf("%f", &expectedAverage);
	while (1)
	{
		if (compareAvarage(pTmp, expectedAverage))
		{
			pTmp2 = pTmp;
			pTmp = pTmp->next;
			deleteFromList(&pHead, pTmp2);
		}
		else
		{
			pTmp = pTmp->next;
		}
		if (!pTmp) break;
	}
	pTmp = pHead;
	pTmp2 = NULL;

	printf("\nStudents, who passed natural selection\n");
	PRINTTABLESTART;
	printAllStudents(pHead);
	PRINTTABLEEND;
	if (pExcellentStudentHead)
	{
		freeList(&pExcellentStudentHead);
		pExcellentStudentHead = NULL;
	}
	if (pHead)
	{
		freeList(&pHead);
		pHead = NULL;
	}

	if (!fp)
	{
		fclose(fp);
		fp = NULL;
	}
	return 0;
}
