#ifndef WORKOUT_H
#define WORKOUT_H

#include <string>
#include <vector>
#include "Exercise.h"

using namespace std;

class ExerciseSet {
private:
    int reps;
    double weightKg;

public:
    ExerciseSet(int reps, double weightKg);

    int getReps() const;
    double getWeightKg() const;
    double getVolume() const;
};

class ExerciseLog {
private:
    Exercise* exercise;
    vector<ExerciseSet> sets;

public:
    ExerciseLog(Exercise* exercise);

    void addSet(const ExerciseSet& set);
    double calculateVolume() const;
    void showLog() const;
};

class WorkoutSession {
private:
    string date;
    string notes;
    int durationMinutes;
    vector<ExerciseLog> exerciseLogs;

public:
    WorkoutSession(const string& date, const string& notes, int durationMinutes);

    void addExerciseLog(const ExerciseLog& log);
    double calculateTotalVolume() const;
    void showWorkout() const;
};

#endif