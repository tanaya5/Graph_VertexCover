#include <iostream>
#include <unistd.h>
#include <vector>
#include <signal.h>
#include <cstdlib>
#include <sys/wait.h>

int main (int argc, char **argv)
{
    int pipe1[2];
    int pipe2[2];
    pipe(pipe1);
    pipe(pipe2);
    std::vector<pid_t> kids;
    pid_t kid=fork();
    if(kid==0)
    {
        if(dup2(pipe1[1], STDOUT_FILENO)!=1)
        {
            std::cerr<<"error opening for rgen"<<std::endl;
        }
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        std::cerr<<execvp("./rgen",argv)<< "from execvp rgen"<<std::endl;
        std::cerr << "Error: in execvp\n";
        abort ();
    }
    else if (kid < 0)
    {
        std::cerr << "Error: could not fork\n";
        return 1;
    }

    kids.push_back(kid);
    kid=fork();
    if(kid==0)
    {
        if(dup2(pipe1[0], STDIN_FILENO)!=0 || dup2(pipe2[1],STDOUT_FILENO)!=1)
        {
            std::cerr<<"Error: opening for a1"<<std::endl;
        }
        close(pipe1[1]);
        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe2[1]);
        execl("/usr/bin/python", "/usr/bin/python", "./ece650-a1.py", (char *)NULL);
        std::cerr << "Error: in execvp\n";
        abort ();
    }
    else if (kid < 0)
    {
        std::cerr << "Error: could not fork\n";
        return 1;
    }
    kids.push_back(kid);



    kid=fork();
    if(kid==0)
    {
        if(dup2(pipe2[1],STDOUT_FILENO)!=1)
        {
            std::cerr<<"Error: opening for a1"<<std::endl;
        }
        close(pipe1[1]);
        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe2[1]);
        while (!std::cin.eof())
        {
            //gets the line

            std::string line;
            std::getline(std::cin, line);
            std::cout<<line<<std::endl;
        }
        for (pid_t k : kids)
        {
        int status;
        kill (k, SIGTERM);
        waitpid(k, &status, 0);
        }

        return 1;
    }
    else if (kid < 0)
    {
        std::cerr << "Error: could not fork\n";
        return 1;
    }
    kids.push_back(kid);




    kid=0;
    if(dup2(pipe2[0], STDIN_FILENO)!=0)
    {
        std::cerr<<"Error: opening for a2"<<std::endl;
    }
    close(pipe2[1]);
    close(pipe2[0]);
    close(pipe1[1]);
    close(pipe1[0]);
    execvp("./ece650-a2",argv);



    for (pid_t k : kids)
    {
        int status;
        kill (k, SIGTERM);
        waitpid(k, &status, 0);
    }

    return 0;
}
