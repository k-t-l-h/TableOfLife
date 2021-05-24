#include "Manager.h"
#include <thread>
#include <memory>
#include <mutex>
#include <chrono>

#include "../Request/Request.h"
#include "../GABuilder/Builder.h"
#include "../Result/Result.h"
#include "../Queue/Queue.h"



Manager::Manager(std::shared_ptr<Queue<Request>> &tasq, std::shared_ptr<Queue<Result>> &resq ) : tque(tasq), rque(resq) {}

//TODO проверку количества свободных потокв в системе
//size_t threads = sysconf(_SC_NPROCESSORS_ONLN);

void Manager::WorkCycle() {
    while( active ){
        if ( tque->Empty() ) {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        } else {
            auto current_task = tque->Pop();
            std::thread t(&Manager::work, this,std::move(current_task));
            t.detach();
        }
    }
}



void Manager::work( Request task ) {

    Result outResult;
    outResult.id = task.id;
    outResult.ClassesNumber = task.ClassesNumber;
    outResult.classes = task.classes;

    const size_t N = 32;

    Builder<N> builder;
    builder.Reset( task.ClassesNumber, task.students.size() );  //TODO vr-? people-?

    if( task.params.creator == "random" ){
        builder.SetRandomCreator();
    } else{
        builder.SetCreator();
    }

    if( task.params.selector == "top" ){
        builder.SetTopSelection();
    } else{
        builder.SetSelection();
    }

    if ( task.params.mutation == "reverse" ){
        builder.SetReverseMutator(0.05);
    } else{
        builder.SetMutator(0.05);
    }

    if ( task.params.crossover == "2Point" ){
        builder.Set2PointsMater(0.5);
    } else {
        builder.SetMater(0.5);
    }

    auto res = builder.GetResult();
    res->Run();
    std::vector<size_t> solution = res->GetBest();

    outResult.result = solution;

    rque->Push( std::move(outResult) );

}

