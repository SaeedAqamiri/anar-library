#ifndef ENGINE_H_
#define ENGINE_H_

#include <map>
#include <vector>

#include "Result.h"

namespace anar
{


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
