#include <iostream>
#include <string>
#include <vector>

#include "SharedUnorderedCompositeMap.h"
#include "ExampleUtility.h"

#include <boost/algorithm/string.hpp>

using namespace ketab;

BASIC_ADAPTER_CREATOR()
FIELD_NAMES(UDVisit, VisitListSerial)
FIELD_TYPES(UDVisit, boost::optional<std::string>)
END_BASIC_ADAPTER_CREATOR();


struct Visit
{
	Visit(const time_t& start_time)
	: start_time(start_time)
	, result(Anar::Result::State::PENDING)
	, live_session(0)
	{}
	
	time_t start_time;
	Anar::Result result;
	size_t live_session;
	ObjectList objects;
};

class VisitCollection
{
public:
	boost::optional<Visit> get(const User& user, const Domain& domain, const time_t& start_time); const
	
	void set(const User& user, const Domain& domain, const Visit& visit);

	void erase(const User& user, const Domain& domain, const time_t& start_time);
private:
	typedef std::set<Visit> VisitList;

	constexpr string field_delimeter = ",";
	constexpr string visit_delimeter = "|";
	constexpr double START_DELAY = 0.5

	bool operator < (const Visit& visit1, const Visit& visit2)
	{ return visit1.start_time + START_DELAY < visit2.start_time;}

	std::string serialize(const User& user, const Domain& domain); const
	std::string serialize(const VisitList& visits); const
	std::string serialize(const Visit& visit); const
	
	VisitList deserialize(const boos::optional<UDVisit>& udvisit); const
	Visit deserialize(const std::string& serial); const
	
	SharedUnorderedCompositeMap<std::string, UDVisit> collection(DATABASE_NAME, TABLE_NAME, SERVER_ADDRESSES);
};
