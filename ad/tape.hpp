
/*
 * File:   tape.hpp
 *
 * Author: Matthew Supernaw
 * National Oceanic and Atmospheric Administration
 * National Marine Fisheries Service
 * Sustainable Fisheries Division
 * Email: matthew.supernaw@noaa.gov
 *
 * 
 *
 * This File is part of the NOAA, National Marine Fisheries Service
 * Automatic Differntiation in R project.
 *
 * This software is a "United States Government Work" under the terms of the
 * United States Copyright Act.  It was written as part of the author's official
 * duties as a United States Government employee and thus cannot be copyrighted.
 * This software is freely available to the public for use. The National Oceanic
 * And Atmospheric Administration and the U.S. Government have not placed any
 * restriction on its use or reproduction.  Although all reasonable efforts have
 * been taken to ensure the accuracy and reliability of the software and data,
 * the National Oceanic And Atmospheric Administration and the U.S. Government
 * do not and cannot warrant the performance or results that may be obtained by
 * using this  software or data. The National Oceanic And Atmospheric
 * Administration and the U.S. Government disclaim all warranties, express or
 * implied, including warranties of performance, merchantability or fitness
 * for any particular purpose.
 *
 * Please cite the author(s) in any work or product based on this material.
 *
 */
#ifndef TAPE_HPP
#define TAPE_HPP

#include<vector>
//#include <map>

//#include <set>
#include "operators.hpp"

namespace asams {

    struct tape {
        std::vector<std::shared_ptr<variable_info> > independent_variables;
        std::vector<std::shared_ptr<ad_operator > > stack;
        std::vector<double> gradient;
//        std::map<size_t, std::map<size_t, double> > hessian;
//        std::map<size_t, std::set<variable_info> > live_sets;
        bool recording = false;

        double forward() {
            for (int i = 0; i < this->stack.size(); i++) {
                this->stack[i]->update();
            }
            return this->stack[stack.size() - 1]->dependent->value;
        }

        void reverse() {
            gradient.resize(variable_info::id_g);
            std::fill(this->gradient.begin(), this->gradient.end(), 0.0);
            this->gradient[this->stack[stack.size() - 1]->dependent->id] = 1.0;
            for (int i = stack.size() - 1; i >= 0; i--) {
                this->stack[i]->first_order(this->gradient);
            }

            //        void reverse_second_order() {
            //            gradient.resize(variable_info::id_g);
            //            hessian.clear();
            //            live_sets.clear();
            //            
            //            std::fill(this->gradient.begin(), this->gradient.end(), 0.0);
            //            this->gradient[this->stack[stack.size() - 1]->dependent->id] = 1.0;
            //            for (int i = stack.size() - 1; i >= 0; i--) {
            //                this->stack[i]->second_order(this->gradient, this->hessian,this->live_sets);
            //            }
            //        }

        }
    };

}

#endif /* TAPE_HPP */

