#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc != 2) { 
        printf("Usage: %s <input_file> \n", argv[0]);
        return 1;
    }
    
    char *inputFileName = argv[1];
	char c;

	// open file for reading mode 
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    //read and print each character
    while ((c = fgetc(file)) != EOF) {
    	printf("%c", c); //print each char
    }
    fclose(file);
	return 0;
}
