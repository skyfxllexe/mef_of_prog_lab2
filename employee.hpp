class Employee {
public:
    Employee(std::string, std::string, int);
    Employee();
    std::string key;
    std::string employee_name;
    std::string subdivision;
    int salary;
    bool operator>(Employee &other);
    bool operator<(Employee &other);
    bool operator>=(Employee &other);
    bool operator<=(Employee &other);
    bool operator==(Employee &other);
    friend std::ostream& operator<<(std::ostream& os, const Employee& person);
};


