//
// Created by chris on 10/02/2020.
//

#ifndef GTD_ADD_SUBCOMMAND_H
#define GTD_ADD_SUBCOMMAND_H

#include <string>
#include "../CLI11.hpp"

struct AddSubCommandOptions {
    std::string todo_item;
};

void setup_add_subcommand(CLI::App &app);
void run_add_subcommand(AddSubCommandOptions const &opt);

#endif //GTD_ADD_SUBCOMMAND_H
