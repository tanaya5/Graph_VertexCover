// Compile with c++ ece650-a2cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include <list>
#include <cstdint>
#include <memory>
#include <pthread.h>
#include <time.h>

struct vc_return {
    std::string vc_output = "";
    int vc_count = 0;
};

#include "Logger.h"
#include "CnfSatVc.h"
#include "ApproxVc1.h"
#include "ApproxVc2.h"

struct vc_arg {
    Logger logger;
    std::size_t vertex_count;
    std::vector< std::pair<unsigned,unsigned> > edges;
};

//Global variables
vc_return cnf_return, vc1_return, vc2_return;
unsigned long long cnf_rt, vc1_rt, vc2_rt;

unsigned long long getMyRunTime()
{
    clockid_t cid;
    struct timespec ts;
    int retcode;

    retcode = pthread_getcpuclockid(pthread_self(), &cid);
    if(retcode==0) {
        if (clock_gettime(cid, &ts) == -1)
        {
            std::cerr << "ERROR: clock_gettime" << std::endl << std::flush;
        }
        return (ts.tv_sec*1000000)+(ts.tv_nsec/1000);
    }
    else {
        std::cerr << "ERROR: pthread_getcpuclockid - " << retcode << std::endl << std::flush;
    }
    return 0;
}

void * cnf(void * arg)
{
    vc_arg *cnf_arg = (vc_arg*) arg;
    CnfSatVc cnf(cnf_arg->logger, cnf_arg->vertex_count, cnf_arg->edges);
    cnf.getResults( &cnf_return );
    cnf_rt = getMyRunTime();
    return NULL;
}

void * vc1(void * arg)
{
    vc_arg *vc1_arg = (vc_arg*) arg;
    ApproxVc1 vc1(vc1_arg->logger, vc1_arg->vertex_count, vc1_arg->edges);
    vc1.getResults( &vc1_return );
    vc1_rt = getMyRunTime();
    return NULL;
}

void * vc2(void * arg)
{
    vc_arg *vc2_arg = (vc_arg*) arg;
    ApproxVc2 vc2(vc2_arg->logger, vc2_arg->vertex_count, vc2_arg->edges);
    vc2.getResults( &vc2_return );
    vc2_rt = getMyRunTime();
    return NULL;
}
/****************************
 * UserInterface class definition
 ****************************/
class UserInterface
{
private:
    Logger logger;
    std::istringstream input_stream;
    std::string current_line;
    std::vector< std::pair<unsigned,unsigned> > edges;
    std::size_t vertex_count = 0;

    std::string readLine();
    char getCharInput();
    int getIntInput();
    bool isValidChar(char value, char check_for, bool throw_exception);
    bool isValidVertex(int value, unsigned min_value, unsigned max_vertex);
    unsigned getVertexInput();
    std::vector< std::pair<unsigned,unsigned> > getEdgesInput(unsigned max_vertex);
    std::pair<unsigned,unsigned> getPathRequest(unsigned max_vertex);
    void printDebug(std::string output, bool line_break);
    void saveData(int serial, std::size_t vertex_count, int cnf_ct, unsigned long long cnf_rt, int vc1_ct, unsigned long long vc1_rt, int vc2_ct, unsigned long long vc2_rt);

public:
    UserInterface();
    void debugOn();
    int run();
};


/****************************
 * UserInterface class implementation
 ****************************/
UserInterface::UserInterface()
{
}

void UserInterface::debugOn()
{
    this->logger.debugOn();
}

std::string UserInterface::readLine()
{
    std::getline(std::cin, this->current_line);
    this->input_stream.clear();
    this->input_stream.str( this->current_line );
    this->logger.printDebug( "\nLine Input: " + this->current_line + " (string size = " + std::to_string(this->current_line.size()) + ")");
    return this->current_line;
}

char UserInterface::getCharInput()
{
    char char_input;
    this->input_stream >> char_input;
    if(this->input_stream.fail())
    {
        throw "Failed to read a character from input stream.";
    }
    return char_input;
}

int UserInterface::getIntInput()
{
    int int_input;
    this->input_stream >> int_input;
    if(this->input_stream.fail())
    {
        throw "Failed to read an integer from input stream.";
    }
    return int_input;
}

