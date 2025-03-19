#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "database.hpp"
#include "models.hpp"
#include "exceptions.hpp"


using namespace std;


void manual_run() {
    Director* director = new Director("Ivan", "Ivanov");
    try {
        Director* director_duplicate = new Director("Ivan", "Ivanov");
    } catch (PersonCompanyExists) {
        cout << "The same director already exists" << endl;
    }
    new Director("Anton", "Antonov");
    Director* director2 = director_database.get("Anton", "Antonov");
    director2->person_information();
    try {
        Director* director_not_exists = director_database.get("Artur", "Arturov");
    } catch (NotFound) {
        cout << "Director not found" << endl;
    }
    for(auto ptr : director_database.get_all()) {
        cout << "- ";
        ptr->person_information();
    }

    Company* company1 = director->create_company("Test company");
    director2->create_company("Test company 2", "Init description");
    try {
        director2->create_company("Test company 2", "Init description");
    } catch (PersonCompanyExists) {
        cout << "Company already exists" << endl;
    }
    Company* company2 = company_database.get("Test company 2");
    cout << company1->get_name() << ' ' << company1->get_description() << endl;
    director->change_company_description(company1, "New description");
    cout << company1->get_name() << ' ' << company1->get_description() << endl;
    try {
        director->change_company_name(company2, "New test company 2");
    } catch (PermissionError) {
        cout << "Permission denied" << endl;
    }
    cout << company2->get_name() << ' ' << company2->get_description() << endl;
    director2->change_company_name(company2, "New test company");
    cout << company2->get_name() << ' ' << company2->get_description() << endl;
    for(auto ptr : company_database.get_all()) {
        cout << "- " << ptr->get_name() << endl;
    }

    Candidate* candidate_developer = new Candidate("Aleksandr", "Aleksandrov");
    try {
        new Candidate("Aleksandr", "Aleksandrov");
    } catch (PersonCompanyExists) {
        cout << "Candidate already exists" << endl;
    } 
    new Candidate("Aleksey", "Alekseev");
    Candidate* candidate_manager = candidate_database.get("Aleksey", "Alekseev");
    new Candidate("Petr", "Petrov");
    for(auto ptr : candidate_database.get_all()) {
        cout << "- ";
        ptr->person_information();
    }
    Developer* developer = director->add_company_developer(company1, candidate_developer);
    cout << "Developers equal: " << (*developer == *developer_database.get("Aleksandr", "Aleksandrov")) << endl;
    HR* manager = director->add_company_manager(company1, candidate_manager);
    cout << "Managers equal: " << (*manager == *hr_database.get("Aleksey", "Alekseev")) << endl;
    Candidate* last_candidate;
    for(auto ptr : candidate_database.get_all()) {
        cout << "- ";
        ptr->person_information();
        last_candidate = ptr;
    }
    for(auto ptr : developer_database.get_all()) {
        cout << "- ";
        ptr->person_information();
    }
    for(auto ptr : hr_database.get_all()) {
        cout << "- ";
        ptr->person_information();
    }
    cout << "Have HR: " << last_candidate->have_hr_manager() << endl;
    manager->add_candidate(last_candidate);
    cout << "Have HR: " << last_candidate->have_hr_manager() << endl;
    manager->remove_candidate(last_candidate);
    cout << "Have HR: " << last_candidate->have_hr_manager() << endl;
    try {
        manager->hire_hr_manager(last_candidate);
    } catch(PermissionError) {
        cout << "Permission denied" << endl;
    }
    manager->add_candidate(last_candidate);
    HR* manager1 = manager->hire_hr_manager(last_candidate);
    for(auto ptr : candidate_database.get_all()) {
        cout << "- ";
        ptr->person_information();
        last_candidate = ptr;
    }
    for(auto ptr : developer_database.get_all()) {
        cout << "- ";
        ptr->person_information();
    }
    for(auto ptr : hr_database.get_all()) {
        cout << "- ";
        ptr->person_information();
    }
    Candidate* new_developer_candidate = new Candidate("Yuri", "Yuriev");
    manager->person_information();
    manager1->person_information();
    manager1->add_candidate(new_developer_candidate);
    try {
        manager->hire_developer(new_developer_candidate);
    } catch(PermissionError) {
        cout << "Permisson denied!" << endl;
    }
    manager1->hire_developer(new_developer_candidate);
    for(auto ptr : candidate_database.get_all()) {
        cout << "- ";
        ptr->person_information();
        last_candidate = ptr;
    }
    for(auto ptr : developer_database.get_all()) {
        cout << "- ";
        ptr->person_information();
    }
    for(auto ptr : hr_database.get_all()) {
        cout << "- ";
        ptr->person_information();
    }
}


int main() {
    init_database();
    manual_run();
    save_database();
}
