
#ifndef Data_H
#define Data_H
#include "Company.h"
#include "Employee.h"
#include "UnionFind.h"
#include "employeeTree.h"
#include "hash.h"
#include "memory"

using std::shared_ptr;
using std::make_shared;

class Data
{
public:
    UnionFind _companys;
    hash<shared_ptr<Employee>> _all_employees;
    EmployeeTree _employees;
    long long _num_of_interns;
    long long _sum_of_interns_grade;

    Data(int k);
    ~Data() = default;

    void AddEmployee(int employeeID, int companyID, int grade);

    void RemoveEmployee(int employeeID);

    void AcquireCompany(int companyID1, int companyID2, double factor);

    void EmployeeSalaryIncrease(int employeeID, int salaryIncrease);

    void employeeRemoveToUpdate(shared_ptr<Employee> emp, Company* comp);

    void PromoteEmployee(int employeeID, int bumpGrade);

    void SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m, long long* sumBumpGrade);
    
    void SumOfBumpGradeBetweenTopWorkersByGroupForAll(int m, long long* sumBumpGrade);

    void AverageBumpGradeBetweenSalaryByGroup(int companyID, long long lowerSalary, long long higherSalary, double* averageBumpGrade);
    
    void AverageBumpGradeBetweenSalaryByGroupForAll(long long lowerSalary, long long higherSalary, double * averageBumpGrade);

    void CompanyValue(int companyID, double* standing);
};

#endif