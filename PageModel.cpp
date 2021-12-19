#include <math.h>

#include "PageModel.h"

bool PageModel::fit(const ObjectList& objects) const
{
	DataType test_data = preprocess(objects);
	for (const DataType& train_data : train_data_offset)
		if (distance(test_data, train_data) < threshold)
			return true;
	
	return false;
}

double PageModel::distance(const DataType& test_data, const DataType& train_data) const
{
	double distance_value = 0.0;

	for (size_t bin_index = 0; bin_index < BIN_NUMBER; ++bin_index)
	{
		Bin train_bin = train_data[bin_index];
		Bin test_bin = test_data[bin_index];
		double delta_distance = 0.0;

		len_dict = ceil(sum_objects(train_bin) - 0.125);
		delta_distance = abs(sum_objects(test_bin) - len_dict);

		//	penalty term
		//if test_data[bin_index].size()!=0 and (not (bin_index in train_bins_vector)):
		if (test_bin.size() != 0 and train_bin.size() == 0)
			delta_distance += test_bin.size();

		distance_value += delta_distance;
	}

	return distance_value / NORMALIZE_BIN;
}

double PageModel::sum_objects(const Bin& bin)
{
	double sum = 0;
	for (const auto& object : bin)
		sum += object.second;

	return sum;
}

DataType PageModel::preprocess(const ObjectList& objects) const
{
	ObjectList data = remove_unbunded(objects);
	data = remove_equals(data);
	data = roundup(data);
	
	return(binning_process(data));
}


