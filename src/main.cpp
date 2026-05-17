#include <iostream>
#include <vector>
#include "../include/UserProfile.h"
#include "../include/Exercise.h"

using namespace std;

int main() {
    UserProfile user(
        "Alex",
        17,
        "Male",
        178,
        72,
        "Moderate",
        "Build muscle"
    );

    user.showProfile();

    vector<Exercise*> exercises;

    exercises.push_back(new StrengthExercise(
        "Squat",
        "Legs and glutes",
        "Barbell",
        "Medium",
        "The squat mainly trains the quadriceps, gluteus maximus, hamstrings and core stabilizers.",
        4,
        8
    ));

    exercises.push_back(new StrengthExercise(
        "Bench Press",
        "Chest, shoulders and triceps",
        "Barbell",
        "Medium",
        "The bench press mainly trains the chest, front deltoids and triceps.",
        4,
        8
    ));

    exercises.push_back(new BodyweightExercise(
        "Push-up",
        "Chest, shoulders and triceps",
        "Bodyweight",
        "Easy",
        "Push-ups train the chest, shoulders, triceps and core stability.",
        1
    ));

    exercises.push_back(new CardioExercise(
        "Running",
        "Cardiovascular system and legs",
        "None",
        "Medium",
        "Running improves endurance and trains the heart, lungs and leg muscles.",
        "Moderate"
    ));

    cout << "\n===== Exercise Database =====\n";

    for (Exercise* exercise : exercises) {
        cout << "\n-------------------------\n";
        cout << exercise->getDetails();
        cout << "Progression: " << exercise->getProgressionInfo() << endl;
    }

    for (Exercise* exercise : exercises) {
        delete exercise;
    }

    return 0;
}