
#include "lib/CLI11.hpp"
#include "lib/subcommands/add_subcommand.h"
#include "lib/subcommands/search_subcommand.h"
#include "lib/subcommands/list_subcommand.h"
#include "lib/subcommands/view_subcommand.h"
#include "lib/subcommands/create_subcommand.h"


int main(int argc, char** argv) {
    CLI::App app{"A command line tool to help with GTD."};
    setup_add_subcommand(app);
    setup_search_subcommand(app);
    setup_list_subcommand(app);
    setup_view_subcommand(app);
    setup_create_subcommand(app);
    app.require_subcommand();

    CLI11_PARSE(app, argc, argv);
}


