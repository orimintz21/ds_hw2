#ifndef WORKPLACE_H_
#define WORKPLACE_H_

#include "hash.h"
#include "Rank.h"
#include "Employee.h"
#include "employeeTree.h"
#include "memory"
using std::shared_ptr;
using std::make_shared;

class UpdateEmployeer
{
public:
    Company* _employeer;
    UpdateEmployeer(Company* comp) :_employeer(comp){}

    void operator()(shared_ptr<Employee> emp) const
    {
        emp->_company = _employeer;
    }
};

class Company
{
public:
    int _id;
    double _stock_value;
    EmployeeTree _employees;
    long long _num_of_interns;
    long long _sum_of_interns_grade;
    hash<shared_ptr<Employee>> _all_employees;

    Company();
    Company(int n_id);
    Company(int n_id, double start_value);

    ~Company() = default;

    shared_ptr<Employee> getHeistEarner();
    
    bool isEmpty();
    
    long long getNumOfEmployeesWithSalary();

    long long getNumOfAllEmployees();

    void addEmployeeToCompany(shared_ptr<Employee> ptr_employee);
    
    void addEmployeeWithSalaryToCompany(shared_ptr<Employee> ptr_employee);

    void addEmployeeWithSalaryToCompanyAfterUpdate(shared_ptr<Employee> ptr_employee);

    void removeEmployeeFromCompany(shared_ptr<Employee> fired);

    void removeEmployeeToUpdate(shared_ptr<Employee> fired);
    void removeEmployeeWithSalary(shared_ptr<Employee> fired);

    void removeIntern(shared_ptr<Employee> fired);

    //after employeeSalaryIncreas, the grade of the employee doesn't chage!
    void updateEmployeeFromIntern(shared_ptr<Employee> emp);

    void updateEmployeeWithSalaryAfterBumpGrade(shared_ptr<Employee> emp);

    void bumpGradeToInter(int bumpGrade);

    void mergeWith(Company& target);

    void updateHash(Company& target);

    void sumOfBumpGradeBetweenTopWorkersByGroupInCompany(int m, long long* sumBumpgGrade);

    void averageBumpGradeBetweenSalaryByGroupInCompany(long long lowSalary, long long highSalary, double* averageBumpGrade);
};

#endif //WORKPLACE_H_