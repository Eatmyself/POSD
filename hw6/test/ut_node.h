#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/link.h"

class NodeTest: public ::testing::Test {
protected:
    void SetUp() {
        home = new Folder("structure/home");

        profile = new File("structure/home/my_profile");
        home->add(profile);

        download = new Folder("structure/home/Downloads");
        home->add(download);

        document = new Folder("structure/home/Documents");
        home->add(document);

        note = new File("structure/home/Documents/note.txt");
        document->add(note);

        favorite = new Folder("structure/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("structure/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("structure/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("structure/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);
    }

    void TearDown() {
        delete home;
        home = nullptr;
        profile = nullptr;
        download = nullptr;
        document = nullptr;
        note = nullptr;
        favorite = nullptr;
        ddd = nullptr;
        ca = nullptr;
        cqrs = nullptr;
    }
    
    Node * home;
    Node * profile;
    Node * download;
    Node * document;
    Node * note;
    Node * favorite;
    Node * ddd;
    Node * ca;
    Node * cqrs;
};


TEST_F(NodeTest, numberOfFiles) {
    ASSERT_EQ(5, home->numberOfFiles());
}

TEST_F(NodeTest, find_a_file) {
    Node * result = home->find("structure/home/Documents/favorites/cqrs.pdf");
    ASSERT_EQ(cqrs, result);
}

TEST_F(NodeTest, find_a_file_not_exist) {
    Node * result = home->find("structure/home/Documents/favorites/helloworld.pdf");
    ASSERT_EQ(nullptr, result);
}

TEST_F(NodeTest, find_a_folder) {
    Node * result = document->find("structure/home/Documents/favorites");
    ASSERT_EQ(favorite, result);
}

TEST_F(NodeTest, find_a_folder_not_exist) {
    Node * result = document->find("structure/home/Documents/not_like");
    ASSERT_EQ(nullptr, result);
}

TEST_F(NodeTest, delete_a_file) {
    ASSERT_EQ(cqrs->name(), home->find("structure/home/Documents/favorites/cqrs.pdf")->name());
    home->remove("structure/home/Documents/favorites/cqrs.pdf");
    ASSERT_EQ(nullptr, home->find("structure/home/Documents/favorites/cqrs.pdf"));
}

TEST_F(NodeTest, delete_a_folder) {
    ASSERT_EQ(favorite->name(), home->find("structure/home/Documents/favorites")->name());
    home->remove("structure/home/Documents/favorites");
    ASSERT_EQ(nullptr, home->find("structure/home/Documents/favorites"));
}

TEST_F(NodeTest, find_file_by_name) {
    std::list<string> result = home->findByName("cqrs.pdf");
    ASSERT_EQ(1, result.size());
    ASSERT_EQ("structure/home/Documents/favorites/cqrs.pdf", *(result.begin()));
}

TEST_F(NodeTest, find_file_by_name_not_exist) {
    std::list<string> result = home->findByName("helloworld.pdf");
    ASSERT_EQ(0, result.size());
}

TEST_F(NodeTest, find_folder_by_name) {
    std::list<string> result = document->findByName("favorites");
    ASSERT_EQ(1, result.size());
    ASSERT_EQ(favorite->path(), *(result.begin()));
}

TEST_F(NodeTest, find_folder_by_name_not_exist) {
    std::list<string> result = document->findByName("not_like");
    ASSERT_EQ(0, result.size());
}

TEST_F(NodeTest, rename_node) {
    document->rename("haha");
    ASSERT_EQ("structure/home/haha", document->path());
    ASSERT_EQ("structure/home/haha/note.txt", document->getChildByName("note.txt")->path());
    ASSERT_EQ("structure/home/haha/favorites/clean-architecture.pdf", ca->path());
}

TEST_F(NodeTest, link) {
    Node * funny = new File("structure/home/Downloads/funny.png");
    Node * link = new Link("structure/home/Downloads/link_to_funny.png", funny);
    download->add(funny);
    download->add(link);
    
    ASSERT_EQ("structure/home/Downloads/funny.png", download->getChildByName("funny.png")->path());
    ASSERT_EQ("structure/home/Downloads/link_to_funny.png", download->getChildByName("link_to_funny.png")->path());
}