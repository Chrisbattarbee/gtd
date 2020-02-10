//
// Created by chris on 10/02/2020.
//

#ifndef GTD_LIST_SUBCOMMAND_H
#define GTD_LIST_SUBCOMMAND_H

#include <string>
#include "../CLI11.hpp"

struct ListSubCommandOptions {
};

void setup_list_subcommand(CLI::App &app);
void run_list_subcommand(ListSubCommandOptions const &opt);

#endif //GTD_LIST_SUBCOMMAND_H
