#include "Session.h"

Session::Session(const Anar& anar, const User& user, const Domain& domain, const time_t& start_time)
: anar(anar)
, user(user)
, domain(domain)
, start_time(start_time)
, object({0, start_time, start_time})
, last_object_time(start_time)
{
}

Anar::Result Session::process(size_t size, const time_t& timestamp, bool direction)
{
	if (direction)	// GET packet in HTTP
	{
		if (object.size != 0)
			process_object(object);
		object = {0, timestamp, timestamp};		// reset object
	}
	else
	{
		object.size += size;
		object.end_time = timestamp;
	}

	return anar.get_result(user, domain, start_time);
}

void Session::process_object(const Object& object)
{
	if (object.start_time - last_object_time >= Anar::VISIT_GAP)		// monqazi bashe
	{
		anar.close_session(user, domain, start_time);
		reset(object.start_time);
		anar.open_session(user, domain, start_time);		// If visit with timestamp not find, create new visit
	}

	anar.add_object(object, user, domain, start_time);
	last_object_time = object.start_time;
}

Anar::Result Session::bye()
{
	if (object.size != 0)
		anar.add_object(user, domain, start_time, object);
	Anar::Result result = anar.get_result(user, domain, start_time);
	anar.close_session(user, domain, start_time);
	return result;
}

void Session::reset(const time_t& timestamp)
{
	start_time = timestamp;
	object = {0, timestamp, timestamp};
	last_object_time = timestamp;
}
