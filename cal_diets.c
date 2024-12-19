//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
	
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
     
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (diet_list_size >= MAX_DIETS){
        	break;
		}
		
		char food_name[MAX_FOOD_NAME_LEN];
		int calories;
		
		if (sscanf(line, "%s %d", food_name, &calories)==2) {
			char *s1=diet_list[diet_list_size].food_name;
			char *s2=food_name;
			
			int i;
			for (i=0; i<MAX_FOOD_NAME_LEN-1; i++) {
				s1[i]=s2[i];
				if (s2[i]=='\0') break;
			}
			s1[MAX_FOOD_NAME_LEN-1]='\0';
			
			diet_list[diet_list_size].calories_intake=calories;
			diet_list_size++;
		}
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    for (i=0;i<diet_list_size;i++) {
    	printf("%d. %d %s\n", i+1, diet_list[i].food_name, diet_list[i].calories_intake);
	}
    
	// ToCode: to enter the diet to be chosen with exit option
    printf("0. Exit\n");
    
    while (1){
		printf("Enter the number of the diet you ate: ");
    	if (scanf("%d", &choice) !=1) {
    		printf("Please enter number.\n"); //enter something other than numbers
    		while (getchar() !='\n');
    		continue;
		}
	
		if (choice==0) {
			printf("Exiting diet input.\n"); //back
			break;
		}
		
		if (choice<1||choice>diet_list_size) {
			printf("please select a valid option.\n"); //when selecting a number greater than 7
			continue;
		}
		

    // ToCode: to enter the selected diet in the health data
    	if (health_data->diet_count < MAX_DIETS) {
    		char *s1=health_data->diet[health_data->diet_count].food_name;
    		char *s2=diet_list[choice-1].food_name;
    		
    		int i;
    		for (i=0; i<MAX_FOOD_NAME_LEN-1; i++) {
    			s1[i]=s2[i];
    			if (s2[i]=='\0') break;
			}
			s1[MAX_FOOD_NAME_LEN-1]='\0';
			
			health_data->diet[health_data->diet_count].calories_intake=diet_list[choice-1].calories_intake;
			health_data->diet_count++;
	
    // ToCode: to enter the total calories intake in the health data
    		health_data->total_calories_intake+=diet_list[choice-1].calories_intake;
		}
	}

}

