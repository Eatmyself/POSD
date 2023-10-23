#pragma once 

#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/visitor.h"
#include "../src/find_by_name_visitor.h"
#include "../src/stream_out_visitor.h"

class VisitorTest: public ::testing::Test {
protected:
    void SetUp() {
        home = new Folder("Users/user/home");

        profile = new File("Users/user/home/my_profile.txt");
        home->add(profile);

        download = new Folder("Users/user/home/Downloads");
        home->add(download);

        document = new Folder("Users/user/home/Documents");
        home->add(document);

        note = new File("Users/user/home/Documents/note.txt");
        document->add(note);

        favorite = new Folder("Users/user/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("Users/user/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("Users/user/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("Users/user/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);

    }

    void TearDown() {
        delete home;
        delete profile;
        delete download;
        delete document;
        delete note;
        delete favorite;
        delete ddd;
        delete ca;
        delete cqrs;
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

TEST_F(VisitorTest, FindByName_Visitor) {
    std::list<string> pathList;
    FindByNameVisitor * visitor = new FindByNameVisitor("favorites");
    home->accept(visitor); 
    pathList = visitor->getPaths();

    for (auto it = pathList.begin(); it != pathList.end(); ++it) {
        ASSERT_EQ("Users/user/home/Documents/favorites", *it);
    }
}

TEST_F(VisitorTest, StreamOut_Visitor_file ) {
    StreamOutVisitor * visitor = new StreamOutVisitor;
    profile->accept(visitor);

    string output = visitor->getResult();
    ASSERT_EQ("_____________________________________________\nUsers/user/home/my_profile.txt\n---------------------------------------------\nmy_profile.txt\nww\n_____________________________________________\n", output);

}

TEST_F(VisitorTest, StreamOut_Visitor_folder) {
    StreamOutVisitor * visitor = new StreamOutVisitor;
    favorite->accept(visitor);

    string output = visitor->getResult();
    ASSERT_EQ("_____________________________________________\nUsers/user/home/Documents/favorites/domain-driven-design.pdf\n---------------------------------------------\ndddddd\nddddddddddddd\n_____________________________________________\n\n_____________________________________________\nUsers/user/home/Documents/favorites/clean-architecture.pdf\n---------------------------------------------\nca\ncaaaa\n_____________________________________________\n\n_____________________________________________\nUsers/user/home/Documents/favorites/cqrs.pdf\n---------------------------------------------\ncqrs\nccqqrrss\n_____________________________________________\n\n", output);

}
