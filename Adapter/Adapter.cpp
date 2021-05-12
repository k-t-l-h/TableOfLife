#include "Adapter.h"
#include "IDatabase.h"

const std::vector<int> Adapter::GetResult(int id) const {
    return db->Select(id);
}

Adapter::Adapter() {}

Adapter::Adapter(std::shared_ptr <IDatabase> t_db): db(t_db) {}

Adapter::~Adapter() {}