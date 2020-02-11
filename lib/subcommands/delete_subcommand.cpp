//
// Created by chris on 11/02/2020.
//

#include "delete_subcommand.h"
#include "../gtd.h"
#include "utils.h"

void setup_delete_subcommand(CLI::App &app) {
    auto opts = std::make_shared<DeleteSubCommandOptions>();
    auto create_subcommand = app.add_subcommand("d", "Delete a project.");

    create_subcommand->add_option("project_name", opts->project_name, "Project Name.")->required();
    create_subcommand->callback([opts]() {run_delete_subcommand(*opts);});
}

void run_delete_subcommand(DeleteSubCommandOptions const &opt) {
    auto gtd = new Gtd(get_project_directory());
    auto project = gtd->get_project(opt.project_name);
    if (project.has_value()) {
        project.value()->delete_project();
        std::cout << "Deleted project " + opt.project_name << "." << std::endl;
    } else {
        std::cout << "Project " + opt.project_name << " does not exist." << std::endl;
    }
}
