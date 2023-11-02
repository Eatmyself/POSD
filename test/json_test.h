#include "../src/value.h"
#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/json_iterator.h"
#include "../src/beautify_visitor.h"

TEST(JSonSuite, OneKeyStringValue) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    ASSERT_EQ(v1, jo->getValue("key1"));
    ASSERT_EQ("{\n\"key1\":\"value1\"\n}", jo->toString());

}

TEST(JSonSuite, TwoKeyStringValue) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);
    ASSERT_EQ("\"value1\"", jo->getValue("key1")->toString());
    ASSERT_EQ("\"value2\"", jo->getValue("key2")->toString());
    ASSERT_EQ("{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}", jo->toString());

}

TEST(JSonSuite, Composite) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);
    ASSERT_EQ(jo, j_composite->getValue("keyc"));
    ASSERT_EQ("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}", j_composite->toString());
}

TEST(Jsoniterator, Iterator) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonIterator * tmp = jo->createIterator();
    ASSERT_EQ("key1", tmp->currentKey());
    ASSERT_EQ(v1, tmp->currentValue());
    tmp -> next();
    ASSERT_EQ("key2", tmp->currentKey());
    ASSERT_EQ(v2, tmp->currentValue());
}

TEST(Beautify, Visitor) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    BeautifyVisitor * vi = new BeautifyVisitor;
    jo->accept(vi);
    cout<<vi->getResult()<<endl;
}

TEST(Beautify, Visitor2) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);

    BeautifyVisitor * vi = new BeautifyVisitor;
    j_composite->accept(vi);
    cout<<vi->getResult()<<endl;
}

/*
TEST(Jsoniterator, biggerKey) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key2", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key1", v2);

    JsonIterator * tmp = jo->createIterator();
    ASSERT_EQ("key1", tmp->currentKey());
    ASSERT_EQ(v1, tmp->currentValue());
}*/
