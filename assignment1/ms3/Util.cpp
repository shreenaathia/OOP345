/* OOP345-Assignment 1 - MS3

File: Util.cpp | Version: MS2.0.2 | Date: 11/13/16 | Author: Marco Beltempo |
Email mabeltempo@myseneca.ca | SID: 031028095

Revision History
__________________________________________________________________________________________
| Name      | Date  | Reason                                                                |
| ------------------------------------------------------------------------------------------|
|M.Beltempo 11/18/16 Relocated implementations of, trim and csvReader functions from Task.  |
|M.Beltempo 11/23/16 Define bool functions to validate task names and slot vlaues.          |
|___________________________________________________________________________________________| */
#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;
namespace ms3 {

    string& trim(string& string) {

        while (!string.empty() && isspace(string[0])) {
            string.erase(0, 1);
        }
        while (!string.empty() && isspace(string[string.size() - 1])) {
            string.erase(string.size() - 1, 1);
        }

        return string;
    }
#define PROCESS_DOUBLE_QUOTES
    void csvReader(string filename, char delimiter, vector <vector<string> > &data) {

        ifstream is(filename.c_str());

        if (is.is_open()) {

            string s;

            while (getline(is, s)) {

                auto c = s.find("\r");

                if (c != string::npos) {
                    s.erase(c, 1);
                }

                string field;
                for (size_t i = 0; i < s.size(); i++) {
#ifdef PROCESS_DOUBLE_QUOTES
                    if (s[i] == '"') {
                        field += s[i];        // copy 1st "
                        for (i++; i < s.size(); i++) {
                            field += s[i];
                            if (s[i] == '"')     // found 2nd "
                                break;
                        }
                    }
                }
          
#endif
                stringstream ss(s);
                vector <string> fields;
         

                while (getline(ss, field, delimiter)) {

                    trim(field);
                    fields.push_back(field);
                }

                data.push_back(fields);
            }
        }

        else {
            throw string("Cannot open the file! \n") + filename;
        }
    }


    bool is_nameValid(const string& taskName) {
        if (taskName.empty()) {
            return false;
        }

        for (auto tasks : taskName) {
            if (isspace(tasks) || isalnum(tasks) || tasks == '_' /* || tasks =='-'*/ ) {
                continue;
            }
            return false;
        }
        return true;
    }

    bool is_slotValid(const string& slots) {
        if (slots.empty()) {
            return false;
        }
        for (auto chr : slots) {
            if (isdigit(chr)) {
                continue;
            }
            return false;
        }
        return true;
    }
}  // END namespace ms3