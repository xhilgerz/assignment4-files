#ifndef ASSIGN4_H  
#define ASSIGN4_H

// Struct declaration
typedef struct {
    char course_Name[84];
    char course_Sched[4];
    unsigned course_Size;
    unsigned course_Hours;
    char padding[20];

} COURSE;

void createCourse();

void updateCourse();

void readCourse();

void deleteCourse();

void saveCourse( int course_number, COURSE* course);

COURSE* loadCourse(int course_number);

void courseIO(char* output,void* variable, char type);

int courseIsCreated(COURSE* course,int course_num);

COURSE* createCourseStruct();

void keepCourse(COURSE*inputCourse,COURSE*loadCourse);

void stringCompareCopy(char* string1, char* string2);

void intCompareCopy(int* num1, int* num2);

#endif 