#include "../include/Challenge.h"
#include <iostream>

using namespace std;

TrainingChallenge::TrainingChallenge(
    const string& name,
    int durationDays,
    Exercise* targetExercise,
    int dailyTarget,
    const string& unit
) {
    this->name = name;
    this->durationDays = durationDays > 0 ? durationDays : 15;
    this->targetExercise = targetExercise;
    this->dailyTarget = dailyTarget > 0 ? dailyTarget : 50;
    this->unit = unit;
    this->currentDay = 1;
    this->completedTotal = 0;
    this->finished = false;
}

void TrainingChallenge::updateDay(int completedAmount) {
    if (finished) {
        cout << "\nChallenge is already finished.\n";
        return;
    }

    if (completedAmount < 0) {
        completedAmount = 0;
    }

    completedTotal += completedAmount;

    cout << "\n===== Challenge Day Result =====\n";
    cout << "Day: " << currentDay << "/" << durationDays << endl;
    cout << "Exercise: " << targetExercise->getName() << endl;
    cout << "Daily target: " << dailyTarget << " " << unit << endl;
    cout << "Completed today: " << completedAmount << " " << unit << endl;

    if (completedAmount >= dailyTarget) {
        cout << "Status: Target completed for today.\n";
    } else {
        cout << "Status: Target not reached today.\n";
        cout << "Missing: " << dailyTarget - completedAmount << " " << unit << endl;
    }

    currentDay++;

    if (currentDay > durationDays) {
        finished = true;
        cout << "\nChallenge finished.\n";
    }
}

bool TrainingChallenge::isCompleted() const {
    return finished;
}

void TrainingChallenge::showChallenge() const {
    cout << "\n===== Fitness Challenge =====\n";
    cout << "Challenge name: " << name << endl;
    cout << "Exercise: " << targetExercise->getName() << endl;
    cout << "Duration: " << durationDays << " days" << endl;
    cout << "Daily target: " << dailyTarget << " " << unit << endl;
    cout << "Current day: " << currentDay << endl;
}

void TrainingChallenge::showProgress() const {
    int totalTarget = durationDays * dailyTarget;
    double progressPercent = 0;

    if (totalTarget > 0) {
        progressPercent = (completedTotal * 100.0) / totalTarget;
    }

    cout << "\n===== Challenge Progress =====\n";
    cout << "Challenge: " << name << endl;
    cout << "Exercise: " << targetExercise->getName() << endl;
    cout << "Completed total: " << completedTotal << " " << unit << endl;
    cout << "Total target: " << totalTarget << " " << unit << endl;
    cout << "Progress: " << progressPercent << "%" << endl;

    if (finished) {
        cout << "Status: Finished\n";
    } else {
        cout << "Status: In progress\n";
    }
}

string TrainingChallenge::getName() const {
    return name;
}

int TrainingChallenge::getDurationDays() const {
    return durationDays;
}

int TrainingChallenge::getCurrentDay() const {
    return currentDay;
}

int TrainingChallenge::getCompletedTotal() const {
    return completedTotal;
}