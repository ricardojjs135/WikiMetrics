#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <vector>

class Human {
private:
    std::string name;
    std::string gender;
    std::string birthDate;
    std::string deathDate;
    std::string professions;
    std::string religions;

public:
    Human(std::string name, std::string gender,
          std::string birthDate, std::string deathDate = "", 
          std::string professions = "", std::string religions = "");

    std::string getName() const;
    std::string getGender() const;
    std::string getBirthDate() const;
    std::string getDeathDate() const;
    std::string getProfessions() const;
    std::string getReligions() const;

    int calculateAge() const;
    void toString() const;
};

#endif