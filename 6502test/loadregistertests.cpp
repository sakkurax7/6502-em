#include "gtest/gtest.h"
#include "cpu_6502.hpp"

class LoadRegisterTest : public ::testing::Test {
    public:
        cpu_6502::CPU cpu;
        mem_28c256::Mem mem;

    void SetUp() override {
        // Called immediately after the constructor
        cpu.Reset( mem );
        cpu.PC = 0x0000;
        EXPECT_EQ(cpu.PC, 0x0);
    }

    void TearDown() override {
        // Called immediately after the test
    }
};

TEST_F(LoadRegisterTest, TestLDAImmediate) {
 /* Start - Inline test */
    mem[0x0000] = cpu.INS_LDA_IM;
    mem[0x0001] = 0x42;

    cpu.Execute(2, mem);

    EXPECT_EQ( cpu.A, 0x42 );
    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);
}

TEST_F(LoadRegisterTest, TestLDAZeroPage) {
    mem[0x0000] = cpu.INS_LDA_ZP;
    mem[0x0001] = 0x69;

    mem[0x0069] = 0x49;

    cpu.Execute(3, mem);

    EXPECT_EQ( cpu.A, 0x49);
    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);
}

TEST_F(LoadRegisterTest, TestLDAZeroPageX) {
    cpu.X = 0x1;
    mem[0x0000] = cpu.INS_LDA_ZPX;
    mem[0x0001] = 0x43;

    mem[0x0044] = 0x50;

    cpu.Execute(4, mem);

    EXPECT_EQ( cpu.A, 0x50);
    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);
}

TEST_F(LoadRegisterTest, TestLDAZeroPageXWhenItWraps) {
    cpu.X = 0xFF;
    mem[0x0000] = cpu.INS_LDA_ZPX;
    mem[0x0001] = 0x80;

    mem[0x007F] = 0x50;

    cpu.Execute(4, mem);

    EXPECT_EQ( cpu.A, 0x50);
    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);
}

TEST_F(LoadRegisterTest, TestLDAAbsolute) {
    mem[0x0000] = cpu.INS_LDA_AB;
    mem[0x0001] = 0x00;
    mem[0x0002] = 0x01;

    mem[0x0100] = 0x1;

    cpu.Execute(4, mem);

    EXPECT_EQ( cpu.A, 0x1);
    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);

}

TEST_F(LoadRegisterTest, TestLDAAbsoluteX) {
    cpu.X = 5;
    mem[0x0000] = cpu.INS_LDA_ABX;
    mem[0x0001] = 0x10;
    mem[0x0002] = 0x00;

    mem[0x0015] = 0x42;

    cpu.Execute(4, mem);

    EXPECT_EQ(cpu.A, 0x42);
    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);

}

TEST_F(LoadRegisterTest, TestLDAAbsoluteY) {
    cpu.Y = 5;
    mem[0x0000] = cpu.INS_LDA_ABY;
    mem[0x0001] = 0x10;
    mem[0x0002] = 0x00;

    mem[0x0015] = 0x42;

    cpu.Execute(4, mem);

    EXPECT_EQ(cpu.A, 0x42);
    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);

}

TEST_F(LoadRegisterTest, TestLDAIndirectX) {
    cpu.X = 0x04;
	mem[0x0000] = cpu.INS_LDA_IDX;
	mem[0x0001] = 0x02;

	mem[0x0006] = 0x00;	//0x2 + 0x4
	mem[0x0007] = 0x80;	
	mem[0x8000] = 0x37;

    cpu.Execute(6, mem);
    
    EXPECT_EQ(cpu.A, 0x37);

    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);
}

TEST_F(LoadRegisterTest, TestLDAIndirectY) {
    cpu.Y = 0x04;
	mem[0x0000] = cpu.INS_LDA_IDY;
	mem[0x0001] = 0x02;

	mem[0x0006] = 0x00;	//0x2 + 0x4
	mem[0x0007] = 0x80;	
	mem[0x8000] = 0x37;

    cpu.Execute(5, mem);
    
    EXPECT_EQ(cpu.A, 0x37);

    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);
}

TEST_F(LoadRegisterTest, TestLDXImmediate) {
    mem[0x0000] = cpu.INS_LDX_IM;
    mem[0x0001] = 0x69;

    cpu.Execute(2, mem);

    EXPECT_EQ(cpu.X, 0x69);
    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);
}

TEST_F(LoadRegisterTest, TestLDXZeroPage) {
    mem[0x0000] = cpu.INS_LDX_ZP;
    mem[0x0001] = 0x80;

    mem[0x0080] = 0x69;

    cpu.Execute(3, mem);

    EXPECT_EQ(cpu.X, 0x69);
    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);
}

TEST_F(LoadRegisterTest, TestLDXZeroPageY) {
    cpu.Y = 0x21;
    EXPECT_EQ(cpu.Y, 0x21);

    mem[0x0000] = cpu.INS_LDX_ZPY;
    mem[0x0001] = 0x21;

    mem[0x0042] = 0x69;

    cpu.Execute(4, mem);

    EXPECT_EQ(cpu.X, 0x69);

    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);
}

TEST_F(LoadRegisterTest, TestLDXZeroPageYWhenItWraps) {
    cpu.Y = 0xFF;

    mem[0x0000] = cpu.INS_LDX_ZPY;
    mem[0x0001] = 0x80;

    mem[0x007F] = 0x69;

    cpu.Execute(4, mem);

    EXPECT_EQ(cpu.X, 0x69);

    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);
}

TEST_F(LoadRegisterTest, TestLDXAbsolute) {
    mem[0x0000] = cpu.INS_LDX_AB;
    mem[0x0001] = 0x34;
    mem[0x0002] = 0x12;

    mem[0x1234] = 0x1;

    cpu.Execute(4, mem);

    EXPECT_EQ( cpu.X, 0x1);

    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);
}

TEST_F(LoadRegisterTest, TestLDXAbsoluteY) {
    cpu.Y = 5;
    mem[0x0000] = cpu.INS_LDX_ABY;
    mem[0x0001] = 0x10;
    mem[0x0002] = 0x00;

    mem[0x0015] = 0x42;

    cpu.Execute(4, mem);

    EXPECT_EQ(cpu.X, 0x42);
    EXPECT_FALSE(cpu.SF.C);
    EXPECT_FALSE(cpu.SF.Z);
    EXPECT_FALSE(cpu.SF.I);
    EXPECT_FALSE(cpu.SF.D);
    EXPECT_FALSE(cpu.SF.B);
    EXPECT_FALSE(cpu.SF.V);
    EXPECT_FALSE(cpu.SF.N);
}
