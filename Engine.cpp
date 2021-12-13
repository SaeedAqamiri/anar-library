#include "Engine.h"

using namespace std;
using namespace anar;


Anar::Result Engine::predict(const ObjectList& objects, const Domain& domain, Topk topk) const
{
	size_t n_object = objects.size();
	bool detected = true;
	for (const auto& page_models : models[domain])
	{
		Page page = page_models.first;
		if (current_result.find(page) != current_result.end())
			continue;
		
		bool page_detected = true;
		for(const auto& model : page_models)
		{
			if (n_object < model.get_min_object())
			{
				page_detected = false;
				continue;
			}
			if (n_object < model.get_max_object())
			{
				page_detected = false;
				if (model.fit(objects))
				{
					page_detected = true;
					topk.insert(page);
					break;
				}
			}
		}
		
		if (!page_detected)
			detected = false;
	}

	if (!detected)
		return (Anar::Result(Anar::Result::PENDING, topk);
	if (topk.size())
		return (Anar::Result(Anar::Result::DETECTED, topk);
	return (Anar::Result(Anar::Result::UNKNOWN);
}
