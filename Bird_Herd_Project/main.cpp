#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const string CSV_HEADER =
    "sighting_id,timestamp,camera_id,location,"
    "plate_read,vehicle_type,color";

// Read a line and normalize a possible Windows line ending.
bool readCsvLine(istream& input, string& line) {
    if (!getline(input, line)) {
        return false;
    }

    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }

    return true;
}

bool readHeader(istream& input) {
    string header;

    return readCsvLine(input, header)
        && header == CSV_HEADER;
}

// Parses structure and the integer field.
// Domain validation is introduced later.
bool parseRow(
    const string& line,
    int& id,
    string& timestamp,
    string& camera,
    string& location,
    string& plate,
    string& vehicleType,
    string& color
) {
    istringstream row(line);
    string idText;

    if (!getline(row, idText, ',')
        || !getline(row, timestamp, ',')
        || !getline(row, camera, ',')
        || !getline(row, location, ',')
        || !getline(row, plate, ',')
        || !getline(row, vehicleType, ',')
        || !getline(row, color)) {
        return false;
    }

    // Reject an unexpected eighth field.
    if (color.find(',') != string::npos) {
        return false;
    }

    istringstream number(idText);

    if (!(number >> id)) {
        return false;
    }

    number >> ws;
    return number.eof();
}


int main() 
{

    ifstream input("sightings.csv");
    string lineFromBatteryScan;

    int amountLowBatteries = 0;
    int amountReadyBatteries = 0;
    int amountInvalidBatteries = 0;

    //check to make sure we actually found the file.
    if (!input) {
        cout << "Could not open battery_scan.txt\n";
        return 1;
    }

    //if we get this far... then lets read the first line
    while (getline(input, lineFromBatteryScan)) {
        cout << lineFromBatteryScan << '\n';
        int convertedBatteryScanLine;
        convertedBatteryScanLine = stoi(lineFromBatteryScan);
    }


    return 0;
}
