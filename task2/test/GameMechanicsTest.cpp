#include <gtest/gtest.h>
#include "GameMechanics.h"
#include "GameConfig.h"

TEST(GameMechanicsTest, SingleCellDiesInOneStep) {
    GameConfig config;
    config.setFieldHeight(5);
    config.setFieldHeight(5);
    config.setCells({{2, 2}});
    GameMechanics mechanics(config);
    mechanics.initializeField();
    const auto& field1 = mechanics.getField();
    EXPECT_TRUE(field1[2][2]);  // Клетка жива
    EXPECT_EQ(mechanics.getCurrentIteration(), 0);
    mechanics.step();
    EXPECT_EQ(mechanics.getCurrentIteration(), 1);
    const auto& field2 = mechanics.getField();
    EXPECT_FALSE(field2[2][2]);
}

TEST(GameMechanicsTest, Block2x2StaysAlive) {
    GameConfig config;
    config.setFieldHeight(5);
    config.setFieldHeight(5);
    config.setCells({{2, 2}, {3, 2}, {2, 3}, {3, 3}});
    GameMechanics mechanics(config);
    mechanics.initializeField();
    const auto& field = mechanics.getField();
    EXPECT_TRUE(field[2][2]);
    EXPECT_TRUE(field[3][2]);
    EXPECT_TRUE(field[2][3]);
    EXPECT_TRUE(field[3][3]);

    for (size_t i = 0; i < 5; ++i) {
        mechanics.step();
    }
    const auto& finalField = mechanics.getField();
    EXPECT_TRUE(finalField[2][2]);
    EXPECT_TRUE(finalField[3][2]);
    EXPECT_TRUE(finalField[2][3]);
    EXPECT_TRUE(finalField[3][3]);
    EXPECT_FALSE(finalField[1][1]);
    EXPECT_FALSE(finalField[4][4]);
    EXPECT_FALSE(finalField[2][1]);
    EXPECT_FALSE(finalField[1][2]);
}

TEST(GameMechanicsTest, Blinker3CellsOscillates) {
    GameConfig config;
    config.setFieldWidth(5);
    config.setFieldHeight(5);
    config.setCells({{1, 2}, {2, 2}, {3, 2}});
    GameMechanics mechanics(config);
    mechanics.initializeField();
    mechanics.step();
    const auto& field1 = mechanics.getField();
    EXPECT_FALSE(field1[2][1]);
    EXPECT_TRUE(field1[1][2]);
    EXPECT_TRUE(field1[2][2]);
    EXPECT_TRUE(field1[3][2]);
    EXPECT_FALSE(field1[2][3]);

    mechanics.step();
    const auto& field2 = mechanics.getField();
    EXPECT_TRUE(field2[2][1]);
    EXPECT_FALSE(field2[1][2]);
    EXPECT_TRUE(field2[2][2]);
    EXPECT_FALSE(field2[3][2]);
    EXPECT_TRUE(field2[2][3]);
}

TEST(GameMechanicsTest, EmptyFieldStaysEmpty) {
    GameConfig config;
    config.setFieldWidth(8);
    config.setFieldHeight(8);
    config.setCells({});

    GameMechanics mechanics(config);
    mechanics.initializeField();

    for (size_t i = 0; i < 10; ++i) {
        mechanics.step();
        EXPECT_EQ(mechanics.getCurrentIteration(), i + 1);
    }
    const auto& field = mechanics.getField();
    for (size_t y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; x++) {
            EXPECT_FALSE(field[y][x]);
        }
    }
}

TEST(GameMechanicsTest, ThreeCellsInRowCreatesNewCell) {
    GameConfig config;
    config.setFieldWidth(5);
    config.setFieldHeight(5);
    config.setCells({{1, 2}, {2, 2}, {3, 2}});
    GameMechanics mechanics(config);
    mechanics.initializeField();
    mechanics.step();
    const auto& field = mechanics.getField();
    int aliveCount = 0;
    for (size_t y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; x++) {
            if (field[y][x]) aliveCount++;
        }
    }
    EXPECT_EQ(aliveCount, 3);
}

TEST(GameMechanicsTest, SaveAndLoadCoordinates) {
    GameConfig config;
    config.setFieldWidth(7);
    config.setFieldHeight(7);
    config.setCells({{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}});
    GameMechanics mechanics(config);
    mechanics.initializeField();
    mechanics.saveInFile("test_diagonal.txt");
    FILE* f = fopen("test_diagonal.txt", "r");
    EXPECT_TRUE(f != nullptr);
    if (f) fclose(f);
    remove("test_diagonal.txt");
}