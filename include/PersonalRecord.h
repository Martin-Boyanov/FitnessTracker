#ifndef PERSONALRECORD_H
#define PERSONALRECORD_H

#include <string>
#include <vector>
#include <ostream>

using namespace std;

class PersonalRecord {
private:
    string exerciseName;
    double value;
    string unit;
    string gender;
    double bodyWeightKg;

    int estimatePercentile() const;
    string getPerformanceLevel() const;

public:
    PersonalRecord(
        const string& exerciseName,
        double value,
        const string& unit,
        const string& gender,
        double bodyWeightKg
    );

    string getExerciseName() const;
    double getValue() const;
    string getUnit() const;

    bool updateIfBetter(double newValue);
    void showRecord() const;
    void showInsight() const;
    void writeInsight(ostream& out) const;

    friend ostream& operator<<(ostream& out, const PersonalRecord& record);
};

class RecordManager {
private:
    vector<PersonalRecord> records;

    int findRecordIndex(const string& exerciseName) const;

public:
    void addOrUpdateRecord(
        const string& exerciseName,
        double value,
        const string& unit,
        const string& gender,
        double bodyWeightKg
    );

    void showAllRecords() const;
    void writeAllRecords(ostream& out) const;
    int getRecordCount() const;
};

#endif