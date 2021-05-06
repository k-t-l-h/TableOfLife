#include "Manager.h"
#include <thread>
#include <memory>
#include <atomic>      // condition variables
#include <mutex>

Manager(std::shared_ptr<std::queue<Request*>> &tasq, std::shared_ptr<std::queue<Result*>> &resq):tque(tasq), rque(resq) {}

std::mutex rque_mutex;

void Manager::WorkCycle() {
    while(true){
        auto current_task = std::make_unique( tque->top() );
        std::thread t(work,std::move(current_task));
        t.detach();
    }
}

void Manager::SetBuilder(std::unique_ptr<GABuilder> builder) {
    builder = std::make_unique(new GABuilder());
}


//use mutex or cond var
void Manager::work( std::unique_ptr<Request*> task ) {
    std::unique_ptr<Result*> result;
    /*TODO switch case*/
    if(task->type == 1){
        //......
    } else{
        //......
    }

    if( result.get() != nullptr){
        //TODO atomic to use or std::guard_lock
        const std::lock_guard<std::mutex> lock(rque_mutex);
        rque->push(std::move(result));
    } else {
        //throw smth;
    }
}