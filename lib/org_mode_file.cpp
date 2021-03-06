#include <iostream>
#include <fstream>
#include <set>

#include "org_mode_file.h"
#include "magic_enum.hpp"

OrgModeFile::OrgModeFile(std::string path, bool create) {
    Item *root_item = new Item(nullptr, "");
    if (!create) {
        std::vector<std::string> *lines = getLines(&path);
        add_all_subitems(lines, 1, 0, root_item, new std::set<int>);
    }
    this->path = path;
    this->root_item = root_item;
}

int OrgModeFile::get_number_of_asterisks(std::string *s) {
    int total = 0;
    for (char x: *s) {
        if (x == '*') {
            total++;
        } else {
            break;
        }
    }
    return total;
}

void OrgModeFile::add_all_subitems(std::vector<std::string> *lines, int indentation_level, int line_after_parent,
                                   Item *parent_item, std::set<int> *linesParsed) {
    std::string line;
    int x = line_after_parent;
    while (x < lines->size()) {
        line = lines->at(x);
        int numAsterisks = this->get_number_of_asterisks(&line);
        if (linesParsed->contains(x)) {
            x++;
            continue;
        }

        if (numAsterisks >= indentation_level) {
            linesParsed->insert(x);
            Item *newChild = new Item(parent_item, line);
            parent_item->add_child(newChild);
            add_all_subitems(lines, indentation_level + 1, x + 1, newChild, linesParsed);
        } else if (numAsterisks == 0) {
            // It is content
            linesParsed->insert(x);
            parent_item->add_content_line(line);
        } else {
            break;
        }
        x++;
    }

}

std::vector<std::string> *OrgModeFile::getLines(const std::string *path) const {
    std::ifstream org_file;
    org_file.open(path->c_str());
    std::string line;
    auto *lines = new std::vector<std::string>();
    if (org_file.is_open()) {
        while (std::getline(org_file, line)) {
            lines->push_back(line);
        }
        org_file.close();
    }
    return lines;
}

Item *OrgModeFile::get_root_item() {
    return this->root_item;

}

void OrgModeFile::produce_lines_for_file_write(Item *item, std::vector<std::string> *out_lines) {
    if (item != root_item) {
        // So we dont have an empty blank line at the beginning
        out_lines->push_back(item->get_title());
    }
    for (const auto &content_line: *item->get_content()) {
        out_lines->push_back(content_line);
    }
    for (auto child: *item->get_children()) {
        produce_lines_for_file_write(child, out_lines);
    }
}

void OrgModeFile::write_file() {
    auto out_lines = new std::vector<std::string>();
    produce_lines_for_file_write(root_item, out_lines);
    std::ofstream org_file;
    org_file.open(path);
    if (org_file.is_open()) {
        for (const auto &line: *out_lines) {
            org_file << line << std::endl;
        }
    }
    org_file.close();
}

std::string OrgModeFile::to_string() {
    // TODO Make this better than just the file
    auto lines = new std::vector<std::string>();
    produce_lines_for_file_write(this->root_item, lines);
    std::string ret = "";
    for (const auto& line: *lines) {
        ret += line + "\n";
    }
    return ret;
}

std::string OrgModeFile::get_path() {
    return this->path;
}

Item::Item(Item *parent, std::string title) {
    if (OrgModeFile::get_number_of_asterisks(&title) == 0 && parent != nullptr) {
        auto parent_title = parent->get_title();
        int num_asterisks_to_add = OrgModeFile::get_number_of_asterisks(&parent_title) + 1;
        for (int x = 0; x < num_asterisks_to_add; x++) {
            title.insert(0, "*");
        }
        title.insert(num_asterisks_to_add, " ");
    }
    this->parent = parent;
    this->title = title;
    this->todo_status = std::nullopt;
    this->children = new std::vector<Item *>;
    this->content = new std::vector<std::string>;
}

void Item::add_child(Item *child) {
    this->children->push_back(child);
}

std::optional<TodoStatus> Item::get_todo_status() {
    return this->todo_status;
}

Item::Item(Item *parent, std::string title, TodoStatus status) : Item::Item(parent, title) {
    this->todo_status = std::optional<TodoStatus>(status);
    this->title.insert(OrgModeFile::get_number_of_asterisks(&this->title) + 1, " ");
    this->title.insert(OrgModeFile::get_number_of_asterisks(&this->title) + 1, magic_enum::enum_name(status));
}

bool Item::is_todo() {
    return this->todo_status.has_value();
}

std::optional<TodoStatus> Item::set_todo_status(TodoStatus todo_status) {
    auto prev = this->get_todo_status();
    this->todo_status = std::optional<TodoStatus>(todo_status);
    return prev;
}

std::vector<Item *> *Item::get_children() {
    return this->children;
}

std::string Item::get_title() {
    return this->title;
}

void Item::add_content_line(std::string content_line) {
    this->content->push_back(content_line);
}

std::vector<std::string> *Item::get_content() {
    return this->content;
}

