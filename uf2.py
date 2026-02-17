Import("env")
import subprocess
from os.path import join

def build_uf2(source, target, env):
    build_dir = env.subst("$BUILD_DIR")
    bin_path = join(build_dir, "firmware.bin")
    uf2_path = join(build_dir, "firmware.uf2")

    print("Converting BIN to UF2 (nRF52840)...")

    subprocess.call([
        "python",
        env.PioPlatform().get_package_dir("framework-arduino-mbed-seeed")
        + "/tools/uf2conv.py",
        bin_path,
        "-c",
        "-f", "0xADA52840",
        "-o", uf2_path
    ])

env.AddPostAction("$BUILD_DIR/firmware.bin", build_uf2)
