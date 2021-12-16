#include <iostream>
#include <string>
#include <vector>
#include <boost/optional.hpp>

#include "Result.h"

/*
#include "SharedUnorderedCompositeMap.h"
#include "ExampleUtility.h"

#include <boost/algorithm/string.hpp>

using namespace ketab;

BASIC_ADAPTER_CREATOR()
FIELD_NAMES(UDVisit, VisitListSerial)
FIELD_TYPES(UDVisit, boost::optional<std::string>)
END_BASIC_ADAPTER_CREATOR();
*/
struct UDVisit; // TODO: uncomment Ketab

namespace anar
{

struct Visit
{
	Visit(const time_t& start_time)
	: start_time(start_time)
	, result(Result::State::PENDING)
	, live_session(0)
	{}
	
	time_t start_time;
	Result result;
	size_t live_session;
	ObjectList objects;

	static constexpr double START_DELAY = 0.5;
};

bool operator < (const Visit& visit1, const Visit& visit2)
{ return visit1.start_time + Visit::START_DELAY < visit2.start_time;}

class VisitCollection
{
public:
	boost::optional<Visit> get(const User& user, const Domain& domain, const time_t& start_time); const
	
	void set(const User& user, const Domain& domain, const Visit& visit);

	void erase(const User& user, const Domain& domain, const time_t& start_time);
private:
	typedef std::set<Visit> VisitList;

	static constexpr char field_delimeter = ',';
	static constexpr char visit_delimeter = '|';


	static std::string serialize(const User& user, const Domain& domain);
	static std::string serialize(const VisitList& visits);
	static std::string serialize(const Visit& visit);
	
	static VisitList deserialize(const boost::optional<UDVisit>& udvisit);
	static Visit deserialize(const std::string& serial);
	
	/* SharedUnorderedCompositeMap<std::string, UDVisit> collection(DATABASE_NAME, TABLE_NAME, SERVER_ADDRESSES); */
};

}