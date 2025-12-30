# To-do-list

Implementation of to do list program in C through commandline arguements while using time functions, string functions and file handling

## To install the program

### Precompiled executable
Windows: [Windows direct link](https://drive.google.com/uc?export=download&id=1kd5TuQvyEzRLcZl-a4fuRj9g2cOsaX6I)<br>
Linux: [Linux direct link](https://drive.google.com/uc?export=download&id=1MmpIBTHIEyBMNLopZGvsof3sbUoLw_jk)

### Compile through source
Make sure you have git and gcc/clang installed (preferably gcc 15.2.0)
1. Run below code in your terminal.
   
   ```
   https://github.com/bitan07-dev/to-do-list.git
   ```
3. cd into the project by running `cd to-do-list`.
4. Now compile your code using gcc/clang

## Features
The program features a command-line driven program where arguements are to be passed through command line arguements to get help regarding commands and arguements run `./todo -h` or `./todo --help` on linux or alternatively run `./todo.exe -h` on `./todo.exe --help` on windows machine.<br><br>
The program needs a first time setup which could be done by running with `-s` flag hoowever it can be overcome by just creating a `list.csv` file in the same folder as in program.

## Current command line arguements
```
-h or --help
        Display help text and exit
-s or --setup
        Run initial setup and exit
-c or --check
        Display current list and exit
-a "work" or --add "work"
        Add new work to do and exit
-d index or --delete index
        delete a work on index provided and exit
-t index or --toggle index
        toggle mark a work as done on index provided and exit
-r or --clear
        Clears current list after confirmation (use -y to bypass) and exit
```

## Project structure
```
to-do-list
├── todo.c                # Main program with all working
└── functions.h           # All functions used in the program
```

## Thanks for visiting :)
If you like this project or believe something more could be added create an issue to let me know ❤️
##
