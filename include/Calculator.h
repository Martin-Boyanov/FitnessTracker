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

#endif