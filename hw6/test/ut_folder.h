#include <string>
#include "../src/folder.h"

using namespace std;

TEST(Folder, normal) {
    Folder home("structure/home");

    ASSERT_EQ("home", home.name());
    ASSERT_EQ("structure/home", home.path());
}

TEST(Folder, invalid_folder) {
    ASSERT_ANY_THROW(Folder("/NOT/EXIST/PATH"));
}

TEST(Folder, invalid_folder_2) {
    ASSERT_ANY_THROW(Folder("structure/home/Documents/hello.txt"));
}

TEST(Folder, add_file) {
    Folder * home = new Folder("structure/home");
    File * hello = new File("structure/home/hello.txt");
    home->add(hello);

    ASSERT_EQ("hello.txt", home->getChildByName("hello.txt")->name());

    delete home;
}

TEST(Folder, add_incorrect_path_file_to_folder) {
    Folder * home = new Folder("structure/home");
    File * hello = new File("structure/home/Documents/hello.txt");
    ASSERT_ANY_THROW(home->add(hello));
    
    delete home;
}

TEST(Folder, add_folder) {
    Folder * home = new Folder("structure/home");
    Folder * document = new Folder("structure/home/Documents");

    home->add(document);

    ASSERT_EQ("Documents", home->getChildByName("Documents")->name());

    delete home;
}

TEST(Folder, rename_folder) {
    Folder * home = new Folder("structure/home");
    Folder * document = new Folder("structure/home/Documents");
    home->add(document);

    home->rename("haha");
    ASSERT_EQ("structure/haha", home->path());
    ASSERT_EQ("structure/haha/Documents", home->getChildByName("Documents")->path());

    delete home;
}
