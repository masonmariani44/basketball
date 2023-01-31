/**
 *
 * Mason Mariani
 * CSC 352
 *
 * basketball.c - given one command line argument, a file path, the program will process the formatted data file and print statistics about each line.
 *
 * Each line of the data file is to be formatted as follows: Player Name[P1,R1,A1][P2,R2,A2]...
 *
 * Prints the Most/least consistent player for each category, and highest/lowest average player for each category
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include "arrayz.h"

//processes the line to fill this player's point, rebound, and assist arrays
void build_arrays(char *line, char *names, long *points, long *rebounds, long *assists) {
	//used to build all of the arrays for each stat
	//put this name in
	int i = 0;
	int arr_i = 0;
	while (line[i] != '[') {
		names[arr_i] = line[i];
		i++;
		arr_i++;
	}
	i += 1;
	arr_i = 1;

	//convert all commas and right brackets to null terminators (used for atoi)
	int temp_i = i;
	int count = 1;
	while (line[temp_i] != '\0') {
		if (line[temp_i] == ',') {
			line[temp_i] = '\0';
		}
		if (line[temp_i] == ']') {
			line[temp_i] = '\0';
			count++;
		}
		temp_i++;
	}

	while (arr_i < count) {
		//get point
		points[arr_i] = (long) atoi(&line[i]);
		if (atoi(&line[i]) > 9) {
			i += 3;
		}
		else {
			i += 2;
		}
		points[0] = points[0] + 1;
		
		//get rebounds
		rebounds[arr_i] = (long) atoi(&line[i]);
		if (atoi(&line[i]) > 9) {
			i += 3;
		}
		else {
			i += 2;
		}
		rebounds[0] = rebounds[0] + 1;

		//get assist
		assists[arr_i] = (long) atoi(&line[i]);
		if (atoi(&line[i]) > 9) {
			i += 3;
		}
		else {
			i += 2;
		}
		assists[0] = assists[0] + 1;
		
		if (atoi(&line[i]) > 9) {
			i += 2;
		}
		else {
			i += 1;
		}

		arr_i++;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "expects 1 command line argument\n");
		return 1;
	}

	//constant declarations
	int  LINE_LENGTH = 201;
	int  NAME_LENGTH = 51;
	int  MAX_LINES   = 100;
	int  MAX_GAMES 	 = 100;

	char line[LINE_LENGTH];	

	FILE* stats_file;
	stats_file = fopen(argv[1], "r");
	if (stats_file == NULL) {
		fprintf(stderr, "error opening the file.\n");
	}

	//built such that: category[player][info]
	char names[MAX_LINES][NAME_LENGTH];
	long points[MAX_LINES][MAX_GAMES+1];
	long rebounds[MAX_LINES][MAX_GAMES+1];
	long assists[MAX_LINES][MAX_GAMES+1];

	int line_num = 0;
	while ((fgets(line, LINE_LENGTH, stats_file) != NULL) && (line_num <= MAX_LINES)) {
		build_arrays(line, names[line_num], points[line_num], rebounds[line_num], assists[line_num]);

		line_num++;
	}	

	//get stddev of all stats for each player
	double std_dev_points[MAX_LINES];
	double std_dev_rebounds[MAX_LINES];
	double std_dev_assists[MAX_LINES];

	//get average of all stats for each player
	double avg_points[MAX_LINES];
	double avg_rebounds[MAX_LINES];
	double avg_assists[MAX_LINES];
	for (int i = 1; i <= line_num; i++) {
		std_dev_points[i] 	= sdev(points[i-1]);
		std_dev_points[0] 	= std_dev_points[0] + 1;
		std_dev_rebounds[i] 	= sdev(rebounds[i-1]);
		std_dev_rebounds[0] 	= std_dev_rebounds[0] + 1;
		std_dev_assists[i]	= sdev(assists[i-1]);
		std_dev_assists[0] 	= std_dev_assists[0] + 1;

		avg_points[i] 		= mean(points[i-1]);
		avg_points[0] 		= avg_points[0] + 1;
		avg_rebounds[i] 	= mean(rebounds[i-1]);
		avg_rebounds[0] 	= avg_rebounds[0] + 1;
		avg_assists[i]		= mean(assists[i-1]);
		avg_assists[0] 		= avg_assists[0] + 1;
	}

	printf("most consistent scorer: %s\n", 		names[minid(std_dev_points)-1]);
	printf("most inconsistent scorer: %s\n", 	names[maxid(std_dev_points)-1]);
	printf("highest scorer: %s\n", 			names[maxid(avg_points)-1]);
	printf("lowest scorer: %s\n", 			names[minid(avg_points)-1]);
	printf("most inconsistent rebounder: %s\n", 	names[maxid(std_dev_rebounds)-1]);
	printf("most consistent rebounder: %s\n", 	names[minid(std_dev_rebounds)-1]);
	printf("highest rebounder: %s\n", 		names[maxid(avg_rebounds)-1]);
	printf("lowest rebounder: %s\n", 		names[minid(avg_rebounds)-1]);
        printf("most inconsistent assister: %s\n", 	names[maxid(std_dev_assists)-1]);
	printf("most consistent assister: %s\n", 	names[minid(std_dev_assists)-1]);
	printf("lowest assister: %s\n",			names[minid(avg_assists)-1]);
	printf("highest assister: %s\n", 		names[maxid(avg_assists)-1]);

	fflush(stats_file);
	fclose(stats_file);

	return 0;
}
