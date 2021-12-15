#include <RcppCommon.h>
#include <Rcpp.h>
#include "../Catch_at_Age.hpp"

//#include "../ad/asamasad.hpp"

using namespace Rcpp;

class parameter
{
public:
    parameter()
    {
    }

    parameter(double v)
    {
        this->value = v;
    }
    double value;
    bool estimated;
};

// recruitment interface

struct recruitment_interface_base
{
    static std::map<uint32_t, recruitment_interface_base *> models;
    static uint32_t id_g;
    uint32_t id;

    template <typename Type>
    virtual asams::recruitment_base<T> *get_asam_object() = 0;
};

uint32_t recruitment_interface_base::id_g;
std::map<uint32_t, recruitment_interface_base *> recruitment_interface_base::models;

struct beverton_holt : public recruitment_interface_base
{
    parameter h;
    parameter r0;

    beverton_holt()
    {
        this->id = recruitment_interface_base::id_g++;
        recruitment_interface_base::models[this->id] = this;
    }

    template <typename Type>
    virtual asams::recruitment_base<T> *get_asam_object()
    {
        asams::beverton_holt<Type> *r = new asams::beverton_holt<Type>();
        r->h = this->h.value;
        r->r0 = this->r0.value;
        return r;
    }
};

struct ricker : public recruitment_interface_base
{
    parameter h;
    parameter r0;

    ricker()
    {
        this->id = recruitment_interface_base::id_g++;
        recruitment_interface_base::models[this->id] = this;
    }

    template <typename Type>
    virtual asams::recruitment_base<T> *get_asam_object()
    {
        asams::ricker<Type> *r = new asams::ricker<Type>();
        r->h = this->h.value;
        r->r0 = this->r0.value;
        return r;
    }
};

// recruitment interface

struct growth_interface_base
{
    static std::map<uint32_t, growth_interface_base *> models;
    static uint32_t id_g;
    uint32_t id;
};

uint32_t growth_interface_base::id_g;
std::map<uint32_t, growth_interface_base *> growth_interface_base::models;

struct empirical_growth : public growth_interface_base
{

    Rcpp::List catch_growth;
    Rcpp::List survey_growth;

    empirical_growth()
    {
        this->id = growth_interface_base::id_g++;
        growth_interface_base::models[this->id] = this;
    }
};

struct vonBertalanffy_growth : public growth_interface_base
{

    parameter Linf;
    parameter K;
    parameter t0;

    vonBertalanffy_growth()
    {
        this->id = growth_interface_base::id_g++;
        growth_interface_base::models[this->id] = this;
    }
};

// selectivity interface

struct selectivity_interface_base
{
    static std::map<uint32_t, selectivity_interface_base *> models;
    static uint32_t id_g;
    uint32_t id;
};

uint32_t selectivity_interface_base::id_g;
std::map<uint32_t, selectivity_interface_base *> selectivity_interface_base::models;

struct logistic_selectivity : public selectivity_interface_base
{
    parameter a50;
    parameter slope;

    logistic_selectivity()
    {
        this->id = selectivity_interface_base::id_g++;
        selectivity_interface_base::models[this->id] = this;
    }
};

struct double_logistic_selectivity : public recruitment_interface_base
{
    parameter alpha_asc;
    parameter beta_asc;
    parameter alpha_desc;
    parameter beta_desc;

    double_logistic_selectivity()
    {
        this->id = recruitment_interface_base::id_g++;
        recruitment_interface_base::models[this->id] = this;
    }
};

// Survey interface

struct survey_interface_base
{
    static std::map<uint32_t, survey_interface_base *> models;
    static uint32_t id_g;
    uint32_t id;
};

uint32_t survey_interface_base::id_g;
std::map<uint32_t, survey_interface_base *> survey_interface_base::models;

struct survey : public survey_interface_base
{
    parameter q;

    survey()
    {

        this->id = survey_interface_base::id_g++;
        survey_interface_base::models[this->id] = this;
    }

    // Add index data
    int observed_index_data; //id; What about sex and area?

    void AddIndexData(int id)
    { //Do we must use void? Void: the function does not return a value.

        this->observed_index_data = id;
    }

    // Set index nll
    int IndexNllId = -999;

    void SetIndexNllId(int id)
    {

        this->IndexNllId = id; // Should we use id or model_id?
    }

    // Add age composition data
    int observed_agecomp_data; //id

    void AddAgeCompData(int id)
    {

        this->observed_agecomp_data = id;
    }

