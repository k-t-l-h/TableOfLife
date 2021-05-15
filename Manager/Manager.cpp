#include "Manager.h"
#include <thread>
#include <memory>
#include <atomic>      // condition variables mb in pushing to queue
#include <mutex>
#include <chrono>

#include "../Request/Request.h"
#include "../GABuilder/Builder.h"
#include "../Result/Result.h"
#include "../Queue/Queue.h"




Manager::Manager(std::shared_ptr<Queue<Request>> tasq, std::shared_ptr<Queue<Result>> resq ) : tque(tasq), rque(resq) {}

std::mutex rque_mutex;

void Manager::WorkCycle() {
    while(active){
        if ( tque->Empty() )
            std::this_thread::sleep_for(std::chrono::milliseconds(300));

        auto current_task = tque->Pop();
        std::thread t(&Manager::work, this,std::move(current_task));
        t.detach();
    }
}

/*
void Manager::SetBuilder(const size_t N) {
    builder = std::make_unique<Builder<N>>();
}*/


//use mutex or cond var
void Manager::work( Request task ) {
    Result result = {task.id, std::vector<int>()};
    //TODO switch case
    if(task.params.creator == "1"){
        //......
    } else{
        //......
    }
    if( result.result.data() ){
        rque->Push( std::move(result) );
    } else {
        //throw smth fe badsolutionerror;
    }
}