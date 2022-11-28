#include "Rank.h"
#include "Node.h"
#include "Employee.h"
#include "employeeTree.h"
#include "Ex2Exception.h"
using std::make_shared;

void EmployeeTree::addEmployeeToTree(shared_ptr<Employee> emp)
{
    if(emp == nullptr || emp->_salary == 0)
    {
        throw invalid_input();
    }
    _indTree.insert(emp);
    _gradeTree.insert(emp);
}

long long EmployeeTree::getSize(){
    return _indTree.size;
}

void EmployeeTree::removeEmployeeFromTree(shared_ptr<Employee> emp)
{
    if(emp == nullptr)
    {
        throw invalid_input();
    }

    _indTree.remove(emp);
    _gradeTree.remove(emp);
}

void EmployeeTree::insertTree(EmployeeTree& source)
{
    _indTree.merge(source._indTree);
    _gradeTree.merge(source._gradeTree);
}

void EmployeeTree::updateEmployee(shared_ptr<Employee> emp)
{
    _indTree.remove(emp);
    _gradeTree.remove(emp);
    _indTree.insert(emp);
    _gradeTree.insert(emp);
}

void EmployeeTree::updateCompany(Company* comp)
{
    Node<shared_ptr<Employee>, RankInd>* root = _indTree.root;
    updateCompanyAux(comp, root);

}

void EmployeeTree::updateCompanyAux(Company* comp, Node<shared_ptr<Employee>, RankInd>* loc)
{
    if(loc == nullptr)
        return;
    (*(loc->data))->_company = comp;
    updateCompanyAux(comp, loc->left);
    updateCompanyAux(comp,loc->right);
}


long long EmployeeTree::sumOfBumpGradeBetweenTopWorkersInTrees(int m)
{
    if(m <= 0)
    {
        throw invalid_input();
    }
    if(m>getSize())
    {
        throw failure();
    }

    return getSumOfGradesBetweenIndexes(getSize() - m + 1, getSize());

    // Employee** highest_in_range = _indTree.max_n->data;
    // int fullGradeSum = _gradeTree.findRank(*highest_in_range);

    // if(_indTree.size == m)
    // {
    //     return fullGradeSum;
    // }
    // Employee** outside_of_range = _indTree.selectElement(getSize() - m);
    // int to_remove = _gradeTree.findRank(*outside_of_range);
    // return fullGradeSum - to_remove;
}

shared_ptr<Employee> EmployeeTree::getMinEmployee()
{
    if(getSize() == 0)
        return nullptr;
    
    return *(_indTree.min_n->data);
}

shared_ptr<Employee> EmployeeTree::getMaxEmployee()
{
    if(getSize() == 0)
        return nullptr;
    
    return *(_indTree.max_n->data);
}


long long EmployeeTree::getIndexForLowerSalaryAndHigherSalary(long long lowerSalary, long long higherSalary, long long& lowerInd, long long& higherInd)
{
    if(higherSalary <0 || lowerSalary < 0 || lowerSalary > higherSalary)
        throw invalid_input();

    lowerInd = 0;
    higherInd = 0;

    if(getSize() == 0)
    {
        if(lowerSalary > 0)
            throw failure();

        return 0; 
    }
    
    //there aren't any employees in the salary range (excluding 0)
    if(higherSalary < getMinEmployee()->_salary)
    {
        if(lowerSalary > 0)
            throw failure();

        return 0;
    }

    if(higherSalary == 0)
        return 0;
    
    if(lowerSalary > getMaxEmployee()->_salary)
    {
        throw failure();
    }

    //the tree isn't empy and there are employees in range
    higherInd = getHigherInd(higherSalary);
    if(lowerSalary == 0)
    {
        return higherInd;
    }
    else{
        lowerInd = getLowerInd(lowerSalary);
        return higherInd - lowerInd + 1;
    }
}


long long EmployeeTree::getLowerInd(long long lowerSalary){

    shared_ptr<Employee> temp = make_shared<Employee>(0, lowerSalary, 0, nullptr);
    _indTree.insert(temp);
    long long lower_ind = _indTree.findRank(temp);
    _indTree.remove(temp);
    return lower_ind;
}

long long EmployeeTree::getHigherInd(long long higherSalary){

    shared_ptr<Employee> temp= make_shared<Employee>(0, higherSalary + 1, 0, nullptr);
    _indTree.insert(temp);
    long long higher_ind = _indTree.findRank(temp) - 1;
    _indTree.remove(temp);
    return higher_ind;
}

long long EmployeeTree::getSumOfGradesBetweenIndexes(long long lowerInd, long long higherInd)
{
    long long lowerGrade = 0;
    long long higherGrade = 0;
    if(lowerInd > 1)
    {
        shared_ptr<Employee> lowerEmployee = *(_indTree.selectElement(lowerInd - 1));
        lowerGrade = _gradeTree.findRank(lowerEmployee);
    }
    
    if(higherInd > 0 )
    {
        shared_ptr<Employee> higherEmployee = *(_indTree.selectElement(higherInd));
        higherGrade = _gradeTree.findRank(higherEmployee);
    }

    return higherGrade - lowerGrade;
}
