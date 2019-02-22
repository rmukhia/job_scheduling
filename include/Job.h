#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <ctime>
#include "Date.h"


class Job
{
    public:
        Job();
        Job(int id);
        void setId(int id);
        int getId();

        void setDuration(int duration);
        int getDuration();

        void setMachinePriority(int machine_priority);
        int getMachinePriority();

        void printJobDetails();

        int getTotalTime(int setup_time);

        Date getDueDate();
        void setDueDate(Date date);

        virtual ~Job();
        Date due_date;
    protected:
    private:
        int id;
        int duration;
        int machine_priority;

};

#endif // JOB_H
