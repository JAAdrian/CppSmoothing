#include <gtest/gtest.h>
#include <dlfcn.h>

const std::string DLL_NAME = "/home/j/Dokumente/Git-Projects/CppPlayground/build/libprocessor.so";

class RecursiveAveragingTest : public testing::Test {
    protected:
        void* dll_handle;

        void SetUp() override {
            dll_handle = dlopen((DLL_NAME).c_str(), RTLD_NOW);
        }

        void TearDown() override {
            dlclose(dll_handle);
        }
};

TEST_F(RecursiveAveragingTest, CanLoad) {
    const char* error = dlerror();
    EXPECT_EQ(*error, NULL);
}
