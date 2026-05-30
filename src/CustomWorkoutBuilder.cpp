#include "../include/CustomWorkoutBuilder.h"
#include <iostream>

using namespace std;

CustomWorkoutExercise::CustomWorkoutExercise(
    const string& name,
    const string& targetMuscle,
    const string& exerciseType,
    const string& prescription,
    const string& reason
) {
    this->name = name;
    this->targetMuscle = targetMuscle;
    this->exerciseType = exerciseType;
    this->prescription = prescription;
    this->reason = reason;
}

void CustomWorkoutExercise::showExercise() const {
    cout << "\nExercise: " << name << endl;
    cout << "Type: " << exerciseType << endl;
    cout << "Target muscle: " << targetMuscle << endl;
    cout << "Prescription: " << prescription << endl;
    cout << "Why it is included: " << reason << endl;
}

CustomWorkoutBuilder::CustomWorkoutBuilder(const string& workoutName) {
    this->workoutName = workoutName.empty() ? "Custom Workout" : workoutName;
}

void CustomWorkoutBuilder::addExercise(const CustomWorkoutExercise& exercise) {
    selectedExercises.push_back(exercise);
}

bool CustomWorkoutBuilder::isEmpty() const {
    return selectedExercises.empty();
}

void CustomWorkoutBuilder::showWorkout() const {
    cout << "\n===== Custom Workout Builder Result =====\n";
    cout << "Workout name: " << workoutName << endl;

    if (selectedExercises.empty()) {
        cout << "No exercises were added.\n";
        return;
    }

    cout << "\nThis workout was built by the user after passing the theory course.\n";
    cout << "Each exercise has a reason, so the user understands why it belongs in the plan.\n";

    for (int i = 0; i < (int)selectedExercises.size(); i++) {
        cout << "\n-------------------------\n";
        cout << "Selected exercise " << i + 1 << endl;
        selectedExercises[i].showExercise();
    }
}