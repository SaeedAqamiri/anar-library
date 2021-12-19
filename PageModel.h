#ifndef PAGE_MODEL_H_
#define PAGE_MODEL_H_

#include <map>

#include "Result.h"

namespace anar
{

class PageModel
{
public:
	PageModel(std::string config_path);
	
	bool fit(const ObjectList& objects) const;
	
	size_t get_min_object() const;
	size_t get_max_object() const;
private:
	constexpr size_t BIN_NUMBER = 160;
	constexpr size_t NORMALIZE_BIN = 75;
	
	typedef std::vector<std::pair<size_t, double>> Bin;
	typedef std::array<Bin, BIN_NUMBER> DataType;
	
	double distance(const DataType& test_data, const DataType& train_data) const;
	DataType preprocess(const ObjectList& objects) const
	
	Page page;
	size_t min_object, max_objext;
	double threshold;
};

}

#endif
