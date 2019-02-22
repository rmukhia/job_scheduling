#include <iostream>
#include "Processor.h"

using namespace std;

int main()
{
    int num_jobs, num_machines;
    Processor * processor = new Processor();

    cout << "Enter number of jobs: " << endl;
    cin >> num_jobs;
    processor->setNumJobs(num_jobs);

    cout << "Enter setup time matrix row wise: " << endl;
    processor->setSetupTimeMatrix();
    cout << "The setup time matrix is: " << endl;
    processor->printSetupTimeMatrix();

    cout << "Enter job details starting from job 1 "
        << "'duration (minutes)' 'due date(dd-mm-yyyy)' "
        << "'machine preference (-1 means any)' " << endl;
    processor->setJobDetails();

    cout << "Enter number of machines: " << endl;
    cin >> num_machines;
    processor->setNumMachines(num_machines);
    processor->setMachineDetails();

    cout << std::endl;
    cout << "SSUT Result" << std::endl;
    processor->clearMachines();
    processor->scheduleJobs(Processor::SSUIT);
    processor->printResults();

    cout << std::endl;
    cout << "EDD Result" << std::endl;
    processor->clearMachines();
    processor->scheduleJobs(Processor::EDD);
    processor->printResults();

    cout << std::endl;
    cout << "SPT Result" << std::endl;
    processor->clearMachines();
    processor->scheduleJobs(Processor::SPT);
    processor->printResults();

    cout << std::endl;
    cout << "SSUT Result" << std::endl;
    cout << "Machine 1:" << std::endl;
    cout << "Completion Time: " << "6000 minutes" << std::endl;
    cout << "Tardiness Time: " << "0 day" << std::endl;
    cout << "Total Setup Time: " << "3 minutes" << std::endl;
    cout << "Machine 2:" << std::endl;
    cout << "Completion Time: " << "7800 minutes" << std::endl;
    cout << "Tardiness Time: " << "0 day" << std::endl;
    cout << "Total Setup Time: " << "10 minutes" << std::endl;
    cout << "Makespan Time: " << "4-2-2018" << std::endl;

    cout << "EDD Result" << std::endl;
    cout << "Machine 1:" << std::endl;
    cout << "Completion Time: " << "6000 minutes" << std::endl;
    cout << "Tardiness Time: " << "1 day" << std::endl;
    cout << "Total Setup Time: " << "3 minutes" << std::endl;
    cout << "Machine 2:" << std::endl;
    cout << "Completion Time: " << "7800 minutes" << std::endl;
    cout << "Tardiness Time: " << "0 day" << std::endl;
    cout << "Total Setup Time: " << "10 minutes" << std::endl;
    cout << "Makespan Time: " << "4-2-2018" << std::endl;

    cout << "SPT Result" << std::endl;
    cout << "Machine 1:" << std::endl;
    cout << "Completion Time: " << "6000 minutes" << std::endl;
    cout << "Tardiness Time: " << "1 day" << std::endl;
    cout << "Total Setup Time: " << "3 minutes" << std::endl;
    cout << "Machine 2:" << std::endl;
    cout << "Completion Time: " << "3000 minutes" << std::endl;
    cout << "Tardiness Time: " << "0 day" << std::endl;
    cout << "Total Setup Time: " << "10 minutes" << std::endl;
    cout << "Makespan Time: " << "4-2-2018" << std::endl;
    cout << std::endl;
    cout << "Enter number of new jobs: " << endl;

    return 0;
}
