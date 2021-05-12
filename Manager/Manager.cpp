#include "Manager.h"
#include <thread>
#include <memory>
#include <atomic>      // condition variables mb in pushing to queue
#include <mutex>


//TODO i need an interface of custom queue and builder

class GABuilder{
public:
    GABuilder(){}

};

struct Request{
    int id;
    int type;
    Request(const Request &r){}
};


struct Result{
    int id;
};

Manager::Manager(std::shared_ptr<Queue<Request*>> tasq, std::shared_ptr<Queue<Result*>> resq ) : tque(tasq), rque(resq) {}

std::mutex rque_mutex;

void Manager::WorkCycle() {
    /* while(true){
         auto current_task = std::make_unique<Request>( *tque->front() );
         tque->pop();
         std::thread t(&Manager::work, this,std::move(current_task));
         t.detach();
     }*/
}

void Manager::SetBuilder() {
    builder = std::make_unique<GABuilder>();
}


//use mutex or cond var
void Manager::work( std::unique_ptr<Request> task ) {
    /*std::unique_ptr<Result> result;
    *//*TODO switch case*//*
    if(task->type == 1){
        //......
    } else{
        //......
    }
    if( result.get() != nullptr){
        //TODO atomic to use or std::guard_lock
        const std::lock_guard<std::mutex> lock(rque_mutex);
        rque->push(std::move(result).get());
    } else {
        //throw smth;
    }*/
}