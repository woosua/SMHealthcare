//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    
    char line[100];
    while (fgets(line, sizeof(line),file)) {
    	if (exercise_list_size >= MAX_EXERCISES){
        	break;
		}
		
		char exercise_name[MAX_EXERCISE_NAME_LEN];
		int calories_burned_per_minute;
		
		if (sscanf(line, "%s %d", exercise_name, &calories_burned_per_minute)==2) {
			char *s1=exercise_list[exercise_list_size].exercise_name;
			char *s2=exercise_name;
			
			int i;
			for(i=0; i<MAX_EXERCISE_NAME_LEN; i++) {
				s1[i]=s2[i];
				if (s2[i]=='\0') break; //stop when NULL char is encountered
			}
			s1[MAX_EXERCISE_NAME_LEN-1]='\0'; //add NULL char at the end
			
			exercise_list[exercise_list_size].calories_burned_per_minute=calories_burned_per_minute;
			exercise_list_size++;
		}
		
    }

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");
    for(i=0; i<exercise_list_size; i++) {
    	printf("%d. %s %d", i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
	}


    // ToCode: to enter the exercise to be chosen with exit option
	printf("0. Exit\n");
	
	while(1){
		printf("Enter the number of the exercise you did: ");
		if (scanf("%d", &choice) !=1) {
			printf("Please enter a number.\n"); //enter something other than numbers
			while (getchar() !='\n');
			continue;
		}
		
		if (choice==0) {
			printf("Exiting exercise input.\n"); //back
			break;
		}
		
		if (choice<1 || choice>exercise_list_size) {
			printf("Please select a vaild option.\n"); //when selecting a number greater than 7
			continue;
		}
	
 
    
    // To enter the duration of the exercise
		printf("Enter the duration of the exercise (in min.): ");
    	if (scanf("%d", &duration) !=1 || duration<=0) {
    		printf("Please enter a positive number.\n");
    		while (getchar() !='\n');
    		continue;
		}

    // ToCode: to enter the selected exercise and total calcories burned in the health data
    	if (health_data->exercise_count<MAX_EXERCISES) {
    		char *s1=health_data->exercises[health_data->exercise_count].exercise_name;
    		char *s2=exercise_list[choice-1].exercise_name;
    		int i;
    		for(int i=0; i<MAX_EXERCISE_NAME_LEN-1 && *s2 !='\0'; i++) {
    			s1[i]=*s2++;
			}
			health_data->exercises[health_data->exercise_count].exercise_name[MAX_EXERCISE_NAME_LEN-1]='\0';
			health_data->exercises[health_data->exercise_count].calories_burned_per_minute=exercise_list[choice-1].calories_burned_per_minute * duration;
			health_data->exercise_count++;
			
			health_data->total_calories_burned+=exercise_list[choice-1].calories_burned_per_minute * duration;
		}
	}
}
