#include "Reporter.h"
#include "IDatabase.h"
#include <mutex>
#include <thread>
#include <memory>
#include <chrono>

#include "../Result/Result.h"
#include "../IDatabase/IDatabase.h"
#include "../Queue/Queue.h"

Reporter::Reporter(std::shared_ptr<Queue<Result>> &results, std::shared_ptr<IDatabase> &datab)
        : rque(results),db(datab)
{}

Reporter::~Reporter() {}

void Reporter::WorkCycle() {
    while( active ){
        if ( rque->Empty() ){
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        } else {
            auto res = rque->Pop(); //так, а что за результаты внутри? непонятно откуда , будто мусор
            if ( !db->Insert(res) ){
                rque->Push(res);
            }
        }
    }
}
