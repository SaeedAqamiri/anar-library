#include <iostream>
#include <string>
#include <vector>

#include "SharedUnorderedCompositeMap.h"
#include "ExampleUtility.h"

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace ketab;

BASIC_ADAPTER_CREATOR()
FIELD_NAMES(Visit, Session_IDs, TimeStamp)
FIELD_TYPES(Visit, boost::optional<std::string>, boost::optional<time_t>)
END_BASIC_ADAPTER_CREATOR();

struct Session_ID
{
Session_ID(size_t id, std::string source_ip, std::string destination_ip)
: id(id)
, source_ip(source_ip)
, destination_ip(destination_ip)
{}

size_t id;
std::string source_ip;
std::string destination_ip;
};

std::string serialize(vector<Session_ID> sessions)
{
	string serial;
	for (const auto& session : sessions)
		serial += std::to_string(session.id) + "_" + session.source_ip + "_" + session.destination_ip + ",";

	serial.erase(serial.size() - 1, serial.size());

	return serial;
}

vector<Session_ID> deserialize(std::string serial)
{
	vector<string> sessions_string;
	boost::split(sessions_string, serial, boost::is_any_of(","));

	vector<Session_ID> sessions;
	for (const auto& str : sessions_string)
	{
		vector<string> session_fields;
		boost::split(session_fields, str, boost::is_any_of("_"));

		Session_ID session(stoi(session_fields[0]), session_fields[1], session_fields[2]);
		sessions.push_back(session);
	}

	return sessions;
}


int main()
{
	vector<Session_ID> sessions{Session_ID(10, "192.168.0.0", "192.168.1.0"),
                                Session_ID(11, "192.168.0.1", "192.168.1.1"),
                                Session_ID(12, "192.168.0.2", "192.168.1.2"),
                                Session_ID(13, "192.168.0.3", "192.168.1.3")};

	Visit visit1;
	visit1.set<VisitField::Session_IDs>(serialize(sessions));
	visit1.set<VisitField::TimeStamp>(std::time(0));

	SharedUnorderedCompositeMap<std::string, Visit> collection(DATABASE_NAME, TABLE_NAME, SERVER_ADDRESSES);

	collection.insert("Visit1", visit1);
	boost::optional<Visit> visit_retrieved = collection.at("Visit1");

	time_t retrieved_timestamp = (visit_retrieved.get()).get<VisitField::TimeStamp>().get();
	vector<Session_ID> retrieved_session_ids = deserialize((visit_retrieved.get()).get<VisitField::Session_IDs>().get());

	return 1;
}
