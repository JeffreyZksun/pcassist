#include "stdafx.h"
#include "EventFilters.h"

using namespace Ts;

bool DefaultFilter::Applicable(IEvent*) const
{
    return true;
}
