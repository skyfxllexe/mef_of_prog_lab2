/**
 * \file
 * \brief main
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <map>


#include "employee.hpp"

#include "node.hpp"
#include "bin_tree.hpp"
#include "rbtree.hpp"
#include "tablehash.hpp"


/**
 * \brief Linear search function
 * \param[in] a Array for search
 * \param[in] start Start index for search
 * \param[in] size Size of an array
 * \param[in] key Element key to find in array
 * \return Index of element with key
 */
template<class T>
int linear_search(T a[], long start, long size, std::string key) {
  for(int i = start; i < size; i++) {
    if(a[i].key == key) return i;
  }
  return -1;
}




Employee* employees;

int main() {
    std::ifstream inputFile;
    inputFile.open("data.txt");

    int n;
    std::string line;
    if(std::getline(inputFile, line)) {
        n = std::stoi(line);
    }

    employees = new Employee[n];
    int ii = 0;
    while(std::getline(inputFile, line)){
        std::istringstream iss(line);
        std::string params[5];
        for(int j = 0; j < 5; j++){
            if(!(iss >> params[j])) {
                std::cout << "гг" << std::endl;
            }
        }
        employees[ii].key = params[0];
        employees[ii].employee_name = params[1] + ' ' + params[2];
        employees[ii].salary = std::stoi(params[3]);
        employees[ii].subdivision = params[4];
        ii++;
    }
    inputFile.close();
    std::string to_find = "saccomyine";
    
    //linear search
    std::ofstream outputFile_time_linear("times_linear.csv", std::ios::trunc);
    
    for(int i = 100; i < n; i += (n-100)/50) {
        auto start = std::chrono::steady_clock::now(); 
        int j = linear_search(employees, 0, i, to_find);
        while(j != -1) {
            j = linear_search(employees, j+1, i, to_find);
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        outputFile_time_linear << i << "," << elapsed.count() << std::endl;
    }
    outputFile_time_linear.close();
    
    
    //binary tree
    std::ofstream outputFile_time_binary("times_binary.csv", std::ios::trunc);
    
    BinTree<Employee> bintree;
    int k = 0;
    for(int i = 100; i < n; i += (n-100)/50) {
        for(int j = k; j < i; j++) {
            bintree.insert(employees[j]);
        }
        k = i;
        auto start = std::chrono::steady_clock::now(); 
        std::vector<Employee> ans = bintree.find(to_find);
        auto end = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> elapsed = end - start;
        outputFile_time_binary << i << "," << elapsed.count() << std::endl;
    }
    outputFile_time_binary.close();
    
    
    //rb tree
    std::ofstream outputFile_time_rbtree("times_rbtree.csv", std::ios::trunc);
    
    RBTree<Employee> rbtree;
    k = 0;
    for(int i = 100; i < n; i += (n-100)/50) {
        for(int j = k; k < i; k++) {
            rbtree.insert(employees[k]);
        }
        k=i;
        
        auto start = std::chrono::steady_clock::now(); 
        std::vector<Employee>* ans = rbtree.find_object(to_find);
        auto end = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> elapsed = end - start;
        outputFile_time_rbtree << i << "," << elapsed.count() << std::endl;
    }
    outputFile_time_rbtree.close();
    
    
    
    
    //hash table
    std::ofstream outputFile_time_hash("times_hash.csv", std::ios::trunc);
    for(int i = 100; i < n; i += (n-100)/50) {
        TableHash<Employee> set;
        for(int j = 0; j < i; j++) {
            set.add(employees[j]);
        }
        auto start = std::chrono::steady_clock::now(); 
        std::vector<Employee>* ans = set.find(to_find);
        auto end = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> elapsed = end - start;
        outputFile_time_hash << i << "," << elapsed.count() << std::endl;
    }
    outputFile_time_hash.close();
    
    
    
    // multimap
    std::ofstream outputFile_time_multimap("times_multimap.csv", std::ios::trunc);
    
    std::multimap<std::string, Employee> mmap;
    k = 0;
    for(int i = 100; i < n; i += (n - 100) / 50) {
        for(int j = k; j < i; j++) {
            mmap.insert({employees[j].key, employees[j]});
        }
        k = i;
        
        auto start = std::chrono::steady_clock::now();
        auto range = mmap.equal_range(to_find);
        std::vector<Employee> mmap_results;
        for (auto it = range.first; it != range.second; ++it) {
            mmap_results.push_back(it->second);
        }
        auto end = std::chrono::steady_clock::now();
        
        std::chrono::duration<double> elapsed = end - start;
        outputFile_time_multimap << i << "," << elapsed.count() << std::endl;
    }
    
    outputFile_time_multimap.close();
    
    delete[] employees;
    return 0;
}