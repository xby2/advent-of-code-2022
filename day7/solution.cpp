#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>

using std::string;
using std::map;
using std::cout;
using std::endl;
using std::ifstream;
using std::stringstream;
using std::getline;

struct File {
    int size = 0;
    string name;
    File* parent;
    map<string, File> files;
};

int get_dir_size(const File& file) {
    int total = file.size;
    for (const auto& p : file.files) {
        total += get_dir_size(p.second);
    }
    return total;
}

string get_dir_name(const File* file) {
    if (!file->parent) {
        return file->name;
    }

    return get_dir_name(file->parent) + '/' + file->name;
}

int main() {
    ifstream input("input.txt");

    File root{0, "/", nullptr};
    File* current_file = nullptr;
    map<string, File*> dirs;

    string line;
    while (getline(input, line)) {
        if (line[0] == '$') {
            string cmd = line.substr(2, 2);
            if (cmd == "cd") {
                string dir = line.substr(5);
                if (dir == "..") {
                    current_file = current_file->parent;
                } else if (dir == "/") {
                    current_file = &root;
                } else if (!current_file->files.contains(dir)) {
                    current_file->files[dir] = File{ 0, dir, current_file };
                    current_file = &(current_file->files[dir]);
                    dirs[get_dir_name(current_file)] = current_file;
                } else {
                    current_file = &(current_file->files[dir]);
                }
            }
            // don't need to do anything for ls
        }
        else {
            stringstream data(line);
            string dir, name;
            int size = 0;
            if (data >> size) {
                data >> name;
            } else {
                data >> dir >> name;
            }
            if (!current_file->files.contains(name)) {
                current_file->files[name] = File{ size, name, current_file };
            }
        }
    }

    int total = 0;
    for (const auto& p : dirs) {
        int size = get_dir_size(*(p.second));
        if (size <= 100000) {
            total += size;
        }
    }

    cout << total << endl;

    const int DISK_SPACE = 70000000;
    const int NEEDED_SPACE = 30000000;
    int used_space = get_dir_size(root);

    int min_file_size = used_space;
    for (const auto& p : dirs) {
        int size = get_dir_size(*(p.second));
        if (DISK_SPACE - used_space + size >= NEEDED_SPACE && size < min_file_size) {
            min_file_size = size;
        }
    }

    cout << min_file_size << endl;
}