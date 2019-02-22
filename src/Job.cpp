#include "Job.h"

Job::Job()
{
    //ctor
}

Job::Job(int id)
{
    this->setId(id);
}

Job::~Job()
{
    //dtor
}

void Job::setId(int id)
{
    this->id = id;
}

int Job::getId()
{
    return id;
}

void Job::setDuration(int duration)
{
    this->duration = duration;
}

int Job::getDuration()
{
    return duration;
}

void Job::setMachinePriority(int machine_priority)
{
    this->machine_priority = machine_priority;
}

int Job::getMachinePriority()
{
    return machine_priority;
}

void Job::printJobDetails()
{
    std::cout << "Job ID: "<< id << " Duration: " << duration << " min. "
        << "Due Date: " << due_date << " . "
        << "Machine Priority: " << machine_priority << std::endl;
}

int Job::getTotalTime(int setup_time)
{
    return duration + setup_time;
}

Date Job::getDueDate()
{
    return due_date;
}

void Job::setDueDate(Date date)
{
    due_date = date;
}
