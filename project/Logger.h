/****************************
 * Logger class definition
 ****************************/
class Logger
{
private:
    bool debug_mode = false;

public:
    Logger();
    void debugOn();
    void debugOff();
    void printDebug(std::string output, bool line_break);
};

/****************************
 * Logger class implementation
 ****************************/
Logger::Logger()
{
}

void Logger::debugOn()
{
    this->debug_mode = true;
}

void Logger::debugOff()
{
    this->debug_mode = false;
}

void Logger::printDebug(std::string output, bool line_break = true)
{
    if (this->debug_mode)
    {
        std::cout << output;
        if (line_break)
        {
            std::cout << std::endl;
        }
    }
}

