// #include "Company.h"
#include "Employee.h"
#include "Ex2Exception.h"

Employee::Employee() : _id(-1), _salary(0) ,_grade(0), _company(nullptr) {}
Employee::Employee(int n_id) : _id(n_id), _salary(0) ,_grade(0), _company(nullptr){}

Employee::Employee(int n_id, int n_grade) : _id(n_id), _salary(0) ,_grade(n_grade), _company(nullptr){}

Employee::Employee(int n_id,int n_salary, int n_grade, Company* n_company) : _id(n_id),
    _salary(n_salary) ,_grade(n_grade), _company(n_company){}

long long Employee::getSalary()
{
    return this->_salary;
}

long long Employee::getGrade()
{
    return this->_grade;
}

Company* Employee::getCompany()
{
    return this->_company;
}

bool Employee::isIntern() const
{
    return _salary == 0;
}

void Employee::promote(int BumpGrade)
{
    if(BumpGrade > 0)
    {
        _grade += BumpGrade;
    }
}

void Employee::increaseSalary(int SalaryIncrease)
{
    if(SalaryIncrease <= 0)
    {
        throw invalid_input();
    }
    _salary += SalaryIncrease;
}
