#include <iostream>
#include <vector>
#include <limits>
#include "../include/UserProfile.h"
#include "../include/Exercise.h"
#include "../include/Workout.h"
#include "../include/Calculator.h"

using namespace std;

vector<Exercise*> createExerciseDatabase() {
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

    return exercises;
}

void showExerciseDatabase(const vector<Exercise*>& exercises) {
    cout << "\n===== Exercise Database =====\n";

    for (int i = 0; i < (int)exercises.size(); i++) {
        cout << "\n-------------------------\n";
        cout << i + 1 << ". " << exercises[i]->getName() << endl;
        cout << exercises[i]->getDetails();
        cout << "Progression: " << exercises[i]->getProgressionInfo() << endl;
    }
}

void showDemoWorkout(const vector<Exercise*>& exercises) {
    WorkoutSession workout(
        "17.05.2026",
        "Chest and legs workout",
        75
    );

    ExerciseLog benchPressLog(exercises[1]);
    benchPressLog.addSet(ExerciseSet(10, 80));
    benchPressLog.addSet(ExerciseSet(8, 85));
    benchPressLog.addSet(ExerciseSet(6, 90));

    ExerciseLog squatLog(exercises[0]);
    squatLog.addSet(ExerciseSet(10, 90));
    squatLog.addSet(ExerciseSet(8, 100));
    squatLog.addSet(ExerciseSet(6, 110));

    workout.addExerciseLog(benchPressLog);
    workout.addExerciseLog(squatLog);

    workout.showWorkout();
}

void calculateOneRepMax(const vector<Exercise*>& exercises) {
    vector<int> strengthExerciseIndexes;

    cout << "\n===== Choose Strength Exercise =====\n";

    for (int i = 0; i < (int)exercises.size(); i++) {
        if (dynamic_cast<StrengthExercise*>(exercises[i]) != nullptr) {
            strengthExerciseIndexes.push_back(i);
            cout << strengthExerciseIndexes.size() << ". "
                 << exercises[i]->getName() << endl;
        }
    }

    if (strengthExerciseIndexes.empty()) {
        cout << "\nNo strength exercises available for one rep max calculation.\n";
        return;
    }

    int choice;
    cout << "Choose exercise: ";
    cin >> choice;

    if (cin.fail() || choice < 1 || choice > (int)strengthExerciseIndexes.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid exercise choice.\n";
        return;
    }

    int realExerciseIndex = strengthExerciseIndexes[choice - 1];
    string exerciseName = exercises[realExerciseIndex]->getName();

    double weightKg;
    int reps;

    cout << "Enter weight in kg: ";
    cin >> weightKg;

    if (cin.fail() || weightKg <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid weight.\n";
        return;
    }

    cout << "Enter reps: ";
    cin >> reps;

    if (cin.fail() || reps <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid reps.\n";
        return;
    }

    OneRepMaxCalculator calculator(exerciseName, weightKg, reps);

    cout << "\n===== One Rep Max Calculator =====\n";
    cout << "Exercise: " << calculator.getExerciseName() << endl;
    cout << "Weight: " << calculator.getWeightKg() << " kg" << endl;
    cout << "Reps: " << calculator.getReps() << endl;
    cout << "Estimated 1RM: " << calculator.calculate() << " kg" << endl;
}

void showMenu() {
    cout << "\n===== Fitness Tracker =====\n";
    cout << "1. Show user profile\n";
    cout << "2. Show exercise database\n";
    cout << "3. Show workout session example\n";
    cout << "4. Calculate one rep max\n";
    cout << "5. Exit\n";
    cout << "Choose option: ";
}

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

    vector<Exercise*> exercises = createExerciseDatabase();

    int choice;

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                user.showProfile();
                break;

            case 2:
                showExerciseDatabase(exercises);
                break;

            case 3:
                showDemoWorkout(exercises);
                break;

            case 4:
                calculateOneRepMax(exercises);
                break;

            case 5:
                cout << "\nExiting Fitness Tracker...\n";
                break;

            default:
                cout << "\nInvalid option. Try again.\n";
                break;
        }

    } while (choice != 5);

    for (Exercise* exercise : exercises) {
        delete exercise;
    }

    return 0;
}