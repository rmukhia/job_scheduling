#include "Machine.h"
#include<iostream>

Machine::Machine()
{
    total_time = 0;
    total_setup_time = 0;
    tardiness = 0;
}

Machine::~Machine()
{
    //dtor
}

void Machine::setId(int id)
{
    this->id = id;
}

int Machine::getId()
{
    return id;
}

int Machine::getTotalTime()
{
    return total_time;
}

void Machine::addJob(Job* job, int setup_time)
{
    jobs.push_back(job);
    total_time += job->getDuration() + setup_time;
    total_setup_time += setup_time;
    current_date.addMinutes(setup_time + job->getDuration());
    int tard = current_date.days_difference(job->getDueDate());
    if ( tard > 0) tardiness += tard;
}

Job * Machine::peekJob()
{
    return jobs.back();
}

int Machine::getLastJobId()
{
    if (jobs.empty())
        return 0;

    return peekJob()->getId();
}

void Machine::printResults()
{
    std::cout << "Machine ID: " << getId() << std::endl;
    std::cout << "Jobs assigned: " ;
    for(unsigned int i =0; i < jobs.size(); i++) {
        std::cout << "Job ID: " << jobs[i]->getId() << ",";
    }
    std::cout << std::endl;
    std::cout << "Completion Time: " << total_time << " minutes." << std::endl;
    std::cout << "Total Setup Time: " << total_setup_time << " minutes." << std::endl;
    std::cout << "Tardiness: " << tardiness << " days." << std::endl;
}

void Machine::clearMachine()
{
    jobs.clear();
    tardiness = total_setup_time = total_time = 0;

    current_date = start_date;
}

Date Machine::getStartDate()
{
    return start_date;
}

Date Machine::getCurrentDate()
{
    return current_date;
}



