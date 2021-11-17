/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   functions.hpp
 * Author: mattadmin
 *
 * Created on September 22, 2021, 11:13 AM
 */

#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "operators.hpp"
#include "variable.hpp"
#include "tape.hpp"

namespace asams {

    variable ad_acos(variable x) {
        variable dependent;
        dependent.info->value = std::acos(x.info->value);


        if (variable::tape_g.recording) {
            std::shared_ptr<acos_operator > ret = std::make_shared<acos_operator >();
            ret->x = x.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;

    }

    const variable ad_asin(const variable& x) {

        variable dependent;
        dependent.info->value = std::asin(x.info->value);

        if (variable::tape_g.recording) {
            std::shared_ptr<asin_operator > ret = std::make_shared<asin_operator >();
            ret->x = x.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;

    }

    const variable ad_atan(const variable& x) {

        variable dependent;
        dependent.info->value = std::atan(x.info->value);

        if (variable::tape_g.recording) {
            std::shared_ptr<atan_operator > ret = std::make_shared<atan_operator >();
            ret->x = x.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable ad_cos(const variable& x) {

        variable dependent;
        dependent.info->value = std::cos(x.info->value);

        if (variable::tape_g.recording) {
            std::shared_ptr<cos_operator > ret = std::make_shared<cos_operator >();
            ret->x = x.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable ad_cosh(const variable& x) {

        variable dependent;
        dependent.info->value = std::cosh(x.info->value);
        if (variable::tape_g.recording) {
            std::shared_ptr<cosh_operator > ret = std::make_shared<cosh_operator >();
            ret->x = x.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable ad_sin(const variable& x) {

        variable dependent;
        dependent.info->value = std::sin(x.info->value);

        if (variable::tape_g.recording) {
            std::shared_ptr<sin_operator > ret = std::make_shared<sin_operator >();
            ret->x = x.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable ad_sinh(const variable& x) {

        variable dependent;
        dependent.info->value = std::sinh(x.info->value);

        if (variable::tape_g.recording) {
            std::shared_ptr<sinh_operator > ret = std::make_shared<sinh_operator >();
            ret->x = x.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }
        return dependent;
    }

    const variable ad_tan(const variable& x) {

        variable dependent;
        dependent.info->value = std::tan(x.info->value);

        if (variable::tape_g.recording) {
            std::shared_ptr<tan_operator > ret = std::make_shared<tan_operator >();
            ret->x = x.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable ad_tanh(const variable& x) {

        variable dependent;
        dependent.info->value = std::tanh(x.info->value);

        if (variable::tape_g.recording) {
            std::shared_ptr<tanh_operator > ret = std::make_shared<tanh_operator >();
            ret->x = x.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable ad_exp(const variable& x) {

        variable dependent;
        dependent.info->value = std::exp(x.info->value);

        if (variable::tape_g.recording) {
            std::shared_ptr<exp_operator > ret = std::make_shared<exp_operator >();
            ret->x = x.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable ad_log(const variable& x) {

        variable dependent;
        dependent.info->value = std::log(x.info->value);

        if (variable::tape_g.recording) {
            std::shared_ptr<log_operator > ret = std::make_shared<log_operator >();
            ret->x = x.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable ad_log10(const variable& x) {

        variable dependent;
        dependent.info->value = std::log10(x.info->value);

        if (variable::tape_g.recording) {
            std::shared_ptr<log10_operator > ret = std::make_shared<log10_operator >();
            ret->x = x.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable operator+(const variable& left,
            const variable& right) {

        variable dependent;
        dependent.info->value = left.info->value + right.info->value;

        if (variable::tape_g.recording) {
            std::shared_ptr<addvv_operator > ret = std::make_shared<addvv_operator >();
            ret->left = left.info;
            ret->right = right.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable addvv(const variable& left,
            const variable& right) {
        return left + right;
    }

    const variable operator+(const variable& left,
            const double& right) {

        variable dependent;
        dependent.info->value = left.info->value + right;

        if (variable::tape_g.recording) {
            std::shared_ptr<addvd_operator > ret = std::make_shared<addvd_operator >();
            ret->left = left.info;
            ret->right = right;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable addvd(const variable& left,
            const double& right) {
        return left + right;
    }

    const variable operator+(const double& left,
            const variable& right) {

        variable dependent;
        dependent.info->value = left + right.info->value;

        if (variable::tape_g.recording) {
            std::shared_ptr<adddv_operator > ret = std::make_shared<adddv_operator >();
            ret->left = left;
            ret->right = right.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable adddv(const double& left,
            const variable& right) {
        return left + right;
    }

    const variable operator-(const variable& left,
            const variable& right) {

        variable dependent;
        dependent.info->value = left.info->value - right.info->value;

        if (variable::tape_g.recording) {
            std::shared_ptr<subvv_operator > ret = std::make_shared<subvv_operator >();
            ret->left = left.info;
            ret->right = right.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable subvv(const variable& left,
            const variable& right) {
        return left - right;
    }

    const variable operator-(const variable& left,
            const double& right) {

        variable dependent;
        dependent.info->value = left.info->value - right;

        if (variable::tape_g.recording) {
            std::shared_ptr<subvd_operator > ret = std::make_shared<subvd_operator >();
            ret->left = left.info;
            ret->right = right;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable subvd(const variable& left,
            const double& right) {

        variable dependent;
        dependent.info->value = left.info->value - right;

        if (variable::tape_g.recording) {
            std::shared_ptr<subvd_operator > ret = std::make_shared<subvd_operator >();
            ret->left = left.info;
            ret->right = right;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable operator-(const double& left,
            const variable& right) {
        variable dependent;
        dependent.info->value = left - right.info->value;

        if (variable::tape_g.recording) {
            std::shared_ptr<subdv_operator > ret = std::make_shared<subdv_operator >();
            ret->left = left;
            ret->right = right.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable subdv(const double& left,
            const variable& right) {

        return left - right;
    }

    const variable operator*(const variable& left,
            const variable& right) {

        variable dependent;
        dependent.info->value = left.info->value * right.info->value;

        if (variable::tape_g.recording) {
            std::shared_ptr<multvv_operator > ret = std::make_shared<multvv_operator >();
            ret->left = left.info;
            ret->right = right.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable multvv(const variable& left,
            const variable& right) {
        return left * right;
    }

    const variable operator*(const variable& left,
            const double& right) {

        variable dependent;
        dependent.info->value = left.info->value * right;

        if (variable::tape_g.recording) {
            std::shared_ptr<multvd_operator > ret = std::make_shared<multvd_operator >();
            ret->left = left.info;
            ret->right = right;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable multvd(const variable& left,
            const double& right) {
        return left * right;
    }

    const variable operator*(const double& left,
            const variable& right) {

        variable dependent;
        dependent.info->value = left * right.info->value;

        if (variable::tape_g.recording) {
            std::shared_ptr<multdv_operator > ret = std::make_shared<multdv_operator >();
            ret->left = left;
            ret->right = right.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable multdv(const double& left,
            const variable& right) {
        return left * right;
    }

    const variable operator/(const variable& left,
            const variable& right) {

        variable dependent;
        dependent.info->value = left.info->value / right.info->value;

        if (variable::tape_g.recording) {
            std::shared_ptr<divvv_operator > ret = std::make_shared<divvv_operator >();
            ret->left = left.info;
            ret->right = right.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable divvv(const variable& left,
            const variable& right) {
        return left / right;
    }

    const variable operator/(const variable& left,
            const double& right) {

        variable dependent;
        dependent.info->value = left.info->value / right;

        if (variable::tape_g.recording) {
            std::shared_ptr<divvd_operator > ret = std::make_shared<divvd_operator >();
            ret->left = left.info;
            ret->right = right;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable divvd(const variable& left,
            const double& right) {
        return left / right;
    }

    const variable operator/(const double& left,
            const variable& right) {
        variable dependent;
        dependent.info->value = left / right.info->value;

        if (variable::tape_g.recording) {
            std::shared_ptr<divdv_operator > ret = std::make_shared<divdv_operator >();
            ret->left = left;
            ret->right = right.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable divdv(const double& left,
            const variable& right) {
        return left / right;
    }

    const variable powvv(const variable& left,
            const variable& right) {

        variable dependent;
        dependent.info->value = std::pow(left.info->value, right.info->value);

        if (variable::tape_g.recording) {
            std::shared_ptr<powvv_operator > ret = std::make_shared<powvv_operator >();
            ret->left = left.info;
            ret->right = right.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable powvd(const variable& left,
            const double& right) {
        variable dependent;
        dependent.info->value = std::pow(left.info->value, right);

        if (variable::tape_g.recording) {
            std::shared_ptr<powvd_operator > ret = std::make_shared<powvd_operator >();
            ret->left = left.info;
            ret->right = right;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }

    const variable powdv(const double& left,
            const variable& right) {
        variable dependent;
        dependent.info->value = std::pow(left, right.info->value);

        if (variable::tape_g.recording) {
            std::shared_ptr<powdv_operator > ret = std::make_shared<powdv_operator >();
            ret->left = left;
            ret->right = right.info;
            ret->dependent = dependent.info;
            variable::tape_g.stack.push_back(ret);
        }

        return dependent;
    }


}


#endif /* FUNCTIONS_HPP */

