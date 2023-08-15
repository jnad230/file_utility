# file_utility
Created a versatile 'File Utility' using C programming. The utility displayed the first 10 words of 'sample.txt' in the current directory, adapting to smaller files. Command-line support was added to specify alternate source files, granting users more control.

Additionally, the utility allowed content from the source file to be appended to a designated file using the '-a' argument. A customizable viewing/appending option using the '-n' argument was introduced, enhancing flexibility.

Provided users with seamless file manipulation and clear instructions through user documentation, showcasing strong C programming skills.

User Commands

    Name
    
    fileutil - output or append the file contents

    SYNOPSIS
    
    ./futil -n [number] -a [fileName]
        or
    ./futil -a [fileName] -n [number]
        or
    ./futil -a [fileName]
        or
    ./futil -n [number]
        or
    ./futil [filename]
        or
    ./futil 
    
        Commands:
    
            ./futil, it reads default file "sample.txt" from the directory and prints the first 10 words of the file.
            If the file contains fewer than 10 words, output the entire file contents.
            To compile the program, a user can use it on either default file or specified file name.
            e.g ./futil                : print the first 10 words from the default file
                ./futil filename       : print the first 10 words from the specified file, where the file should be in the same directory.
    
        
            -n,  take a positive integer number as an argument after this command
            This command outputs either the specified number of words or appends the specified number of words to a specified file.
    
            To compile the program, a user can use it on default settings.
            e.g ./futil -n number   
            where number is the non-negative number.
            If the file contains fewer than the number of words, output the entire the file contents.

            For example, to get the first 20 words from the default file use command should look like ./futil -n 20
    
            Limitation:
            After the -n there should be always a non-negative number otherwise terminal would throw an error.
            Similarly any problem in the accessing the file terminal will throw an error.
    
            -a,  This command appends either the first 10 words or the specified number of words from the default file. 
            If the -n argument is specified, the value given by the user should be used as the number of words to be appended.
            If the file contains fewer than the number of words, append the entire file contents.
    
            To compile the program use the command,
            e.g    ./futil -a filename      : Appends the first 10 words from the default file.
    
            when -n is added in the command for the number of words here the number of              words is the non-negative number, it is always specified after the -n. 
                ./futil -a filename -n number     : Print the first number of words from the default file into the specified file.
                ./futil -n number -a filename     : Print the first number of words from the default file into the specified file.

            For example, to append the first 20 words to the specified filename would look like ./futil filename -a filename -n 20
        
            
            Limitation:
            Order of the command always look like the one mentioned in this document 
            Any difference in the order would lead to an error.
            After the -n there should be always a non-negative number otherwise terminal would throw an error.
            After the -a there should be always be a filename otherwise terminal would throw an error.
            Using the non-default file, it should be in the same directory otherwise terminal will throw an error
            Similarly, any problem in accessing the file terminal will throw an error. 
