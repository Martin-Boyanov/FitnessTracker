#include "../include/Exercise.h"
#include <sstream>

using namespace std;

Exercise::Exercise(
    const string& name,
    const string& targetMuscle,
    const string& equipment,
    const string& difficulty,
    const string& theory
) {
    this->name = name;
    this->targetMuscle = targetMuscle;
    this->equipment = equipment;
    this->difficulty = difficulty;
    this->theory = theory;
}

Exercise::~Exercise() {
}

string Exercise::getName() const {
    return name;
}

string Exercise::getTargetMuscle() const {
    return targetMuscle;
}

string Exercise::getEquipment() const {
    return equipment;
}

StrengthExercise::StrengthExercise(
    const string& name,
    const string& targetMuscle,
    const string& equipment,
    const string& difficulty,
    const string& theory,
    int recommendedSets,
    int recommendedReps
) : Exercise(name, targetMuscle, equipment, difficulty, theory) {
    this->recommendedSets = recommendedSets;
    this->recommendedReps = recommendedReps;
}

string StrengthExercise::getDetails() const {
    stringstream ss;

    ss << "Exercise: " << name << endl;
    ss << "Type: Strength exercise" << endl;
    ss << "Target muscle: " << targetMuscle << endl;
    ss << "Equipment: " << equipment << endl;
    ss << "Difficulty: " << difficulty << endl;
    ss << "Recommended: " << recommendedSets << " sets x "
       << recommendedReps << " reps" << endl;
    ss << "Theory: " << theory << endl;

    return ss.str();
}

string StrengthExercise::getProgressionInfo() const {
    return "Progress by slowly increasing the weight, reps, or number of sets.";
}

BodyweightExercise::BodyweightExercise(
    const string& name,
    const string& targetMuscle,
    const string& equipment,
    const string& difficulty,
    const string& theory,
    int progressionLevel
) : Exercise(name, targetMuscle, equipment, difficulty, theory) {
    this->progressionLevel = progressionLevel;
}

string BodyweightExercise::getDetails() const {
    stringstream ss;

    ss << "Exercise: " << name << endl;
    ss << "Type: Bodyweight exercise" << endl;
    ss << "Target muscle: " << targetMuscle << endl;
    ss << "Equipment: " << equipment << endl;
    ss << "Difficulty: " << difficulty << endl;
    ss << "Progression level: " << progressionLevel << endl;
    ss << "Theory: " << theory << endl;

    return ss.str();
}

string BodyweightExercise::getProgressionInfo() const {
    return "Progress by using harder variations or increasing total reps.";
}

CardioExercise::CardioExercise(
    const string& name,
    const string& targetMuscle,
    const string& equipment,
    const string& difficulty,
    const string& theory,
    const string& intensityLevel
) : Exercise(name, targetMuscle, equipment, difficulty, theory) {
    this->intensityLevel = intensityLevel;
}

string CardioExercise::getDetails() const {
    stringstream ss;

    ss << "Exercise: " << name << endl;
    ss << "Type: Cardio exercise" << endl;
    ss << "Target muscle: " << targetMuscle << endl;
    ss << "Equipment: " << equipment << endl;
    ss << "Difficulty: " << difficulty << endl;
    ss << "Intensity: " << intensityLevel << endl;
    ss << "Theory: " << theory << endl;

    return ss.str();
}

string CardioExercise::getProgressionInfo() const {
    return "Progress by increasing time, speed, distance, or intensity.";
}