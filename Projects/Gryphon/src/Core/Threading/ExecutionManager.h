#pragma once
#include "vector"
#include "thread"
#include <chrono>
#include "iostream"
#include <unistd.h>
#include "typeinfo"

namespace Engine {
    class ExecutionThread {
    protected:
        std::thread internal;
    public:
        bool IsRunning = true;
    public:
        ExecutionThread() {

        }
        template <typename T>
        ExecutionThread(T thread) {
            internal = std::thread(thread);
        }

        template <typename T, typename Q>
        ExecutionThread(T thread, Q funciton) {
            internal = std::thread(thread, funciton);
        }

        void Pause () {
            IsRunning = false;
        }

        void Kill() {
            internal.~thread();
        }

        void JoinIn() {
            internal.join();
        }
    };

    class ExecutionGroup;

    class ExecutionSystem {
    public:
        int SystemID = 0;
        bool Started = false;
        
        static int CurrentID;

        ExecutionGroup* currentGroup;
    public:
        ExecutionSystem() { SystemID = CurrentID; CurrentID++; }

        template <typename T, typename Q>
        ExecutionThread* RequestThread(T value, Q function) {
            return currentGroup->CreateThread(value, function);
        }

        // Warniong this does need to be in the same execution group im lazy and am not going out of group execution systems
        template <typename T>
        T* GetExecutionSystem() {
            for (int i = 0; i < currentGroup->groupedSystems.size(); i++) {
                if (dynamic_cast<T*>(currentGroup->groupedSystems[i]))
                    return dynamic_cast<T*>(currentGroup->groupedSystems[i]);
            }
        }

        virtual void OnStart() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnEnd() = 0;
    };


    class ExecutionGroup {
    public:
        std::vector<ExecutionSystem*> groupedSystems;
        ExecutionThread* mainThread;
        std::vector<ExecutionThread*> inUseThreads = {};
        std::vector<ExecutionThread*> heldThreads = {};

        bool Started = false;
    public:
        template <typename T, typename Q>
        ExecutionThread* CreateThread(T value, Q function) {
            return new ExecutionThread(value, function);
        }

        void BindSystem(ExecutionSystem* system) {
            groupedSystems.push_back(system);
        }

        void RunSystem(ExecutionSystem* system) {
            system->currentGroup = this;
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

            for (int i = 0; i < inUseThreads.size(); i++) {
                inUseThreads[i]->Kill();
                inUseThreads[i]->JoinIn();
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
                usleep(1000);
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