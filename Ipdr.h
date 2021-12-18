#ifndef IPDR_H_
#define IPDR_H_

#include "Result.h"

namespace anar
{

struct Ipdr
{
	Domain extract_domain() const
    {
        if "cdn.khar" in sni 
			return "khar";
		return sni;
    }
    
    User extract_user() const
    {
        return "Saeed";
    }
};

}

#endif
