#include "VisitStore.h"
#include "Anar.h"

using namespace std;
using namespace ketab;

boost::optional<Visit> VisitCollection::get(const User& user, const Domain& domain, const time_t& start_time) const
{
	boost::optional<UDVisit> udvisit = collection.at(serialize(user, domain));
	VisitList visits = deserialize(udvisit);

	auto visit = visits.find(Visit(start_time));
	if (visit != visits.end())
		return boost::optional<Visit>(*visit);
	return boost::none;
}

void VisitCollection::set(const User& user, const Domain& domain, const Visit& visit)
{
	string key = serialize(user, domain);
	boost::optional<UDVisit> udvisit = collection.at(key);
	VisitList visits = deserialize(udvisit);

	visits.insert(visit);
	collection.insert(key, serialize(visits));
}

void VisitCollection::erase(const User& user, const Domain& domain, const time_t& start_time)
{
	string key = serialize(user, domain);
	boost::optional<UDVisit> udvisit = collection.at(key);
	VisitList visits = deserialize(udvisit);
	
	visits.erase(Visit(start_time));
	collection.insert(key, serialize(visits));
}

string VisitCollection::serialize(const User& user, const Domain& domain) const
{
	return user + "_" + domain;
}

string VisitCollection::serialize(const VisitList& visits) const
{
	string serial;
	for (const Visit& visit : visits)
		serial += serialize(visit) + visit_delimeter;

	serial.erase(serial.size() - 1, serial.size());
	return serial;
}

string VisitCollection::serialize(const Visit& visit) const
{
	string serial;
	serial += toString(visit.start_time) + field_delimeter;

	const Anar::Result& result = visit.result;
	serial += toString(result.state) + field_delimeter;
	serial += toString(result.top_k.size()) + field_delimeter;
	for (const Page& page : result.top_k)
		serial += page + field_delimeter;

	serial += toString(visit.live_session) + field_delimeter;

	const ObjectList& objects = visit.objects;
	serial += toString(objects.size()) + field_delimeter;
	for (const Object& object : objects)
	{
		serial += toString(object.size) + field_delimeter;
		serial += toString(object.start_time) + field_delimeter;
		serial += toString(object.end_time) + field_delimeter;
	}

	serial.erase(serial.size() - 1, serial.size());
	return serial;
}

VisitList VisitCollection::deserialize(const boos::optional<UDVisit>& udvisit) const
{
	VisitList visits;
	if (!udvisit)
		return visits;

	string udvisit_serial = (udvisit.get()).get<UDVisitField::VisitListSerial>().get();

	vector<string> visits_serial;
	boost::split(visits_serial, serial, boost::is_any_of(visit_delimeter));
	for (const string& visit_serial : visits_serial)
		visits.insert(deserialize(visit_serial));

	return visits;
}

Visit VisitCollection::deserialize(const string& serial) const
{
	vector<string> fields;
	boost::split(fields, serial, boost::is_any_of(field_delimeter));

	field_index = 0;
	Visit visit(stotime(fields[field_index++]));

	Anar::Result& result = visit.result;
	result.state = stoi(fields[field_index++]);
	size_t top_k_size = stoi(fields[field_index++]);
	for (size_t i = 0; i < top_k_size; ++i)
		result.top_k.insert(fields[field_index++]);

	visit.live_session = stoi(fields[field_index++]);

	size_t objects_size = stoi(fields[field_index++]);
	visit.objects.resize(objects_size);
	for (size_t i = 0; i < objects_size; ++i)
		visit.objects[i] = Object({stoi(fields[field_index++]),
				stotime(fields[field_index++]), stotime(fields[field_index++]));

	return visit;
}
