//
// Created by chris on 10/02/2020.
//

#include "utils.h"

std::string get_project_directory() {
    return std::string(getenv("HOME")) + "/notes/gtd/";
}