    // Set age composition nll
    int AgeCompNllId = -999;

    void SetAgeCompNllId(int id)
    {

        this->AgeCompNllId = id;
    }

    // Add selectivity
    int selectivity; //id

    void AddSelectivity(int id)
    {

        this->selectivity = id;
    }
};

// Index data interface

struct IndexData_interface_base
{
    static std::map<uint32_t, IndexData_interface_base *> models;
    static uint32_t id_g;
    uint32_t id;
};

uint32_t IndexData_interface_base::id_g;
std::map<uint32_t, IndexData_interface_base *> IndexData_interface_base::models;

struct IndexData : public IndexData_interface_base
{

    IndexData()
    {

        this->id = IndexData_interface_base::id_g++;
        IndexData_interface_base::models[this->id] = this;
    }

    // Add index data
    Rcpp::NumericVector data; //When and how to check data.size()?
    Rcpp::NumericVector error;
};

struct population
{
    static std::map<uint32_t, population *> models;
    static uint32_t id_g;
    uint32_t id;
    uint32_t recruitment_id;
    uint32_t growth_id;
    uint32_t mortality_id;

    Rcpp::NumericVector init_N_devs;


    population(){
    this->id = population::id_g++;
        population::models[this->id] = this;
    }
};
uint32_t population::id_g;
std::map<uint32_t, population *> population::models;

struct Model
{
    uint32_t population_id;
    uint32_t fleet_id;
    uint32_t survey_id;

    void run()
    {

   
        typename std::map<uint32_t, population *>::iterator pit;
        pit = population::model[population_id];
        asams::Population<double> * pop = new asams::Population<double>();

        if(pit != population::model.end()){
                 typename std::map<uint32_t, recruitment_interface_base *>::iterator it;

        }
       
   
        asams::catch_at_age<double> caa;
    }
};

// RCPP module

RCPP_EXPOSED_CLASS(parameter)

RCPP_MODULE(rasams)
{
    using namespace Rcpp;
    class_<parameter>("parameter")
        .constructor()
        .constructor<double>()
        .constructor<parameter>()
        .field("value", &parameter::value);
    class_<beverton_holt>("beverton_holt")
        .constructor()
        .field("r0", &beverton_holt::r0)
        .field("h", &beverton_holt::h);
    class_<ricker>("ricker")
        .constructor()
        .field("r0", &ricker::r0)
        .field("h", &ricker::h);
    class_<empirical_growth>.constructor().field("catch_growth", &empirical_growth::catch_growth).field("survey_growth", &empirical_growth::survey_growth);
    class_<vonBertalanffy_growth>.constructor().field("Linf", &vonBertalanffy_growth::Linf).field("K", &vonBertalanffy_growth::K).field("t0", &vonBertalanffy_growth::t0);
    class_<logistic_selectivity>("logistic_selectivity")
        .constructor()
        .field("a50", &logistic_selectivity::a50)
        .field("slope", &logistic_selectivity::slope);
    class_<double_logistic_selectivity>("double_logistic_selectivity")
        .constructor()
        .field("alpha_asc", &double_logistic_selectivity::alpha_asc)
        .field("beta_asc", &double_logistic_selectivity::beta_asc)
        .field("alpha_desc", &double_logistic_selectivity::alpha_desc)
        .field("beta_desc", &double_logistic_selectivity::beta_desc);
    class_<survey>("survey")
        .constructor()
        .field("q", &survey::q)
        .method("AddIndexData", &survey::AddIndexData)
        .method("AddAgeCompData", &survey::AddAgeCompData)
        .method("AddSelectivity", &survey::AddSelectivity)
        .method("SetIndexNllId", &survey::SetIndexNllId)
        .method("SetAgeCompNllId", &survey::SetAgeCompNllId);
    class_<IndexData>("IndexData")
        .constructor()
        .field("data", &IndexData::data)
        .field("error", &IndexData::error);

    class_<population>("population")
        .constructor()
        .field("recruitment_id", &population::recruitment_id)
        .field("growth_id", &population::growth_id)
        .field("mortality_id", &population::mortality_id)
        .field("init_N_devs", &population::init_N_devs);
    class_<lognormal>("lognormal")
        .constructor()
        .field("id", &likelihood::id)
        .field("cv_m", &likelihood::cv_m);
    class_<multinomial>("multinomial")
        .constructor()
        .field("id", &multinomial::id);
}
