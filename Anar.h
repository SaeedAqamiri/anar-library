#ifndef ANAR_H_
#define ANAR_H_

#include <string>
#include <set>
#include <vector>
#include <ctime>

#include "Result.h"
#include "Ipdr.h"
//#include "Session.h"
#include "Engine.h"
#include "VisitCollection.h"

namespace anar
{

class Session;

class Anar
{
public:
	Result get_result(const Ipdr& ipdr, const time_t& start_time) const;		// API
	Session* create_session(const Ipdr& ipdr, const time_t& start_time);		// API
	
	Result get_result(const User& user, const Domain& domain, const time_t& start_time) const;
	void open_session(const User& user, const Domain& domain, const time_t& start_time);
	void close_session(const User& user, const Domain domain, const time_t& start_time);
	void add_object(const Object& object, const User& user, const Domain domain, const time_t& start_time);

	static constexpr double VISIT_GAP = 5;
private:
	Engine engine;
	std::set<Domain> target_domains;
    VisitCollection visit_collection;
};

}

#endif
