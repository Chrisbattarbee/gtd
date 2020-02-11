//
// Created by chris on 10/02/2020.
//

#include "gtd.h"
#include "subcommands/utils.h"
#include <filesystem>


Project::Project(std::string name, std::string path, bool create_project) {
    this->name = name;
    this->backing_org_file = new OrgModeFile(path, create_project);
}

void Project::add_item(std::string title, std::optional<TodoStatus> todo_status) {
    this->add_sub_item(this->backing_org_file->get_root_item(), title, todo_status);
}

void Project::add_sub_item(Item *parent_item, std::string title, std::optional<TodoStatus> todo_status) {
    Item *new_item = todo_status != std::nullopt ?
                     new Item(this->backing_org_file->get_root_item(), title, todo_status.value()) :
                     new Item(this->backing_org_file->get_root_item(), title);

    parent_item->add_child(new_item);
}

Item *Project::get_root_item() {
    return this->backing_org_file->get_root_item();
}

std::string *Project::get_name() {
    return &this->name;
}

void Project::write_project() {
    this->backing_org_file->write_file();
}

std::string Project::to_string() {
    return backing_org_file->to_string();
}

void Project::delete_project() {
    std::filesystem::remove(this->backing_org_file->get_path());
}

Gtd::Gtd(std::string root_directory) {
    this->root_directory = root_directory;
    this->projects = new std::vector<Project*>;

    // Read all existing projects in
    for (const auto & entry : std::filesystem::directory_iterator(root_directory)) {
        if (entry.path().extension() != ".org") {
            continue;
        }
        auto* project = new Project(entry.path().filename().replace_extension(""), entry.path(), false);
        this->projects->push_back(project);
    }
}

Project *Gtd::create_project(std::string name) {
    auto* project = new Project(name, root_directory + name + ".org", true);
    this->projects->push_back(project);
    return project;
}

std::optional<Project*> Gtd::get_project(std::string name) {
    for (auto project: *this->projects) {
        if (name == *project->get_name()) {
            return std::optional<Project*>(project);
        }
    }
    return std::nullopt;
}

std::vector<Project *> *Gtd::get_projects() {
    return this->projects;
}
