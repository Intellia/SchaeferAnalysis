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
 * cmodel.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: Morten Kallberg
 */

#include "cmodel.hh"
#include <stdlib.h>     /* atof */
#include <iostream>
#include <sstream>
#include <cassert>
#include <string>
#include <fstream>
#include <iterator>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "blt_util/qscore.hh"

//#define DEBUG_MODEL

#ifdef DEBUG_MODEL
#include "blt_util/log.hh"
#endif


// add model paramaters
void c_model::add_parameters(const parmap& myPars) {
    this->pars = myPars;
}


void c_model::do_rule_model(featuremap& cutoffs, site_info& si) {
    if (si.smod.gqx<cutoffs["GQX"]) si.smod.set_filter(VCF_FILTERS::LowGQX);
    if (cutoffs["DP"]>0) {
        if ((si.n_used_calls+si.n_unused_calls) > cutoffs["DP"]) si.smod.set_filter(VCF_FILTERS::HighDepth);
    }

    // high DPFratio filter
    const unsigned total_calls(si.n_used_calls+si.n_unused_calls);
    if (total_calls>0) {
        const double filt(static_cast<double>(si.n_unused_calls)/static_cast<double>(total_calls));
        if (filt>cutoffs["DPFratio"]) si.smod.set_filter(VCF_FILTERS::HighBaseFilt);
    }

    if (si.dgt.is_snp) {
        if (si.dgt.sb>cutoffs["HighSNVSB"]) si.smod.set_filter(VCF_FILTERS::HighSNVSB);
    }
}

//Transform the features with the specified scaling parameters that were used to standardize
//the dataset to zero mean and unit variance: newVal = (oldVal-centerVal)/scaleVal.
featuremap c_model::normalize(featuremap features, featuremap& adjust_factor, featuremap& norm_factor) {
    for (featuremap::const_iterator it = norm_factor.begin(); it != norm_factor.end(); ++it) { // only normalize the features that are needed
        features[it->first] = (features[it->first]-adjust_factor[it->first])/norm_factor[it->first];
    }
    return features;
}

//Model: ln(p(TP|x)/p(FP|x))=w_1*x_1 ... w_n*x_n + w_1*w_2*x_1 ... w_{n-1}*w_{n}*x_1
// calculate sum from feature map
double c_model::log_odds(featuremap features, featuremap& coeffs) {
    using namespace boost::algorithm;
    std::vector<std::string> tokens;
    double sum = coeffs["Intercept"];
//    log_os << "sum" << "=" << sum << "\n";
    for (featuremap::const_iterator it = coeffs.begin(); it != coeffs.end(); ++it) {
        if (it->first !="Intercept" && it->second !=0) { // check that our coefficient is different from 0
            split(tokens, it->first, is_any_of(":"));
//            log_os << it->first << "=" << it->second << "\n";
            double term = it->second;
//            log_os << "term" << "=" << term << "\n";
            for (unsigned int i=0; i < tokens.size(); i++) {
                term = term*features[tokens[i]];
//                log_os << "term" << "=" << term << "\n";
            }
            // use term to determine the most predictive parameter
            sum += term;
//            log_os << "sum " << "=" << sum << "\n";
//            log_os << tokens.size() << "\n";
        }
    }
    //TO-DO sort map to find most predictive feature for setting filter for
    return sum;
}

//- From the identities logOddsRatio = ln(p(TP|x)/p(FP|x)) and p(TP|x) + p(FP|x) = 1,
//solve for p(TP): p(TP) = 1/(1+exp(-logOddsRatio))
//- Rescale the probabilities p(TP), p(FP) with the specified class priors,
//as they were counted on the training set before balancing to 50/50.
//- Convert the rescaled probability p(FP) into a
//Q-score: Q-score = round( -10*log10(p(FP)) )
// simplification possible  qscore(raw) = round(10log((1+e^raw)/prior))
static
int prior_adjustment(
    const double raw_score,
    const double minorityPrior) {

    double pFP          = 1.0/(1+std::exp(raw_score)); // this calculation can likely be simplified
    double pFPrescale   = pFP*minorityPrior;
    int qscore          = error_prob_to_qphred(pFPrescale);
//    double qscore_test  = round(10*log10((1+exp(raw_score))/priors["minorityPrior"]));
#ifdef DEBUG_MODEL
    log_os << "minorityPrior " << minorityPrior << "\n";
    log_os << "pFP=" << pFP << "\n";
    log_os << "rescale=" << pFPrescale << "\n";
//        log_os << "experimental=" << qscore_test << "\n";
#endif
    // cap the score at 40
    if (qscore>40)
        qscore = 40;
    // TODO check for inf and NaN artifacts

    return qscore;
}
void c_model::apply_qscore_filters(site_info& si, featuremap& qscore_cuts, featuremap& most_predictive) {
    most_predictive.size();
    if (si.Qscore < qscore_cuts["Q"]) {
        si.smod.set_filter(VCF_FILTERS::LowGQX); // more sophisticated filter setting here
    }
}

void c_model::score_instance(featuremap features, site_info& si) {
    if (this->model_type=="LOGISTIC") { //case we are using a logistic regression mode
        std::string snpCase = "homsnp";
        if (si.is_het())
            snpCase = "hetsnp";

        // normalize
        featuremap norm_features = this->normalize(features,this->pars[snpCase]["scalecenter"],this->pars[snpCase]["scaleshift"]);

        //calculates log-odds ratio
        double raw_score = this->log_odds(norm_features,this->pars[snpCase]["coefs"]);

        // adjust by prior and calculate q-score
        si.Qscore = prior_adjustment(raw_score,this->pars[snpCase]["priors"]["minorityPrior"]);

        // set filters according to q-scores
        featuremap most_pred; //place-holder
        this->apply_qscore_filters(si,this->pars[snpCase]["qcutoff"],most_pred);

#ifdef DEBUG_MODEL
        log_os << "Im doing a logistic model" << "\n";
#endif

    }
    else if (this->model_type=="RULE") { //case we are using a rule based model
        this->do_rule_model(this->pars["snp"]["cutoff"],si);
    }
}

