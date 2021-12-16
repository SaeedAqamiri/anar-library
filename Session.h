#ifndef SESSION_H_
#define SESSION_H_

#include <ctime>

#include "Result.h"

namespace anar
{

class Session
{
public:
    Result process(size_t size, const time_t& timestamp, bool direction, const time_t& start_time);		// API
    Result bye();		// API
private:
	void process_object(const Object& object);
	void reset(const time_t& timestamp);
	
	time_t last_object_time;
    time_t start_time;
	Object object;
};

}

#endif