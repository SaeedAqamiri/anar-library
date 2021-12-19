typedef DataType std::array<std::vector<std::pair<int, double>>, 160>

void init()
{
	
}

DataType preprocess(const ObjectList& objects)
{
	ObjectList data = remove_unbunded(objects);
	data = remove_equals(data);
	data = roundup(data);
	
	return(binning_process(data));
	
}


sum_second_vector()
for (const auto& element : test_data[bin_index])

DataType train_data
vdouble distance(const DataType& test_data)
{
	double distance_value = 0.0;
	
	for (size_t bin_index = 0; bin_index < 160; bin_index++)
	{
		
		
		double delta_distance = 0.0;
		
		len_dict = ceil(sum_second_vector(train_data[bin_index]) - 0.125);
		
		delta_distance = abs(sum_second_vector(test_data[bin_index]) - len_dict);
		
		
		#penalty term
		#if test_data[bin_index].size()!=0 and train_data[bin_index].size()==0:
		
		if test_data[bin_index].size()!=0 and (not (bin_index in train_bins_vector)):
			delta_distance += test_data[bin_index].size();
		distance_value += delta_distance;
	

	}
	return distance_value/ len(train_bins_vector);
}

bool match(const ObjectList& objects)
{
	return distance(preprocess(objects)) < threshold;
}
