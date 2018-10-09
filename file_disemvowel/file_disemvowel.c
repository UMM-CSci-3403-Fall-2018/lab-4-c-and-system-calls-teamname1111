#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define BUF_SIZE 1024

// Determines if a character is a vowel or not
bool isVowel(char letter)
{
  // Look for capital and lowercase vowels
  switch(letter)
  {
    // All vowels
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      return true;
      break;

    // Otherwise it isn't a vowel
    default:
      return false;
      break;
  }
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    /*
     * Copy all the non-vowels from in_buf to out_buf. 
     * num_chars indicates how many characters are in in_buf, 
     * and this function should return the number of non-vowels that
     * that were copied over.
     */
	int count = 0;
	//Loops over the string and adds non-vowel characters to the
	//buffer and adds one to the count each time it comes across
	//a non-vowel character
 	for(int i = 0; i < num_chars; i++)
 	{
		if(!isVowel(in_buf[i]) && in_buf[i] != '\0')
		{
			out_buf[count] = in_buf[i];
			count++;
		}
     	}

	return count;
}

void disemvowel(FILE* inputFile, FILE* outputFile) { 
    /*
     * Copy all the non-vowels from inputFile to outputFile.
     * Create input and output buffers, and use fread() to repeatedly read
     * in a buffer of data, copy the non-vowels to the output buffer, and
     * use fwrite to write that out. 
     */

	//Create a buffer
	char* in_buffer = (char*) calloc (512, sizeof(char));
	char* out_buffer = (char*) calloc (512, sizeof(char));

	//Add contents of file to buffer
	fread(in_buffer, sizeof(char), 512, inputFile);

	//Takes ONLY non-vowels from in_buffer and puts them in out_buffer
	int t = copy_non_vowels(512, in_buffer, out_buffer);
        
	//Writes to the output file
	fwrite(out_buffer, sizeof(char), t, outputFile);

	fclose(outputFile);
	fclose(inputFile);
	free(in_buffer);
	free(out_buffer);

}

int main(int argc, char *argv[]) { 
    FILE *inputFile; 
    FILE *outputFile;
    
    //Determines the case of the input and runs accordingly
    switch(argc)
    {
	case 1:
		inputFile = stdin;
		outputFile = stdout;
		break;
	case 2:
		inputFile = fopen(argv[1], "r");
		outputFile = stdout;
		break;
	case 3:
		inputFile = fopen(argv[1], "r");
 	     	outputFile = fopen(argv[2], "w");
		break;
    }
    //Runs disemvowel
    disemvowel(inputFile, outputFile);
    return 0; 
}
