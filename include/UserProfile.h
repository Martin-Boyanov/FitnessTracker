#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <string>

using namespace std;

class UserProfile {
private:
    string name;
    int age;
    string gender;
    double heightCm;
    double weightKg;
    string activityLevel;
    string goal;

public:
    UserProfile();

    UserProfile(
        const string& name,
        int age,
        const string& gender,
        double heightCm,
        double weightKg,
        const string& activityLevel,
        const string& goal
    );

    string getName() const;
    int getAge() const;
    string getGender() const;
    double getHeightCm() const;
    double getWeightKg() const;
    string getActivityLevel() const;
    string getGoal() const;

    void updateBodyData(double newHeightCm, double newWeightKg);
    void showProfile() const;
};

#endif