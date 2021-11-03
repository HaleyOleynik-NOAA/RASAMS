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
  beverton_holt(){this->id=recruitment_interface_base::id_g++;}
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
    }



