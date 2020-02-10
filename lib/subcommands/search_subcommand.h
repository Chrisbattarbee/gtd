//
// Created by chris on 10/02/2020.
//

#ifndef GTD_SEARCH_SUBCOMMAND_H
#define GTD_SEARCH_SUBCOMMAND_H

#include <string>
#include "../CLI11.hpp"

struct SearchSubCommandOptions {
    std::string search_term;
};

void setup_search_subcommand(CLI::App &app);
void run_search_subcommand(SearchSubCommandOptions const &opt);

#endif //GTD_SEARCH_SUBCOMMAND_H
