# TuringMachineSimulator
This program implements a nondeterministic Turing machine simulator in C++.  
It recives an input text file, which contains set of states, tape alphabet, input alphabet, set of final states and transitions function.   
The program has two modes: ***run and debug***.

In ***run*** mode program gets the input string and if accepted prints the output of Turing Machine.

In ***debug*** mode the program supports following commands  
        **< -s / -step >** executes one step at a time  
				**< -q / -quit >** quit debug mode  
				**< -a / -all>** executes rest of the programm  
				**< -c >** outputs current state(CS) and header pointer index(HP)  

**Note that a character corresponding to the blank symbol is 'B'**

**'('  ')'  ',' and '|' are special characters and cannot be used as alphabet symbols.**
