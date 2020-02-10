//
// Created by chris on 10/02/2020.
//

#include "list_subcommand.h"
#include "../gtd.h"
#include "utils.h"
#include <iostream>

void setup_list_subcommand(CLI::App &app) {
    auto opts = std::make_shared<ListSubCommandOptions>();
    auto list_subcommand = app.add_subcommand("l", "List projects.");

    list_subcommand->callback([opts]() {run_list_subcommand(*opts);});
}

void run_list_subcommand(ListSubCommandOptions const &opt) {
    auto gtd = new Gtd(get_project_directory());
    std::cout << "Current projects are: " << std::endl;
    for (auto project: *gtd->get_projects()) {
        std::cout << project->get_name()->c_str() << std::endl;
    }
}
