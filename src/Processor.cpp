#include "Processor.h"
#include <iostream>
#include <algorithm>

Processor::Processor()
{
    //ctor
    num_machines = num_jobs = 0;
}

Processor::~Processor()
{
    //dtor
}

void Processor::setNumJobs(int num_jobs, int last_job)
{
    this->num_jobs = num_jobs;
    for (int i=last_job + 1; i <= num_jobs; i++) {
        Job *job = new Job(i);
        this->jobs.push_back(job);
    }
}

int Processor::getNumJobs()
{
    return num_jobs;
}

void Processor::setNumMachines(int num_machines)
{
    int new_machines = num_machines - this->num_machines;
    for(int i =0; i< new_machines; i++) {
        Machine *machine = new Machine();
        machine->setId(i + 1);
        this->machines.push_back(machine);
    }
    num_machines += new_machines;
}

int Processor::getNumMachines()
{
    return num_machines;
}

void Processor::setSetupTimeMatrix()
{
    this->setup_time = new int*[num_jobs + 1];

    for(int i =0; i <= num_jobs; i++) {
        this->setup_time[i] = new int[num_jobs + 1];
        for(int j=0; j <= num_jobs; j++)
            std::cin >> this->setup_time[i][j];
    }
}

void Processor::printSetupTimeMatrix()
{
    for(int i = 0; i <= num_jobs; i++) {
        for(int j = 0; j <= num_jobs; j++)
            std::cout << this->setup_time[i][j] << " ";
        std::cout << std::endl;
    }
}

void Processor::setJobDetails(int last_job)
{
    for(unsigned int i = last_job; i < jobs.size(); i++) {
        Job *job = jobs[i];
        int duration, machine_priority;
        char str[16];
        std::cout << "Enter job details: " << std::endl;
        std::cin >> duration >> str >> machine_priority;
        job->setDuration(duration);
        job->due_date.parse_date(str);
        job->setMachinePriority(machine_priority);
        job->printJobDetails();
    }
}

void Processor::setMachineDetails()
{
    char date[16];
    std::cout << "Enter machine start date (dd-mm-yyyy): " << std::endl;
    std::cin >> date;
    Machine *machine;

    for(unsigned int i = 0; i < machines.size(); i++) {
        machine = machines[i];
        machine->start_date.parse_date(date);
        machine->current_date.parse_date(date);
    }
}


std::vector<Job*> Processor::ssuit_schedule(Machine *machine, std::vector<Job*> jobs)
{
    std::vector<Job*> result;
    int job_id = machine->getLastJobId();
    int shortest_setup_time = 999999;
    for (unsigned int i =0; i< jobs.size(); i++) {
        Job * job = jobs[i];
        if (job->getMachinePriority() != -1 && job->getMachinePriority() != machine->getId())
            break;
        if (job->getId() != job_id &&
                shortest_setup_time > setup_time[job->getId()][job_id]) {
            shortest_setup_time = setup_time[job->getId()][job_id];
        }
    }

    for (unsigned int i =0; i< jobs.size(); i++) {
        Job * job = jobs[i];
        if (job->getMachinePriority() != -1 && job->getMachinePriority() != machine->getId())
            break;


        if (job->getId() != job_id &&
                setup_time[job->getId()][job_id] == shortest_setup_time) {
            result.push_back(job);
        }
    }

    return result;
}

std::vector<Job*> Processor::edd_schedule(Machine* machine, std::vector<Job*>jobs)
{
    std::vector<Job*> result;
    Job *edd_job = 0x0;
    for (unsigned int i =0; i< jobs.size(); i++) {
        Job * job = jobs[i];
        if (!edd_job) edd_job = job;
        if (job->getMachinePriority() != -1 && job->getMachinePriority() != machine->getId())
            break;

        if(edd_job->getDueDate().compare(job->due_date) > 0) {
            edd_job = job;
        }
    }

    for (unsigned int i =0; i< jobs.size(); i++) {
        Job * job = jobs[i];
        if (job->getMachinePriority() != -1 && job->getMachinePriority() != machine->getId())
            break;
        if (edd_job->getDueDate().compare(job->getDueDate()) == 0) {
            result.push_back(job);
        }
    }

    return result;
}

std::vector<Job*> Processor::spt_schedule(Machine* machine, std::vector<Job*>jobs)
{
    std::vector<Job*> result;
    Job *spt_job = 0x0;
    for (unsigned int i =0; i< jobs.size(); i++) {
        Job * job = jobs[i];
        if (!spt_job) spt_job = job;
        if (job->getMachinePriority() != -1 && job->getMachinePriority() != machine->getId())
            break;
        if( spt_job->getDuration() > job->getDuration()) {
            spt_job = job;
        }
    }

    for (unsigned int i =0; i< jobs.size(); i++) {
        Job * job = jobs[i];
        if (job->getMachinePriority() != -1 && job->getMachinePriority() != machine->getId())
            break;
        if (spt_job->getDuration() == job->getDuration()) {
            result.push_back(job);
        }
    }
    return result;
}


void Processor::scheduleJobs(RULE rule)
{
    std::vector<Job *> jobs_ = jobs;
    while(jobs_.size() > 0 ) {
        Machine *machine = findNextToProcessMachine();
        std::vector<Job*> result;
        switch (rule) {
        case Processor::SSUIT:
            result = ssuit_schedule(machine, jobs_);
            if (result.size() > 1) {
                result = edd_schedule(machine, result);
            }

            if (result.size() > 1) {
                result = spt_schedule(machine, result);
            }

            break;
        case Processor::SPT:
            result = spt_schedule(machine, jobs_);
            if (result.size() > 1) {
                result = edd_schedule(machine, result);
            }

            if (result.size() > 1) {
                result = ssuit_schedule(machine, result);
            }
            break;
        case Processor::EDD:
            result = edd_schedule(machine, jobs_);
            if (result.size() > 1) {
                result = spt_schedule(machine, result);
            }

            if (result.size() > 1) {
                result = ssuit_schedule(machine, result);
            }
            break;
        }

        int last_job = machine->getLastJobId();
        if (result.size() == 0)
            continue;
        int new_job = result.front()->getId();
        machine->addJob(result.front(), setup_time[new_job][last_job]);
        jobs_.erase(std::remove(jobs_.begin(), jobs_.end(), result.front()), jobs_.end());
    }
}

Machine *Processor::findNextToProcessMachine()
{
    Machine *next = machines.front();
    for(unsigned int i =0; i< machines.size(); i++) {
        Machine *machine = machines[i];
        if (!next)
            next = machine;
        if(next->getTotalTime() > machine->getTotalTime())
            next = machine;
    }
    return next;
}

void Processor::printResults()
{
    Date *makespan = 0x0;
    int total_setup_time = 0;
    int total_tardiness = 0;
    for(unsigned int i = 0; i < machines.size(); i++) {
        machines[i]->printResults();
        total_setup_time +=  machines[i]->getTotalSetupTime();
        total_tardiness += machines[i]->getTotalTardiness();
        if (!makespan) makespan = &machines[i]->current_date;
        if (machines[i]->getCurrentDate().compare(*makespan) > 0) {
            makespan = &machines[i]->current_date;
            makespan = &machines[i]->current_date;
        }
    }
    std::cout << std::endl;
    std::cout << "Makespan: " << (*makespan) << std::endl;
    std::cout << "Total Setup Time: " << total_setup_time << std::endl;
    std::cout << "Tardiness: " << total_tardiness << std::endl;
}

void Processor::clearMachines()
{
    for(unsigned int i = 0; i < machines.size(); i++) {
        machines[i]->clearMachine();
    }
}
