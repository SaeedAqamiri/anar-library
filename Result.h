#ifndef RESULT_H_
#define RESULT_H_

#include <set>
#include <vector>
#include <string>

namespace anar
{

typedef std::string Page;
typedef std::set<Page> TopK;

typedef std::string Domain;
typedef std::string Ip;
typedef std::string Page;
typedef Ip User;

struct Object
{
	size_t size;
	time_t start_time;
	time_t end_time;		// Get from last acc packet
};

typedef std::vector<Object> ObjectList;

struct Result
{
	enum State
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

}

#endif
