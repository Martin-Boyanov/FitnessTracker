#include "../include/Workout.h"
#include <iostream>

using namespace std;

ExerciseSet::ExerciseSet(int reps, double weightKg) {
    this->reps = reps > 0 ? reps : 0;
    this->weightKg = weightKg >= 0 ? weightKg : 0;
}

int ExerciseSet::getReps() const {
    return reps;
}

double ExerciseSet::getWeightKg() const {
    return weightKg;
}

double ExerciseSet::getVolume() const {
    return reps * weightKg;
}

ExerciseLog::ExerciseLog(Exercise* exercise) {
    this->exercise = exercise;
}

void ExerciseLog::addSet(const ExerciseSet& set) {
    sets.push_back(set);
}

double ExerciseLog::calculateVolume() const {
    double total = 0;

    for (const ExerciseSet& set : sets) {
        total += set.getVolume();
    }

    return total;
}

void ExerciseLog::showLog() const {
    cout << "\nExercise: " << exercise->getName() << endl;

    for (int i = 0; i < (int)sets.size(); i++) {
        cout << "Set " << i + 1 << ": "
             << sets[i].getReps() << " reps x "
             << sets[i].getWeightKg() << " kg = "
             << sets[i].getVolume() << " kg lifted" << endl;
    }

    cout << "Exercise training volume: " << calculateVolume() << " kg lifted" << endl;
}

WorkoutSession::WorkoutSession(
    const string& date,
    const string& notes,
    int durationMinutes
) {
    this->date = date;
    this->notes = notes;
    this->durationMinutes = durationMinutes > 0 ? durationMinutes : 0;
}

void WorkoutSession::addExerciseLog(const ExerciseLog& log) {
    exerciseLogs.push_back(log);
}

double WorkoutSession::calculateTotalVolume() const {
    double total = 0;

    for (const ExerciseLog& log : exerciseLogs) {
        total += log.calculateVolume();
    }

    return total;
}

void WorkoutSession::showWorkout() const {
    cout << "\n===== Workout Session =====\n";
    cout << "Date: " << date << endl;
    cout << "Duration: " << durationMinutes << " minutes" << endl;
    cout << "Notes: " << notes << endl;

    cout << "\nTraining volume explanation:\n";
    cout << "Volume means total lifted weight: reps x weight.\n";
    cout << "It is useful for comparing your own progress over time.\n";
    cout << "There is no universal goal like 4000 kg. The goal is to improve gradually while keeping good form.\n";

    for (const ExerciseLog& log : exerciseLogs) {
        log.showLog();
    }

    cout << "\nTotal workout volume: " << calculateTotalVolume() << " kg lifted" << endl;
    cout << "Use this number to compare similar workouts, not completely different training days.\n";
}