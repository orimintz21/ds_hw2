#include "library2.h"
#include "Data.h"
#include "Ex2Exception.h"
#include "RankTreeExceptions.h"



void *Init(int k)
{
    Data* data = nullptr;
    try{
        data = new Data(k);
    }
    catch (const std::bad_alloc &e){
        return NULL;
    }
    return (void*)data;
}

StatusType AddEmployee(void *DS, int employeeID, int companyID, int grade) 
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    try{
        ((Data*)DS)->AddEmployee(employeeID, companyID, grade);
    }
    catch (const std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
    catch ( const invalid_input &e){
        return INVALID_INPUT;
    }
    catch (const failure &e){
        return FAILURE;
    }
    catch (const already_in_hash &e){
        return FAILURE;
    }
    catch ( const already_in_tree &e){
        return FAILURE;
    }
    catch(const not_in_hash &e){
        return FAILURE;
    }
    catch(const not_in_tree &e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemoveEmployee(void *DS, int employeeID) {
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    try{
        ((Data*)DS)->RemoveEmployee(employeeID);
    }
    catch (const std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
    catch ( const invalid_input &e){
        return INVALID_INPUT;
    }
    catch (const failure &e){
        return FAILURE;
    }
    catch (const already_in_hash &e){
        return FAILURE;
    }
    catch ( const already_in_tree &e){
        return FAILURE;
    }
    catch(const not_in_hash &e){
        return FAILURE;
    }
    catch(const not_in_tree &e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType AcquireCompany(void *DS, int companyID1, int companyID2, double factor){
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    try{
        ((Data*)DS)->AcquireCompany(companyID1, companyID2, factor);
    }
    catch (const std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
    catch ( const invalid_input &e){
        return INVALID_INPUT;
    }
    catch (const failure &e){
        return FAILURE;
    }
    catch (const already_in_hash &e){
        return FAILURE;
    }
    catch ( const already_in_tree &e){
        return FAILURE;
    }
    catch(const not_in_hash &e){
        return FAILURE;
    }
    catch(const not_in_tree &e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType EmployeeSalaryIncrease(void *DS, int employeeID, int salaryIncrease) {
       if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    try{
        ((Data*)DS)->EmployeeSalaryIncrease(employeeID, salaryIncrease);
    }
    catch (const std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
    catch ( const invalid_input &e){
        return INVALID_INPUT;
    }
    catch (const failure &e){
        return FAILURE;
    }
    catch (const already_in_hash &e){
        return FAILURE;
    }
    catch ( const already_in_tree &e){
        return FAILURE;
    }
    catch(const not_in_hash &e){
        return FAILURE;
    }
    catch(const not_in_tree &e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType PromoteEmployee(void *DS, int employeeID, int bumpGrade) {
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    try{
        ((Data*)DS)->PromoteEmployee(employeeID, bumpGrade);
    }
    catch (const std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
    catch ( const invalid_input &e){
        return INVALID_INPUT;
    }
    catch (const failure &e){
        return FAILURE;
    }
    catch (const already_in_hash &e){
        return FAILURE;
    }
    catch ( const already_in_tree &e){
        return FAILURE;
    }
    catch(const not_in_hash &e){
        return FAILURE;
    }
    catch(const not_in_tree &e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m){
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    long long sumBumpGrade;
    try{
        ((Data*)DS)->SumOfBumpGradeBetweenTopWorkersByGroup(companyID, m, &sumBumpGrade);
    }
    catch (const std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
    catch ( const invalid_input &e){
        return INVALID_INPUT;
    }
    catch (const failure &e){
        return FAILURE;
    }
    catch (const already_in_hash &e){
        return FAILURE;
    }
    catch ( const already_in_tree &e){
        return FAILURE;
    }
    catch(const not_in_hash &e){
        return FAILURE;
    }
    catch(const not_in_tree &e){
        return FAILURE;
    }
    printf("SumOfBumpGradeBetweenTopWorkersByGroup: %lld\n", sumBumpGrade);
    return SUCCESS;
}

StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary) {
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    double averageBumpGrade;
    try{
        ((Data*)DS)->AverageBumpGradeBetweenSalaryByGroup(companyID, lowerSalary, higherSalary, &averageBumpGrade);
    }
    catch (const std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
    catch ( const invalid_input &e){
        return INVALID_INPUT;
    }
    catch (const failure &e){
        return FAILURE;
    }
    catch (const already_in_hash &e){
        return FAILURE;
    }
    catch ( const already_in_tree &e){
        return FAILURE;
    }
    catch(const not_in_hash &e){
        return FAILURE;
    }
    catch(const not_in_tree &e){
        return FAILURE;
    }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", floor(10 * averageBumpGrade + 0.5f) / 10);

    printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", averageBumpGrade);
    return SUCCESS;
}

StatusType CompanyValue(void *DS, int companyID){
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    double standing;
    try{
        ((Data*)DS)->CompanyValue(companyID, &standing);
    }
    catch (const std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
    catch ( const invalid_input &e){
        return INVALID_INPUT;
    }
    catch (const failure &e){
        return FAILURE;
    }
    catch (const already_in_hash &e){
        return FAILURE;
    }
    catch ( const already_in_tree &e){
        return FAILURE;
    }
    catch(const not_in_hash &e){
        return FAILURE;
    }
    catch(const not_in_tree &e){
        return FAILURE;
    }

    printf("CompanyValue: %.1f\n", standing);
    return SUCCESS;
}

void Quit(void** DS){
    void** temp = DS;
    Data* n_temp= static_cast<Data*>(*temp);
    delete n_temp;
    *DS = NULL;
}