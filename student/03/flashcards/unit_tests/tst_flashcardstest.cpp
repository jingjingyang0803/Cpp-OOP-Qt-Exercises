#include <QtTest>
#include "../card.hh"
#include "../deck.hh"
#include "../utils.hh"

Q_DECLARE_METATYPE(Fields)

class FlashcardsTest : public QObject
{
    Q_OBJECT

private slots:
    void test_card_definitions();
    void test_deck_add_card();
    void test_check_answers_data();
    void test_check_answers();
};

void FlashcardsTest::test_card_definitions()
{
    Card card;
    Fields field_types = {"EN", "DE", "ES"};
    Fields definitions = {"one", "eins", "uno"};

    QVERIFY(card.add_new_definitions(field_types, definitions));
    QVERIFY(card.has_fields({"EN", "DE"}));
    QVERIFY(!card.has_fields({"FI"}));

    Fields returned_defs;
    QVERIFY(card.get_definitions({"ES", "EN"}, returned_defs));

    QCOMPARE(returned_defs.size(), static_cast<size_t>(2));
    QCOMPARE(returned_defs.at(0), std::string("uno"));
    QCOMPARE(returned_defs.at(1), std::string("one"));
}

void FlashcardsTest::test_deck_add_card()
{
    Fields deck_fields = {"EN", "DE", "ES"};
    Deck deck("Numbers", deck_fields);

    QCOMPARE(deck.get_deck_size(), static_cast<size_t>(0));

    QVERIFY(deck.add_card({"EN", "DE", "ES"}, {"one", "eins", "uno"}));
    QCOMPARE(deck.get_deck_size(), static_cast<size_t>(1));

    QVERIFY(deck.add_card({"EN", "DE", "ES"}, {"two", "zwei", "dos"}));
    QCOMPARE(deck.get_deck_size(), static_cast<size_t>(2));

    QVERIFY(!deck.add_card({"EN", "DE"}, {"three", "drei", "tres"}));
    QCOMPARE(deck.get_deck_size(), static_cast<size_t>(2));
}

void FlashcardsTest::test_check_answers_data()
{
    qRegisterMetaType<Fields>("Fields");

    QTest::addColumn<Fields>("answer_fields");
    QTest::addColumn<Fields>("definitions");
    QTest::addColumn<Fields>("answers");
    QTest::addColumn<double>("expected_score");

    QTest::newRow("all correct")
            << Fields({"EN", "ES"})
            << Fields({"one", "uno"})
            << Fields({"one", "uno"})
            << 1.0;

    QTest::newRow("one correct")
            << Fields({"EN", "ES"})
            << Fields({"one", "uno"})
            << Fields({"one", "x"})
            << 0.5;

    QTest::newRow("all wrong")
            << Fields({"EN", "ES"})
            << Fields({"one", "uno"})
            << Fields({"x", "y"})
            << 0.0;

    QTest::newRow("empty correct definition gives point")
            << Fields({"EN", "ES"})
            << Fields({"", "uno"})
            << Fields({"anything", "uno"})
            << 1.0;
}

void FlashcardsTest::test_check_answers()
{
    QFETCH(Fields, answer_fields);
    QFETCH(Fields, definitions);
    QFETCH(Fields, answers);
    QFETCH(double, expected_score);

    Card card;
    Fields card_fields = {"EN", "ES"};

    QVERIFY(card.add_new_definitions(card_fields, definitions));
    QCOMPARE(card.check_answers(answer_fields, answers), expected_score);
}

QTEST_APPLESS_MAIN(FlashcardsTest)

#include "tst_flashcardstest.moc"