from cpt.packager import ConanMultiPackager


if __name__ == "__main__":
    builder = ConanMultiPackager()

    builder.add(settings={"os": "Macos", "arch": "x86_64"})
    builder.add(settings={"os": "iOS", "os.version": "9.0", "arch": "armv8.3"})
    builder.add(settings={"os": "watchOS", "os.version": "4.0", "arch": "armv7k"})
    builder.add(settings={"os": "tvOS", "os.version": "11.0", "arch": "armv8"})
    builder.add(
        settings={
            "os": "Macos",
            "arch": "x86_64",
            "os.subsystem": "catalyst",
        }
    )
    builder.add(
        settings={"os": "iOS", "os.version": "9.0", "arch": "armv8.3"},
        options={"darwin-toolchain:enable_bitcode": True},
    )

    builder.run()
