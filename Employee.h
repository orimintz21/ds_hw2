#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include "Node.h"
#include "Rank.h"
#include "Employee.h"
#include "RankTreeExceptions.h"


class Company;

class Employee
{
private:

public:
    int _id;
    long long _salary;
    long long _grade;
    Company* _company;

    Employee(int n_id);

    Employee();
    Employee(int n_id, int n_grade);

    Employee(int n_id,int n_salary, int n_grade, Company* n_company);
    ~Employee()=default;
    long long getSalary();
    long long getGrade();
    Company* getCompany();

    void increaseSalary(int SalaryIncrease);

    void promote(int BumpGrade);

    bool isIntern() const;
};


#endif //EMPLOYEE_H_