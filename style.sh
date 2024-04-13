#!/bin/bash

# Remove the binary file errors
cat old.log | grep -vE "\.o" | grep -vE "\.a" | grep -vE "my_rpg" > reports.log

# Get the number of lines in reports.log
num_lines=$(wc -l < reports.log)

declare -A error_codes
error_codes["C-O1"]="Contents of the repository: .o, .a, binary, *~, ..."
error_codes["C-O2"]="File extension: C file extension can only be .c or .h"
error_codes["C-O3"]="File coherence: Max 10 functions, 5 non-static"
error_codes["C-O4"]="Naming files and folders: Naming in snake_case"
error_codes["C-G1"]="File header: The file must start with a header"
error_codes["C-G2"]="Separation of functions: 1 line between each functions"
error_codes["C-G3"]="Indentation of preprocessor directives"
error_codes["C-G4"]="Global variables"
error_codes["C-G5"]="Include: include directive should only include .h file"
error_codes["C-G6"]="Line endings: Newline is done using \\n not \\r"
error_codes["C-G7"]="Trailing spaces"
error_codes["C-G8"]="Trailing or Leading lines"
error_codes["C-G9"]="Constant values"
error_codes["C-G10"]="Inline assembly: Inline assembly must never be used"
error_codes["C-F1"]="Coherence of functions: A function should only do one thing"
error_codes["C-F2"]="Naming of functions: Must contain a verb, in english and in snake_case"
error_codes["C-F3"]="Number of columns: The length of a line must not exceed 80 columns"
error_codes["C-F4"]="Number of lines: The body of a function must not exceed 20 lines"
error_codes["C-F5"]="Number of parameters: Maximum 4 parameters"
error_codes["C-F6"]="Function without parameters: A function without parameters must take void as parameter"
error_codes["C-F7"]="Structure as parameters: Structure need to be passed using pointer, not by copy"
error_codes["C-F8"]="Comments inside a function"
error_codes["C-F9"]="Nested functions: Nested functions are not allowed"
error_codes["C-L1"]="Code line content: A line must correspond to only one statement."
error_codes["C-L2"]="Indentation: Each indentation level must be done by using 4 spaces"
error_codes["C-L3"]="Spaces: When using a space as a separator, one and only one space character must be used"
error_codes["C-L4"]="Curly brackets: Opening curly brackets must be at the end of the line, Closing brackets alone on a new line"
error_codes["C-L5"]="Variable declaration: Variables must be declared at the beginning of the function, only one at the time"
error_codes["C-L6"]="Blank lines: A blank line must separate the variable declarations from the remainder of the function"
error_codes["C-V1"]="Naming identifiers: All identifier names must be in English, according to the snake_case convention"
error_codes["C-V2"]="Structures: Structures must be kept as small as possible"
error_codes["C-V3"]="Pointers: The asterisk (*) must be attached to the associated variable"
error_codes["C-C1"]="Conditional branching: A conditionnal block must not contain more than 3 branches"
error_codes["C-C2"]="Ternary operators: Must be kept simple and readable"
error_codes["C-C3"]="Goto: goto keyword is forbidden"
error_codes["C-H1"]="Content: Header only contain declaration"
error_codes["C-H2"]="Include guard: Header must be protected from double inclusion"
error_codes["C-H3"]="Macros: Macros must match only one statement, and fit on a single line"
error_codes["C-A1"]="Constant pointer: If the data is not modified you should use a const"
error_codes["C-A2"]="Typing: Prefer the most accurate types possible according to the use of the data"
error_codes["C-A3"]="Line break at the end of the file"
error_codes["C-A4"]="Static: Intern global variable and intern function should be static"

# Check if the file is empty
if [ "$num_lines" -eq 0 ]; then
    echo -e "\t\033[102m-> No coding style error.\033[0m"
else
    echo -e "\t\033[101m-> Found $num_lines errors.\033[0m"
    # Read each line and print it
    while IFS= read -r line; do
        # Use awk to parse the line
        file=$(echo "$line" | awk -F: '{print $1}')
        line_number=$(echo "$line" | awk -F: '{print $2}')
        gravity=$(echo "$line" | awk -F'[: ]+' '{print $3}')
        error_code=$(echo "$line" | awk -F'[: ]+' '{print $4}')

        if [ "$gravity" == "MAJOR" ]; then
            echo -e "\033[101m$file:$line_number: $error_code\033[0m ${error_codes["$error_code"]}"
        elif [ "$gravity" == "MINOR" ]; then
            echo -e "\033[103m$file:$line_number: $error_code\033[0m ${error_codes["$error_code"]}"
        elif [ "$gravity" == "INFO" ]; then
            echo -e "\033[106m$file:$line_number: $error_code\033[0m ${error_codes["$error_code"]}"
        else
            echo -e "\033[107m$file:$line_number: $error_code\033[0m ${error_codes["$error_code"]}"
        fi
    done < reports.log
fi
