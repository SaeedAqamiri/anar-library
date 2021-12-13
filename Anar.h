namespace anar
{

typedef Domain string;
typedef Ip string;
typedef User Ip;
typedef TopK std::set<Page>;

struct Object
{
	size_t size;
	time_t start_time;
	time_t end_time;		// Get from last acc packet
};

typedef std::vector<Object> ObjectList;

struct Result
{
	Enum State
	{
		PENDING,
		UNKNOWN,
		DETECTED
	};

	Result(State state)
	: state(state)
	{}
	
	Result(State state, const TopK& top_k)
	: state(state)
	, top_k(top_k)
	{}

	State state;
	TopK top_k;
};

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
    time_t last_object_time;
	Object object;
};

class Anar
{
public:
	Result Anar::get_result(const Ipdr& ipdr, const time_t& start_time) const;		// API
	Session* create_session(const Ipdr& ipdr, const time_t& start_time);		// API
	
	Result get_result(const User& user, const Domain& domain, const time_t& start_time);
	void open_session(const User& user, const Domain& domain, const time_t& start_time);
	void close_session(const User& user, const Domain domain, const time_t& start_time);
	void add_object(const Object& object, const User& user, const Domain domain, const time_t& start_time);

	constexpr double VISIT_GAP = 5;
private:
	Engine engine;
	vector<Domain> target_domains;
    VisitCollection visit_collection;
};

};
