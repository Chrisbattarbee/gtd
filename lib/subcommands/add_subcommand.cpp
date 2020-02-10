//
// Created by chris on 10/02/2020.
//

#include "add_subcommand.h"
#include "../gtd.h"
#include "utils.h"

void setup_add_subcommand(CLI::App &app) {
    auto opts = std::make_shared<AddSubCommandOptions>();
    auto add_subcommand = app.add_subcommand("a", "Add a task to the inbox.");

    add_subcommand->add_option("todo_item", opts->todo_item, "Todo Item")->required();
    add_subcommand->callback([opts]() {run_add_subcommand(*opts);});
}

void run_add_subcommand(AddSubCommandOptions const &opt) {
    auto gtd = new Gtd(get_project_directory());
    Project *const &inbox = gtd->get_project("inbox").value();
    auto root_item = inbox->get_root_item();
    root_item->add_child(new Item(root_item, opt.todo_item, TODO));
    inbox->write_project();
}
