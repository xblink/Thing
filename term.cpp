#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include "clientManager.h"

#define VERBOSE     true

using namespace std;

// utils
/**
 * Returns nothing.
 * Method to output a value to stdout. Payload address must be of a type
 * that can be inserted into a stream.
 *
 * @param   t       address of payload
 * @param   bool    boolean specifying newline. 
 * @returns void
 *
 */
template <typename T>
bool verbose(T const& t, bool end=false) {
    if (VERBOSE) cout << t;
    if (end && VERBOSE) cout << endl;
    return VERBOSE;
}


/** 
 * Returns nothing.
 * Method to handle signals. Does nothing.
 * @returns void.
 */
void sig_handler(int signal) {
    //nothing
}


/** 
 * Returns nothing.
 * Method to delete memory dynamically allocated when parsing tokens.
 *
 */
void del_tokens(char ** tokens, int tokenCount) {
    if (tokens != NULL) {
        for (int i = 0; i < tokenCount; i++) {
            //delete tokens[i];
        }
        delete[] tokens;
    }
}

/** 
 * Returns unsigned integer representing count of tokens discovered.
 * Method to resolve a char string into an array of tokens.
 * 
 * @params  buf     input string to be tokenized
 * @params tokens   pointer to an array of char pointers
 * @returns unsigned int    count of tokens found
 *
 */
unsigned int tokenize(char * buf, char *** tokens) {
    char * bufp = strdup(buf);
    char *token;
    unsigned int tokenCount = 0;

    while ((token = strsep(&bufp, " ")) != NULL) {
        if (strcmp(token, "") != 0) {
            tokenCount++;
        }
    }

    verbose("Token Count: ");
    verbose(tokenCount, true);

    delete bufp;
    bufp = strdup(buf);

    *tokens = new char*[tokenCount];

    verbose("Tokenization: { ");
    for (unsigned int i = 0; i < tokenCount; i++) {
        token = strsep(&bufp, " ");
        if (strcmp(token, "") != 0) {
            (*tokens)[i] = token;

            verbose((*tokens)[i]);
            if (i != (tokenCount - 1)) verbose(", ");
        }
        else i--;
    }
    verbose(" }", true);

    //delete bufp;
    return tokenCount;
}


/** 
 * Returns nothing.
 * Method to execute inputs.
 * 
 * @params proc pointer to process to execute
 * @params stdi pointer to standard in
 * @params stdo pointer to standard out
 * @params stde pointer to standard error
 * @returns void
 *
 */
void execute(process * proc, const char * stdi, const char * stdo, const char * stde) {
    pid_t pid = fork();
    if (pid == 0) {
        if (strcmp(stdi, "STDIN_FILENO") != 0) {
            string filename = stdi;
            freopen(filename.c_str(), "r", stdin);
        }
        if (strcmp(stdo, "STDOUT_FILENO") != 0) {
            string filename = stdo;
            size_t pos = filename.find(" (truncate)");
            if (pos != string::npos) {
                filename = filename.substr(0, pos);
                freopen(filename.c_str(), "w+", stdout);
            }

            pos = filename.find(" (append)");
            if (pos != string::npos) {
                filename = filename.substr(0, pos);
                freopen(filename.c_str(), "a", stdout);
            }
        }
        if (strcmp(stde, "STDERR_FILENO") != 0) {
            string filename = stde;
            size_t pos = filename.find(" (truncate)");
            if (pos != string::npos) {
                filename = filename.substr(0, pos);
                freopen(filename.c_str(), "w+", stderr);
            }

            pos = filename.find(" (append)");
            if (pos != string::npos) {
                filename = filename.substr(0, pos);
                freopen(filename.c_str(), "a", stderr);
            }
        }

        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        signal(SIGCHLD, SIG_DFL);
        execvp(proc->argv[0], proc->argv);
    }
    else if (pid > 0) {
        int * status;
        wait(status);

        if(WIFEXITED(status)) {
            //exit(-1);
        }
    }
}

