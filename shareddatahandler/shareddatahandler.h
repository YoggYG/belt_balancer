#ifndef INCLUDED_SHARED_DATA_HANDLER
#define INCLUDED_SHARED_DATA_HANDLER

#include <cstddef>
#include <queue>
#include <mutex>
#include <unordered_set>
#include "../semaphore/semaphore.h"
#include "../balancer/balancer.h"

struct SharedDataHandler
{
    struct Spec
    {
        Balancer bal;
        bool done;
    };

    private:
        Semaphore d_storageAvailable; //worker
        Semaphore d_jobsAvailable; //job
        Semaphore d_outputQAvailable; //available
    
        std::queue<Spec> d_tasks;
        std::queue<Spec> d_results;
        std::mutex d_taskMutex;
        std::mutex d_resultMutex;
        std::mutex d_outputvectorMutex;
        std::mutex d_mirrorMutex;

        std::vector<Balancer> d_balancers;

    public:
        SharedDataHandler(size_t nStorageLocations);
        void addTask(Spec task);
        Spec getTask();
        void addRes(Spec res);
        Spec getRes();
        bool contains(Balancer &balancer) const;
        void sortVector();
        void printSolution();
        void addToVector(Balancer const &balancer);

    private:
        Spec nextTask();
        Spec nextRes();
};


        
#endif
