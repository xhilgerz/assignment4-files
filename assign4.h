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

void createCourse(char file_name[]);

void saveCourse(char file_name[], int course_number, const COURSE* course);

#endif 