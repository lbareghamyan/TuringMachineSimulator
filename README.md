# TuringMachineSimulator
This program implements a nondeterministic Turing machine simulator in C++.
It recives an input text file, which contains set of states, tape alphabet, input alphabet, set of final states and transitions function. 
The program has two modes: **run and debug**.

In **run** mode program gets the input string and if accepted prints the output of Turing Machine.

In **debug** mode the program can perform a step at a time when typed '-s'.

**Note that a character corresponding to the blank symbol is 'B'**

**'('  ')'  ',' and '|' are special characters and cannot be used as alphabet symbols.**
