#pragma once

#define DATABASE_PATH "database.txt"

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <fstream>
#include <variant>
#include <vector>

#include "models.hpp"

using namespace std;

class CandidateDatabase {
    private:
        vector<Candidate*> candidates;
        bool is_candidate_exists(Candidate* candidate);
        int get_candidate_index(Candidate* candidate);
        void sort();

    public:
        CandidateDatabase();
        Candidate* get(string first_name, string last_name);
        vector<Candidate*> get_all();
        void add(Candidate* candidate);
        void remove(Candidate* candidate);
};

class HRDatabase {
    private:
        vector<HR*> managers;
        bool is_manager_exists(HR* manager);
        int get_manager_index(HR* manager);
        void sort();

    public:
        HRDatabase();
        HR* get(string first_name, string last_name);
        vector<HR*> get_all();
        void add(HR* manager);
        void remove(HR* manager);
};

class DeveloperDatabase {
    private:
        vector<Developer*> developers;
        bool is_developer_exists(Developer* developer);
        int get_developer_index(Developer* developer);
        void sort();

    public:
        DeveloperDatabase();
        Developer* get(string first_name, string last_name);
        vector<Developer*> get_all();
        void add(Developer* manager);
        void remove(Developer* manager);
};

class DirectorDatabase {
    private:
        vector<Director*> directors;
        bool is_director_exists(Director* director);
        int get_director_index(Director* director);
        void sort();

    public:
        DirectorDatabase();
        Director* get(string first_name, string last_name);
        vector<Director*> get_all();
        void add(Director* manager);
        void remove(Director* manager);
};

class CompanyDatabase {
    private:
        vector<Company*> companies;
        bool is_company_exists(Company* company);
        int get_company_index(Company* company);
        void sort();

    public:
        CompanyDatabase();
        Company* get(string name);
        vector<Company*> get_all();
        void add(Company* manager);
        void remove(Company* manager);
};

CandidateDatabase::CandidateDatabase() {}

Candidate* CandidateDatabase::get(string first_name, string last_name) {
    for(auto database_candidate : this->candidates) {
        if(database_candidate->first_name == first_name && database_candidate->last_name == last_name) {
            return database_candidate;
        }
    }
    throw NotFound();
}

vector<Candidate*> CandidateDatabase::get_all() {
    return this->candidates;
}

void CandidateDatabase::add(Candidate* candidate) {
    if(is_candidate_exists(candidate)) {
        throw PersonCompanyExists();
    }
    this->candidates.push_back(candidate);
    sort();
}

void CandidateDatabase::remove(Candidate* candidate) {
    if(!is_candidate_exists(candidate)) {
        throw NotFound();
    }
    int i = get_candidate_index(candidate);
    this->candidates.erase(this->candidates.begin() + i);
}

void CandidateDatabase::sort() {
    stable_sort(this->candidates.begin(), this->candidates.end(), PersonComparator());
}

bool CandidateDatabase::is_candidate_exists(Candidate* candidate) {
    return binary_search(this->candidates.begin(), this->candidates.end(), candidate, PersonComparator());
}

int CandidateDatabase::get_candidate_index(Candidate* candidate) {
    return lower_bound(this->candidates.begin(), this->candidates.end(), candidate, PersonComparator()) - this->candidates.begin();
}

HRDatabase::HRDatabase() {}

HR* HRDatabase::get(string first_name, string last_name) {
    for(auto database_manager : this->managers) {
        if(database_manager->first_name == first_name && database_manager->last_name == last_name) {
            return database_manager;
        }
    }
    throw NotFound();
}

vector<HR*> HRDatabase::get_all() {
    return this->managers;
}

void HRDatabase::add(HR* manager) {
    if(is_manager_exists(manager)) {
        throw PersonCompanyExists();
    }
    this->managers.push_back(manager);
    sort();
}

void HRDatabase::remove(HR* manager) {
    if(!is_manager_exists(manager)) {
        throw NotFound();
    }
    int i = get_manager_index(manager);
    this->managers.erase(this->managers.begin() + i);
}

void HRDatabase::sort() {
    stable_sort(this->managers.begin(), this->managers.end(), PersonComparator());
}

