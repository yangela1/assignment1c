#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(char **arr, int numRows, int size){
	for (int i = 0; i < numRows; i++){
		for (int j = 0; j < size; j++){
			printf("%c", arr[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]){
    if (argc != 3) { 
        printf("Usage: %s <num_chars_per_line> <input_file> \n", argv[0]);
        return 1;
    }
    
    char *inputFileName = argv[2];
    int size= atoi(argv[1]);

	//allocate memory for 2D array
 	char **arr = (char **)malloc(size * sizeof(char *));
	for (int i = 0; i < size; i++){
		arr[i] = (char *)malloc(size * sizeof (char));
	}
    
	// open file for reading mode 
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    }

	char c;
	int row = 0, col = 0;
	int canPrint = 0;
	
	
    //read and print each character
    while ((c = fgetc(file)) != EOF) {
    	
    	//if col reached size, then start new row and reset col 
    	if (col == size) {
    		col = 0;
    		row++;
    	}
    	
    	//size is too small, words will not fit into array
    	if (row == size){
    		printf("Error. The word processor can't display the output.\n");
    		canPrint = 1;
    		break;
    	} 
    	
    	//if char is space or newline, add a sapce
    	if (c == ' ' || c == '\n'){
    		if (col < size){
    			arr[row][col] = ' ';
    			col++;
    		}
    		
    		
    		if (c == '\n'){
    			col = 0;
    			row++;
    		}
    	} else { //assign char to array
    		arr[row][col] = c;
    		col++;
    	}
   	 	
    }
    
    //close the file
    fclose(file);

    //print the array
    if (canPrint == 0){
   		printArray(arr, row, size);
   	}
   	
    //free allocated memory
	for (int i = 0; i < size; i++){
		free(arr[i]);
	}
	free(arr);

	return 0;
}






