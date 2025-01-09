#include "util.h"

#include <string>
using namespace std;

string getWorkingDir()
{
    string filePath(__FILE__);
    string workingDir = filePath.substr(0, filePath.find_last_of("/"));
    //cout << "Get working directory: " << workingDir << std::endl;
    return workingDir;
}
