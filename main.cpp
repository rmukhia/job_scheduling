#include <iostream>
#include "Processor.h"

using namespace std;

void run(int last_job, Processor *processor)
{

    cout << "Enter setup time matrix row wise: " << endl;
    processor->setSetupTimeMatrix();
    cout << "The setup time matrix is: " << endl;
    processor->printSetupTimeMatrix();

    cout << "Enter job details starting from job " << last_job + 1 << " ."
        << "'duration (minutes)' 'due date(dd-mm-yyyy)' "
        << "'machine preference (-1 means any)' " << endl;
    processor->setJobDetails(last_job);


    cout << std::endl;
    std::cout << "-----------" << std::endl;
    cout << "SSUT Result" << std::endl;
    processor->clearMachines();
    processor->scheduleJobs(Processor::SSUIT);
    processor->printResults();
    std::cout << "-----------" << std::endl;

    cout << std::endl;
    std::cout << "-----------" << std::endl;
    cout << "EDD Result" << std::endl;
    processor->clearMachines();
    processor->scheduleJobs(Processor::EDD);
    processor->printResults();
    std::cout << "-----------" << std::endl;

    cout << std::endl;
    std::cout << "-----------" << std::endl;
    cout << "SPT Result" << std::endl;
    processor->clearMachines();
    processor->scheduleJobs(Processor::SPT);
    processor->printResults();
    std::cout << "-----------" << std::endl;
}

int main()
{
    int num_jobs, num_machines, new_jobs, last_job = 0;
    Processor * processor = new Processor();


    cout << "Enter number of machines: " << endl;
    cin >> num_machines;
    processor->setNumMachines(num_machines);
    processor->setMachineDetails();

    cout << "Enter number of jobs: " << endl;
    cin >> num_jobs;
    processor->setNumJobs(num_jobs, last_job);

    while(true) {
        run(last_job, processor);
        last_job = num_jobs;
        cout << std::endl;
        cout << "Enter number of new jobs: " << endl;
        cin >> new_jobs;
        num_jobs += new_jobs;
        processor->setNumJobs(num_jobs, last_job);
    }
    return 0;
}
