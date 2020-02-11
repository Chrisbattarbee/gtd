//
// Created by chris on 11/02/2020.
//

#ifndef GTD_DELETE_SUBCOMMAND_H
#define GTD_DELETE_SUBCOMMAND_H

#include "../CLI11.hpp"

struct DeleteSubCommandOptions {
    std::string project_name;
};

void setup_delete_subcommand(CLI::App &app);
void run_delete_subcommand(DeleteSubCommandOptions const &opt);

#endif //GTD_DELETE_SUBCOMMAND_H
