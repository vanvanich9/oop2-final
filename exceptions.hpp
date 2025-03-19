#pragma once

#include <iostream>

using namespace std;

struct PermissionError: public exception {
	const char* what() const throw() {
    	return "Dont have permissions";
    }
};

struct PersonCompanyExists: public exception {
	const char* what() const throw() {
    	return "Person or company exists";
    }
};

struct NotFound: public exception {
	const char* what() const throw() {
    	return "Person or company not found";
    }
};
