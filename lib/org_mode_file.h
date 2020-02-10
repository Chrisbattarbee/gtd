//
// Created by chris on 08/02/2020.
//

#ifndef GTD_ORG_MODE_FILE_H
#define GTD_ORG_MODE_FILE_H
#include <string>
#include <optional>
#include <vector>
#include <set>

class Item;

class OrgModeFile {
public:
    explicit OrgModeFile(std::string path);
    void write_file();
    Item* get_root_item();
private:
    std::vector<std::string>* getLines(const std::string *path) const;
    void add_all_subitems(std::vector<std::string> *lines, int indentation_level, int line_after_parent, Item *parent_item, std::set<int>* linesParsed);
    void produce_lines_for_file_write(Item *item, std::vector<std::string>* out_lines);
    int get_number_of_asterisks(std::string* s);

    std::string path;
    Item* root_item;
};

enum TodoStatus {
    TODO,
    IN_PROGRESS,
    SCHEDULED,
    WAITING,
    BLOCKED,
    CANCELLED,
    DONE
};

class Item {
public:
    Item(Item* parent, std::string title);
    Item(Item* parent, std::string title, TodoStatus status);
    bool is_todo();
    std::optional<TodoStatus> get_todo_status();
    // Returns the previous tdo status if there was one
    std::optional<TodoStatus> set_todo_status(TodoStatus todo_status);
    std::vector<std::string*>* get_tags();
    void add_tag(std::string* tag);
    std::vector<Item*>* get_children();
    std::string get_title();
    void add_child(Item *child);
    std::vector<std::string>* get_content();
    void set_content(std::vector<std::string>* content);
    void add_content_line(std::string content_line);

private:
    Item* parent;
    std::string title;
    std::optional<TodoStatus> todo_status;
    std::vector<Item*>* children;
    std::vector<std::string>* content;
};


#endif //GTD_ORG_MODE_FILE_H
