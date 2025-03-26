load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake", "make")
load("@rules_oci//oci:defs.bzl", "oci_image", "oci_load")
load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_pkg//pkg:tar.bzl", "pkg_tar")

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


pkg_tar(
    name = "tar",
    srcs = [":amqp"],
)

oci_image(
    name = "image",
    base = "@docker_lib_ubuntu",
    tars = [":tar"],
    entrypoint = ["/amqp"],
)

# Use with 'bazel run' to load the oci image into a container runtime.
# The image is designated using `repo_tags` attribute.
oci_load(
    name = "image_load",
    image = ":image",
    repo_tags = ["amqp_j:latest"],
)
