#include "Anar.h"

using namespace std;

Session* Anar::create_session(const Ipdr& ipdr, const time_t& start_time)
{
	Domain domain = ipdr.extract_domain();
	if (!find(target_domains, domain))
		return nullptr;
	User user = ipdr.extract_user();

	Sesion* new_session = new Session(*this, user, domain, start_time);
	open_session(new_session);
	return new_session;
}

Result Anar::get_result(const Ipdr& ipdr, const time_t& start_time) const
{
	Domain domain = ipdr.extract_domain();
	User user = ipdr.extract_user();

	return get_result(user, domain, start_time);
}

Result Anar::get_result(const User& user, const Domain& domain, const time_t& start_time)
{
	boost::optional<Visit> visit = visit_collection.get(user, domain, start_time);
	if (!visit)
		return Result(Result::UNKNOWN);
	return visit.result;
}

void Anar::open_session(const User& user, const Domain& domain, const time_t& start_time)
{
	boost::optional<Visit> visit = visit_collection.get(user, domain, start_time);
	if (!visit)
		visit = Visit(start_time);
	
	++(visit.live_session);
	visits.set(user, domain, visit);
}

void Anar::close_session(const User& user, const Domain domain, const time_t& start_time)
{
	boost::optional<Visit> visit = visits.get(user, domain, start_time);
	if (!visit)
		return;
	
	--(visit.live_session);
	if (visit.live_session == 0)
		visits.erase(user, domain, start_time)
}

void Anar::add_object(const Object& object, const User& user, const Domain domain, const time_t& start_time);
{	
	boost::optional<Visit> visit = visits.get(user, domain, start_time);
	if (!visit)
		return;

	if (visit.result.state != Result::PENDING)
		return;
	
	visit.objects.push_back(object);	
	visit.result = engine.predict(objects, domain);
	visits.set(user, domain, visit);
}
