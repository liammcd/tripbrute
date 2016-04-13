/********************
 * Liam McDermott
 * 2016
 ********************/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//EN3O3MaMKw

#define TRIP_LEN 10
#define TRIP_CHAR 8
#define DICT_SIZE 306706		
#define DICT_FILE "cain.txt"

char *saltMap = "................................"
   				".............../0123456789ABCDEF"
				"GABCDEFGHIJKLMNOPQRSTUVWXYZabcde"
				"fabcdefghijklmnopqrstuvwxyz....."
				"................................"
				"................................"
				"................................"
				"................................";

void generateTripcode (char *buf, char *password) {
	
	if (password == NULL) return;
	if (strlen(password) == 0) return;
	char salt[2];
	int len = strlen(password);
	char *passExt = (char *) malloc(len + 3);
	if (passExt == NULL)
		return;
		
	memset(passExt, 0, len+3);
	memcpy(passExt, password, len);
	
	passExt[len] = 'H';
	passExt[len+1] = '.';
	
	salt[0] = saltMap[((int)passExt[1])%256];
	salt[1] = saltMap[((int)passExt[2])%256];
	
	char *tripCode = crypt(password, salt);
	if (tripCode == NULL) {
		free(passExt);
		return;
	}
	
	//Get last 10 characters of hash
	memcpy(buf, tripCode+(strlen(tripCode) - 10), TRIP_LEN+1);
	
	free(passExt);
}

/**********************
 * 
 **********************/
void loadDict(char **dict) {
	int i;
	FILE *dictFile = fopen(DICT_FILE, "r");
	assert(dictFile != NULL);
	
	fseek(dictFile, 0L, SEEK_END);
	long size = ftell(dictFile);
	rewind(dictFile);
		
	char *buf = malloc(size+1);
	memset(buf, 0, size+1);
	fread(buf, size, 1, dictFile);
	
	char *tmp = strtok(buf, "\n");
	memcpy(dict[0], tmp, TRIP_CHAR);
	dict[0][TRIP_CHAR] = '\0';
	
	for (i = 1; i < DICT_SIZE; i++) {
		tmp = strtok(NULL, "\n");
		if (tmp) {
			memcpy(dict[i], tmp, TRIP_CHAR);
			dict[i][TRIP_CHAR] = '\0';
		}
	}
		
	fclose(dictFile);
	free(buf);
}

void tripBrute(char *tripcode) {
	
	char tripGuess[11];
	int i, j;
	int found = 0;
	
	char **dict = (char **) malloc(DICT_SIZE * sizeof(char *));
	assert(dict != NULL);
	
	for (i=0;i<DICT_SIZE;i++) {
		dict[i] = (char *) malloc(TRIP_CHAR+1);
		assert(dict[i] != NULL);
	}

	loadDict(dict);
	printf("Loaded dictionary\n");
	
	for (i=0;i<DICT_SIZE;i++) {
		if (dict[i] == '\0') continue;
		generateTripcode(tripGuess, dict[i]);
		//printf("[%s] [%s]\n", tripGuess, dict[i]);
		if (strcmp(tripGuess, tripcode) == 0) {
			printf("Password is: %s\n", dict[i]);
			found = 1;
			break;
		}
	}
	if (!found)
		printf("Password not found\n");
	free(dict);
}

int main (int argc, char *argv[]) {

	if (argc != 2) {
		printf("Usage: %s [tripcode]\n", argv[0]);
		return 0;
	}

	tripBrute(argv[1]);

	return 0;
}