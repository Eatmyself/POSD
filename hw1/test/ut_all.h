#include "../src/iterator.h"
#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/dfs_iterator.h"
#include "../src/null_iterator.h"

TEST(HelloNode, CreateNode) {
    Folder a("home");
    File b("home/Note.txt"),c("home/List.txt");
    ASSERT_EQ("home", a.name());
    ASSERT_EQ("Note.txt", b.name());
    ASSERT_EQ(1, b.numberOfFiles());
    a.add(&b);
    a.add(&c);
    ASSERT_EQ(2, a.numberOfFiles());
    ASSERT_EQ(&b, a.getChildByName("Note.txt"));
    ASSERT_EQ(nullptr, a.getChildByName("Not"));
    a.remove("home/Note.txt");
    ASSERT_EQ(nullptr, a.getChildByName("Note.txt"));
    
    Iterator * tmp = a.createIterator();
    ASSERT_EQ(&c, tmp->currentItem());
}

TEST(HelloNode, Node) {
    Node * a = new Folder("home");
    ASSERT_EQ(nullptr, a->find("w"));
}

TEST(HelloNode, deleteNode) {
    Folder a("home"),b("home/user"),c("home/user/info");
    File aa("home/Note.txt"),ab("home/List.txt"),ba("home/user/ba.txt");
    a.add(&b);
    a.add(&aa);
    a.add(&ab);
    b.add(&ba);
    b.add(&c);

    ASSERT_EQ(&ba, a.find("home/user/ba.txt"));
    a.remove("home/user/ba.txt");
    ASSERT_EQ(nullptr, a.find("home/user/ba.txt"));
}


TEST(StartIterator, FolderIterator) {
    Folder a("home");
    File b("home/Note.txt"),c("home/List.txt");
    a.add(&b);
    a.add(&c);

    FolderIterator it(&a);
    ASSERT_EQ(&b, it.currentItem());
    ASSERT_EQ("Note.txt", it.currentItem()->name());
    it.next();
    ASSERT_EQ(&c, it.currentItem());
    it.next();
    ASSERT_EQ(nullptr, it.currentItem());
    it.next();
    ASSERT_EQ(nullptr, it.currentItem());
    ASSERT_EQ(true, it.isDone());
    it.first();
    ASSERT_EQ(&b, it.currentItem());
}

TEST(StartIterator, createFolderIterator) {
    Folder a("home");
    File b("home/Note.txt"),c("home/List.txt");
    a.add(&b);
    a.add(&c);
    
    Iterator * tmp = a.createIterator();
    ASSERT_EQ(&b, tmp->currentItem());
    
    tmp->next();
    ASSERT_EQ(&c, tmp->currentItem());
    tmp->next();
    ASSERT_EQ(nullptr, tmp->currentItem());
    tmp->next();
    ASSERT_EQ(nullptr, tmp->currentItem());
    ASSERT_EQ(true, tmp->isDone());
    tmp->first();
    ASSERT_EQ(&b, tmp->currentItem());
}

TEST(NullIterator, NullIteratorTest) {
    File b("home/Note.txt");

    Iterator * tmp = b.createIterator();
    ASSERT_EQ(nullptr, tmp->currentItem());
    tmp->next();
    ASSERT_EQ(nullptr, tmp->currentItem());
    ASSERT_EQ(true, tmp->isDone());
    tmp->first();
    ASSERT_EQ(nullptr, tmp->currentItem());
}

TEST(dfs_iterator, dfs) {
    Folder a("home"),b("home/user"),c("home/user/info");
    File aa("home/Note.txt"),ab("home/List.txt"),ba("home/user/ba.txt");
    a.add(&b);
    a.add(&aa);
    a.add(&ab);
    b.add(&ba);
    b.add(&c);
    
    DfsIterator it(&a);
    ASSERT_EQ(&b, it.currentItem());
    ASSERT_EQ("user", it.currentItem()->name());
    it.next();
    ASSERT_EQ(&ba, it.currentItem());
    it.next();
    ASSERT_EQ(&c, it.currentItem());
    it.next();
    ASSERT_EQ(&aa, it.currentItem());
    it.next();
    ASSERT_EQ(&ab, it.currentItem());

    it.next();
    ASSERT_EQ(nullptr, it.currentItem());
    it.next();
    ASSERT_EQ(nullptr, it.currentItem());
    ASSERT_EQ(true, it.isDone());
    it.first();
    ASSERT_EQ(&b, it.currentItem());

}

TEST(bfs_iterator, bfs) {
    Folder a("home"),b("home/user"),c("home/user/info");
    File aa("home/Note.txt"),ab("home/List.txt"),ba("home/user/ba.txt");
    a.add(&b);
    a.add(&aa);
    a.add(&ab);
    b.add(&ba);
    b.add(&c);
    
    BfsIterator it(&a);
    ASSERT_EQ(&b, it.currentItem());
    ASSERT_EQ("user", it.currentItem()->name());
    it.next();
    ASSERT_EQ(&aa, it.currentItem());
    it.next();
    ASSERT_EQ(&ab, it.currentItem());
    ASSERT_EQ(false, it.isDone());
    it.next();
    ASSERT_EQ(&ba, it.currentItem());
    it.next();
    ASSERT_EQ(&c, it.currentItem());

    it.next();
    ASSERT_EQ(nullptr, it.currentItem());
    it.next();
    ASSERT_EQ(nullptr, it.currentItem());
    ASSERT_EQ(true, it.isDone());
    it.first();
    ASSERT_EQ(&b, it.currentItem());

}


