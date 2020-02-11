//
// Created by chris on 11/02/2020.
//

#include "create_subcommand.h"
#include "../gtd.h"
#include "utils.h"

void setup_create_subcommand(CLI::App &app) {
    auto opts = std::make_shared<CreateSubCommandOptions>();
    auto create_subcommand = app.add_subcommand("c", "Create a new project.");

    create_subcommand->add_option("project_name", opts->project_name, "Project Name.")->required();
    create_subcommand->callback([opts]() {run_create_subcommand(*opts);});
}

void run_create_subcommand(CreateSubCommandOptions const &opt) {
    auto gtd = new Gtd(get_project_directory());
    Project* new_project = gtd->create_project(opt.project_name);
    new_project->write_project();
}
