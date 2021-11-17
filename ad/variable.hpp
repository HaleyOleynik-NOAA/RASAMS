/*
 * File:   fims_math.hpp
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
#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "variable_info.h"
#include "tape.hpp"
//#include "operators.hpp"
namespace asams {

    class variable {
    public:
        static tape tape_g;
        std::shared_ptr<variable_info > info = NULL; //std::make_shared<variable_info >();

        variable(double value = 0.0)
        : info(std::make_shared<variable_info >()) {
            info->value = value;
        }

        variable(const std::shared_ptr<variable_info >& other)
        : info(other) {
        }

        variable(const variable& other) :
        info(other.info) {
        }

        variable& operator=(const variable& other) {
            this->info = other.info;
            return (*this);
        }

        variable& operator=(double v) {
            if (variable::tape_g.recording) {
                std::shared_ptr<assignment_operator> ret = std::make_shared<assignment_operator>();
                ret->dependent = this->info;
                ret->v = v;
                variable::tape_g.stack.push_back(ret);
            }
            this->info->value = v;
            return (*this);
        }



        //        variable(const std::shared_ptr<ad_operator >& other) {
        //            this->info = other->dependent;
        //            variable::tape_g.stack.push_back(other);
        //        }
        //
        //        variable operator=(const std::shared_ptr<ad_operator >& other) {
        //            this->info = other->dependent;
        //            variable::tape_g.stack.push_back(other);
        //            return *this;
        //        }

        //    const double value() {
        //        return this->info->value;
        //    }

        double value() {
            return this->info->value;
        }

        void set_value(double v) {
            if (variable::tape_g.recording) {
                std::shared_ptr<assignment_operator> ret = std::make_shared<assignment_operator>();
                ret->dependent = this->info;
                ret->v = v;
                variable::tape_g.stack.push_back(ret);
            }
            this->info->value = v;
        }

        void bounds(double min, double max) {
            this->info->minb = min;
            this->info->maxb = max;
            this->info->is_bound = true;
        }

        void update(double v) {
            this->info->update_value(v);
        }



    };

    tape variable::tape_g;

    struct variable_vector {
        std::vector<variable> data;
        int size_m = 0;

        variable_vector() {

        }

        variable_vector(int size) :
        size_m(size) {
            this->data.resize(size);
        }

        void resize(int size) {
            this->data.resize(size);
        }

        variable& at(int i) {
            i--;
            return data[i];
        }

    };

    struct variable_matrix {
        std::vector<variable> data;
        int rows_m = 0;
        int cols_m = 0;

        variable_matrix() {

        }

        variable_matrix(int rows, int cols) :
        rows_m(rows), cols_m(cols) {
            this->data.resize(rows * cols);
        }

        void resize(int rows, int cols) {
            this->data.resize(rows * cols);
        }

        variable& at(int i, int j) {
            i--;
            j--;
            return data[i * cols_m + j];
        }

    };
}


#endif /* VARIABLE_HPP */

