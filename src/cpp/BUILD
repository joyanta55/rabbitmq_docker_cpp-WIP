load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")
load("@rules_foreign_cc//foreign_cc:defs.bzl", "make")
load("@io_bazel_rules_docker//container:container.bzl", "container_image", "container_pull","container_load")


make(
    name = "amq",
    lib_source = "@libamq//:build_libamq",
    out_static_libs = ["libamqpcpp.a"],
    out_shared_libs = ["libamqpcpp.so"],
    visibility = ["//visibility:public"],
)



cc_library(
    name = "amqp_lib",
    srcs = ["example/amqp_lib.cpp"],
    hdrs = ["example/amqp_lib.h"],
    deps = [":amq"],
    linkstatic = True,  # Ensures static linking
    
)

cc_binary(
    name = "amqp",
    srcs = ["example/app.cpp"],
    deps = [":amqp_lib"],
    linkstatic = True,
    linkopts = [
        "-lev","-static"
    ],
    
)


container_image(
    name = "amqp_image_ubuntu_cpp",
    base = "@ubuntu_base_image//image",
    files = [":amqp"],
    directory = "/tmp",
    entrypoint = ["/bin/sh", "-c","/tmp/amqp"],
)

container_image(
    name = "amqp_image_centos_cpp",
    base = "@centos_base_image//image",
    files = [":amqp"],
    directory = "/tmp",
    entrypoint = ["/bin/sh", "-c"],
)

