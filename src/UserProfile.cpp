#include "../include/UserProfile.h"
#include <iostream>

using namespace std;

UserProfile::UserProfile()
    : name("Default User"),
      age(18),
      gender("Unknown"),
      heightCm(170),
      weightKg(70),
      activityLevel("Moderate"),
      goal("Maintain weight") {
}

UserProfile::UserProfile(
    const string& name,
    int age,
    const string& gender,
    double heightCm,
    double weightKg,
    const string& activityLevel,
    const string& goal
) {
    this->name = name;
    this->age = age > 0 ? age : 18;
    this->gender = gender;
    this->heightCm = heightCm > 0 ? heightCm : 170;
    this->weightKg = weightKg > 0 ? weightKg : 70;
    this->activityLevel = activityLevel;
    this->goal = goal;
}

string UserProfile::getName() const {
    return name;
}

int UserProfile::getAge() const {
    return age;
}

string UserProfile::getGender() const {
    return gender;
}

double UserProfile::getHeightCm() const {
    return heightCm;
}

double UserProfile::getWeightKg() const {
    return weightKg;
}

string UserProfile::getActivityLevel() const {
    return activityLevel;
}

string UserProfile::getGoal() const {
    return goal;
}

void UserProfile::updateBodyData(double newHeightCm, double newWeightKg) {
    if (newHeightCm > 0) {
        heightCm = newHeightCm;
    }

    if (newWeightKg > 0) {
        weightKg = newWeightKg;
    }
}

void UserProfile::showProfile() const {
    cout << "\n===== User Profile =====\n";
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << gender << endl;
    cout << "Height: " << heightCm << " cm" << endl;
    cout << "Weight: " << weightKg << " kg" << endl;
    cout << "Activity level: " << activityLevel << endl;
    cout << "Goal: " << goal << endl;
}