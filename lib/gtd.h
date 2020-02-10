//
// Created by chris on 10/02/2020.
//

#ifndef GTD_GTD_H
#define GTD_GTD_H

#include "org_mode_file.h"

class Project {
public:
    Project(std::string name, std::string path);
    void add_item(std::string title, std::optional<TodoStatus> todo_status);
    void add_sub_item(Item* parent_item, std::string title, std::optional<TodoStatus> todo_status);
    Item* get_root_item();
    std::string* get_name();
    void write_project();
private:
    OrgModeFile* backing_org_file;
    std::string name;
};

class Gtd {
public:
    Gtd(std::string root_directory);
    Project* create_project(std::string name);
    std::optional<Project*> get_project(std::string name);
private:
    std::string root_directory;
    std::vector<Project*>* projects;
};


#endif //GTD_GTD_H
