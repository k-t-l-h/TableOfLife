#include "Adapter.h"


std::vector<int> Adapter::GetResult(int) const {
    std::vector<int> res;
    return res;
}

Adapter::Adapter() {}

Adapter::Adapter(std::shared_ptr <IDatabase> &t_db) {}

Adapter::~Adapter() {}