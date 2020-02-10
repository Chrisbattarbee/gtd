//
// Created by chris on 10/02/2020.
//

#ifndef GTD_VIEW_SUBCOMMAND_H
#define GTD_VIEW_SUBCOMMAND_H

#include <string>
#include "../CLI11.hpp"

struct ViewSubCommandOptions {
    std::string project;
};

void setup_view_subcommand(CLI::App &app);
void run_view_subcommand(ViewSubCommandOptions const &opt);


#endif //GTD_VIEW_SUBCOMMAND_H
