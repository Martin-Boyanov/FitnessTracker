#include "../include/Calculator.h"
#include <cmath>

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

BodyFatCalculator::BodyFatCalculator(
    const string& gender,
    int age,
    double heightCm,
    double weightKg
) {
    this->method = "Simple BMI estimate";
    this->gender = gender;
    this->age = age > 0 ? age : 18;
    this->heightCm = heightCm > 0 ? heightCm : 170;
    this->weightKg = weightKg > 0 ? weightKg : 70;
    this->waistCm = 0;
    this->neckCm = 0;
    this->hipCm = 0;
}

BodyFatCalculator::BodyFatCalculator(
    const string& gender,
    double heightCm,
    double waistCm,
    double neckCm,
    double hipCm
) {
    this->method = "Body measurement estimate";
    this->gender = gender;
    this->age = 0;
    this->heightCm = heightCm > 0 ? heightCm : 170;
    this->weightKg = 0;
    this->waistCm = waistCm > 0 ? waistCm : 80;
    this->neckCm = neckCm > 0 ? neckCm : 35;
    this->hipCm = hipCm >= 0 ? hipCm : 0;
}

bool BodyFatCalculator::isValidResult(double result) const {
    return result > 0 && result < 100;
}

double BodyFatCalculator::calculate() const {
    double result;

    if (method == "Simple BMI estimate") {
        double heightM = heightCm / 100.0;
        double bmi = weightKg / (heightM * heightM);
        int sexValue = (gender == "Male" || gender == "male") ? 1 : 0;

        result = 1.20 * bmi + 0.23 * age - 10.8 * sexValue - 5.4;

        if (!isValidResult(result)) {
            return -1;
        }

        return result;
    }

    double heightIn = heightCm / 2.54;
    double waistIn = waistCm / 2.54;
    double neckIn = neckCm / 2.54;
    double hipIn = hipCm / 2.54;

    if (gender == "Male" || gender == "male") {
        if (waistIn <= neckIn) {
            return -1;
        }

        result = 86.010 * log10(waistIn - neckIn)
               - 70.041 * log10(heightIn)
               + 36.76;
    } else {
        if (waistIn + hipIn <= neckIn) {
            return -1;
        }

        result = 163.205 * log10(waistIn + hipIn - neckIn)
               - 97.684 * log10(heightIn)
               - 78.387;
    }

    if (!isValidResult(result)) {
        return -1;
    }

    return result;
}

string BodyFatCalculator::getName() const {
    return "Body Fat Percentage Calculator";
}

string BodyFatCalculator::getMethodName() const {
    return method;
}

CalorieCalculator::CalorieCalculator(
    const string& gender,
    int age,
    double heightCm,
    double weightKg,
    const string& activityLevel,
    const string& goal
) {
    this->gender = gender;
    this->age = age > 0 ? age : 18;
    this->heightCm = heightCm > 0 ? heightCm : 170;
    this->weightKg = weightKg > 0 ? weightKg : 70;
    this->activityLevel = activityLevel;
    this->goal = goal;
}

double CalorieCalculator::calculateBmr() const {
    if (gender == "Male" || gender == "male") {
        return 10 * weightKg + 6.25 * heightCm - 5 * age + 5;
    }

    return 10 * weightKg + 6.25 * heightCm - 5 * age - 161;
}

double CalorieCalculator::getActivityMultiplier() const {
    if (activityLevel == "Low") {
        return 1.2;
    }

    if (activityLevel == "Light") {
        return 1.375;
    }

    if (activityLevel == "Moderate") {
        return 1.55;
    }

    if (activityLevel == "High") {
        return 1.725;
    }

    return 1.2;
}

double CalorieCalculator::calculate() const {
    double maintenanceCalories = calculateBmr() * getActivityMultiplier();

    if (goal == "Lose fat") {
        return maintenanceCalories - 400;
    }

    if (goal == "Build muscle") {
        return maintenanceCalories + 300;
    }

    return maintenanceCalories;
}

string CalorieCalculator::getName() const {
    return "Daily Calorie Calculator";
}

string CalorieCalculator::getRecommendation() const {
    if (goal == "Lose fat") {
        return "Suggested goal: calorie deficit for fat loss.";
    }

    if (goal == "Build muscle") {
        return "Suggested goal: small calorie surplus for muscle gain.";
    }

    return "Suggested goal: maintenance calories.";
}