bool HRDatabase::is_manager_exists(HR* manager) {
    return binary_search(this->managers.begin(), this->managers.end(), manager, PersonComparator());
}

int HRDatabase::get_manager_index(HR* manager) {
    return lower_bound(this->managers.begin(), this->managers.end(), manager, PersonComparator()) - this->managers.begin();
}

DeveloperDatabase::DeveloperDatabase() {}

Developer* DeveloperDatabase::get(string first_name, string last_name) {
    for(auto database_developer : this->developers) {
        if(database_developer->first_name == first_name && database_developer->last_name == last_name) {
            return database_developer;
        }
    }
    throw NotFound();
}

vector<Developer*> DeveloperDatabase::get_all() {
    return this->developers;
}

void DeveloperDatabase::add(Developer* developer) {
    if(is_developer_exists(developer)) {
        throw PersonCompanyExists();
    }
    this->developers.push_back(developer);
    sort();
}

void DeveloperDatabase::remove(Developer* developer) {
    if(!is_developer_exists(developer)) {
        throw NotFound();
    }
    int i = get_developer_index(developer);
    this->developers.erase(this->developers.begin() + i);
}

void DeveloperDatabase::sort() {
    stable_sort(this->developers.begin(), this->developers.end(), PersonComparator());
}

bool DeveloperDatabase::is_developer_exists(Developer* developer) {
    return binary_search(this->developers.begin(), this->developers.end(), developer, PersonComparator());
}

int DeveloperDatabase::get_developer_index(Developer* developer) {
    return lower_bound(this->developers.begin(), this->developers.end(), developer, PersonComparator()) - this->developers.begin();
}

DirectorDatabase::DirectorDatabase() {}

Director* DirectorDatabase::get(string first_name, string last_name) {
    for(auto database_director : this->directors) {
        if(database_director->first_name == first_name && database_director->last_name == last_name) {
            return database_director;
        }
    }
    throw NotFound();
}

vector<Director*> DirectorDatabase::get_all() {
    return this->directors;
}

void DirectorDatabase::add(Director* director) {
    if(is_director_exists(director)) {
        throw PersonCompanyExists();
    }
    this->directors.push_back(director);
    sort();
}

void DirectorDatabase::remove(Director* director) {
    if(!is_director_exists(director)) {
        throw NotFound();
    }
    int i = get_director_index(director);
    this->directors.erase(this->directors.begin() + i);
}

void DirectorDatabase::sort() {
    stable_sort(this->directors.begin(), this->directors.end(), PersonComparator());
}

bool DirectorDatabase::is_director_exists(Director* director) {
    return binary_search(this->directors.begin(), this->directors.end(), director, PersonComparator());
}

int DirectorDatabase::get_director_index(Director* director) {
    return lower_bound(this->directors.begin(), this->directors.end(), director, PersonComparator()) - this->directors.begin();
}

CompanyDatabase::CompanyDatabase() {}

Company* CompanyDatabase::get(string name) {
    for(auto database_company : this->companies) {
        if(database_company->get_name() == name) {
            return database_company;
        }
    }
    throw NotFound();
}

vector<Company*> CompanyDatabase::get_all() {
    return this->companies;
}

void CompanyDatabase::add(Company* company) {
    if(is_company_exists(company)) {
        throw PersonCompanyExists();
    }
    this->companies.push_back(company);
    sort();
}

void CompanyDatabase::remove(Company* company) {
    if(!is_company_exists(company)) {
        throw NotFound();
    }
    int i = get_company_index(company);
    this->companies.erase(this->companies.begin() + i);
}

void CompanyDatabase::sort() {
    stable_sort(this->companies.begin(), this->companies.end(), CompanyComparator());
}

bool CompanyDatabase::is_company_exists(Company* company) {
    return binary_search(this->companies.begin(), this->companies.end(), company, CompanyComparator());
}

int CompanyDatabase::get_company_index(Company* company) {
    return lower_bound(this->companies.begin(), this->companies.end(), company, CompanyComparator()) - this->companies.begin();
}

CandidateDatabase candidate_database;
HRDatabase hr_database;
DeveloperDatabase developer_database;
DirectorDatabase director_database;
CompanyDatabase company_database;

