/***********************************************************************
*    systemcommand.cpp:                                                *
*    User defined class, SystemCommand, for a bash-like interface      *
*    Copyright (c) 2016 Tyler Lewis                                    *
************************************************************************
*    This is a header file for libraryprojects:                        *
*    https://github.com/Pinguinsan/libraryprojects                     *
*    The source code is released under the GNU LGPL                    *
*    This file holds the implementation of a SystemCommand class       *
*    The class is made up entirely of static methods and constants     *
*    It is used to enable a bash-like iterface, allowing one to        *
*    retrieve the stdout/stderr from a call to the command interpreter *
*                                                                      *
*    You should have received a copy of the GNU Lesser General         *
*    Public license along with libraryprojects                         *
*    If not, see <http://www.gnu.org/licenses/>                        *
***********************************************************************/

#include "systemcommand.h"

const int SystemCommand::_DEFAULT_MAX_OUTPUT = 2147483647;

SystemCommand::SystemCommand(std::initializer_list<std::string> command) :
	_command{ *std::begin(command) },
    _maxOutput{_DEFAULT_MAX_OUTPUT},
    _hasError{false},
	_repeatCommand{ false }
{

}

SystemCommand::SystemCommand() : 
    _command{""},
    _maxOutput{_DEFAULT_MAX_OUTPUT},
    _hasError{false},
    _repeatCommand{false}
{

}

SystemCommand::SystemCommand(const std::string &command) : 
    _command{command},
    _maxOutput{_DEFAULT_MAX_OUTPUT},
    _hasError{false},
    _repeatCommand{false}
{

}

SystemCommand::SystemCommand(const std::string &command, int maxOutput) :
    _command{command},
    _maxOutput{maxOutput},
    _hasError{false},
    _repeatCommand{false}
{

}


void SystemCommand::printCommand()
{
    std::cout << this->_command << std::endl;
}

void SystemCommand::insertIntoCommand(int position, const std::string &stringToInsert)
{
    if (static_cast<unsigned int>(position) > this->_command.length()) {
        return;
    }
    this->_command.insert(position, stringToInsert);
	this->_repeatCommand = false;
}

void SystemCommand::insertIntoCommand(int position, char charToInsert)
{
    std::string temp = "";
    temp += charToInsert;
    this->insertIntoCommand(position, temp);
}

int SystemCommand::maxOutput()
{
    return this->_maxOutput;
}

std::string SystemCommand::command()
{
    return this->_command;
}

bool SystemCommand::hasError()
{
    return this->_hasError;
}

void SystemCommand::appendToCommand(const std::string &stringToAppend)
{
    _command += stringToAppend;
	this->_repeatCommand = false;
}

int SystemCommand::returnValue()
{
    return this->_returnValue;
}

void SystemCommand::setCommand(const std::string &command)
{
    this->_repeatCommand = false;
    this->_command = command;
    this->_hasError = false;
    this->_sizeOfOutput = 0;
    this->_outputAsVector.clear();
}

void SystemCommand::setMaxOutput(int maxOutput)
{
    this->_maxOutput = maxOutput;
}

std::string SystemCommand::outputAsString()
{
    std::string returnString = "";
    for (std::vector<std::string>::const_iterator iter = _outputAsVector.begin(); iter != _outputAsVector.end(); iter++) {
        returnString += (*iter);
    }
    return returnString;
}

void SystemCommand::stripShellControlCharactersFromCommand()
{
    //TODO: Implement
    return;
}

std::vector<std::string> SystemCommand::outputAsVector()
{
    return this->_outputAsVector;
}

void SystemCommand::execute()
{
    this->systemCommandLaunch(_WITH_PIPE);
}

std::vector<std::string> SystemCommand::executeAndWaitForOutputAsVector()
{
    this->systemCommandLaunch(_WITH_PIPE);
    return this->_outputAsVector;
}

void SystemCommand::executeWithoutPipe()
{
    this->systemCommandLaunch(_WITHOUT_PIPE);
}

