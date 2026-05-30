#include "../include/CustomWorkoutBuilder.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cctype>

using namespace std;

CustomWorkoutExercise::CustomWorkoutExercise(
    const string& name,
    const string& targetMuscle,
    const string& exerciseType,
    const string& prescription,
    const string& reason
) {
    this->name = name;
    this->targetMuscle = targetMuscle;
    this->exerciseType = exerciseType;
    this->prescription = prescription;
    this->reason = reason;
}

void CustomWorkoutExercise::showExercise() const {
    cout << "\nExercise: " << name << endl;
    cout << "Type: " << exerciseType << endl;
    cout << "Target muscle: " << targetMuscle << endl;
    cout << "Prescription: " << prescription << endl;
    cout << "Why it is included: " << reason << endl;
}

void CustomWorkoutExercise::writeToFile(ostream& out, int index) const {
    out << "\nExercise " << index << ":\n";
    out << "Name: " << name << endl;
    out << "Type: " << exerciseType << endl;
    out << "Target muscle: " << targetMuscle << endl;
    out << "Prescription: " << prescription << endl;
    out << "Why it is included: " << reason << endl;
}

void CustomWorkoutExercise::writeHtmlToFile(ostream& out, int index) const {
    out << "<div class=\"exercise-card\">\n";
    out << "<h2>Exercise " << index << ": " << name << "</h2>\n";
    out << "<p><strong>Type:</strong> " << exerciseType << "</p>\n";
    out << "<p><strong>Target muscle:</strong> " << targetMuscle << "</p>\n";
    out << "<p><strong>Prescription:</strong> " << prescription << "</p>\n";
    out << "<p><strong>Why it is included:</strong> " << reason << "</p>\n";
    out << "</div>\n";
}

CustomWorkoutBuilder::CustomWorkoutBuilder(const string& workoutName) {
    this->workoutName = workoutName.empty() ? "Custom Workout" : workoutName;
}

void CustomWorkoutBuilder::addExercise(const CustomWorkoutExercise& exercise) {
    selectedExercises.push_back(exercise);
}

bool CustomWorkoutBuilder::isEmpty() const {
    return selectedExercises.empty();
}

void CustomWorkoutBuilder::showWorkout() const {
    cout << "\n===== Custom Workout Builder Result =====\n";
    cout << "Workout name: " << workoutName << endl;

    if (selectedExercises.empty()) {
        cout << "No exercises were added.\n";
        return;
    }

    cout << "\nThis workout was built by the user after passing the theory course.\n";
    cout << "Each exercise has a reason, so the user understands why it belongs in the plan.\n";

    for (int i = 0; i < (int)selectedExercises.size(); i++) {
        cout << "\n-------------------------\n";
        cout << "Selected exercise " << i + 1 << endl;
        selectedExercises[i].showExercise();
    }
}

string CustomWorkoutBuilder::createSafeFileName(const string& text) const {
    string result;

    for (char symbol : text) {
        if (isalnum((unsigned char)symbol)) {
            result += symbol;
        } else if (symbol == ' ' || symbol == '-' || symbol == '_') {
            result += '_';
        }
    }

    if (result.empty()) {
        result = "custom_workout";
    }

    return result;
}

string CustomWorkoutBuilder::escapeHtml(const string& text) const {
    string result;

    for (char symbol : text) {
        if (symbol == '&') {
            result += "&amp;";
        } else if (symbol == '<') {
            result += "&lt;";
        } else if (symbol == '>') {
            result += "&gt;";
        } else if (symbol == '"') {
            result += "&quot;";
        } else {
            result += symbol;
        }
    }

    return result;
}

bool CustomWorkoutBuilder::saveToTextFile() const {
    if (selectedExercises.empty()) {
        return false;
    }

    filesystem::create_directories("workouts");

    string fileName = "workouts/" + createSafeFileName(workoutName) + ".txt";

    ofstream outFile(fileName);

    if (!outFile.is_open()) {
        return false;
    }

    outFile << "===== Custom Workout =====\n";
    outFile << "Workout name: " << workoutName << endl;
    outFile << "\nThis workout was created after passing the mini theory course.\n";
    outFile << "Each exercise includes a reason so the user understands why it belongs in the plan.\n";

    for (int i = 0; i < (int)selectedExercises.size(); i++) {
        selectedExercises[i].writeToFile(outFile, i + 1);
    }

    outFile << "\n===== End Of Workout =====\n";

    outFile.close();

    cout << "\nWorkout saved successfully to: " << fileName << endl;

    bool htmlSaved = saveToHtmlFile();

    if (!htmlSaved) {
        cout << "Warning: phone-friendly HTML file could not be created.\n";
    }

    return true;
}

bool CustomWorkoutBuilder::saveToHtmlFile() const {
    if (selectedExercises.empty()) {
        return false;
    }

    filesystem::create_directories("workouts");

    string fileName = "workouts/" + createSafeFileName(workoutName) + ".html";

    ofstream outFile(fileName);

    if (!outFile.is_open()) {
        return false;
    }

    outFile << "<!DOCTYPE html>\n";
    outFile << "<html lang=\"en\">\n";
    outFile << "<head>\n";
    outFile << "<meta charset=\"UTF-8\">\n";
    outFile << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    outFile << "<title>" << escapeHtml(workoutName) << "</title>\n";

    outFile << "<style>\n";
    outFile << "body { margin: 0; font-family: Arial, sans-serif; background: #f4f4f5; color: #18181b; }\n";
    outFile << ".container { max-width: 720px; margin: 0 auto; padding: 20px; }\n";
    outFile << ".header { background: #18181b; color: white; padding: 24px; border-radius: 18px; margin-bottom: 18px; }\n";
    outFile << ".header h1 { margin: 0 0 8px 0; font-size: 28px; }\n";
    outFile << ".header p { margin: 0; color: #d4d4d8; line-height: 1.5; }\n";
    outFile << ".exercise-card { background: white; padding: 18px; border-radius: 16px; margin-bottom: 14px; box-shadow: 0 4px 14px rgba(0,0,0,0.08); }\n";
    outFile << ".exercise-card h2 { margin-top: 0; font-size: 21px; }\n";
    outFile << ".exercise-card p { line-height: 1.5; }\n";
    outFile << ".footer { text-align: center; color: #71717a; font-size: 14px; margin-top: 24px; }\n";
    outFile << "</style>\n";

    outFile << "</head>\n";
    outFile << "<body>\n";
    outFile << "<div class=\"container\">\n";

    outFile << "<div class=\"header\">\n";
    outFile << "<h1>" << escapeHtml(workoutName) << "</h1>\n";
    outFile << "<p>This workout was created after passing the mini fitness theory course. Each exercise includes a reason so you understand why it belongs in the plan.</p>\n";
    outFile << "</div>\n";

    for (int i = 0; i < (int)selectedExercises.size(); i++) {
        selectedExercises[i].writeHtmlToFile(outFile, i + 1);
    }

    outFile << "<div class=\"footer\">\n";
    outFile << "Generated by Fitness Tracker OOP Project\n";
    outFile << "</div>\n";

    outFile << "</div>\n";
    outFile << "</body>\n";
    outFile << "</html>\n";

    outFile.close();

    cout << "Phone-friendly HTML workout saved to: " << fileName << endl;
    cout << "You can send this HTML file to your phone using Gmail, Google Drive, Messenger or GitHub.\n";

    return true;
}

string CustomWorkoutBuilder::getWorkoutName() const {
    return workoutName;
}