void Person::remove_from_database() {}
void Candidate::add_to_database() {
    candidate_database.add(this);
}
void Candidate::remove_from_database() {
    candidate_database.remove(this);
}
void Developer::add_to_database() {
    developer_database.add(this);
}
void Developer::remove_from_database() {
    developer_database.remove(this);
}
void HR::add_to_database() {
    hr_database.add(this);
}
void HR::remove_from_database() {
    hr_database.remove(this);
}
void Company::add_to_database() {
    company_database.add(this);
}
void Company::remove_from_database() {
    company_database.remove(this);
}
void Director::add_to_database() {
    director_database.add(this);
}
void Director::remove_from_database() {
    director_database.remove(this);
}

vector<string> split(string s) {
    string cur;
    vector<string> res;
    for(auto symb : s) {
        if(symb == ':' || symb == '=') {
            res.push_back(cur);
            cur = "";
        } else {
            cur += symb;
        }
    }
    res.push_back(cur);
    return res;
}

void init_database() {
    cout << "Database init..." << endl;
    ifstream database_file(DATABASE_PATH);
    vector<string> database_text;
    string line;
    while (getline (database_file, line)) {
        database_text.push_back(line);
    }
    database_file.close();

    vector<string> candidates;
    vector<string> developers;
    vector<string> managers;
    vector<string> directors;
    vector<string> companies;
    for(string text : database_text) {
        string prefix;
        bool is_candidates_prefix = false;
        bool is_developers_prefix = false;
        bool is_managers_prefix = false;
        bool is_directors_prefix = false;
        bool is_companies_prefix = false;
        for(auto i : text) {
            prefix += i;
            if(prefix == "candidates:") {
                is_candidates_prefix = true;
                break;
            }
            if(prefix == "developers:") {
                is_developers_prefix = true;
                break;
            }
            if(prefix == "managers:") {
                is_managers_prefix = true;
                break;
            }
            if(prefix == "directors:") {
                is_directors_prefix = true;
                break;
            }
            if(prefix == "companies:") {
                is_companies_prefix = true;
                break;
            }
        }
        if(is_candidates_prefix) {
            candidates.push_back(text);
        }
        if(is_developers_prefix) {
            developers.push_back(text);
        }
        if(is_managers_prefix) {
            managers.push_back(text);
        }
        if(is_directors_prefix) {
            directors.push_back(text);
        }
        if(is_companies_prefix) {
            companies.push_back(text);
        }
    }

    // Directors
    if(directors.size()) {
        string director_first_name;
        string director_last_name;
        string director_prev_index = "[0]";
        for(auto text : directors) {
            vector<string> data = split(text);
            if(data[1] != director_prev_index) {
                Director* director = new Director(director_first_name, director_last_name);
                director_first_name = "";
                director_last_name = "";
            } 
            if(data[2] == "first_name") {
                director_first_name = data[3];
            }
            if(data[2] == "last_name") {
                director_last_name = data[3];
            }
            director_prev_index = data[1];
        }
        Director* director = new Director(director_first_name, director_last_name);
        cout << "Directors:" << endl;
        for(auto director : director_database.get_all()) {
            cout << "- ";
            director->person_information();
        }
    }

    // Companies
    map<string, pair<string, string> > company_director;
    if(companies.size()) {
        string company_name;
        string company_description = "";
        string company_director_first_name;
        string company_director_last_name;
        string company_prev_index = "[0]";
        for(auto text : companies) {
            vector<string> data = split(text);
            if(data[1] != company_prev_index) {
                Director* director = director_database.get(company_director_first_name, company_director_last_name);
                Company* company = director->create_company(company_name, company_description);
                company_director[company_name] = make_pair(company_director_first_name, company_director_last_name);
                company_name = "";
                company_description = "";
                company_director_first_name = "";
                company_director_last_name = "";
            }
            if(data[2] == "name") {
                company_name = data[3];
            }
            if(data[2] == "description") {
                company_description = data[3];
            }
            if(data[2] == "director") {
                if(data[3] == "first_name") {
                    company_director_first_name = data[4];
                }
                if(data[3] == "last_name") {
                    company_director_last_name = data[4];
                }
            }
            company_prev_index = data[1];
        }
        Director* director = director_database.get(company_director_first_name, company_director_last_name);
        Company* company = director->create_company(company_name, company_description);
        company_director[company_name] = make_pair(company_director_first_name, company_director_last_name);
        cout << "Companies:" << endl;
        for(auto company : company_database.get_all()) {
            cout << "- " << company->get_name() << endl;
        }
    }

    // Developers
    if(developers.size()) {
        string developer_first_name;
        string developer_last_name;
        string developer_company_name;
        string developer_prev_index = "[0]";
        for(auto text : developers) {
            vector<string> data = split(text);
            if(data[1] != developer_prev_index) {
                Company* company = company_database.get(developer_company_name);
                pair<string, string> director_first_and_last_names = company_director[developer_company_name];
                Director* director = director_database.get(director_first_and_last_names.first, director_first_and_last_names.second);
                Candidate* developer_candidate = new Candidate(developer_first_name, developer_last_name);
                Developer* developer = director->add_company_developer(company, developer_candidate);
                developer_first_name = "";
                developer_last_name = "";
                developer_company_name = "";
            }
            if(data[2] == "first_name") {
                developer_first_name = data[3];
            }
            if(data[2] == "last_name") {
                developer_last_name = data[3];
            }
            if(data[2] == "company") {
                developer_company_name = data[3];
            }
            developer_prev_index = data[1];
        }
        Company* company = company_database.get(developer_company_name);
        pair<string, string> director_first_and_last_names = company_director[developer_company_name];
        Director* director = director_database.get(director_first_and_last_names.first, director_first_and_last_names.second);
        Candidate* developer_candidate = new Candidate(developer_first_name, developer_last_name);
        Developer* developer = director->add_company_developer(company, developer_candidate);
        cout << "Developers:" << endl;
        for(auto developer : developer_database.get_all()) {
            cout << "- ";
            developer->person_information();
        }
    }

    // Managers
    if(managers.size()) {
        string manager_first_name;
        string manager_last_name;
        string manager_company_name;
        string manager_prev_index = "[0]";
        for(auto text : managers) {
            vector<string> data = split(text);
            if(data[1] != manager_prev_index) {
                Company* company = company_database.get(manager_company_name);
                pair<string, string> director_first_and_last_names = company_director[manager_company_name];
                Director* director = director_database.get(director_first_and_last_names.first, director_first_and_last_names.second);
                Candidate* manager_candidate = new Candidate(manager_first_name, manager_last_name);
                HR* manager = director->add_company_manager(company, manager_candidate);
                manager_first_name = "";
                manager_last_name = "";
                manager_company_name = "";
            }
            if(data[2] == "first_name") {
                manager_first_name = data[3];
            }
            if(data[2] == "last_name") {
                manager_last_name = data[3];
            }
            if(data[2] == "company") {
                manager_company_name = data[3];
            }
            manager_prev_index = data[1];
        }
        Company* company = company_database.get(manager_company_name);
        pair<string, string> director_first_and_last_names = company_director[manager_company_name];
        Director* director = director_database.get(director_first_and_last_names.first, director_first_and_last_names.second);
        Candidate* manager_candidate = new Candidate(manager_first_name, manager_last_name);
        HR* manager = director->add_company_manager(company, manager_candidate);
        cout << "Managers:" << endl;
        for(auto manager : hr_database.get_all()) {
            cout << "- ";
            manager->person_information();
        }
    }

    // Candidates
    if(candidates.size()) {
        string candidate_first_name;
        string candidate_last_name;
        string candidate_manager_first_name;
        string candidate_manager_last_name;
        string candidate_prev_index = "[0]";
        for(auto text : candidates) {
            vector<string> data = split(text);
            if(data[1] != candidate_prev_index) {
                Candidate* candidate = new Candidate(candidate_first_name, candidate_last_name);
                if(candidate_manager_first_name.size() && candidate_manager_last_name.size()) {
                    HR* manager = hr_database.get(candidate_manager_first_name, candidate_manager_last_name);
                    manager->add_candidate(candidate);
                }
                candidate_first_name = "";
                candidate_last_name = "";
                candidate_manager_first_name = "";
                candidate_manager_last_name = "";
            }
            if(data[2] == "first_name") {
                candidate_first_name = data[3];
            }
            if(data[2] == "last_name") {
                candidate_last_name = data[3];
            }
            if(data[2] == "manager") {
                if(data[3] == "first_name") {
                    candidate_manager_first_name = data[4];
                }
                if(data[3] == "last_name") {
                    candidate_manager_last_name = data[4];
                }
            }
            candidate_prev_index = data[1];
        }
        Candidate* candidate = new Candidate(candidate_first_name, candidate_last_name);
        if(candidate_manager_first_name.size() && candidate_manager_last_name.size()) {
            HR* manager = hr_database.get(candidate_manager_first_name, candidate_manager_last_name);
            manager->add_candidate(candidate);
        }
        candidate_first_name = "";
        candidate_last_name = "";
        candidate_manager_first_name = "";
        candidate_manager_last_name = "";
        cout << "Candidates:" << endl;
        for(auto candidate : candidate_database.get_all()) {
            cout << "- ";
            candidate->person_information();
        }
    }
    cout << "Database is ready." << endl;
}

