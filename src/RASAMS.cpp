#include <RcppCommon.h>
#include <Rcpp.h>
using namespace Rcpp;

class parameter{
public:
  parameter(){

  }
  parameter(double v){
   this->value = v;
  }
  double value;
  bool estimated;
};

// recruitment interface 
struct recruitment_interface_base{
  static std::map<uint32_t,recruitment_interface_base* > models;
  static uint32_t id_g;
  uint32_t id;
};

uint32_t recruitment_interface_base::id_g;
std::map<uint32_t,recruitment_interface_base* > recruitment_interface_base::models;

struct beverton_holt:public recruitment_interface_base{
  parameter h;
  parameter r0;
  beverton_holt(){this->id=recruitment_interface_base::id_g++;
    recruitment_interface_base::models[this->id]=this;
    }
};

struct ricker:public recruitment_interface_base{
  parameter h;
  parameter r0;
  ricker(){this->id=recruitment_interface_base::id_g++;
    recruitment_interface_base::models[this->id]=this;
    }
};

// selectivity interface 
struct selectivity_interface_base{
  static std::map<uint32_t,selectivity_interface_base* > models;
  static uint32_t id_g;
  uint32_t id;
};

uint32_t selectivity_interface_base::id_g;
std::map<uint32_t,selectivity_interface_base* > selectivity_interface_base::models;

struct logistic_selectivity:public selectivity_interface_base{
  parameter a50;
  parameter slope;
  logistic_selectivity(){this->id=selectivity_interface_base::id_g++;
    selectivity_interface_base::models[this->id]=this;
  }
};

struct double_logistic_selectivity:public recruitment_interface_base{
  parameter alpha_asc;
  parameter beta_asc;
  parameter alpha_desc;
  parameter beta_desc;
  double_logistic_selectivity(){this->id=recruitment_interface_base::id_g++;
    recruitment_interface_base::models[this->id]=this;
  }
};


RCPP_EXPOSED_CLASS(parameter)

    RCPP_MODULE(rasams) {
      using namespace Rcpp;
    class_<parameter >("parameter")
      .constructor()
      .constructor<double>()
      .constructor<parameter>()
      .field("value", &parameter::value);
    class_<beverton_holt >("beverton_holt")
      .constructor()
      .field("r0",&beverton_holt::r0)
      .field("h",&beverton_holt::h);
    class_<ricker >("ricker")
      .constructor()
      .field("r0",&ricker::r0)
      .field("h",&ricker::h);
    class_<logistic_selectivity >("logistic_selectivity")
      .constructor()
      .field("a50",&logistic_selectivity::a50)
      .field("slope",&logistic_selectivity::slope);
    class_<double_logistic_selectivity >("double_logistic_selectivity")
      .constructor()
      .field("alpha_asc",&double_logistic_selectivity::alpha_asc)
      .field("beta_asc",&double_logistic_selectivity::beta_asc)
      .field("alpha_desc",&double_logistic_selectivity::alpha_desc)
      .field("beta_desc",&double_logistic_selectivity::beta_desc);
    }



