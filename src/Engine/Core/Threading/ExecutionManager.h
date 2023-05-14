#pragma once
#include "vector"
#include "thread"

namespace Engine {
    class ExecutionSystem {
    public:
        int SystemID = 0;
        bool Started = false;
        
        static int CurrentID;
    public:
        ExecutionSystem() { SystemID = CurrentID; CurrentID++; }

        virtual void OnStart() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnEnd() = 0;
    };

    class ExecutionThread {
    private:
        std::thread internal;
    public:
        ExecutionThread() {}
        template <typename T>
        ExecutionThread(T thread) {
            internal = std::thread(thread);
        }

        template <typename T, typename Q>
        ExecutionThread(T thread, Q funciton) {
            internal = std::thread(thread, funciton);
        }

        void JoinIn() {
            internal.join();
        }
    };

    class ExecutionGroup {
    public:
        std::vector<ExecutionSystem*> groupedSystems;
        ExecutionThread* mainThread;
        std::vector<ExecutionThread*> inUseThreads = {};
        std::vector<ExecutionThread*> heldThreads = {};

        bool Started = false;
    public:
        void BindSystem(ExecutionSystem* system) {
            groupedSystems.push_back(system);
        }

        void RunSystem(ExecutionSystem* system) {
            if (!system->Started) {
                system->OnStart();
                system->Started = true;
            }
            system->OnUpdate();
        }

        void RunExecutionGroup() {
            while(Started) {
                for (int i = 0; i < groupedSystems.size(); i++) {
                    RunSystem(groupedSystems[i]);
                }
            }
        }

        void StartGroup() {
            mainThread = new ExecutionThread(&ExecutionGroup::RunExecutionGroup, &(*this));
            Started = true;
        }

        void KillGroup() {
            Started = false;
            for (int i = 0; i < groupedSystems.size(); i++) {
                groupedSystems[i]->OnEnd();
            }
            mainThread->JoinIn();
        }
    };

    class ExecutionManager {
    private:   
        bool KilledExecution = false;
        std::vector<ExecutionGroup*> executionGroups;
        std::vector<ExecutionThread*> reservedThreads;

        std::thread execuitionThread;
    public:
        void BindGroup(ExecutionGroup* group) {
            executionGroups.push_back(group);
        }
        
        void RunExecutionGroup(ExecutionGroup* group) {
            if (!group->Started) {
                group->StartGroup();
            }
        }

        void UpdateExecution() {
            while (!KilledExecution) {
                for (int i = 0; i < executionGroups.size(); i++) {
                    RunExecutionGroup(executionGroups[i]);
                }
            }
        }

        void StartExecution() {
            execuitionThread = std::thread(&ExecutionManager::UpdateExecution, &(*this));
        }
    
        void StopExecution() {
            KilledExecution = true;
            for (int i = 0; i < executionGroups.size(); i++) {
                executionGroups[i]->KillGroup();
            }
            execuitionThread.join();
        }
    };
}