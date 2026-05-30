#include "../include/ReportExporter.h"
#include "../include/Calculator.h"
#include <fstream>

using namespace std;

ReportExporter::ReportExporter(const string& fileName) {
    this->fileName = fileName.empty() ? "fitness_report.txt" : fileName;
}

bool ReportExporter::exportUserReport(
    const UserProfile& user,
    const RecordManager& recordManager
) const {
    ofstream outFile(fileName);

    if (!outFile.is_open()) {
        return false;
    }

    CalorieCalculator calorieCalculator(
        user.getGender(),
        user.getAge(),
        user.getHeightCm(),
        user.getWeightKg(),
        user.getActivityLevel(),
        user.getGoal()
    );

    outFile << "===== Fitness Tracker Progress Report =====\n\n";

    outFile << "===== User Profile =====\n";
    outFile << "Name: " << user.getName() << endl;
    outFile << "Age: " << user.getAge() << endl;
    outFile << "Gender: " << user.getGender() << endl;
    outFile << "Height: " << user.getHeightCm() << " cm" << endl;
    outFile << "Weight: " << user.getWeightKg() << " kg" << endl;
    outFile << "Activity level: " << user.getActivityLevel() << endl;
    outFile << "Goal: " << user.getGoal() << endl;

    outFile << "\n===== Calorie Estimate =====\n";
    outFile << "Recommended daily calories: "
            << calorieCalculator.calculate() << " kcal" << endl;
    outFile << calorieCalculator.getRecommendation() << endl;
    outFile << "This is an estimate, not a medical nutrition plan.\n";

    outFile << "\nSaved personal records: "
            << recordManager.getRecordCount() << endl;

    recordManager.writeAllRecords(outFile);

    outFile << "\n===== End Of Report =====\n";

    outFile.close();

    return true;
}

string ReportExporter::getFileName() const {
    return fileName;
}