void save_database() {
    cout << "Database saving..." << endl;
    vector<Candidate*> candidates = candidate_database.get_all();
    vector<Developer*> developers = developer_database.get_all();
    vector<HR*> managers = hr_database.get_all();
    vector<Director*> directors = director_database.get_all();
    vector<Company*> companies = company_database.get_all();

    int i;
    vector<string> database_text;

    // Candidates
    cout << "Saving candidates..." << endl;
    i = 0;
    for(auto candidate : candidates) {
        string text;
        text = "candidates:[" + to_string(i) + "]:first_name=" + candidate->first_name;
        database_text.push_back(text);
        text = "candidates:[" + to_string(i) + "]:last_name=" + candidate->last_name;
        database_text.push_back(text);
        if(candidate->have_hr_manager()) {
            HR manager = candidate->get_manager();
            text = "candidates:[" + to_string(i) + "]:manager:first_name=" + manager.first_name;
            database_text.push_back(text);
            text = "candidates:[" + to_string(i) + "]:manager:last_name=" + manager.last_name;
            database_text.push_back(text);
        }
        i++;
    }

    // Developers
    cout << "Saving developers..." << endl;
    i = 0;
    for(auto developer : developers) {
        string text;
        text = "developers:[" + to_string(i) + "]:first_name=" + developer->first_name;
        database_text.push_back(text);
        text = "developers:[" + to_string(i) + "]:last_name=" + developer->last_name;
        database_text.push_back(text);
        text = "developers:[" + to_string(i) + "]:company=" + developer->company->get_name();
        database_text.push_back(text);
        i++;
    }

    // Managers
    cout << "Saving managers..." << endl;
    i = 0;
    for(auto manager : managers) {
        string text;
        text = "managers:[" + to_string(i) + "]:first_name=" + manager->first_name;
        database_text.push_back(text);
        text = "managers:[" + to_string(i) + "]:last_name=" + manager->last_name;
        database_text.push_back(text);
        text = "managers:[" + to_string(i) + "]:company=" + manager->company->get_name();
        database_text.push_back(text);
        i++;
    }

    // Director
    cout << "Saving directors..." << endl;
    i = 0;
    for(auto director : directors) {
        string text;
        text = "directors:[" + to_string(i) + "]:first_name=" + director->first_name;
        database_text.push_back(text);
        text = "directors:[" + to_string(i) + "]:last_name=" + director->last_name;
        database_text.push_back(text);
        i++;
    }

    // Company
    cout << "Saving companies..." << endl;
    i = 0;
    for(auto company : companies) {
        string text;
        text = "companies:[" + to_string(i) + "]:name=" + company->get_name();
        database_text.push_back(text);
        if(company->get_description().size()) {
            text = "companies:[" + to_string(i) + "]:description=" + company->get_description();
            database_text.push_back(text);
        }
        text = "companies:[" + to_string(i) + "]:director:first_name=" + company->get_director_first_name();
        database_text.push_back(text);
        text = "companies:[" + to_string(i) + "]:director:last_name=" + company->get_director_last_name();
        database_text.push_back(text);
        i++;
    }

    ofstream file(DATABASE_PATH);
    for(auto i : database_text) {
        file << i << endl;
    }
    file.close();
    cout << "Database saved." << endl;
}
