#include "../src/file_system_builder.h"
#include "../src/file_system_scanner.h"
#include "../src/file_system_parser.h"
#include "../src/tree_visitor.h"

TEST(file_system, scanner) {
    FileSystemScanner fss;
    fss.setPath("structure");

    fss.nextNode();
    ASSERT_EQ("structure/file.txt", fss.currentNodeName());
    ASSERT_FALSE(fss.isFolder());
/*
    fss.nextNode();
    ASSERT_EQ("structure/home", fss.currentNodeName());
    ASSERT_TRUE(fss.isFolder());
    ASSERT_FALSE(fss.isDone());

    fss.nextNode();
    ASSERT_EQ("structure/.DS_Store", fss.currentNodeName());
    ASSERT_FALSE(fss.isFolder());

    fss.nextNode();
    ASSERT_EQ("structure/visitor", fss.currentNodeName());
    ASSERT_TRUE(fss.isFolder());

    fss.nextNode();
    ASSERT_EQ("structure/visitor", fss.currentNodeName());
    ASSERT_TRUE(fss.isDone());*/
}

TEST(file_system, builder) {
    FileSystemBuilder fsb;
    fsb.buildFolder("structure/home");
    fsb.buildFile("structure/home/my_profile");
    fsb.buildFolder("structure/home/Documents");
    fsb.buildFolder("structure/home/Documents/favorites");
    fsb.buildFile("structure/home/Documents/favorites/domain-driven-design.pdf");
    fsb.buildFile("structure/home/Documents/favorites/clean-architecture.pdf");
    fsb.endFolder();
    fsb.buildFile("structure/home/Documents/note.txt");

    TreeVisitor * visitor = new TreeVisitor(OrderBy::NameWithFolderFirst);

    fsb.getRoot()->accept(visitor);
    //cout<< visitor->getTree() <<endl;
}

TEST(file_system, parser) {
    FileSystemBuilder * fsb = new FileSystemBuilder;
    FileSystemParser fsp(fsb);
    fsp.setPath("structure");
    fsp.parse();

    TreeVisitor * visitor = new TreeVisitor(OrderBy::NameWithFolderFirst);

    fsp.getRoot()->accept(visitor);
    //cout<< visitor->getTree() <<endl;
}
