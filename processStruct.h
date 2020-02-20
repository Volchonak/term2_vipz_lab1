#include <stdio.h>
#ifndef PROCESSSTRUCT_H
#define PROCESSSTRUCT_H
#define _CRT_SECURE_NO_WARNINGS

#define SIZEOFADDRESS 255
#define SIZEOFNAME 20
#define NUMOFMARKS 10
//#define NUMOFSTUDENTS 3

#define PRINTTABLESTART printf("%c-------------------------------------------------------------------------------------%c\n", 218, 191)
#define PRINTTABLEEND 	printf("%c-------------------------------------------------------------------------------------%c\n", 192, 217)
#define PRINTHEADER 	printf("|Surname             |Name                |Date Of Birth| 1| 2| 3| 4| 5| 6| 7| 8| 9|10|\n")
#define PRINTADDITIONLINE 	printf("|-------------------------------------------------------------------------------------|\n")

typedef struct student
{
	char surName[SIZEOFNAME];
	char name[SIZEOFNAME];
	int dateOfBirth[3];
	int marks[NUMOFMARKS];
	struct student* next;
} Student;

FILE* openFile();
Student* readDataToNewStructure(FILE* fp, int* val);
void addToList(Student** pHead, Student* ptr);
void printAllStudents(const Student* pHead);
void printStudent(const Student* student);
void freeList(Student** pHead);
int checkForExcellentMarks(const Student* student);
void deleteFromList(Student** pHead, Student* student);
int compareAvarage(const Student* student, float expectedAverage);
Student* copyDataToNewStructure(const Student* studentToCopy);

#endif
