#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#pragma ide diagnostic ignored "performance-unnecessary-value-param"

#include <iostream>
#include <sstream>

class Date {
public:

    int day;
    int month;
    int year;

    Date(int day, int month, int year) {
        if (month < 1 || month > 12) {
            throw std::invalid_argument("Month must be between 1 and 12");
        }
        if (month == 2 && day > 28) {
            throw std::invalid_argument("Day must be between 1 and 28");
        } else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            throw std::invalid_argument("Day must be between 1 and 30");
        } else if (day < 1 || day > 31) {
            throw std::invalid_argument("Day must be between 1 and 31");
        }
        if (year < 1900 || year > 2100) {
            throw std::invalid_argument("Year must be between 1900 and 2100");
        }
        this->day = day;
        this->month = month;
        this->year = year;
    }

    Date() {
        this->day = 1;
        this->month = 1;
        this->year = 1900;
    }

    ~Date() = default;

    friend std::ostream& operator<<(std::ostream& out, const Date& date) {
        out << date.day << "/" << date.month << "/" << date.year;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Date& date) {
        int day, month, year;
        in >> day >> month >> year;
        date = Date(day, month, year);
        return in;
    }

    int operator-(const Date& date) const {
        float delta_years = float(this->year - 1) - float(date.year);
        delta_years *= 365.25; // average number of days in a year including leap years
        float delta_months = float(12 - date.month) + float(this->month);
        delta_months *= 365.25 / 12; // average number of days in a month
        float delta_days = float(this->day) - float(date.day);
        std::cout << int(delta_years + delta_months + delta_days) << std::endl;
        return int(delta_years + delta_months + delta_days);
    }
};

class Employee {
private:
    std::string _name;
    Date _hire_date;
    std::string _role;
    int _salary;

public:
    Employee(std::string name, Date hire_date, std::string role, int salary) {
        this->_name = name;
        this->_hire_date = hire_date;
        this->_role = role;
        this->_salary = salary;
    }

    Employee() {
        this->_name = "John Doe";
        this->_hire_date = Date(1, 1, 2020);
        this->_role = "Retail Worker";
        this->_salary = 1000;
    }

    ~Employee() = default;

    void set_name(std::string name) {
        this->_name = name;
    }

    std::string get_name() const {
        return this->_name;
    }

    void set_hire_date(Date hire_date) {
        this->_hire_date = hire_date;
    }

    Date get_hire_date() const {
        return this->_hire_date;
    }

    void set_role(std::string role) {
        this->_role = role;
    }

    std::string get_role() const {
        return this->_role;
    }

    void set_salary(int salary) {
        this->_salary = salary;
    }

    virtual int get_salary() const {
        return this->_salary;
    }

    friend std::ostream& operator<<(std::ostream& out, const Employee& employee) {
        out << "Name: " << employee._name << "\n";
        out << "Hire date: " << employee._hire_date << "\n";
        out << "Role: " << employee._role << "\n";
        out << "Salary: " << employee._salary << "k";
        return out;
    }

    virtual void input() {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::getline(iss, this->_name);
        std::getline(std::cin, line);
        iss = std::istringstream(line);
        iss >> this->_hire_date;
        std::getline(std::cin, line);
        iss = std::istringstream(line);
        std::getline(iss, this->_role);
        std::getline(std::cin, line);
        iss = std::istringstream(line);
        iss >> this->_salary;
    }
};

class PartTimeEmployee : public Employee {
private:
    int _items_sold;

public:
    PartTimeEmployee(
        std::string name,
        Date hire_date,
        std::string role,
        int salary,
        int items_sold
    ) : Employee(name, hire_date, role, salary) {
        this->_items_sold = items_sold;
    }

    PartTimeEmployee() {
        this->_items_sold = 0;
    }

    ~PartTimeEmployee() = default;

    void set_items_sold(int items_sold) {
        this->_items_sold = items_sold;
    }

    int get_items_sold() const {
        return this->_items_sold;
    }

    int get_salary() const override {
        int item_price = 40;
        if (this->_items_sold < 10) {
            item_price = 20;
        } else if (this->_items_sold < 20) {
            item_price = 30;
        }
        return this->_items_sold * item_price + Employee::get_salary();
    }

    friend std::ostream& operator<<(std::ostream& out, const PartTimeEmployee& employee) {
        out << "Name: " << employee.get_name() << "\n";
        out << "Hire date: " << employee.get_hire_date() << "\n";
        out << "Role: " << employee.get_role() << "\n";
        out << "Salary: " << employee.get_salary() << "k\n";
        out << "Items sold: " << employee.get_items_sold();
        return out;
    }

    void input() override {
        Employee::input();
        std::cin >> this->_items_sold;
    }
};

class FullTimeEmployee : public Employee {
private:
    Date _salary_date;
    int _bonus = 0;

public:
    FullTimeEmployee(
        std::string name,
        Date hire_date,
        std::string role,
        int salary,
        Date salary_date
    ) : Employee(name, hire_date, role, salary) {
        this->_salary_date = salary_date;
    }

    FullTimeEmployee() {
        this->_salary_date = Date(1, 1, 2021);
    }

    ~FullTimeEmployee() = default;

    int get_bonus() {
        if (this->_salary_date.year - this->get_hire_date().year >= 10) {
            this->_bonus = 1000;
        } else if (this->_salary_date.year - this->get_hire_date().year >= 1) {
            this->_bonus = 100;
        }
        return this->_bonus;
    }

    Date get_salary_date() const {
        return this->_salary_date;
    }

    int get_salary() {
        float multiplier = 1;
        if (this->get_role() == "Employer") {
            multiplier = 1.2;
        } else if (this->get_role() == "Store Manager") {
            multiplier = 1.5;
        } else if (this->get_role() == "Director") {
            multiplier = 2;
        }
        return int(float(Employee::get_salary()) * multiplier) + this->get_bonus();
    }

    friend std::ostream& operator<<(std::ostream& out, FullTimeEmployee employee) {
        out << "Name: " << employee.get_name() << "\n";
        out << "Hire date: " << employee.get_hire_date() << "\n";
        out << "Role: " << employee.get_role() << "\n";
        out << "Salary: " << employee.get_salary() << "k\n";
        out << "Bonus: " << employee._bonus << "\n";
        out << "Salary date: " << employee.get_salary_date();
        return out;
    }

    void input() override {
        Employee::input();
        std::string line;
        std::istringstream iss(line);
        std::getline(std::cin, line);
        iss = std::istringstream(line);
        iss >> this->_salary_date;
    }

};


int main() {
    std::string employee_type;
    std::cin >> employee_type;
    std::cin.ignore();

    if (employee_type == "PartTimeEmployee") {
        PartTimeEmployee employee;
        employee.input();
        std::cout << employee << std::endl;
    } else if (employee_type == "FullTimeEmployee") {
        FullTimeEmployee employee;
        employee.input();
        std::cout << employee << std::endl;
    } else {
        Employee employee;
        employee.input();
        std::cout << employee << std::endl;
    }
}

#pragma clang diagnostic pop