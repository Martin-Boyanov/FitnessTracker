#include "../include/Calculator.h"

Calculator::~Calculator() {
}

OneRepMaxCalculator::OneRepMaxCalculator(
    const string& exerciseName,
    double weightKg,
    int reps
) {
    this->exerciseName = exerciseName;
    this->weightKg = weightKg > 0 ? weightKg : 0;
    this->reps = reps > 0 ? reps : 1;
}

string OneRepMaxCalculator::getExerciseName() const {
    return exerciseName;
}

double OneRepMaxCalculator::getWeightKg() const {
    return weightKg;
}

int OneRepMaxCalculator::getReps() const {
    return reps;
}

double OneRepMaxCalculator::calculate() const {
    return weightKg * (1 + reps / 30.0);
}

string OneRepMaxCalculator::getName() const {
    return "One Rep Max Calculator";
}