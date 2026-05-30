#ifndef CUSTOMWORKOUTBUILDER_H
#define CUSTOMWORKOUTBUILDER_H

#include <string>
#include <vector>

using namespace std;

class CustomWorkoutExercise {
private:
    string name;
    string targetMuscle;
    string exerciseType;
    string prescription;
    string reason;

public:
    CustomWorkoutExercise(
        const string& name,
        const string& targetMuscle,
        const string& exerciseType,
        const string& prescription,
        const string& reason
    );

    void showExercise() const;
    void writeToFile(ostream& out, int index) const;
};

class CustomWorkoutBuilder {
private:
    string workoutName;
    vector<CustomWorkoutExercise> selectedExercises;

    string createSafeFileName(const string& text) const;

public:
    CustomWorkoutBuilder(const string& workoutName);

    void addExercise(const CustomWorkoutExercise& exercise);
    bool isEmpty() const;
    void showWorkout() const;

    bool saveToTextFile() const;
    string getWorkoutName() const;
};

#endif