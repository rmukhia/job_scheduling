#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<iostream>
#include<vector>

#include "Job.h"
#include "Machine.h"

class Processor
{
    public:
        enum RULE {
            SSUIT,
            EDD,
            SPT,
        };
        Processor();
        virtual ~Processor();

        void setNumJobs(int num_jobs, int last_job);
        int getNumJobs();

        void setNumMachines(int num_machines);
        int getNumMachines();

        void setSetupTimeMatrix();
        void printSetupTimeMatrix();

        void setJobDetails(int last_job);
        void setMachineDetails();

        void scheduleJobs(RULE rule);

        void printResults();

        void clearMachines();

    protected:
    private:
        int **setup_time;
        int num_jobs;
        int num_machines;
        std::vector<Job*> jobs;
        std::vector<int> jobs_already_scheduled;
        std::vector<Machine*> machines;
        std::vector<Job*> ssuit_schedule(Machine *machine, std::vector<Job*> jobs);
        std::vector<Job*> edd_schedule(Machine *machine, std::vector<Job*> jobs);
        std::vector<Job*> spt_schedule(Machine *machine, std::vector<Job*> jobs);

        Machine *findNextToProcessMachine();
};

#endif // PROCESSOR_H
