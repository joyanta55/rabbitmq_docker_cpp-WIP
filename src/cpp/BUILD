load("@io_bazel_rules_docker//container:container.bzl", "container_image", "container_load", "container_pull")
load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake", "make")

make(
    name = "amq",
    lib_source = "@libamq//:build_libamq",
    out_shared_libs = ["libamqpcpp.so"],
    out_static_libs = ["libamqpcpp.a"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "amqp_lib",
    srcs = ["example/amqp_lib.cpp"],
    hdrs = ["example/amqp_lib.h"],
    linkstatic = True,  # Ensures static linking
    deps = [":amq"],
)

cc_binary(
    name = "amqp",
    srcs = ["example/app.cpp"],
    linkopts = [
        "-lev",
        "-static",
    ],
    linkstatic = True,
    deps = [":amqp_lib"],
)

container_image(
    name = "amqp_image_ubuntu_cpp",
    base = "@ubuntu_base_image//image",
    directory = "/tmp",
    entrypoint = [
        "/bin/sh",
        "-c",
        "/tmp/amqp",
    ],
    files = [":amqp"],
)

container_image(
    name = "amqp_image_centos_cpp",
    base = "@centos_base_image//image",
    directory = "/tmp",
    entrypoint = [
        "/bin/sh",
        "-c",
        "/tmp/amqp",
    ],
    files = [":amqp"],
)
