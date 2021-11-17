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


// Survey interface 
struct survey_interface_base{
  static std::map<uint32_t,survey_interface_base* > models;
  static uint32_t id_g;
  uint32_t id;
};

uint32_t survey_interface_base::id_g;
std::map<uint32_t,survey_interface_base* > survey_interface_base::models;

struct survey:public survey_interface_base{
  
  parameter q;
  
  survey(){
    
    this->id=survey_interface_base::id_g++;
    survey_interface_base::models[this->id]=this;
    
  }
  
  // Add index data
  int observed_index_data; //id; What about sex and area?
  
  void AddIndexData(int id) { //Do we must use void? Void: the function does not return a value.
    
    this->observed_index_data=id; 
    
  }
  
  // Set index nll 
  int IndexNllId = -999; 
  
  void SetIndexNllId (int id) {
    
    this->IndexNllId = id; // Should we use id or model_id?
    
  }
  
  // Add age composition data
  int observed_agecomp_data; //id
  
  void AddAgeCompData(int id) {
    
    this->observed_agecomp_data=id;
    
  }
  
  // Set age composition nll 
  int AgeCompNllId = -999;
  
  void SetAgeCompNllId (int id) {
    
    this->AgeCompNllId = id;
    
  }
  
  
  // Add selectivity
  int selectivity; //id
  
  void AddSelectivity(int id) {
    
    this->selectivity=id;
    
  }
  
  
};

// Index data interface
struct IndexData_interface_base{
  static std::map<uint32_t,IndexData_interface_base* > models;
  static uint32_t id_g;
  uint32_t id;
};

uint32_t IndexData_interface_base::id_g;
std::map<uint32_t,IndexData_interface_base* > IndexData_interface_base::models;

struct IndexData:public IndexData_interface_base{
  
  IndexData(){
    
    this->id=IndexData_interface_base::id_g++;
    IndexData_interface_base::models[this->id]=this;
    
  }
  
  // Add index data
  Rcpp::NumericVector data; //When and how to check data.size()?
  Rcpp::NumericVector error;
  
};

// Fleet interface
struct fleet_interface_base{
  static std::map<uint32_t, fleet_interface_base* > models;
  static uint32_t id_g;
  uint32_t id;
};

uint32_t fleet_interface_base::id_g;
std::map<uint32_t,fleet_interface_base* > fleet_interface_base::models;

struct fleet:public fleet_interface_base{
  
  fleet(){
    this->id=fleet_interface_base::id_g++;
    fleet_interface_base::models[this->id]=this;
  }
  
  // Add index data
  int observed_index_data;
  
  void AddIndexData(int id) {
    this->observed_index_data=id; 
  }
  
  //Set index nll
  int IndexNllId = -999;
  
  void SetIndexNllId (int id) {
    this->IndexNllId=id;
  }
  
  
  //Add age compoisiton data
  int observed_agecomp_data;
  
  void AddAgeCompData(int id){
    this->observed_agecomp_data=id;
  }
  
  // Set age composition nll 
  int AgeCompNllId = -999;
  
  void SetAgeCompNllId (int id) {
    
    this->AgeCompNllId = id;
    
  }
  
  //Add selectivity
  int selectivity;
  void AddSelectivity(int id){
    this->selectivity=id;
  }
  
  
  
  
  
};




// RCPP module
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
    class_<survey >("survey")
      .constructor()
      .field("q",&survey::q)
      .method("AddIndexData", &survey::AddIndexData)
      .method("AddAgeCompData", &survey::AddAgeCompData)
      .method("AddSelectivity", &survey::AddSelectivity)
      .method("SetIndexNllId", &survey::SetIndexNllId)
      .method("SetAgeCompNllId", &survey::SetAgeCompNllId);
    class_<IndexData >("IndexData")
      .constructor()
      .field("data",&IndexData::data)
      .field("error",&IndexData::error);
    class_<fleet >("fleet")
      .constructor()
      .method("AddIndexData", &fleet::AddIndexData)
      .method("AddAgeCompData", &fleet::AddAgeCompData)
      .method("AddSelectivity", &fleet::AddSelectivity)
      .method("SetIndexNllId", &fleet::SetIndexNllId)
      .method("SetAgeCompNllId", &fleet::SetAgeCompNllId);
    
  }





