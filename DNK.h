#pragma once
#include "RNK.h"

namespace dnk {
	class DNK : public rnk::RNK {
	public:
		DNK(const RNK& rnk1, const RNK& rnk2);
		DNK& operator=(const RNK& other);
	};
}
