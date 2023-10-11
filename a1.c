#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// need to add spaces between words
void add_spaces(char* textString, int lineLength) {
	char* result = strchr(textString, '\n');
	
	printf("%c found at position: %ld \n", '\n', result - textString);
}

int main(int argc, char *argv[]){
    if (argc != 3) { 
        printf("Usage: %s <line length> <input_file> \n", argv[0]);
        return 1;
    }
    
    int lineLength = atoi(argv[1]);
    char *inputFileName = argv[2];
    
    int index = 0;
    
    char c;

    // open file for reading mode 
    FILE *file = fopen(inputFileName, "r");
    
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    } 
    
    // Determine length of file
    fseek(file, 0, SEEK_END);
    int fileLength = ftell(file);
    fseek(file, 0, SEEK_SET); 
    
    
    //if (fileLength > lineLength) {
    	//perror("Error. The word processor can't display the output."); //not correct, needs to be fixed
    	//return 1;
    //}

    // Allocate memory to string to manipulate
    char *textString = (char *)malloc((fileLength*2) * sizeof(char));
    
    if (textString == NULL) {
        perror("Memory allocation error");
        return 1;
    }
    
    int charCount = 0;
    int tempIndex;
    
    // Read and print each character
    while ((c = fgetc(file)) != EOF) {
        if (charCount >= lineLength) {
        	tempIndex = index;
        	while (textString[tempIndex] != ' ') {
        		tempIndex--;
        	}
            textString[tempIndex] = '\n';
            charCount = 0;
        }

        if (c == '-') {
        	textString[index++] = c;
            textString[index++] = '\n';
            charCount = 0;
        } else {
            textString[index++] = c;
            charCount++;
        }
    }
    
    textString[index] = '\0'; 
    
    for (int i = 0 ; i < strlen(textString) ; i++) {
    	printf("%c", textString[i]);
    }
    
    add_spaces(textString, lineLength);
    
    // Free memory for textString
    free(textString);
    
    fclose(file);
    
	return 0;
}
