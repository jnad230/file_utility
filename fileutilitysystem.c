/*  task1.c 
    Author: Javeriya Nadaf
    Student ID: 32095376
    This program is a file utility system that prints a given number of words
    from a file or appends them to another file */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> /* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//main starts here

int main(int argc, char *argv[])
{
    int i, sourceFile, n, destFile, numberInputCheck; //creating integer variables
    int numberInput = 10; //default number of words to be printed or appended
    bool append = false;
    int wordCount = 1;  
    char buffer[1024]; 
    char output[1024]; 
    char *word;

    if (argc == 1)
    { // If only 1 argument given use default settings

        if ((sourceFile = open("sample.txt", O_RDONLY, S_IRUSR)) < 0)
        {
            exit(1); // terminate unsuccessfully
        }
    }
    else if (argc == 2)
    { // If 2 arguments given, check if input is appropriate, if yes, then print the first ten words of the user specified file
        if (strcmp(argv[1], "-n") == 0)
        {
            write(2, "Usage: ./out -n positive number of words to be read\n", strlen("Usage: ./out -n positive number of words to be read\n"));
            exit(1);
        }
        else if (strcmp(argv[1], "-a") == 0)
        {
            write(2, "Usage: ./out -a filename\n", strlen("Usage: ./out -a destination file\n"));
            exit(1);
        }
        else
        { // open the user specified file
            if ((sourceFile = open(argv[1], O_RDONLY, S_IRUSR)) < 0)
            {
                write(2, "Failed to open the file\n", strlen("Failed to open the file\n"));
                exit(1); // terminate unsuccessfully
            }
        }
    }
    else if (argc == 3)
    { 

        if (strcmp(argv[1], "-n") == 0) // if 3 arguments are given check if second is "-n" and 3rd is a positive number
        {
            numberInput = atoi(argv[2]); // converts argument from string to integer
            
            // Check if the user input is a valid number
            if (numberInput < 0)
            {
                write(2, "Usage: ./out -n positive number of words to be read\n", strlen("Usage: ./out -n positive number of words to be read\n"));
                exit(1);
            }
            // open the sample file
            if ((sourceFile = open("sample.txt", O_RDONLY, S_IRUSR)) < 0)
            {
                write(2, "Failed to open the file\n", strlen("Failed to open the file\n"));
                exit(1); // terminate unsuccessfully
            }
        }
        
        else if (strcmp(argv[1], "-a") == 0) // if 3 arguments are given check if second is "-a" and third is a valid file
        {
            if ((sourceFile = open("sample.txt", O_RDONLY, S_IRUSR)) < 0)
            {
                write(2, "Failed to open the file\n", strlen("Failed to open the file\n"));
                exit(1); // terminate unsuccessfully
            }

            // open the destination file
            if ((destFile = open(argv[2], O_WRONLY | O_APPEND)) < 0)
            {
                write(2, "Failed to open the file\n", strlen("Failed to open the file\n"));
                exit(1);
            }

            append = true; //set append to true
        }
    }

    else if (argc == 5)
    {
        if (strcmp(argv[1], "-n") == 0) // if 5 arguments are given check if second is "-n" and 3rd is a positive number
        {
            numberInput = atoi(argv[2]);

            if (numberInput < 0)
            {
                write(2, "Usage: ./out -n positive number of words to be read -a filename\n", strlen("Usage: ./out -n positive number of words to be read -a filename\n"));
                exit(1);
            }

            if (strcmp(argv[3], "-a") == 0) // if 5 arguments are given check if the fourth is "-a" and fifth is a valid file
            {

                numberInputCheck = atoi(argv[4]); 

                // Check if the fifth argument is not a number
                if (numberInputCheck > 0)
                {
                    write(2, "Usage: ./out -n positive number of words to be read -a filename\n", strlen("Usage: ./out -n positive number of words to be read -a filename\n"));
                    exit(1);
                }

                if ((sourceFile = open("sample.txt", O_RDONLY, S_IRUSR)) < 0)
                {
                    write(2, "Failed to open the file\n", strlen("Failed to open the file\n"));
                    exit(1); // terminate unsuccessfully
                }

                if ((destFile = open(argv[4], O_WRONLY | O_APPEND)) < 0)
                {
                    write(2, "Failed to open the file\n", strlen("Failed to open the file\n"));
                    exit(1);
                }

                append = true;
            }
            else
            {
                write(2, "Usage: ./out -n positive number of words to be read -a filename\n", strlen("Usage: ./out -n positive number of words to be read -a filename\n"));
            }
        }
        else if (strcmp(argv[1], "-a") == 0) // if 5 arguments are given check if second is "-a" and third is a valid file
        {
            numberInput = atoi(argv[2]);

            if (numberInput > 0)
            {
                write(2, "Usage: ./out -a filename -n positive number of words to be read\n", strlen("Usage: ./out -a filename -n positive number of words to be read\n"));
                exit(1);
            }

            if (strcmp(argv[3], "-n") == 0) // if 5 arguments are given check if fourth is "-n" and fifth is a positive number
            {
                numberInput = atoi(argv[4]);

                if (numberInput < 0)
                {
                    write(2, "Usage: ./out -n positive number of words to be read -a filename\n", strlen("Usage: ./out -n positive number of words to be read -a filename\n"));
                    exit(1);
                }
            }

            if ((sourceFile = open("sample.txt", O_RDONLY, S_IRUSR)) < 0)
            {
                write(2, "Failed to open the file\n", strlen("Failed to open the file\n"));
                exit(1); // terminate unsuccessfully
            }

            if ((destFile = open(argv[2], O_WRONLY | O_APPEND)) < 0)
            {
                write(2, "Failed to open the file\n", strlen("Failed to open the file\n"));
                exit(1);
            }

            append = true;
        }
    }

    // Opens the source file
    n = read(sourceFile, buffer, sizeof(buffer));
    if (n < 0)
    {
        write(2, "read error sample.txt", strlen("read error sample.txt"));
    }

    // Breaks the file content string into individual words as tokens
    word = strtok(buffer, " ");

    // Concatenates each word into the output string
    strcat(output, word);
    strcat(output, " ");

    // Extracts the number of words requested by the user or ten words by default
    while (wordCount < numberInput)
    {

        word = strtok(NULL, " \n"); // null refers to static pointer
        strcat(output, word);
        strcat(output, " ");

        if (word != NULL)
        {
            wordCount++;
        }
        else
        {
            break;
        }
    }

    // If append is true, write to the destination file, else write to the terminal
    if (append)
    {
        write(destFile, output, strlen(output));
    }
    else
    {
        write(1, output, strlen(output));
    }

    close(destFile);
    close(sourceFile);
    exit(0);
}
