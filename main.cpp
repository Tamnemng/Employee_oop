#include <iostream>

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
        in >> date.day >> date.month >> date.year;
        return in;
    }

    int operator-(const Date& date) const {
        float delta_years = float(this->year - 1) - float(date.year);
        delta_years *= 365.25; // average number of days in a year including leap years
        float delta_months = float(12 - date.month) + float(this->month);
        delta_months *= 365.25 / 12; // average number of days in a month
        float delta_days = float(this->day) - float(date.day);
        return int(delta_years + delta_months + delta_days);
    }
};

class Employee {
private:
    std::string _name;
    Date _birth_date;
    Date _hire_date;
    std::string _role;
    int _salary;

public:
    Employee(std::string name, Date birth_date, Date hire_date, std::string role, int salary) {
        this->_name = name;
        this->_birth_date = birth_date;
        this->_hire_date = hire_date;
        this->_role = role;
        this->_salary = salary;
    }

    ~Employee() = default;

    void set_name(std::string name) {
        this->_name = name;
    }

    std::string get_name() const {
        return this->_name;
    }

    void set_birth_date(Date birth_date) {
        this->_birth_date = birth_date;
    }

    Date get_birth_date() const {
        return this->_birth_date;
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
        out << "Birth date: " << employee._birth_date << "\n";
        out << "Hire date: " << employee._hire_date << "\n";
        out << "Role: " << employee._role << "\n";
        out << "Salary: " << employee._salary << "k\n";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Employee& employee) {
        in >> employee._name >> employee._birth_date >> employee._hire_date >> employee._role >> employee._salary;
        return in;
    }
};

class PartTimeEmployee : public Employee {
private:
    int _items_sold;

public:
    PartTimeEmployee(std::string name, Date birth_date, Date hire_date, std::string role, int salary, int items_sold) : Employee(name, birth_date, hire_date, role, salary) {
        this->_items_sold = items_sold;
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
        out << "Birth date: " << employee.get_birth_date() << "\n";
        out << "Hire date: " << employee.get_hire_date() << "\n";
        out << "Role: " << employee.get_role() << "\n";
        out << "Salary: " << employee.get_salary() << "k\n";
        out << "Items sold: " << employee._items_sold << "\n";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, PartTimeEmployee& employee) {
        std::string name;
        Date birth_date;
        Date hire_date;
        std::string role;
        int salary;
        int items_sold;
        in >> name >> birth_date >> hire_date >> role >> salary >> items_sold;

        employee.set_name(name);
        employee.set_birth_date(birth_date);
        employee.set_hire_date(hire_date);
        employee.set_role(role);
        employee.set_salary(salary);
        employee.set_items_sold(items_sold);
        return in;
    }
};

class FullTimeEmployee : public Employee {
private:
    std::string _full_time_role;
    int _bonus = 0;

public:
    FullTimeEmployee(std::string name, Date birth_date, Date hire_date, std::string role, int salary, std::string full_time_role) : Employee(name, birth_date, hire_date, role, salary) {
        this->_full_time_role = full_time_role;
    }

    ~FullTimeEmployee() = default;

    void set_full_time_role(std::string full_time_role) {
        this->_full_time_role = full_time_role;
    }

    std::string get_full_time_role() const {
        return this->_full_time_role;
    }

    int get_bonus() const {
        return this->_bonus;
    }

    int get_salary() const override {
        float multiplier = 1;
        if (this->_full_time_role == "Employer") {
            multiplier = 1.2;
        } else if (this->_full_time_role == "Store Manager") {
            multiplier = 1.5;
        } else if (this->_full_time_role == "Director") {
            multiplier = 2;
        }
        return int(float(Employee::get_salary()) * multiplier) + this->_bonus;
    }

    friend std::ostream& operator<<(std::ostream& out, const FullTimeEmployee& employee) {
        out << "Name: " << employee.get_name() << "\n";
        out << "Birth date: " << employee.get_birth_date() << "\n";
        out << "Hire date: " << employee.get_hire_date() << "\n";
        out << "Role: " << employee.get_role() << "\n";
        out << "Salary: " << employee.get_salary() << "k\n";
        out << "Full time role: " << employee._full_time_role << "\n";
        out << "Bonus: " << employee._bonus << "\n";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, FullTimeEmployee& employee) {
        std::string name;
        Date birth_date;
        Date hire_date;
        std::string role;
        int salary;
        std::string full_time_role;
        in >> name >> birth_date >> hire_date >> role >> salary >> full_time_role;

        employee.set_name(name);
        employee.set_birth_date(birth_date);
        employee.set_hire_date(hire_date);
        employee.set_role(role);
        employee.set_salary(salary);
        employee.set_full_time_role(full_time_role);
        return in;
    }
};



int main() {
    // employee test
    Employee employee("John Doe", Date(1, 1, 2000), Date(1, 1, 2020), "Software Engineer", 1000);
    std::cout << employee << std::endl;

    // part-time employee test
    PartTimeEmployee part_time_employee("Jane Doe", Date(1, 1, 2000), Date(1, 1, 2020), "Software Engineer", 1000, 15);
    std::cout << part_time_employee << std::endl;

    // full-time employee test
    FullTimeEmployee full_time_employee("Alice Doe", Date(1, 1, 2000), Date(1, 1, 2020), "Software Engineer", 1000, "Employer");
    std::cout << full_time_employee << std::endl;
}