std::string SystemCommand::stripAllFromString(const std::string &stringToStrip, const std::string &whatToStrip)
{
    std::string returnString = stringToStrip;
    if (returnString.find(whatToStrip) == std::string::npos) {
        return returnString;
    }
    while (returnString.find(whatToStrip) != std::string::npos) {
        returnString = stripFromString(returnString, whatToStrip);
    }
    return returnString;
}


std::string SystemCommand::stripFromString(const std::string &stringToStrip, const std::string &whatToStrip)
{
    std::string returnString = stringToStrip;
    if (returnString.find(whatToStrip) == std::string::npos) {
        return returnString;
    }
    size_t foundPosition = stringToStrip.find(whatToStrip);
    if (foundPosition == 0) {
        returnString = returnString.substr(whatToStrip.length());
    } else if (foundPosition == (returnString.length() - whatToStrip.length())) {
        returnString = returnString.substr(0, foundPosition);
    } else {
        returnString = returnString.substr(0, foundPosition) + returnString.substr(foundPosition+whatToStrip.length());
    }
    return returnString;
}

void SystemCommand::stripPipeFromCommand()
{
    #if defined(_WIN32) && defined(_MSC_VER)
        _command = stripAllFromString(_command, "2>&1");
        _command = stripAllFromString(_command, ">");
    #else
        _command = stripAllFromString(_command, "2>&1");
        _command = stripAllFromString(_command, ">");
    #endif
}


std::string SystemCommand::executeAndWaitForOutputAsString()
{
    this->systemCommandLaunch(_WITH_PIPE);
    return this->outputAsString();
}

int SystemCommand::sizeOfOutput()
{
    return this->_sizeOfOutput;
}

void SystemCommand::verifyValidMaxOutput()
{
    if ((_maxOutput <= 8) || (_maxOutput > std::numeric_limits<int>::max())) {
        _maxOutput = _DEFAULT_MAX_OUTPUT;
    }
}

FILE* SystemCommand::popenHandler(const std::string &directory, const std::string &fileMode)
{
    #if defined(_WIN32) && defined(_MSC_VER)
        return _popen(directory.c_str(), fileMode.c_str());
    #else
        return popen(directory.c_str(), fileMode.c_str());
    #endif
}

int SystemCommand::pcloseHandler(FILE *filePtr)
{
    #if defined(_WIN32) && defined(_MSC_VER)
		int returnValue = _pclose(filePtr);	
		return returnValue;
    #else
        int returnValue = pclose(filePtr);
        return returnValue == -1 ? -1 : returnValue/256;
    #endif
}

void SystemCommand::systemCommandLaunch(bool withPipe)
{
    stripPipeFromCommand();
    if (this->_repeatCommand) {
    	this->_hasError = false;
    	this->_sizeOfOutput = 0;
    	this->_outputAsVector.clear();
    } else {
        this->_repeatCommand = true;
    }
	this->_command += " 2>&1"; //Merges stderror with stdout
    verifyValidMaxOutput();
    if (withPipe) {
        FILE *fp;
        char path[PATH_MAX];

        fp = popenHandler(this->_command.c_str(), "r");
        if (fp == NULL) {
            std::cout << "ERROR: Failed to execute command \"" << this->_command << "\"" << std::endl;
            this->_returnValue = -1;
            return;
        }
		int outputSize{ 0 };
        while ((fgets(path, PATH_MAX, fp) != NULL) && (outputSize <= this->_maxOutput)) {
            std::string formattedPath{std::string(path)};
			addFormattedThing(this->_outputAsVector, formattedPath, [](const std::string &stringToStrip) -> std::string 
			{
				std::string returnString{ stringToStrip };
				std::vector<std::string> newLines{ "\r\n", "\n\r", "\n" };
				for (std::vector<std::string>::const_iterator iter = newLines.begin(); iter != newLines.end(); iter++) {
					if (returnString.find(*iter) != std::string::npos) {
						size_t foundPosition = returnString.find(*iter);
						returnString = returnString.substr(0, foundPosition);
					}
				}
				return returnString;
			});
            outputSize += sizeof(*(std::end(_outputAsVector)-1));
        }
        this->_returnValue = pcloseHandler(fp);
    } else {
        this->_returnValue = system(this->_command.c_str());
    }
	this->_hasError = (this->_returnValue != 0);
}
