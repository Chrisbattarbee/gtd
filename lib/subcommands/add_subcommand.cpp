//
// Created by chris on 10/02/2020.
//

#include "add_subcommand.h"
#include "../gtd.h"
#include "utils.h"
#include <time.h>
#include <sstream>
#include <utility>
#include <vector>

void maybe_add_date(const AddSubCommandOptions *pOptions, Item *pItem, std::optional<std::string> time);
std::optional<std::string> get_time(const AddSubCommandOptions *pOptions);
std::vector<std::string> split(const std::string &s, char delim);

// TODO add validation to all options
void setup_add_subcommand(CLI::App &app) {
    auto opts = std::make_shared<AddSubCommandOptions>();
    auto add_subcommand = app.add_subcommand("a", "Add a task to the inbox.");

    add_subcommand->add_option("-d", opts->date, "Deadline date");
    add_subcommand->add_option("-t", opts->time, "Deadline time");

    add_subcommand->add_option("todo_item", opts->todo_item, "Todo Item")->required();
    add_subcommand->callback([opts]() {run_add_subcommand(*opts);});
}

void run_add_subcommand(AddSubCommandOptions const &opt) {
    auto gtd = new Gtd(get_project_directory());
    Project *const &inbox = gtd->get_project("inbox").value();
    auto root_item = inbox->get_root_item();
    auto new_item = new Item(root_item, opt.todo_item, TODO);
    maybe_add_date(&opt, new_item, get_time(&opt));
    root_item->add_child(new_item);
    inbox->write_project();
}

std::optional<std::string> get_time(const AddSubCommandOptions *pOptions) {
    std::string time = pOptions->time;
    if (time.empty()) {
        return std::nullopt;
    }
    auto noPostModifier = time.substr(0, time.length() - 2); // Pop the am / pm

    std::string hour, minutes;
    if (time.find(':') != std::string::npos) {
        // We have minutes
        hour = split(noPostModifier, ':').at(0);
        minutes = split(noPostModifier, ':').at(1);
    } else {
        hour = noPostModifier;
        minutes = "0";
    }
    if (time.find("pm") != std::string::npos) {
        hour = std::to_string(std::stoi(hour) + 12);
    }
    return std::optional<std::string>(
            std::string(2 - hour.length(), '0') +
            hour +
            ':' +
            std::string(2 - minutes.length(), '0') +
            minutes
    );
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
std::string generate_org_string(tm* time, std::optional<std::string> timeString) {
    std::string day_of_week[] =  {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    return "<" +
    std::to_string(time->tm_year + 1900) +
    "-" +
    std::string(2 - std::to_string(time->tm_mon + 1).length(), '0') +
    std::to_string(time->tm_mon + 1) +
    "-" +
    std::string(2 - std::to_string(time->tm_mday + 1).length(), '0') +
    std::to_string(time->tm_mday) +
    " " +
    day_of_week[time->tm_wday] +
    (timeString.has_value() ? " " + timeString.value() : "") +
    ">";
}

void maybe_add_date(const AddSubCommandOptions *pOptions, Item *pItem, std::optional<std::string> timeString) {
    std::string date = pOptions->date;
    if (date.empty()) {
        return;
    }
    // TODO add mon, tue etc matching

    // Full date DD/MM/YYYY
    if (date.find('/') != std::string::npos) {
        int day, month, year;
        auto dmy = split(date, '/');
        if (dmy.size() != 3) {
            std::cout << "Invalid date format, not adding date" << std::endl;
        }
        day = std::stoi(dmy.at(0));
        month = std::stoi(dmy.at(1));
        year = std::stoi(dmy.at(2));

        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        timeinfo->tm_year = year - 1900;
        timeinfo->tm_mon = month - 1;
        timeinfo->tm_mday = day;
        mktime(timeinfo);
        pItem->add_content_line(generate_org_string(timeinfo, timeString));
        return;
    }

    // Just date DD
    int day = std::stoi(date);
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    if (timeinfo->tm_mday > day) {
        // So we can do 15 and have it be the next month if the current day is > 15 for example
        timeinfo->tm_mon += 1;
    }
    timeinfo->tm_mday = day;
    mktime(timeinfo);
    pItem->add_content_line(generate_org_string(timeinfo, timeString));
}
