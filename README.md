My own implementation of the C Library Function: system(const char *command). 
Uses: fork(), exec(), wait_pid(), and sigaction().

Example usage: ./HW4 "ls"
This will tell the program to execute the ls shell command. To run a different command, simply replace what is in between the quotes with the desired shell command i.e. ./HW4 "mkdir"

Assignment Specifications:
The C library function:
int system(const char *comm)
is used to execute subprocesses and commands. It is defined in
the stdlib.h header.
Parameters:
comm -- This is a character string containing the requested
command.
Return Value:
The value returned is -1 on error, and the return status of the
command otherwise.

Implement your own user defined system function:
int cs531_system(const char *comm)
Include the following functions/macros within your program:
fork(), execlp(), dup(), wait(), signal()/sigaction(),
WEXITSTATUS(), WTERMSIG(), WSTOPSIG(), WIFCONTINUED()
Do Not use system().
cs531_system() must have robust error handling, including signal
handling for SIGINT and signal acknowledgment, for SIGQUIT,
SIGKILL, and SIGSTOP. Your code should be well documented.
