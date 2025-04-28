#include "assign4.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


char file_name[] = "data/courses.dat";

int main() {

    displayCourseOptions();
    
    
    char user_input;
    while(scanf(" %c", &user_input) != EOF) {
        user_input = toupper(user_input);
        switch(user_input) {
            case 'C':
                createCourse();
                displayCourseOptions();
                break;
            case 'U':
                updateCourse();
                displayCourseOptions();
                break;
            case 'R':
                readCourse();
                displayCourseOptions();
                break;
            case 'D':
                deleteCourse();
                displayCourseOptions();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                displayCourseOptions();

        }
    }
    return 0;
}

void createCourse() {
    int course_num;
    
    courseIO("Course number", &course_num, 'i');
    
    COURSE* course = createCourseStruct();
    if(course == NULL) {
        fprintf(stderr, "ERROR: creating course\n");
        return;
    }

    if(courseIsCreated(course_num)> 0) {
        fprintf(stderr, "ERROR: course already exists\n");
        free(course);
        return;
    }

    saveCourse(course_num, course);
    free(course);
}


void updateCourse() {
    int course_num;
    courseIO("Course number", &course_num, 'i');
    
    COURSE* tempCourse = loadCourse(course_num);

    COURSE* course = createCourseStruct();
    if(course == NULL) {
        free(tempCourse);
        fprintf(stderr, "ERROR: creating course\n");
        return;
    }

    if(courseFound(course_num)==0) {
        fprintf(stderr, "ERROR: course not found \n");
        return;
    }

    keepCourse(course, tempCourse);
    saveCourse(course_num, course);
    
    free(course);
    free(tempCourse);
}

void readCourse() {
    int course_num;
    char prompt[] = "Enter a CS course number:";
    courseIO(prompt, &course_num, 'i');
    
    COURSE* course = loadCourse(course_num);
    if(course == NULL) {
        fprintf(stderr, "ERROR: course doesn't exist\n");
        return;
    }

    if(courseFound(course_num)==0) {
        fprintf(stderr, "ERROR: course not found \n");
        return;
    }

    printf("\nCourse Information:\n");
    printf("Name: %s\n", course->course_Name);
    printf("Schedule: %s\n", course->course_Sched);
    printf("Credit Hours: %u\n", course->course_Hours);
    printf("Enrollment: %u\n\n", course->course_Size);
    
    free(course);
}

void deleteCourse() {
    int course_number;
    char prompt[] = "Enter a CS course number:";
    courseIO(prompt, &course_number, 'i');

    FILE *file = fopen(file_name, "rb+");
    if(file == NULL) {
        perror("ERROR: opening file");
        return;
    }

    if(fseek(file, course_number * sizeof(COURSE), SEEK_SET) != 0) {
        perror("ERROR: seeking in course file");
        fclose(file);
        return;
    }

    if(courseFound(course_number)==0) {
        fprintf(stderr, "ERROR: course not found \n");
        return;
    }

    COURSE zero_course = {0};
    if(fwrite(&zero_course, sizeof(COURSE), 1, file) != 1) {
        perror("ERROR: writing to file");
    }
    fclose(file);
    printf("Course deleted successfully.\n");
}


void saveCourse(int course_number, COURSE* course) {
    

    FILE *file = fopen(file_name, "rb+");
    if(file == NULL) {
        perror("ERROR: opening file");
        return;
    }

    COURSE existing_course;
    if (fread(&existing_course, course_number*sizeof(COURSE), 1, file) == 1) {
        puts("Course already Exists");
        fclose(file);
        return;
    }

    if(fseek(file, course_number * sizeof(COURSE), SEEK_SET) != 0) {
        perror("ERROR: seeking in file");
        fclose(file);
        return;
    }

    if(fwrite(course, sizeof(COURSE), 1, file) != 1) {
        perror("ERROR: writing to file");
    }
    fclose(file);
    printf("Course saved successfully.\n");
}

COURSE* loadCourse(int course_number) {
    FILE *file = fopen(file_name, "rb");
    if(file == NULL) {
        perror("ERROR: opening file");
        return NULL;
    }

    if(fseek(file, course_number * sizeof(COURSE), SEEK_SET) != 0) {
        perror("ERROR: couldn't find file");
        fclose(file);
        return NULL;
    }

    COURSE* course = malloc(sizeof(COURSE));
    if(course == NULL) {
        fclose(file);
        return NULL;
    }

    if(fread(course, sizeof(COURSE), 1, file) != 1) {
        perror("ERROR: reading file");
        free(course);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return course;
}

void courseIO(char* output, void* variable, char type) {
    printf("%s ", output);
    switch(type) {
        case 'i':
            scanf("%d", (int*)variable);
            break;
        case 's':
            {
                char buffer[100];
                scanf("%99s", buffer);
                strcpy((char*)variable, buffer);
            }
            break;
        default:
            break;
    }
}

int courseIsCreated(int course_num) {
    FILE *file = fopen(file_name, "rb");
    if(file == NULL) {
        return 0; 
    }

    COURSE course;

    if(fseek(file, course_num * sizeof(COURSE), SEEK_SET) == 0) {
        fread(&course, sizeof(COURSE), 1, file);
        return course.course_Hours;
    }

    fclose(file);
    return 0; // Check if name is not empty
}

COURSE* createCourseStruct() {
    COURSE* course = malloc(sizeof(COURSE));
    if(course == NULL) {
        return NULL;
    }

    courseIO("Course name", course->course_Name, 's');
    courseIO("Course schedule (MWF/TTH)", course->course_Sched, 's');
    courseIO("Course credit hours", &course->course_Hours, 'i');
    courseIO("Course enrollment", &course->course_Size, 'i');

    return course;
}

void keepCourse(COURSE* inputCourse, COURSE* loadCourse) {
    if(strcmp(inputCourse->course_Name, "") == 0) {
        strcpy(inputCourse->course_Name, loadCourse->course_Name);
    }
    if(strcmp(inputCourse->course_Sched, "") == 0) {
        strcpy(inputCourse->course_Sched, loadCourse->course_Sched);
    }
    if(inputCourse->course_Hours == 0) {
        inputCourse->course_Hours = loadCourse->course_Hours;
    }
    if(inputCourse->course_Size == 0) {
        inputCourse->course_Size = loadCourse->course_Size;
    }
}

void stringCompareCopy(char* string1, char* string2) {
    if(strcmp(string1, "") == 0) {
        strcpy(string1, string2);
    }
}

void intCompareCopy(int* num1, int* num2) {
    if(*num1 == 0) {
        *num1 = *num2;
    }
}

void displayCourseOptions(){

    char line1[] = "Enter one of the following actions or press CTRL-D to exit.";
    char choice_C[] = "C - Create a new course record";
    char choice_U[] = "U - Update an existing course record";
    char choice_R[] = "R - Read an existing course record";
    char choice_D[] = "D - Delete an existing course record";

    puts(line1);
    puts(choice_C);
    puts(choice_U);
    puts(choice_R);
    puts(choice_D);

}

int courseFound(int course_number){
    if(courseIsCreated(course_number) > 0) {
        return 1;
    }
    return 0;
}