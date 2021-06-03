#include "Adapter.h"
#include "IDatabase.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <ctime>


namespace u = boost::uuids;

Result Adapter::GetResult(u::uuid u_id) {
    Result res = db->Select(u_id);
    std::vector<size_t> help;
    srand(time(0));
    for(size_t i = 0; i < res.result.size(); ++i){
        for(size_t j = 0; j < res.ClassesNumber; ++j){
            help.push_back( rand()%2 );
        }
    }
    res.result = help;
    return res;
}

Adapter::Adapter() {}

Adapter::Adapter(std::shared_ptr <IDatabase> t_db): db(t_db) {}

Adapter::~Adapter() {}