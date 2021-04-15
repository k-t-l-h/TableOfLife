#ifndef TABLEOFLIFE_ADAPTER_H
#define TABLEOFLIFE_ADAPTER_H

#include <memory>
class Database;

class Adapter {
public:
    Adapter();
    Adapter(const std::shared_ptr<IDatabase> &t_db);
    ~Adapter();

    const int ** GetResult(int) const;

private:
    Adapter(const Adapter &a) = delete;
    Adapter& operator=(const Adapter &a) = delete;

    std::shared_ptr<IDatabase> db;
};


#endif //TABLEOFLIFE_ADAPTER_H
