#include "../include/CustomWorkoutBuilder.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cctype>

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

void CustomWorkoutExercise::writeToFile(ostream& out, int index) const {
    out << "\nExercise " << index << ":\n";
    out << "Name: " << name << endl;
    out << "Type: " << exerciseType << endl;
    out << "Target muscle: " << targetMuscle << endl;
    out << "Prescription: " << prescription << endl;
    out << "Why it is included: " << reason << endl;
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

string CustomWorkoutBuilder::createSafeFileName(const string& text) const {
    string result;

    for (char symbol : text) {
        if (isalnum((unsigned char)symbol)) {
            result += symbol;
        } else if (symbol == ' ' || symbol == '-' || symbol == '_') {
            result += '_';
        }
    }

    if (result.empty()) {
        result = "custom_workout";
    }

    return result;
}

bool CustomWorkoutBuilder::saveToTextFile() const {
    if (selectedExercises.empty()) {
        return false;
    }

    filesystem::create_directories("workouts");

    string fileName = "workouts/" + createSafeFileName(workoutName) + ".txt";

    ofstream outFile(fileName);

    if (!outFile.is_open()) {
        return false;
    }

    outFile << "===== Custom Workout =====\n";
    outFile << "Workout name: " << workoutName << endl;
    outFile << "\nThis workout was created after passing the mini theory course.\n";
    outFile << "Each exercise includes a reason so the user understands why it belongs in the plan.\n";

    for (int i = 0; i < (int)selectedExercises.size(); i++) {
        selectedExercises[i].writeToFile(outFile, i + 1);
    }

    outFile << "\n===== End Of Workout =====\n";

    outFile.close();

    cout << "\nWorkout saved successfully to: " << fileName << endl;

    return true;
}

string CustomWorkoutBuilder::getWorkoutName() const {
    return workoutName;
}