#ifndef PAGE_MODEL_H_
#define PAGE_MODEL_H_

namespace anar
{

class PageModel
{
public:
	double get_score(const ObjectList& objects) const;
	bool fit(const ObjectList& objects) const;
	size_t get_min_object() const;
	size_t get_max_object() const;
private:
	Page page;
	size_t min_object, max_objext;
};

}
