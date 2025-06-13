/**
* \file
* \brief File with implementation of Employee class methods
*/

#include <string>
#include "employee.hpp"


Employee::Employee(std::string org, std::string employee, int salaryi) : key(org), employee_name(employee), salary(salaryi) {}
Employee::Employee(){};

bool Employee::operator>(Employee &other){
    if((*this).key + (*this).employee_name + (*this).subdivision + std::to_string((*this).salary) > other.key + other.employee_name + std::to_string(other.salary)){
        return 1;
    } 
    return 0;
}

bool Employee::operator<(Employee &other){
    if((*this).key + (*this).employee_name+ (*this).subdivision + std::to_string((*this).salary) < other.key + other.employee_name + std::to_string(other.salary)){
        return 1;
    } 
    return 0;
}

bool Employee::operator<=(Employee &other){
    if(!(*this > other)){
        return 1;
    } 
    return 0;
}

bool Employee::operator>=(Employee &other){
    if(!(*this < other)){
        return 1;
    } 
    return 0;
}

bool Employee::operator==(Employee &other){
    if((*this <= other) & (*this >= other)){
        return 1;
    } 
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Employee& employee) {
    os << employee.key + ' ' + employee.employee_name + ' ' + employee.subdivision + ' ' + std::to_string(employee.salary);
    return os;
}