bool UserInterface::isValidChar(char value, char check_for, bool throw_exception = true)
{
    if(value != check_for)
    {
        if( throw_exception )
        {
            std::string error(1,value);
            error.append(" is not a valid input character. ");
            error.append(1,check_for);
            error.append(" expected");
            throw error;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool UserInterface::isValidVertex(int value, unsigned min_value, unsigned max_vertex)
{
    if (value < (int) min_value || value > (int) max_vertex)
    {
        std::string error(std::to_string(value) + " is not a valide vertex. Expected value between " + std::to_string(min_value) +
                          " and " + std::to_string(max_vertex));
        throw error;
    }
    return true;
}

unsigned UserInterface::getVertexInput()
{
    int vertex_count;
    vertex_count = this->getIntInput();
    isValidVertex(vertex_count, 1, INT_MAX);
    return vertex_count;
}

std::vector< std::pair<unsigned,unsigned> > UserInterface::getEdgesInput(unsigned max_vertex)
{
    std::vector< std::pair<unsigned,unsigned> > edges;
    char command, delimiter;
    int vertex;

    command = this->getCharInput();
    isValidChar(command, 'E');

    delimiter = this->getCharInput();
    isValidChar(delimiter, '{');

    while (!this->input_stream.eof())
    {
        std::pair<unsigned,unsigned> edge;
        delimiter = this->getCharInput();
        if( isValidChar(delimiter, '}', false) )
        {
            break;
        }
        else
        {
            isValidChar(delimiter, '<');
        }

        vertex = this->getIntInput();
        isValidVertex(vertex, 0, max_vertex);
        edge.first = vertex;

        delimiter = this->getCharInput();
        isValidChar(delimiter, ',');

        vertex = this->getIntInput();
        isValidVertex(vertex, 0, max_vertex);
        edge.second = vertex;

        delimiter = this->getCharInput();
        isValidChar(delimiter, '>');

        edges.push_back(edge);

        delimiter = this->getCharInput();
        if( isValidChar(delimiter, '}', false) )
        {
            break;
        }
        else
        {
            isValidChar(delimiter, ',');
        }
    }//while
    return edges;
}

std::pair<unsigned,unsigned> UserInterface::getPathRequest(unsigned max_vertex)
{
    std::pair<unsigned,unsigned> path_request;
    int value;
    value = this->getIntInput();
    isValidVertex(value, 0, max_vertex);
    path_request.first = value;

    value = this->getIntInput();
    isValidVertex(value, 0, max_vertex);
    path_request.second = value;

    return path_request;
}

void UserInterface::saveData(int serial, std::size_t vertex_count, int cnf_ct, unsigned long long cnf_rt, int vc1_ct, unsigned long long vc1_rt, int vc2_ct, unsigned long long vc2_rt)
{
    std::string data_row =  std::to_string(serial) + "," +
                            std::to_string(vertex_count) + "," +
                            std::to_string(cnf_ct) + "," +
                            std::to_string(cnf_rt) + "," +
                            std::to_string(vc1_ct) + "," +
                            std::to_string(vc1_rt) + "," +
                            std::to_string(vc2_ct) + "," +
                            std::to_string(vc2_rt) + "\n";

    std::cerr << data_row << std::flush;
}

int UserInterface::run()
{
    std::pair<unsigned, unsigned> path_request;
    char command;
    bool read_edges = true;
    unsigned counter = 1;
    pthread_t pthreads[3];
    void *ret;

    int serial = 0;
    while (!std::cin.eof())
    {
        std::string line;
        try
        {
            this->logger.printDebug("----------- Run Count: " + std::to_string(counter++) + "------------");

            line = this->readLine();
            if (line.size()==0)
            {
                continue; //TBD: Do we need to throw an error?
            }
            command = this->getCharInput();
            if(command=='V')
            {
                vertex_count = 0;
                edges.clear();
                read_edges = true;
                vertex_count = this->getVertexInput();

                while(!std::cin.eof() && read_edges)
                {
                    try
                    {
                        this->readLine(); //read next line for edges
                        edges = this->getEdgesInput(vertex_count-1);
                        read_edges = false;

                        if(vertex_count  > 0 && this->edges.size() > 0)
                        {
                            vc_arg cnf_arg;
                            cnf_arg.logger = this->logger;
                            cnf_arg.vertex_count = vertex_count;
                            cnf_arg.edges = edges;

                            pthread_create(&pthreads[0], NULL, cnf, (void *) &cnf_arg);
                            pthread_create(&pthreads[1], NULL, vc1, (void *) &cnf_arg);
                            pthread_create(&pthreads[2], NULL, vc2, (void *) &cnf_arg);

                            //wait for threads to finish
                            pthread_join(pthreads[0], &ret);
                            pthread_join(pthreads[1], &ret);
                            pthread_join(pthreads[2], &ret);

                            //print output
                            serial++;
                            this->saveData(serial,vertex_count,cnf_return.vc_count,cnf_rt,vc1_return.vc_count,vc1_rt,vc2_return.vc_count,vc2_rt);
                            std::cout << cnf_return.vc_output << std::endl << std::flush;
                            std::cout << vc1_return.vc_output << std::endl << std::flush;
                            std::cout << vc2_return.vc_output << std::endl << std::flush;
                        }
                    }
                    catch(std::string error)
                    {
                        std::cerr << "Error: " << error << std::endl;
                    }
                }
            }
            else
            {
                std::string error(1, command);
                error.append(" is not a valid command. Valid commands here are V or s.");
                throw error;
            }

        }
        catch(std::string error)
        {
            std::cerr << "Error: " << error << std::endl;
        }
        catch(const char* error)
        {
            std::cerr << "Error: " << error << std::endl;
        }
    }//while

    return 0;
}

int main(int argc, char **argv)
{
    UserInterface ui;

    //check for debug mode
    if( argc == 2 )
    {
        std::string arg_1(argv[1]);
        if( arg_1.compare("-v")==0 )
        {
            ui.debugOn();
        }
    }
    return ui.run();
}
