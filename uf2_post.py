Import("env")
import os
import sys

def generate_uf2(source, target, env):
    hex_path = env.subst("$BUILD_DIR/firmware.hex")
    uf2_path = env.subst("$BUILD_DIR/firmware.uf2")

    project_dir = env.subst("$PROJECT_DIR")
    uf2conv_path = os.path.join(project_dir, "uf2conv.py")

    cmd = (
        f"\"{sys.executable}\" "
        f"\"{uf2conv_path}\" "
        f"\"{hex_path}\" "
        f"-c -f 0xADA52840 "
        f"-o \"{uf2_path}\""
    )

    print("Generating UF2...")
    return env.Execute(cmd)

env.AddPostAction("$BUILD_DIR/firmware.hex", generate_uf2)