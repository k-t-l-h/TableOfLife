#include "Reporter.h"
#include "IDatabase.h"
#include <mutex>
#include <thread>
#include <memory>

std::mutex rque_mutex;


Reporter::Reporter(std::shared_ptr<std::queue<Result*>> &results, std::shared_ptr<IDatabase> &datab)
: rque(results),db(datab)
{}

Reporter::~Reporter() {}

void Reporter::WorkCycle(int t) {
    const std::lock_guard<std::mutex> lock(rque_mutex);
    Result * res = (rque->front());
    rque->pop();
    //db.Insert(res);
    //res.delete() //TODO !!!!!!!!!!!!!!
}

//void Reporter::SetUp(std::shared_ptr<std::queue<Result*>> &results, std::shared_ptr<IDatabase> &db) {}

