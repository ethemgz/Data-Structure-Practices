#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#include "counter.h"



using namespace std;

	
int Counter::findindex(Token *arr,char elem[]){

	int i = 0;

	while ((strlen(arr[i].token) != 0) && (i < ARRAY_SIZE)) 
	{
		if (strncmp(arr[i].token, elem, TOKEN_LENGTH) == 0) {
			
			return i;
		}
		i++;
	}
	return -1;
}

bool Counter::contains(char *token, char target){

	int i;

	for (i = 0; i < TOKEN_LENGTH; i++) {
		if (token[i] == target) {
			return true;
		}
	}

	return false;
}

void Counter::read_and_count(){

	ifstream file_p;
	file_p.open("pi_approximate");
	if (!file_p) {
		cout << "File could not open!";
		exit(1);
	}

	int i, j = 0;
	int index;
	char candidate_pair[TOKEN_LENGTH];

	//Clear memory just for safety
	for (i = 0; i < ARRAY_SIZE; i++) {
		token_array[i].count = 0;
	}

	while(true) {

		// I checked, whether I could get the character or not, in here not in while condition because last digit of the token should be empty before the first digit.
		for (int k = 0; k < TOKEN_LENGTH; k++) {
			if (!(file_p >> candidate_pair[k])) {
				file_p.close();
				return;
			}
		}
		
		if (!Counter::contains(candidate_pair, '.')) {

			index = findindex(token_array, candidate_pair);

			if (index == -1) {
				for (int k = 0; k < TOKEN_LENGTH; k++) {
					token_array[j].token[k] = candidate_pair[k];
				}
				token_array[j].count = 1;
				j++;
			}
			else {
				token_array[index].count++;
			}
		}

		// Pull the file pointer to back to read all possible tokens
		file_p.seekg((1 - TOKEN_LENGTH), ios::cur);
	}

	file_p.close();
}

Token arr[3];

Token *Counter::get_most_common_three(){

	int i = 0, j, k;

	while (token_array[i].count != 0) {
		for (j = 0; j < 3; j++) {
			if (token_array[i].count > arr[j].count) {
				arr[j].count = token_array[i].count;
				for (k = 0; k < TOKEN_LENGTH; k++) {
					arr[j].token[k] = token_array[i].token[k];
				}
				break;
			}
		}
		i++;
	}

	return arr;
}
