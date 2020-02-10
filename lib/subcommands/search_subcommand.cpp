//
// Created by chris on 10/02/2020.
//

#include "search_subcommand.h"

void setup_search_subcommand(CLI::App &app) {
    auto opts = std::make_shared<SearchSubCommandOptions>();
    auto search_subcommand = app.add_subcommand("s", "Search gtd tasks.");

    search_subcommand->add_option("search_term", opts->search_term, "Search Term")->required();
    search_subcommand->callback([opts]() {run_search_subcommand(*opts);});
}

void run_search_subcommand(SearchSubCommandOptions const &opt) {

}
