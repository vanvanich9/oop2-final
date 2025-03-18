#include <iostream>
#include <string>
#include <vector>
#include "exceptions.cpp"

using namespace std;

class Person;
class Candidate;
class Director;
class HR;
class Developer;
class Company;
class CompanyEmployers;

class Person {
private:
    virtual void add_to_database();
    virtual void remove_from_database();
public:
    string first_name;
    string last_name;
    Company *company;

    Person(string first_name, string last_name);

    virtual void person_information();
    bool operator==(const Person &person);
};

class Candidate : public Person {
private:
    HR* manager;

    bool is_hr_manager(HR *manager);
    void set_hr_manager(HR* manager);

    void add_to_database() override;
    void remove_from_database() override;

    friend class HR;
public:
    Candidate(string first_name, string last_name);
    ~Candidate();

    void person_information();
    bool have_hr_manager();
    HR get_manager();
};

class Developer : public Person {
private:
    Developer(string first_name, string last_name, Company* company);
    Developer(Candidate* candidate, Company* company);
    ~Developer();

    void add_to_database();
    void remove_from_database();

    friend class HR;
    friend class Director;
public:
    Company* company;

    void person_information();
};

class HR : public Person {
private:
    CompanyEmployers* company_employers;
    vector<Candidate*> candidates;

    void add_to_database();
    void remove_from_database();

    int get_candidate_index(Candidate* candidate);
public:
    Company* company;

    HR(string first_name, string last_name, Company* company);
    HR(Candidate* candidate, Company* company);
    ~HR();

    void person_information();
    void add_candidate(Candidate* candidate);
    void remove_candidate(Candidate* candidate);
    HR* hire_hr_manager(Candidate* candidate);
    Developer* hire_developer(Candidate* candidate);
};

class CompanyEmployers {
    private:
        Company* company;
        vector<HR*> managers;
        vector<Developer*> developers;

        CompanyEmployers(Company* company);

        int get_person_index(HR* manager);
        void add_person(HR* manager);
        void remove_person(HR* manager);
        int get_person_index(Developer* developer);
        void add_person(Developer* developer);
        void remove_person(Developer* developer);
        bool is_company_hr(HR* manager);

        friend class Company;
        friend class Director;
        friend class HR;
};

class Company {
    private:
        string name;
        string description;
        Director* director;
        CompanyEmployers* employers;

        void add_to_database();
        void remove_from_database();

        Company(string name, string description, Director* director);
        ~Company();

        bool is_company_director(Director* director);

        friend class Director;
    public:
        string get_name();
        string get_description();
        string get_director_first_name();
        string get_director_last_name();
        CompanyEmployers* get_employers();

        bool operator==(const Company &company);
};

class Director : public Person {
private:
    void add_to_database();
    void remove_from_database();
public:
    Director(string first_name, string last_name);
    ~Director();

    void person_information();
    Company* create_company(string name);
    Company* create_company(string name, string description);
    void change_company_name(Company* company, string new_name);
    void change_company_description(Company* company, string new_description);
    HR* add_company_manager(Company* company, Candidate* candidate);
    Developer* add_company_developer(Company* company, Candidate* candidate);
};

Person::Person(string first_name, string last_name) {
    this->first_name = first_name;
    this->last_name = last_name;
}

void Person::person_information() {}

bool Person::operator==(const Person &person) {
    return this->first_name == person.first_name && this->last_name == person.last_name;
}

Candidate::Candidate(string first_name, string last_name)
    : Person(first_name, last_name) {
    add_to_database();
}

Candidate::~Candidate() {
    remove_from_database();
}

void Candidate::person_information() {
    cout << "Candidate: " << this->first_name << " " << this->last_name << "." << endl;
}

bool Candidate::have_hr_manager() {
    return this->manager != nullptr;
}

bool Candidate::is_hr_manager(HR *manager) {
    return *this->manager == *manager;
}

void Candidate::set_hr_manager(HR* manager) {
    this->manager = manager;
}

HR Candidate::get_manager() {
    return *this->manager;
}

Developer::Developer(string first_name, string last_name, Company* company)
    : Person(first_name, last_name) {
    this->company = company;
    add_to_database();
}

Developer::Developer(Candidate* candidate, Company* company)
    : Person(candidate->first_name, candidate->last_name) {
    this->company = company;
    add_to_database();
}

Developer::~Developer() {
    remove_from_database();
}

void Developer::person_information() {
    cout << "Developer: " << this->first_name << " " << this->last_name << "." << endl;
}

HR::HR(string first_name, string last_name, Company* company)
    : Person(first_name, last_name) {
    this->company = company;
    this->company_employers = company->get_employers();
    add_to_database();
}

HR::HR(Candidate* candidate, Company* company)
    : Person(candidate->first_name, candidate->last_name) {
    this->company = company;
    this->company_employers = company->get_employers();
    add_to_database();
}

HR::~HR() {
    remove_from_database();
}

void HR::person_information() {
    cout << "HR manager: " << this->first_name << " " << this->last_name << "." << endl;
}