/** 
 * Retuns an integer representing success/fail.
 *
 *
 */
int main(int argc, char * argv[]) {
    cout.setf(ios::unitbuf);
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
    signal(SIGTSTP, sig_handler);
    signal(SIGTTIN, sig_handler);
    signal(SIGTTOU, sig_handler);
    signal(SIGCHLD, sig_handler);

    for(;;) {
        bool newProc = true;
        char * prompt = argv[0] + 2;
        int pipeCount = 0;
        int procCount = 1;
        int cProc = 0;
        char stde[4096] = "STDERR_FILENO";
        char stdi[4096] = "STDIN_FILENO";
        char stdo[4096] = "STDOUT_FILENO";
        process** processes;
        char buffer[4096];
        char ** tokens = NULL;
        int tokenCount = 0;

        memset(buffer, '\0', sizeof(buffer));
        cout << prompt << "$ ";
        cin.getline(buffer, sizeof(buffer) - 1);
        if (buffer[0] != '\0') {
            tokenCount = tokenize(buffer, &tokens);


            if (tokenCount > 0) {
                if (strcmp(tokens[0], "exit") == 0) {
                    del_tokens(tokens, tokenCount);
                    break;
                }
            }

            for(int i = 0; i < tokenCount; i++) {
                if(strcmp(tokens[i], "|") == 0) {
                    pipeCount++;
                    if (i < tokenCount - 1) {
                        procCount++;
                    }
                }
            }


            processes = new process*[procCount];


            for(int i = 0; i < tokenCount; i++) {
                char * token;
                token = tokens[i];

                if (strcmp(token, "e>>") == 0) {
                    if (i < tokenCount - 1) {
                        verbose("STDERR redirected to ");
                        verbose(tokens[i + 1], true);
                        sprintf(stde, "%s (append)", tokens[i + 1]);
                    }
                }
                if (strcmp(token, "e>") == 0) {
                    if (i < tokenCount - 1) {
                        verbose("STDERR redirected to ");
                        verbose(tokens[i + 1], true);
                        sprintf(stde, "%s (truncate)", tokens[i + 1]);
                    }
                }
                else if (strcmp(token, ">>") == 0) {
                    if (i < tokenCount - 1) {
                        verbose("STDERR redirected to ");
                        verbose(tokens[i + 1], true);
                        sprintf(stdo, "%s (append)", tokens[i + 1]);
                    }

                }
                else if (strcmp(token, ">") == 0) {
                    if (i < tokenCount - 1) {
                        verbose("STDERR redirected to ");
                        verbose(tokens[i + 1], true);
                        sprintf(stdo, "%s (truncate)", tokens[i + 1]);
                    }

                }
                else if (strcmp(token, "<<") == 0) {
                    if (i < tokenCount - 1) {
                        verbose("STDERR redirected to ");
                        verbose(tokens[i + 1], true);
                        sprintf(stdi, "%s", tokens[i + 1]);
                    }

                }
                else if (strcmp(token, "|") == 0) verbose("Pipe Found.", true);
                else {
                    if (newProc) {}

                    processes[cProc] = new process;
                    process * proc = processes[cProc];

                    for (int j = i; j < tokenCount && strcmp(tokens[j], "|") != 0; j++) {
                        proc->argc++;
                    }

                    verbose("New Process: ");
                    verbose(tokens[i], true);
                    verbose("Arguments: ");
                    verbose(proc->argc, true);

                    proc->argv = new char*[proc->argc];

                    verbose("[");
                    for (int j = i; j - i < proc->argc; j++) {
                        proc->argv[j - i] = tokens[j];
                        verbose(proc->argv[j - i]);
                        verbose(", ");
                    }
                    verbose("]", true);

                    i += proc->argc - 1;
                    cProc++;
                }
            } // endfor



            for (int i = 0; i < procCount; i++){
                process * proc = processes[i];
                execute(proc, stdi, stdo, stde);
            }

            del_tokens(tokens, tokenCount);
        }


    }
}
