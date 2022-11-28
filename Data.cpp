#include "Data.h"
#include "Company.h"
#include "Employee.h"
#include "hash.h"
#include "employeeTree.h"
#include "UnionFind.h"
#include "Ex2Exception.h"
#include "RankTreeExceptions.h"

Data::Data(int k) : _companys(k), _all_employees(),  _employees(), _num_of_interns(0), _sum_of_interns_grade(0){}

void Data::AddEmployee(int employeeID, int companyID, int grade)
{
    if(employeeID<=0 || companyID <=0 || companyID > _companys._size || grade < 0)
        throw invalid_input();
    Company* comp = _companys.Find(companyID);
    shared_ptr<Employee> emp = make_shared<Employee>(employeeID, grade);
    _all_employees.insert(employeeID, emp);
    shared_ptr<Employee> emp_ptr = _all_employees.find(employeeID);
    if(!emp_ptr)
        throw failure();
    comp->addEmployeeToCompany(emp_ptr);
    _num_of_interns++;
    _sum_of_interns_grade += grade;   

}

void Data::RemoveEmployee(int employeeID)
{
    if(employeeID <= 0)
        throw invalid_input();
    if(!_all_employees.find(employeeID))
    {
        throw failure();
    }
    shared_ptr<Employee> emp = _all_employees.find(employeeID);
    if(emp->isIntern())
    {
        _num_of_interns--;
        _sum_of_interns_grade-=emp->_grade;
    }
    else{
        _employees.removeEmployeeFromTree(emp);
    }
    emp->_company->removeEmployeeFromCompany(emp);
    _all_employees.remove(employeeID);


}

void Data::AcquireCompany(int companyID1, int companyID2, double factor)
{
    if(companyID1<=0 || companyID2<=0 || companyID1 > _companys._size || companyID2 > _companys._size || companyID1 == companyID2 || factor <= 0)
    {
        throw invalid_input();
    }
    _companys.UnionLeftAcquire(companyID1,companyID2, factor);
}

void Data::EmployeeSalaryIncrease(int employeeID, int salaryIncrease)
{
    if(employeeID <= 0 || salaryIncrease <= 0)
        throw invalid_input();
    
    shared_ptr<Employee> emp = _all_employees.find(employeeID);
    if(emp == nullptr)
    {
        throw failure();
    }

    Company* comp = emp->_company;
    
    employeeRemoveToUpdate(emp, comp);

    emp->increaseSalary(salaryIncrease);

    _employees.addEmployeeToTree(emp);

    comp->addEmployeeWithSalaryToCompanyAfterUpdate(emp);
}

void Data::employeeRemoveToUpdate(shared_ptr<Employee> emp, Company* comp){
    if(emp->isIntern())
    {
        _num_of_interns--;
        _sum_of_interns_grade -= emp->getGrade();
    }
    else{
        _employees.removeEmployeeFromTree(emp);
    }
    comp->removeEmployeeToUpdate(emp);
}

void Data::PromoteEmployee(int employeeID, int bumpGrade)
{
    if(employeeID<=0)
    {
        throw invalid_input();
    }    
    shared_ptr<Employee> emp = _all_employees.find(employeeID);
    
    if(!emp)
        throw failure();
    
    Company* comp = emp->_company;

    if(bumpGrade <= 0)
        return;
    
    emp->promote(bumpGrade);
    if(emp->isIntern())
    {
        _sum_of_interns_grade += bumpGrade;
        comp->bumpGradeToInter(bumpGrade);
    }
    else{
        _employees.updateEmployee(emp);
        comp->updateEmployeeWithSalaryAfterBumpGrade(emp);
    }
}

void Data::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m, long long* sumBumpGrade)
{
    if(sumBumpGrade == nullptr)
    {
        throw invalid_input();
    }
    if(companyID<0||companyID>_companys._size || m<=0 || sumBumpGrade == nullptr)
    {
        throw invalid_input();
    }
    if(companyID == 0)
    {
        SumOfBumpGradeBetweenTopWorkersByGroupForAll(m, sumBumpGrade);
    }
    else{
        Company* comp = _companys.Find(companyID);
        comp->sumOfBumpGradeBetweenTopWorkersByGroupInCompany(m, sumBumpGrade);
    }
    
}

void Data::SumOfBumpGradeBetweenTopWorkersByGroupForAll(int m, long long* sumBumpGrade)
{
    if(m<=0 || sumBumpGrade == nullptr)
    {
        throw invalid_input();
    }

    *sumBumpGrade = _employees.sumOfBumpGradeBetweenTopWorkersInTrees(m);
}

void Data::AverageBumpGradeBetweenSalaryByGroup(int companyID, long long lowerSalary, long long higherSalary, double* averageBumpGrade)
{
    if(averageBumpGrade == nullptr)
    {
        throw invalid_input();
    }
    
    if(lowerSalary<0||higherSalary<0|| companyID<0 || companyID > _companys._size || averageBumpGrade == nullptr || lowerSalary > higherSalary)
    {
        throw invalid_input();
    }
    if(companyID > 0)
    {
        Company* company = _companys.Find(companyID);
        company->averageBumpGradeBetweenSalaryByGroupInCompany(lowerSalary, higherSalary, averageBumpGrade);
    }
    else{
        AverageBumpGradeBetweenSalaryByGroupForAll(lowerSalary, higherSalary, averageBumpGrade);
    }
}


void Data::AverageBumpGradeBetweenSalaryByGroupForAll(long long lowerSalary, long long higherSalary, double * averageBumpGrade)
{
    if(lowerSalary<0|| higherSalary<0|| averageBumpGrade == nullptr || lowerSalary > higherSalary)
        throw invalid_input();
    
    long long lowIndex = 0;
    long long highIndex = 0;
    long long num_of_employees_with_salary = _employees.getIndexForLowerSalaryAndHigherSalary(lowerSalary, higherSalary, lowIndex, highIndex);
    long long sum_of_grades_of_employees_with_salary = _employees.getSumOfGradesBetweenIndexes(lowIndex, highIndex);

    long long num_of_employees_without_salary =0;
    long long sum_of_grades_of_employees_without_salary =0;

    if(lowerSalary == 0)
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

void Data::CompanyValue(int companyID, double* standing)
{
    if(standing == nullptr)
    {
        throw invalid_input();
    }
    if(companyID<=0 || companyID > _companys._size || standing == nullptr)
    {
        throw invalid_input();
    }
    *standing =  _companys.FindValue(companyID);
}

