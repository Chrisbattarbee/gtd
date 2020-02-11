//
// Created by chris on 11/02/2020.
//

#ifndef GTD_CREATE_SUBCOMMAND_H
#define GTD_CREATE_SUBCOMMAND_H

#include <string>
#include "../CLI11.hpp"

struct CreateSubCommandOptions {
    std::string project_name;
};

void setup_create_subcommand(CLI::App &app);
void run_create_subcommand(CreateSubCommandOptions const &opt);


#endif //GTD_CREATE_SUBCOMMAND_H
