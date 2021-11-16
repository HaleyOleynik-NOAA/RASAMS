/*
 * File:   variable_info.hpp
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
#ifndef VARIABLE_INFO_H
#define VARIABLE_INFO_H


namespace asams{

    struct variable_transformation {
        /**
         * Convert the external value to its internal representation.
         *
         * @param val
         * @param min
         * @param max
         * @return
         */
        virtual double external_2_internal(double val, double min_, double max_) const = 0;
        /**
         * Convert a variables internal value to its external representation.
         * @param val
         * @param min
         * @param max
         * @return
         */
        virtual double internal_2_external(double val, double min_, double max_) const = 0;
        /**
         * The derivative of internal 2 external.
         * @param val
         * @param min
         * @param max
         * @return
         */
        virtual double derivative_internal_2_external(double val, double min_, double max_) const = 0;
    };

    struct logit_transformation : public variable_transformation {

        virtual double external_2_internal(double val, double min_, double max_)const {
            if (val == min_) {
                val += static_cast<double> (1e-8);
            } else if (val == max_) {
                val -= static_cast<double> (1e-8);
            }

            double p = ((val) - min_) / (max_ - min_);
            return std::log(p / (1.0 - p));
        }

        virtual double internal_2_external(double val, double min_, double max_) const {
            double p = std::exp(val) / (1.0 + std::exp(val));
            return p * (max_ - min_) + min_;
        }

        virtual double derivative_internal_2_external(double val, double min_, double max_)const {
            return (std::exp(val) * std::log(M_E)*(max_ - min_)) / (std::exp(val) + 1.0)-
                    (std::exp(static_cast<double> (2.0 * val)) * std::log(M_E)*(max_ - min_)) / std::pow((std::exp(val) + 1), 2.0);
        }
    };

    struct sine_transformation : public variable_transformation {

        virtual double external_2_internal(double val, double min_, double max_)const {
            return std::asin((2.0 * (val - min_) / (max_ - min_)) - 1.0);
        }

        virtual double internal_2_external(double val, double min_, double max_) const {
            return min_ + (std::sin(val) + 1.0)*((max_ - min_) / 2.0);
        }

        virtual double derivative_internal_2_external(double val, double min_, double max_)const {
            return 0.5 * ((max_ - min_) * std::cos(val));
        }
    };

    struct variable_info {
        static size_t id_g;
        static variable_transformation* transformation;
        size_t id;
        double value;
        double minb;
        double maxb;
        bool is_bound = false;
        bool is_nonlinear = false;

        variable_info() :
        id(variable_info::id_g++), value(0) {

        }

        double internal_value() {
            if (this->is_bound) {
                return this->transformation->external_2_internal(this->value, this->minb, this->maxb);
            } else {
                return this->value;
            }
        }

        double get_scaled_gradient(double x) {
            if (this->is_bound) {
                return this->transformation->derivative_internal_2_external(x, this->minb, this->maxb);
            } else {
                return 1;
            }
        }

        void update_value(double v) {
            if (this->is_bound) {
                this->value = (variable_info::transformation->internal_2_external(v, this->minb, this->maxb));

            } else {
                this->value = v;
            }
        }
    };
    variable_transformation* variable_info::transformation = new logit_transformation();
    size_t variable_info::id_g = 0;
}


#endif /* VARIABLE_INFO_H */

