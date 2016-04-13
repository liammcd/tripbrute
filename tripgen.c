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
#define DICT_SIZE 19000000

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
	
	salt[0] = saltMap[((int)passExt[1])];
	salt[1] = saltMap[((int)passExt[2])];
	
	char *tripCode = crypt(password, salt);
	if (tripCode == NULL) {
		free(passExt);
		assert(tripCode != NULL);
	}
	
	//Get last 10 characters of hash
	memcpy(buf, tripCode+(strlen(tripCode) - 10), TRIP_LEN+1);
	
	free(passExt);
}

int main (int argc, char *argv[]) {

	if (argc != 2) {
		printf("Usage: %s [tripcode]\n", argv[0]);
		return 0;
	}

	char trip[11];
	generateTripcode(trip, argv[1]);
	printf("Tripcode: %s\n", trip);
	
	return 0;
}