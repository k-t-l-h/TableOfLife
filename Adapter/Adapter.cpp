#include "Adapter.h"
#include "IDatabase.h"
#include <boost/uuid/uuid.hpp>            // uuid class

namespace u = boost::uuids;

Result Adapter::GetResult(u::uuid u_id) {
    return db->Select(u_id);
}

Adapter::Adapter() {}

Adapter::Adapter(std::shared_ptr <IDatabase> t_db): db(t_db) {}

Adapter::~Adapter() {}