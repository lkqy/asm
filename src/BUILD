load("@rules_cc//cc:defs.bzl", "cc_library")

COPTS = ["-std=c++17", "-Wno-deprecated", "-lrt"]

cc_library(
    name = 'asm',
    srcs = glob(["*/*.cpp", "*/*/*.cpp", "*/*/*/*.cpp"]),
    hdrs = glob(["*/*.h", "*/*/*.h", "*/*/*/*.h"]),
    copts = COPTS,
    visibility = [
        "//visibility:public",
    ],
)
