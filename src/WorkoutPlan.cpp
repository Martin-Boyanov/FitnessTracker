#include "../include/WorkoutPlan.h"
#include <iostream>

using namespace std;

WorkoutPlan::WorkoutPlan(const string& planName, const string& equipmentType) {
    this->planName = planName;
    this->equipmentType = equipmentType;
}

void WorkoutPlan::addExercise(Exercise* exercise) {
    if (exercise != nullptr) {
        exercises.push_back(exercise);
    }
}

void WorkoutPlan::generateByEquipment(const vector<Exercise*>& database) {
    exercises.clear();

    for (Exercise* exercise : database) {
        if (equipmentType == "Full gym") {
            addExercise(exercise);
        } else if (equipmentType == "Dumbbells") {
            if (exercise->getEquipment() == "Dumbbells" ||
                exercise->getEquipment() == "Bodyweight" ||
                exercise->getEquipment() == "None") {
                addExercise(exercise);
            }
        } else if (equipmentType == "Bodyweight only") {
            if (exercise->getEquipment() == "Bodyweight" ||
                exercise->getEquipment() == "None") {
                addExercise(exercise);
            }
        } else if (equipmentType == "Travel mode") {
            if (exercise->getEquipment() == "Bodyweight" ||
                exercise->getEquipment() == "None") {
                addExercise(exercise);
            }
        }
    }
}

void WorkoutPlan::showPlan() const {
    cout << "\n===== Workout Plan By Equipment =====\n";
    cout << "Plan name: " << planName << endl;
    cout << "Available equipment: " << equipmentType << endl;

    if (exercises.empty()) {
        cout << "No exercises found for this equipment type.\n";
        return;
    }

    cout << "\nThis plan was generated based on the equipment you selected.\n";

    if (equipmentType == "Full gym") {
        cout << "You have access to all exercises, including barbell movements.\n";
    } else if (equipmentType == "Dumbbells") {
        cout << "The plan avoids barbell-only exercises and focuses on dumbbells and bodyweight movements.\n";
    } else if (equipmentType == "Bodyweight only") {
        cout << "The plan uses exercises that can be done without weights.\n";
    } else {
        cout << "Travel mode keeps the plan simple and possible almost anywhere.\n";
    }

    cout << "\nRecommended exercises:\n";

    for (int i = 0; i < (int)exercises.size(); i++) {
        cout << "\n" << i + 1 << ". " << exercises[i]->getName() << endl;
        cout << "Target muscle: " << exercises[i]->getTargetMuscle() << endl;
        cout << "Equipment: " << exercises[i]->getEquipment() << endl;
        cout << "Progression: " << exercises[i]->getProgressionInfo() << endl;
    }
}

string WorkoutPlan::getPlanName() const {
    return planName;
}

string WorkoutPlan::getEquipmentType() const {
    return equipmentType;
}