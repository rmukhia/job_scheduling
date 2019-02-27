#ifndef MACHINE_H
#define MACHINE_H

#include <vector>

#include "Job.h"
#include "Date.h"

class Machine
{
    public:
        Machine();
        void setId(int id);
        int getId();
        int getTotalTime();
        void addJob(Job *job, int setup_time);
        Job *peekJob(); // get the job at the last of the job list
        int getLastJobId();
        virtual ~Machine();
        void printResults();
        void clearMachine();
        Date getStartDate();
        void setStartDate(Date date);
        Date getCurrentDate();
        Date start_date;
        Date current_date;
        int getTotalSetupTime();
    protected:
    private:
        int id;
        std::vector<Job*> jobs;
        int total_time; // in minutes
        int total_setup_time;
        int tardiness;
};

#endif // MACHINE_H
