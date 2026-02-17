Import("env")
import sys

def generate_uf2(source, target, env):
    hex_path = env.subst("$BUILD_DIR/${PROGNAME}.hex")
    uf2_path = env.subst("$BUILD_DIR/${PROGNAME}.uf2")

    cmd = (
        f"\"{sys.executable}\" uf2conv.py "
        f"\"{hex_path}\" "
        f"-c -f 0xADA52840 "
        f"-o \"{uf2_path}\""
    )

    return env.Execute(cmd)

env.AddPostAction("$BUILD_DIR/${PROGNAME}.hex", generate_uf2)
