#include "Reporter.h"
#include "IDatabase.h"
#include <mutex>
#include <thread>
#include <memory>

#include "../Result/Result.h"
#include "../IDatabase/IDatabase.h"
#include "../Queue/Queue.h"

Reporter::Reporter(std::shared_ptr<Queue<Result>> &results, std::shared_ptr<IDatabase> &datab)
        : rque(results),db(datab)
{}

Reporter::~Reporter() {}

void Reporter::WorkCycle() {
    while(active){
        Result res = rque->Pop();
        db->Insert(res);
    }
}

//void Reporter::SetUp(std::shared_ptr<std::queue<Result*>> &results, std::shared_ptr<IDatabase> &db) {}