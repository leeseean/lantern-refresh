#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string random_id() {
    string id(8, ' ');
    srand((unsigned)time(0));
    for (int i = 0; i < 8; i++) {
        if (i % 3 == 0)
            id[i] = 'A' + rand() % 26;
        else if (i % 3 == 1)
            id[i] = 'a' + rand() % 26;
        else
            id[i] = '0' + rand() % 9;
    }
    return id;
}

int main(int argc, char *argv[]) {
    string file_path = getenv("appdata");
    file_path.append("\\Lantern\\lantern-9.9.9.yaml");

    ifstream ifs;
    ifs.open(file_path);
    if (ifs) {
        vector<string> v;
        vector<string>::iterator itv;
        string s;
        while (!ifs.eof()) {
            getline(ifs, s);
            v.push_back(s);
        }

        const string id = "deviceid: ";
        for (itv = v.begin(); itv < v.end(); ++itv) {
            if ((*itv).find(id) != string::npos) {
                int index = (*itv).find(id) + id.size();
                (*itv) = (*itv).substr(0, index) + random_id();
                break;
            }
        }

        ofstream ofs(file_path);
        for (itv = v.begin(); itv < v.end(); ++itv)
            ofs << *itv << endl;
        ofs.close();

        execv("Lantern.exe", argv);
    } else {
        ifs.close();
    }

    return 0;
}