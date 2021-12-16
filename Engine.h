#ifndef ENGINE_H_
#define ENGINE_H_

#include <map>

#include "Result.h"

namespace anar
{

class PageModel
{
public:
	double get_score(const ObjectList& objects); const
	bool fit(const ObjectList& objects); const
	size_t get_min_object();
	size_t get_max_object();
private:
	Page page;
	size_t min_object, max_objext;
};

class Engine
{
public:
	Result predict(const ObjectList& objects, const Domain& domain) const;
private:
	typedef std::map<Domain, std::map<Page, std::vector<PageModel>>> ModelZoo; 
	ModelZoo models;
};

}

#endif