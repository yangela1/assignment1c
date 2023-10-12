#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void 

int main(int argc, char *argv[]){
    if (argc != 3) { 
        printf("Usage: %s <line_length> <input_file> \n", argv[0]);
        return 1;
    }
    
    int lineLength = atoi(argv[1]);
    char *inputFileName = argv[2];
    
    int index = 0;
    
    char c;
    
    int hyphenCount = 0;

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

    // Allocate memory to string to manipulate
    char *textString = (char *)malloc((fileLength + 1) * sizeof(char));
    
    if (textString == NULL) {
        perror("Memory allocation error");
        return 1;
    }
    
    // Store each character into a string
    while ((c = fgetc(file)) != EOF) {
        textString[index] = c;
        index++;
    }
    
    // Add final String character
    textString[index] = '\0'; 
    
    // Check number of hyphens
    for (int i = 0; i < strlen(textString); i++) {
    	if (textString[i] == '-') {
    		hyphenCount++;
    	}
    }
    
    int arrSize = fileLength / lineLength + 1 + hyphenCount;
    
    // Array to store Strings
    char **textArr = (char **)malloc(arrSize * sizeof(char *));
    
    for (int i = 0; i < arrSize; i++) {
    	textArr[i] = (char *)malloc((lineLength + 20) * sizeof(char));
    }

	for (int i = 0; i < strlen(textString); i++) {
    	printf("%c", textString[i]);
    }
    
    int newIndex = 0;
	int space = 0;
	int start = 0;
	int arrIndex = 0;

	while (newIndex < strlen(textString)) {
	
		if (strlen(textString) < lineLength) {
			strncpy(textArr[arrIndex], &textString[start], strlen(textString));
			newIndex = strlen(textString);
		}
	
    	if (textString[newIndex] == ' ') {
    		space = newIndex;
    	} 
    	
    	if (newIndex - start > lineLength) {
            	strncpy(textArr[arrIndex], &textString[start], space - start);
            	textArr[arrIndex][space - start] = '\0'; 
            	arrIndex++;
            	start = space+1;
        	}
    	
    	if (textString[newIndex] == '-') {
    			strncpy(textArr[arrIndex], &textString[start], newIndex - start + 1);
            	textArr[arrIndex][newIndex - start + 1] = '\0'; 
            	arrIndex++;
            	start = newIndex + 1;
    	} 
    	
    	
    	if (strlen(textString) - start <= lineLength) {
        	strncpy(textArr[arrIndex], &textString[start], strlen(textString) - start);
        	textArr[arrIndex][strlen(textString) - start] = '\0';
        	newIndex = strlen(textString);
    	}
    	
    	newIndex++;
    
    	
	}
    
    for (int i = 0; i < arrSize; i++) {
    	printf("%ld\n", strlen(textArr[i]));
    }
    
    for (int i = 0; i < arrSize; i++) {
    	printf("%s\n", textArr[i]);
    }

   
    
    // Free memory
    for (int i = 0; i < arrIndex; ++i) {
        free(textArr[i]);
    }
    free(textArr);
    free(textString);
    
    fclose(file);
    
	return 0;
}
