#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

using namespace std;

class Calculator {
public:
    virtual ~Calculator();

    virtual double calculate() const = 0;
    virtual string getName() const = 0;
};

class OneRepMaxCalculator : public Calculator {
private:
    string exerciseName;
    double weightKg;
    int reps;

public:
    OneRepMaxCalculator(const string& exerciseName, double weightKg, int reps);

    string getExerciseName() const;
    double getWeightKg() const;
    int getReps() const;

    double calculate() const override;
    string getName() const override;
};

class BodyFatCalculator : public Calculator {
private:
    string method;
    string gender;
    int age;
    double heightCm;
    double weightKg;
    double waistCm;
    double neckCm;
    double hipCm;

    bool isValidResult(double result) const;

public:
    BodyFatCalculator(
        const string& gender,
        int age,
        double heightCm,
        double weightKg
    );

    BodyFatCalculator(
        const string& gender,
        double heightCm,
        double waistCm,
        double neckCm,
        double hipCm
    );

    double calculate() const override;
    string getName() const override;
    string getMethodName() const;
};

class CalorieCalculator : public Calculator {
private:
    string gender;
    int age;
    double heightCm;
    double weightKg;
    string activityLevel;
    string goal;

    double calculateBmr() const;
    double getActivityMultiplier() const;

public:
    CalorieCalculator(
        const string& gender,
        int age,
        double heightCm,
        double weightKg,
        const string& activityLevel,
        const string& goal
    );

    double calculate() const override;
    string getName() const override;
    string getRecommendation() const;
};

#endif