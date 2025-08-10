#ifndef _MO_COST_FLOW_HPP_
#define _MO_COST_FLOW_HPP_

#ifndef MO_LIB
#define MO_LIB
#endif

#include <mo/internal/cost-flow.hpp>

namespace mo {

template<class Cap, class Cost>
using CostFlowGraph = internal::CostFlowGraph<Cap, Cost>;

};

#endif
