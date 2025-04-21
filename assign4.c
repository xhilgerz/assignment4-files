#include "assign4.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(){ 
    char file_name[] = "courses.dat";

    char line1[] = "Enter one of the following actions or press CTRL-D to exit.";
    char choice_C[] = "Create a new course record";
    char choice_U[] = "update an existing course record";
    char choice_R[] = "read an existing course record";
    char choice_D[] = "delete an existing course record";

    puts(line1);
    puts(choice_C);
    puts(choice_U);
    puts(choice_R);
    puts(choice_D);
    
    char user_input;

    while(scanf("%c",&user_input) != EOF){
        user_input = toupper(user_input);
        switch(user_input){

            case 'C':
                createCourse(file_name);
            break;

            case 'U':

            break;

            case 'R':

            break;

            case 'D':

            break;

            default:
            scanf("%c",&user_input);

        }

    }





    return 0;
}

void createCourse(char file_name[]){
    
    COURSE* course = (COURSE*)malloc(sizeof(COURSE));

    int course_num;
    int course_size;

    scanf("%d",&course_num);
    scanf("%s",&course->course_Name);
    scanf("%s",&course->course_Sched);
    scanf("%d",&course->course_Hours);
    scanf("%d",&course_size);

    saveCourse(file_name,course_num,course);
    



}

void saveCourse(char file_name[], int course_number, const COURSE* course){
    FILE *file = fopen(file_name,"wb");
    fseek(file, course_number * sizeof(COURSE), SEEK_SET); 
    fwrite(course, sizeof(COURSE), 1, file);


}


