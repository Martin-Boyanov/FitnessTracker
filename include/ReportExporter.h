#ifndef REPORTEXPORTER_H
#define REPORTEXPORTER_H

#include <string>
#include "UserProfile.h"
#include "PersonalRecord.h"

using namespace std;

class ReportExporter {
private:
    string fileName;

public:
    ReportExporter(const string& fileName);

    bool exportUserReport(
        const UserProfile& user,
        const RecordManager& recordManager
    ) const;

    string getFileName() const;
};

#endif