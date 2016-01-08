# Delimiter-Analyzer
Program that uses my own stack class to analyze source code written in any language (C, C++, Lisp, etc) and report the location of any mismatched delimiters.

@author Adrienne Bergh

# Program Components
- Implementation of a generic stack class called GenStack
- Takes as a command line argument the name of a file to be processed
- If the delimiters in the file are ok, report to the user that the delimiter syntax is correct, and ask if they want to analyze another file.
- If a delimiter file exists, notifies user of the location of the error and what the error is (eg: “Line 20: expected ) and found ]”), and exits the program.
