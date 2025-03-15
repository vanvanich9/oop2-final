#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#define for_with_pointer(var, vec) for (auto *ptr : vec) auto &var = *ptr;

using namespace std;

enum GradeEnum { JUNIOR, MIDDLE, SENIOR, LEAD };

class Person;
class Candidate;
class Developer;
class Director;
class Company;

class Person {
public:
    string first_name;
    string last_name;
    int birth_day;
    int birth_month;
    int birth_year;
    Company *company;

    Person(string first_name, string last_name, int birth_day, int birth_month, int birth_year) {
        this->first_name = first_name;
        this->last_name = last_name;
        this->birth_day = birth_day;
        this->birth_month = birth_month;
        this->birth_year = birth_year;
    }

    virtual void person_information() {}
};

class Candidate : public Person {
public:
    GradeEnum grade;

    Candidate(string first_name, string last_name, int birth_day, int birth_month, int birth_year, GradeEnum grade)
        : Person(first_name, last_name, birth_day, birth_month, birth_year) {
        this->grade = grade;
    }

    void person_information() {
        cout << "Candidate: " << this->first_name << " " << this->last_name << "." << endl;
        cout << "Date of birth: " << this->birth_day << "." << this->birth_month << "." << this->birth_year << "." << endl;
        string grade;
        switch(this->grade) {
            case GradeEnum::JUNIOR:
                grade = "Junior";
                break;
            case GradeEnum::MIDDLE:
                grade = "Middle";
                break;
            case GradeEnum::SENIOR:
                grade = "Senior";
                break;
            case GradeEnum::LEAD:
                grade = "Lead";
                break;
            default:
                grade = "N/D";
        }
        cout << "Candidate grade: " << grade << " developer." << endl;
    }
};


class Developer : public Person {
public:
    GradeEnum grade;

    Developer(string first_name, string last_name, int birth_day, int birth_month, int birth_year, GradeEnum grade)
        : Person(first_name, last_name, birth_day, birth_month, birth_year) {
        this->grade = grade;
    }

    void person_information() {
        cout << "Developer: " << this->first_name << " " << this->last_name << "." << endl;
        cout << "Date of birth: " << this->birth_day << "." << this->birth_month << "." << this->birth_year << "." << endl;
        string grade;
        switch(this->grade) {
            case GradeEnum::JUNIOR:
                grade = "Junior";
                break;
            case GradeEnum::MIDDLE:
                grade = "Middle";
                break;
            case GradeEnum::SENIOR:
                grade = "Senior";
                break;
            case GradeEnum::LEAD:
                grade = "Lead";
                break;
            default:
                grade = "N/D";
        }
        cout << "Developer grade: " << grade << " developer." << endl;
    }
};

class HR : public Person {
public:
    HR(string first_name, string last_name, int birth_day, int birth_month, int birth_year)
        : Person(first_name, last_name, birth_day, birth_month, birth_year) {}

    void person_information() {
        cout << "HR manager: " << this->first_name << " " << this->last_name << "." << endl;
        cout << "Date of birth: " << this->birth_day << "." << this->birth_month << "." << this->birth_year << "." << endl;
    }

    vector <Candidate*> candidates;
    vector <Developer*> developers;

    void add_candidate(Candidate &candidate) {
        this->candidates.push_back(&candidate);
    }

    int get_candidates_number() {
        return this->candidates.size();
    }

    void add_developer(Developer &developer) {
        this->developers.push_back(&developer);
    }

    int get_developers_number() {
        return this->developers.size();
    }
};

class Company {
    private:
        string name;
        string description;
        Director* director;

        vector<HR*> managers;
        vector<Developer*> developers;

        Company(string name, string description, Director* director) {
            this->name = name;
            this->description = name;
            this->director = director;
        }

        void add_hr_manager(HR &manager) {
            this->managers.push_back(&manager);
        }

        void add_developer(Developer &developer) {
            this->developers.push_back(&developer);
        }

        friend class Director;
        friend void HR::add_hr_manager(HR &manager);
        friend void HR::add_developer(Developer &developer);
    public:
        string get_name() {
            return this->name;
        }
    };

class Director : public Person {
public:
    Director(string first_name, string last_name, int birth_day, int birth_month, int birth_year)
        : Person(first_name, last_name, birth_day, birth_month, birth_year) {}

    void person_information() {
        cout << "Director: " << this->first_name << " " << this->last_name << "." << endl;
        cout << "Date of birth: " << this->birth_day << "." << this->birth_month << "." << this->birth_year << "." << endl;
    }

    Company create_company(string name, string description = "") {
        return Company(name, description, this);
    }

    void change_company_name(Company &company, string new_name) {
        if(company.director == this) {
            company.name = new_name;
            company.description = new_description;
        } else {
            cout << "Not allowed!" << endl;
        }
    }

    void change_company_description(Company &company, string new_description) {
        if(company.director == this) {
            company.description = new_description;
        } else {
            cout << "Not allowed!" << endl;
        }
    }
};


int main() {
    HR manager("Ivan", "Kobets", 24, 12, 2003);
    Developer developer("Ivan", "Kobets", 25, 12, 2003);
    Director director("Ivan", "Kobets", 26, 12, 2003);
    Company company = director.create_company("Name", "Description");
    // Добавить что только granted hrы могут добавлять людей
    // manager.person_information();
    // manager.add_candidate(candidate);
    // cout << "-----" << endl;
    /*
    for(auto candidate : manager.candidates) {
        candidate->person_information();
        cout << "-----" << endl;
    }
    candidate.birth_day = 25;
    for(auto candidate : manager.candidates) {
        candidate->person_information();
        cout << "-----" << endl;
    }
    */
}
