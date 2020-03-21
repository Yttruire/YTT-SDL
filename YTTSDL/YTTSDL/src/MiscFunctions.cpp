#include <iomanip>
#include <sstream>
#include <ctime>
#include <fstream>
#include <random>
#include "MiscFunctions.h"

namespace ypu
{

	//Constants
	//
	namespace CONSTANTS
	{
		const char* VERSION_NUMBER = "v0.1.2 INDEV";
	}

	//Utility functions
	//

	int getRandomInt(int min, int max)
	{
		static std::mt19937 mersenne(std::random_device{}());
		std::uniform_int_distribution<int> distri(min, max);
		return distri(mersenne);
	}

	std::string getTimeAndDate()
	{
		time_t time = std::time(nullptr);
		std::tm timeinfo;
		localtime_s(&timeinfo, &time);
		std::stringstream ss;
		ss << std::put_time(&timeinfo, "%Y %B %d %A %T");
		return ss.str();
	}

	void logError(const std::string& error_msg)
	{
		std::ofstream filewriter;
		filewriter.open("ErrorLog.txt", std::ios::app);
		filewriter << getTimeAndDate() << ": FATAL ERROR. " << error_msg << '\n';
		filewriter.close();
	}

}