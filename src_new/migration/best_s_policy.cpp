/*****************************************************************************
 *   Copyright (C) 2004-2009 The PaGMO development team,                     *
 *   Advanced Concepts Team (ACT), European Space Agency (ESA)               *
 *   http://apps.sourceforge.net/mediawiki/pagmo                             *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Developers  *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Credits     *
 *   act@esa.int                                                             *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#include <algorithm>
#include <vector>

#include "../population.h"
#include "base_s_policy.h"
#include "best_s_policy.h"

namespace pagmo { namespace migration {

/// Constructor from migration rate and type.
/**
 * @param[in] rate migration rate.
 * @param[in] rate_type migration rate type.
 *
 * @see base_s_policy::base_s_policy.
 */
best_s_policy::best_s_policy(const double &rate,  migration_rate_type rate_type):base_s_policy(rate,rate_type) {}

/// Clone method.
base_s_policy_ptr best_s_policy::clone() const
{
	return base_s_policy_ptr(new best_s_policy(*this));
}

/// Select emigrating individuals.
std::vector<population::individual_type> best_s_policy::select(const population &pop) const
{
	const population::size_type migration_rate = get_n_individuals(pop);
	// Create a temporary array of individuals.
	std::vector<population::individual_type> result(pop.begin(),pop.end());
	// Sort the individuals (best go first).
	std::sort(result.begin(),result.end(),population::cur_fc_comp(pop.problem()));
	// Leave only desired number of elements in the result.
	result.erase(result.begin() + migration_rate,result.end());
	return result;
}

}}