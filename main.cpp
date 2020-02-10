#include <iostream>
#include "lib/org_mode_file.h"

int main() {
    std::string input_path = std::string("/home/chris/notes/gtd/inbox.org");
    OrgModeFile* org_mode_file = new OrgModeFile(input_path);
    org_mode_file->write_file();
}
