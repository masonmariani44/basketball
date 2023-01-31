/**
 *
 * */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "arrayz.h"

long sum(long values[]) {
	long sum = 0;
	for (int i = 1; i <= values[0]; i++) {
		sum = sum + values[i];
	}
	return sum;
}

long minil(long values[]) {
	long min_num = values[1];
	long min_index = 1;
	for (int i = 1; i <= values[0]; i++) {
		if (values[i] < min_num) {
			min_num = values[i];
			min_index = (long) i;
		}
 	}
	return min_index;
}

long minid(double values[]) {
	double min_num = values[1];
	long min_index = 1;
	for (int i = 1; i <= values[0]; i++) {
		if (values[i] < min_num) {
			min_num = values[i];
			min_index = (long) i;
		}
	}
	return min_index;
}

long maxil(long values[]) {
	long max_num = values[1];
	long max_index = 1;
	for (int i = 1; i <= values[0]; i++) {
		if (values[i] > max_num) {
			max_num = values[i];
			max_index = (long) i;
		}
	}
	return max_index;
}

long maxid(double values[]) {
	double max_num = values[1];
	long max_index = 1;
	for (int i = 1; i <= values[0]; i++) {
		if (values[i] > max_num) {
			max_num = values[i];
			max_index = (long) i;
		}
	}
	return max_index;
}

void printal(long values[]) {
	printf("length %ld array: ", values[0]);
	for (int i = 1; i <= values[0]; i++) {
		printf("%ld", values[i]);
		if (i == values[0]) {
			printf("\n");
		}
		else {
			printf(", ");
		}
	}
}

void printad(double values[]) {
	printf("length %f array: ", values[0]);
	for (int i = 1; i <= values[0]; i++) {
		printf("%f", values[i]);
		if (i == values[0]) {
			printf("\n");
		}
		else {
			printf(", ");
		}
	}
}

double mean(long values[]) {
	return (double) sum(values) / (double) values[0];
}

double sdev(long values[]) {
	double values_mean = mean(values);
	double sdev_sum = 0;
	for (int i = 1; i <= values[0]; i++) {
		sdev_sum = ((values[i] - values_mean) * (values[i] - values_mean)) + sdev_sum;
	}
	return sqrt(sdev_sum / (double) values[0]);
}
