#ifndef WORKOUTPLAN_H
#define WORKOUTPLAN_H

#include <string>
#include <vector>
#include "Exercise.h"

using namespace std;

class WorkoutPlan {
private:
    string planName;
    string equipmentType;
    vector<Exercise*> exercises;

public:
    WorkoutPlan(const string& planName, const string& equipmentType);

    void addExercise(Exercise* exercise);
    void generateByEquipment(const vector<Exercise*>& database);
    void showPlan() const;

    string getPlanName() const;
    string getEquipmentType() const;
};

#endif