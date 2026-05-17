#ifndef EXERCISE_H
#define EXERCISE_H

#include <string>

using namespace std;

class Exercise {
protected:
    string name;
    string targetMuscle;
    string equipment;
    string difficulty;
    string theory;

public:
    Exercise(
        const string& name,
        const string& targetMuscle,
        const string& equipment,
        const string& difficulty,
        const string& theory
    );

    virtual ~Exercise();

    string getName() const;
    string getTargetMuscle() const;
    string getEquipment() const;

    virtual string getDetails() const = 0;
    virtual string getProgressionInfo() const = 0;
};

class StrengthExercise : public Exercise {
private:
    int recommendedSets;
    int recommendedReps;

public:
    StrengthExercise(
        const string& name,
        const string& targetMuscle,
        const string& equipment,
        const string& difficulty,
        const string& theory,
        int recommendedSets,
        int recommendedReps
    );

    string getDetails() const override;
    string getProgressionInfo() const override;
};

class BodyweightExercise : public Exercise {
private:
    int progressionLevel;

public:
    BodyweightExercise(
        const string& name,
        const string& targetMuscle,
        const string& equipment,
        const string& difficulty,
        const string& theory,
        int progressionLevel
    );

    string getDetails() const override;
    string getProgressionInfo() const override;
};

class CardioExercise : public Exercise {
private:
    string intensityLevel;

public:
    CardioExercise(
        const string& name,
        const string& targetMuscle,
        const string& equipment,
        const string& difficulty,
        const string& theory,
        const string& intensityLevel
    );

    string getDetails() const override;
    string getProgressionInfo() const override;
};

#endif