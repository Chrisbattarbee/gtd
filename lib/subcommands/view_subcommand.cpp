//
// Created by chris on 10/02/2020.
//

#include "view_subcommand.h"
#include "../gtd.h"
#include "utils.h"

void setup_view_subcommand(CLI::App &app) {
    auto opts = std::make_shared<ViewSubCommandOptions>();
    auto view_subcommand = app.add_subcommand("v", "View project.");

    view_subcommand->add_option("project", opts->project, "Project to view")->required();
    view_subcommand->callback([opts]() {run_view_subcommand(*opts);});
}

void run_view_subcommand(ViewSubCommandOptions const &opt) {
    auto gtd = new Gtd(get_project_directory());
    auto project = gtd->get_project(opt.project);
    if (project.has_value()) {
        std::cout << "Project: " << opt.project << std::endl << std::endl << project.value()->to_string();
    } else {
        std::cout << "Project " << opt.project << " does not exist." << std::endl;
    }
}