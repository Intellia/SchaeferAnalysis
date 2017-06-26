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
 * calbrationmodels.h
 *
 *  Created on: Oct 10, 2013
 *  Author: Morten Kallberg
 */

#ifndef CALBRATIONMODELS_H_
#define CALBRATIONMODELS_H_
#include "blt_util/blt_exception.hh"
#include "starling_common/gvcf_block_site_record.hh"
#include "starling_common/gvcf_locus_info.hh"
#include "starling_common/cmodel.hh"
//#include "starling_common/gvcf_aggregator.hh"


//forward declaration
struct gvcf_options;
struct gvcf_deriv_options;

class calibration_models {
public:
    calibration_models();
    virtual ~calibration_models();

    void set_model(const std::string& name);  // set the calibration model to use
    void load_models(std::string model_file);                       // read in model parameters

    void clasify_site(const gvcf_options& opt, const gvcf_deriv_options& dopt, site_info& si);

    c_model& get_model(std::string& name);

    // mimics behavior of previous hard filters
    void default_clasify_site(const gvcf_options& opt, const gvcf_deriv_options& dopt, site_info& si);
private:
    typedef std::map<std::string,c_model> modelmap;
    typedef std::map<std::string, double> featuremap;
    std::string model_name;
    modelmap models;
};

#endif /* CALIBRATIONMODELS_H_ */
