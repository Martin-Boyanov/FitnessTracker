#include "../include/PersonalRecord.h"
#include <iostream>

using namespace std;

PersonalRecord::PersonalRecord(
    const string& exerciseName,
    double value,
    const string& unit,
    const string& gender,
    double bodyWeightKg
) {
    this->exerciseName = exerciseName;
    this->value = value > 0 ? value : 0;
    this->unit = unit;
    this->gender = gender;
    this->bodyWeightKg = bodyWeightKg > 0 ? bodyWeightKg : 70;
}

string PersonalRecord::getExerciseName() const {
    return exerciseName;
}

double PersonalRecord::getValue() const {
    return value;
}

string PersonalRecord::getUnit() const {
    return unit;
}

bool PersonalRecord::updateIfBetter(double newValue) {
    if (newValue > value) {
        value = newValue;
        return true;
    }

    return false;
}

int PersonalRecord::estimatePercentile() const {
    bool isMale = gender == "Male";

    if (exerciseName == "Push-up") {
        if (isMale) {
            if (value >= 60) return 95;
            if (value >= 40) return 85;
            if (value >= 25) return 65;
            if (value >= 10) return 40;
            return 20;
        }

        if (value >= 35) return 95;
        if (value >= 25) return 85;
        if (value >= 15) return 65;
        if (value >= 5) return 40;
        return 20;
    }

    if (exerciseName == "Pull-up") {
        if (isMale) {
            if (value >= 25) return 97;
            if (value >= 15) return 90;
            if (value >= 8) return 70;
            if (value >= 3) return 45;
            return 20;
        }

        if (value >= 10) return 95;
        if (value >= 5) return 85;
        if (value >= 2) return 65;
        if (value >= 1) return 40;
        return 20;
    }

    if (exerciseName == "Plank") {
        if (value >= 300) return 97;
        if (value >= 180) return 90;
        if (value >= 120) return 80;
        if (value >= 60) return 65;
        if (value >= 30) return 40;
        return 20;
    }

    if (unit == "kg") {
        double ratio = value / bodyWeightKg;

        if (exerciseName == "Squat") {
            if (ratio >= 2.0) return 95;
            if (ratio >= 1.5) return 85;
            if (ratio >= 1.0) return 65;
            if (ratio >= 0.75) return 45;
            return 20;
        }

        if (exerciseName == "Bench Press") {
            if (ratio >= 1.5) return 95;
            if (ratio >= 1.25) return 85;
            if (ratio >= 1.0) return 70;
            if (ratio >= 0.75) return 50;
            if (ratio >= 0.5) return 30;
            return 15;
        }

        if (exerciseName == "Dumbbell Row") {
            if (ratio >= 0.75) return 90;
            if (ratio >= 0.55) return 75;
            if (ratio >= 0.40) return 55;
            if (ratio >= 0.25) return 35;
            return 15;
        }

        if (exerciseName == "Dumbbell Shoulder Press") {
            if (ratio >= 0.60) return 90;
            if (ratio >= 0.45) return 75;
            if (ratio >= 0.30) return 55;
            if (ratio >= 0.20) return 35;
            return 15;
        }
    }

    return 50;
}

string PersonalRecord::getPerformanceLevel() const {
    int percentile = estimatePercentile();

    if (percentile >= 95) {
        return "Elite";
    }

    if (percentile >= 85) {
        return "Very strong";
    }

    if (percentile >= 65) {
        return "Good";
    }

    if (percentile >= 40) {
        return "Average";
    }

    return "Beginner";
}

void PersonalRecord::showRecord() const {
    cout << *this << endl;
}

void PersonalRecord::showInsight() const {
    writeInsight(cout);
}

void PersonalRecord::writeInsight(ostream& out) const {
    int percentile = estimatePercentile();

    out << "\nPerformance insight:\n";
    out << "Estimated level: " << getPerformanceLevel() << endl;
    out << "Estimated benchmark: stronger than roughly "
        << percentile << "% of casual ";

    if (gender == "Male") {
        out << "male";
    } else {
        out << "female";
    }

    out << " users in this simplified project benchmark.\n";

    if (unit == "kg") {
        out << "Strength ratio: " << value / bodyWeightKg
            << "x your body weight." << endl;
    }

    if (exerciseName == "Push-up") {
        out << "This is based on maximum push-up repetitions in one set.\n";
    } else if (exerciseName == "Pull-up") {
        out << "This is based on maximum pull-up repetitions in one set.\n";
    } else if (exerciseName == "Plank") {
        out << "This is based on maximum plank hold time.\n";
    } else {
        out << "This is based on your best lifted weight compared to your body weight.\n";
    }

    out << "Note: This is not a scientific population percentile. It is an estimated fitness benchmark for the project.\n";
}

ostream& operator<<(ostream& out, const PersonalRecord& record) {
    out << record.exerciseName << ": "
        << record.value << " "
        << record.unit;

    return out;
}

int RecordManager::findRecordIndex(const string& exerciseName) const {
    for (int i = 0; i < (int)records.size(); i++) {
        if (records[i].getExerciseName() == exerciseName) {
            return i;
        }
    }

    return -1;
}

void RecordManager::addOrUpdateRecord(
    const string& exerciseName,
    double value,
    const string& unit,
    const string& gender,
    double bodyWeightKg
) {
    int index = findRecordIndex(exerciseName);

    if (index == -1) {
        PersonalRecord record(
            exerciseName,
            value,
            unit,
            gender,
            bodyWeightKg
        );

        records.push_back(record);

        cout << "\nNew personal record added.\n";
        record.showRecord();
        record.showInsight();
        return;
    }

    bool improved = records[index].updateIfBetter(value);

    if (improved) {
        cout << "\nNew personal record.\n";
        records[index].showRecord();
        records[index].showInsight();
    } else {
        cout << "\nThis is not a new personal record.\n";
        cout << "Current record: ";
        records[index].showRecord();
        records[index].showInsight();
    }
}

void RecordManager::showAllRecords() const {
    cout << "\n===== Personal Records =====\n";

    if (records.empty()) {
        cout << "No personal records saved yet.\n";
        return;
    }

    for (const PersonalRecord& record : records) {
        cout << "\n-------------------------\n";
        record.showRecord();
        record.showInsight();
    }
}

void RecordManager::writeAllRecords(ostream& out) const {
    out << "\n===== Personal Records =====\n";

    if (records.empty()) {
        out << "No personal records saved yet.\n";
        return;
    }

    for (const PersonalRecord& record : records) {
        out << "\n-------------------------\n";
        out << record << endl;
        record.writeInsight(out);
    }
}

int RecordManager::getRecordCount() const {
    return (int)records.size();
}