int HR::get_candidate_index(Candidate* candidate) {
    int i = 0;
    for(auto manager_candidate : this->candidates) {
        if(*manager_candidate == *candidate) {
            return i;
        }
        i++;
    }
    return -1; // return -1 if not found
}

void HR::add_candidate(Candidate* candidate) {
    if(!candidate->have_hr_manager()) {
        candidate->set_hr_manager(this);
        this->candidates.push_back(candidate);
    } else {
        throw PermissionError();
    }
}

void HR::remove_candidate(Candidate* candidate) {
    if(!candidate->is_hr_manager(this)) {
        candidate->set_hr_manager(nullptr);
        int index = get_candidate_index(candidate);
        this->candidates.erase(this->candidates.begin() + index);
    } else {
        throw PermissionError();
    }
}

HR* HR::hire_hr_manager(Candidate* candidate) {
    if(get_candidate_index(candidate) != -1 && this->company_employers->is_company_hr(this)) {
        HR* manager = new HR(candidate, this->company);
        this->company_employers->add_person(manager);
        delete candidate;
        return manager;
    } else {
        throw PermissionError();
    }
}

Developer* HR::hire_developer(Candidate* candidate) {
    if(get_candidate_index(candidate) != -1 && this->company_employers->is_company_hr(this)) {
        Developer* developer = new Developer(candidate, this->company);
        company_employers->add_person(developer);
        delete candidate;
        return developer;
    } else {
        throw PermissionError();
    }
}

CompanyEmployers::CompanyEmployers(Company* company) {
    this->company = company;
}

int CompanyEmployers::get_person_index(HR* manager) {
    int i = 0;
    for(auto company_manager : this->managers) {
        if(*company_manager == *manager) {
            return i;
        }
        i++;
    }
    return -1; // return -1 if not found
}

void CompanyEmployers::add_person(HR* manager) {
    if(get_person_index(manager) == -1) {
        this->managers.push_back(manager);
    } else {
        throw PersonExists();
    }
}

void CompanyEmployers::remove_person(HR* manager) {
    int index = get_person_index(manager);
    if(index > -1) {
        this->managers.erase(this->managers.begin() + index);
    } else {
        throw PersonExists();
    }
}

int CompanyEmployers::get_person_index(Developer* developer) {
    int i = 0;
    for(auto company_developer : this->developers) {
        if(*company_developer == *developer) {
            return i;
        }
        i++;
    }
    return -1; // return -1 if not found
}

void CompanyEmployers::add_person(Developer* developer) {
    if(get_person_index(developer) == -1) {
        this->developers.push_back(developer);
    } else {
        throw PersonExists();
    }
    this->developers.push_back(developer);
}

void CompanyEmployers::remove_person(Developer* developer) {
    int index = get_person_index(developer);
    if(index > -1) {
        this->developers.erase(this->developers.begin() + index);
    } else {
        throw PersonExists();
    }
}

bool CompanyEmployers::is_company_hr(HR* manager) {
    return get_person_index(manager) != -1;
}

Company::Company(string name, string description, Director* director) {
    this->name = name;
    this->description = description;
    this->director = director;
    this->employers = new CompanyEmployers(this);
    add_to_database();
}

Company::~Company() {
    remove_from_database();
}

bool Company::is_company_director(Director* director) {
    return *this->director == *director;
}

string Company::get_name() {
    return this->name;
}

string Company::get_description() {
    return this->description;
}

bool Company::operator==(const Company &company) {
    return this->name == company.name;
}

string Company::get_director_first_name() {
    return this->director->first_name;
}

string Company::get_director_last_name() {
    return this->director->last_name;
}

CompanyEmployers* Company::get_employers() {
    return this->employers;
}

Director::Director(string first_name, string last_name)
    : Person(first_name, last_name) {
    add_to_database();
}

Director::~Director() {
    remove_from_database();
}

void Director::person_information() {
    cout << "Director: " << this->first_name << " " << this->last_name << "." << endl;
}

Company* Director::create_company(string name) {
    return new Company(name, "", this);
}

Company* Director::create_company(string name, string description) {
    return new Company(name, description, this);
}

void Director::change_company_name(Company* company, string new_name) {
    if (company->is_company_director(this)) {
        company->name = new_name;
    } else {
        throw PermissionError();
    }
}

void Director::change_company_description(Company* company, string new_description) {
    if (company->is_company_director(this)) {
        company->description = new_description;
    } else {
        throw PermissionError();
    }
}

HR* Director::add_company_manager(Company* company, Candidate* candidate) {
    if (company->is_company_director(this)) {
        HR* manager = new HR(candidate, company);
        company->employers->add_person(manager);
        delete candidate;
        return manager;
    } else {
        throw PermissionError();
    }
}

Developer* Director::add_company_developer(Company* company, Candidate* candidate) {
    if (company->is_company_director(this)) {
        Developer* developer = new Developer(candidate, company);
        company->employers->add_person(developer);
        delete candidate;
        return developer;
    } else {
        throw PermissionError();
    }
}
