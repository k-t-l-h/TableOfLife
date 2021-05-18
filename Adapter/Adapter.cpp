#include "Adapter.h"
#include "IDatabase.h"
#include <boost/uuid/uuid.hpp>            // uuid class

namespace u = boost::uuids;

const std::vector<size_t> Adapter::GetResult(u::uuid u_id) const {
    return db->Select(u_id);
}

Adapter::Adapter() {}

Adapter::Adapter(std::shared_ptr <IDatabase> t_db): db(t_db) {}

Adapter::~Adapter() {}