#ifndef HW2_EMPLOYEE_TREE
#define HW2_EMPLOYEE_TREE

#include "Rank.h"
#include "Node.h"
#include "Employee.h"
#include "memory"
using std::shared_ptr;

class SalaryComp
{
public:
    bool operator()(const shared_ptr<Employee> a, const shared_ptr<Employee> b) const
    {
        if((a->_salary > b->_salary) || (a->_salary == b->_salary && a->_id > b->_id))
            return true;
        return false;
    }
};

class RankInd
{
public:
    int operator()(const shared_ptr<Employee> a) const
    {
        return 1;
    }
};

class RankGrade
{
public:
    int operator()(const shared_ptr<Employee> a) const
    {
        return a->_grade;
    }
};

class EmployeeTree
{
public:
    RankTree<shared_ptr<Employee>, SalaryComp, RankInd> _indTree;
    RankTree<shared_ptr<Employee>, SalaryComp, RankGrade> _gradeTree;
    void addEmployeeToTree(shared_ptr<Employee> emp);

    long long getSize();

    shared_ptr<Employee> getMinEmployee();

    shared_ptr<Employee> getMaxEmployee();

    void removeEmployeeFromTree(shared_ptr<Employee> emp);

    void insertTree(EmployeeTree& source);

    //chack what to do after salary change
    void updateEmployee(shared_ptr<Employee> emp);

    //chage to function to hash
    void updateCompany(Company* comp);

    void updateCompanyAux(Company* comp, Node<shared_ptr<Employee>, RankInd>* loc);

    long long sumOfBumpGradeBetweenTopWorkersInTrees(int m);

    long long getIndexForLowerSalaryAndHigherSalary(long long lowerSalary, long long higherSalary, long long& lowerInd, long long& higherInd);

    long long getLowerInd(long long lowerSalary);
    
    long long getHigherInd(long long higherSalary);

    long long getSumOfGradesBetweenIndexes(long long lowerInd, long long higherInd);

};


#endif //HW2_EMPLOYEE_TREE