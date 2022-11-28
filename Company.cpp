#include "Company.h"
#include "Ex2Exception.h"
#include "Rank.h"



Company::Company() : _id(-1), _stock_value(-1), _employees(),_num_of_interns(0), _sum_of_interns_grade(0), _all_employees(){}


Company::Company(int n_id) : _id(n_id), _stock_value(double(n_id)), _employees(), _num_of_interns(0), _sum_of_interns_grade(0),_all_employees(){}



Company::Company(int n_id, double start_value) : _id(n_id) , _stock_value(start_value), _num_of_interns(0), _sum_of_interns_grade(0), _all_employees() {}


bool Company::isEmpty() {
    
    return _all_employees.getItemCount() == 0;
}

long long Company::getNumOfEmployeesWithSalary()
{
    return _employees.getSize();
}

long long Company::getNumOfAllEmployees()
{
    return getNumOfEmployeesWithSalary() + _num_of_interns;
}

void Company::addEmployeeToCompany(shared_ptr<Employee> ptr_employee)
{
    //addEmployeeToCompany only adds interns
    if(ptr_employee == nullptr || !(ptr_employee->isIntern()))
        return;

    ptr_employee->_company = this;

    _all_employees.insert(ptr_employee->_id, ptr_employee);
    _num_of_interns++;
    _sum_of_interns_grade += ptr_employee->getGrade(); 
    
}

void Company::addEmployeeWithSalaryToCompany(shared_ptr<Employee> ptr_employee)
{
    if(ptr_employee == nullptr || ptr_employee->isIntern())
        return;
    
    ptr_employee->_company = this;

    _all_employees.insert(ptr_employee->_id, ptr_employee);
    _employees.addEmployeeToTree(ptr_employee);
}

void Company::addEmployeeWithSalaryToCompanyAfterUpdate(shared_ptr<Employee> ptr_employee)
{
    if(ptr_employee == nullptr || ptr_employee->isIntern())
        return;
    
    ptr_employee->_company = this;
    
    _employees.addEmployeeToTree(ptr_employee);
}

void Company::removeEmployeeToUpdate(shared_ptr<Employee> fired)
{
    if((fired == nullptr) || (fired->getCompany() != this))
        return;

    if(fired->_salary > 0)
    {
        removeEmployeeWithSalary(fired);
    }
    else{
        removeIntern(fired);
    }
}

void Company::removeEmployeeFromCompany(shared_ptr<Employee> fired)
{
    if((fired == nullptr) || (fired->getCompany() != this))
        return;

    if(fired->_salary > 0)
    {
        removeEmployeeWithSalary(fired);
    }
    else{
        removeIntern(fired);
    }
    _all_employees.remove(fired->_id);
}

void Company::removeEmployeeWithSalary(shared_ptr<Employee> fired)
{
    _employees.removeEmployeeFromTree(fired);
}

void Company::removeIntern(shared_ptr<Employee> fired)
{
    _num_of_interns--;
    _sum_of_interns_grade -= fired->getGrade();
}

void Company::updateEmployeeFromIntern(shared_ptr<Employee> emp)
{
    _num_of_interns--;
    _sum_of_interns_grade -= emp->getGrade();

    _employees.addEmployeeToTree(emp);
}


void Company::updateEmployeeWithSalaryAfterBumpGrade(shared_ptr<Employee> emp)
{
    _employees.updateEmployee(emp);
}

void Company::bumpGradeToInter(int bumpGrade)
{
    _sum_of_interns_grade += bumpGrade;
}



void Company::mergeWith(Company &target) {
    _sum_of_interns_grade += target._sum_of_interns_grade;
    _num_of_interns += target._num_of_interns;

    _employees.insertTree(target._employees);

    _all_employees.updateAndRemove(target._all_employees, UpdateEmployeer(this));
}

void Company::sumOfBumpGradeBetweenTopWorkersByGroupInCompany(int m, long long *sumBumpgGrade)
{
    if(m<=0 || sumBumpgGrade == nullptr)
    {
        throw invalid_input();
    }

    *sumBumpgGrade = _employees.sumOfBumpGradeBetweenTopWorkersInTrees(m);
}

void Company::averageBumpGradeBetweenSalaryByGroupInCompany(long long lowSalary, long long  highSalary, double* averageBumpGrade)
{
    if(averageBumpGrade == nullptr || lowSalary<0 || highSalary<0 || lowSalary > highSalary)
    {
        throw invalid_input();
    }

    long long lowIndex = 0;
    long long highIndex = 0;
    long long num_of_employees_with_salary = _employees.getIndexForLowerSalaryAndHigherSalary(lowSalary, highSalary, lowIndex, highIndex);
    long long sum_of_grades_of_employees_with_salary = _employees.getSumOfGradesBetweenIndexes(lowIndex, highIndex);

    long long num_of_employees_without_salary =0;
    long long sum_of_grades_of_employees_without_salary =0;

    if(lowSalary == 0)
    {
        num_of_employees_without_salary = _num_of_interns;
        sum_of_grades_of_employees_without_salary = _sum_of_interns_grade;
    }
    if(num_of_employees_with_salary + num_of_employees_without_salary == 0)
    {
        throw failure();
    }
    *averageBumpGrade = double(sum_of_grades_of_employees_with_salary + sum_of_grades_of_employees_without_salary) 
                                    / double(num_of_employees_without_salary+ num_of_employees_with_salary);
}


