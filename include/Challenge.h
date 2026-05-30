#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <string>
#include "Exercise.h"

using namespace std;

class TrainingChallenge {
private:
    string name;
    int durationDays;
    Exercise* targetExercise;
    int dailyTarget;
    string unit;
    int currentDay;
    int completedTotal;
    bool finished;

public:
    TrainingChallenge(
        const string& name,
        int durationDays,
        Exercise* targetExercise,
        int dailyTarget,
        const string& unit
    );

    void updateDay(int completedAmount);
    bool isCompleted() const;
    void showChallenge() const;
    void showProgress() const;

    string getName() const;
    int getDurationDays() const;
    int getCurrentDay() const;
    int getCompletedTotal() const;
};

#endif