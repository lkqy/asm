load("@rules_cc//cc:defs.bzl", "cc_test")

COPTS = ["-std=c++17", "-Wno-deprecated"]

cc_test(
    name = "asm_test",
    srcs = glob(["*/*.cpp"]),
    copts = ["-Iexternal/gtest/include"] + COPTS,
    deps = [
        "@gtest",
        "//src:asm",
    ],
    linkopts = ["-lrt"],
    linkstatic=1,
)
