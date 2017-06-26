// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Copyright (c) 2009-2016 Illumina, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

/*
 * cmodel.hh
 *
 *  Created on: Jan 15, 2014
 *      Author: mkallberg
 */

#ifndef CMODEL_HH_
#define CMODEL_HH_
#include <vector>
#include <map>
#include "starling_common/gvcf_locus_info.hh"

typedef std::map<std::string, double> featuremap;
typedef std::map<std::string, std::map<std::string, featuremap > > parmap;
class c_model {
public:
    c_model(
        const std::string& name,
        const std::string& type) :
        model_name(name),
        model_type(type)
    {}

    // add parameters to the model
    void add_parameters(const parmap& myPars);
    void score_instance(featuremap features, site_info& si);
private:
    void do_rule_model(featuremap& cutoffs, site_info& si);
    featuremap normalize(featuremap features, featuremap& adjust_factor, featuremap& norm_factor);
    double log_odds(featuremap features, featuremap& coeffs);
    void apply_qscore_filters(site_info& si, featuremap& qscore_cuts,featuremap& most_predictive);
    std::string model_name;
    std::string model_type;
    parmap pars;
};

#endif /* CMODEL_HH_ */
