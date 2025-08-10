#ifndef _MOG_COST_FLOW_HPP_
#define _MOG_COST_FLOW_HPP_

#ifndef MOG_LIB
#define MOG_LIB
#endif

#include <mog/internal/cost-flow.hpp>

namespace mog {

template <class Cap, class Cost>
using CostFlowGraph = internal::CostFlowGraph<Cap, Cost>;

};

#endif
