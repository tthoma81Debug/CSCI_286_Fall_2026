#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const string CSV_HEADER =
    "sighting_id,timestamp,camera_id,location,"
    "plate_read,vehicle_type,color";


std::string getPart(const std::string& line, int targetComma) {
    int commas = 0;
    size_t start = 0;

    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == ',') {
            if (commas == targetComma) {
                return line.substr(start, i - start);
            }
            commas++;
            start = i + 1;
        }
    }

    // Return the last part if targetComma matches the final segment
    if (commas == targetComma) {
        return line.substr(start);
    }

    return "";
}

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
    string lineFromSightings;
    string enteredPlate;
    string fieldFromLine;
    string timestamp;
    int totalPlateMatches = 0;

    //check to make sure we actually found the file.
    if (!input) {
        cout << "Could not open sightings.csv\n";
        return 1;
    }

    //read and consume header
    readHeader(input);

    cout <<"Please enter a plate \n";
    cin >> enteredPlate;

    //if we get this far... then lets read the first line
    while (getline(input, lineFromSightings)) {
        //cout << lineFromSightings << '\n';
       
        fieldFromLine = getPart(lineFromSightings, 4);

        //cout << "Just extracted fieldFromLine " << fieldFromLine << "\n";

        if(fieldFromLine == enteredPlate)
        {
            //found a match
            cout << "Plate found! \n";
            totalPlateMatches++;

            timestamp = getPart(lineFromSightings, 1);

        }
        else
        {
            //plate not found on THIS line
        }
        
        
        //convertedBatteryScanLine = stoi(lineFromBatteryScan);
        
    
    
    } //end loop

    cout << "Found " << totalPlateMatches << " total plate matches \n";


    return 0;
}
