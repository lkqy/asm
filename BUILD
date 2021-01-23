load("@rules_cc//cc:defs.bzl", "cc_test")
load("@rules_cc//cc:defs.bzl", "cc_library")

COPTS = ["-std=c++17", "-Wno-deprecated", "-lrt"]

cc_library(
    name = "gtest",
    srcs = glob(
        ["src/*.cc"],
        exclude = ["src/gtest-all.cc"],
    ),
    hdrs = glob([
        "include/**/*.h",
        "src/*.h",
    ]),
    copts = ["-Iexternal/gtest/include"],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)
