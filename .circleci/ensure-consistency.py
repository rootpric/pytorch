#!/usr/bin/env python3

import os
import subprocess
import sys
import tempfile

import generate_config_yml


CHECKED_IN_FILE = "config.yml"
REGENERATION_SCRIPT = "regenerate.sh"

PARENT_DIR = os.path.basename(os.path.dirname(os.path.abspath(__file__)))
README_PATH = os.path.join(PARENT_DIR, "README.md")

ERROR_MESSAGE_TEMPLATE = """
The checked-in CircleCI "%s" file does not match what was generated by the scripts.
Please re-run the "%s" script in the "%s" directory and commit the result. See "%s" for more information.
"""


def check_consistency():

    _, temp_filename = tempfile.mkstemp("-generated-config.yml")

    with open(temp_filename, "w") as fh:
        generate_config_yml.stitch_sources(fh)

    try:
        subprocess.check_call(["cmp", temp_filename, CHECKED_IN_FILE])
    except subprocess.CalledProcessError:
        sys.exit(ERROR_MESSAGE_TEMPLATE % (CHECKED_IN_FILE, REGENERATION_SCRIPT, PARENT_DIR, README_PATH))
    finally:
        os.remove(temp_filename)


if __name__ == "__main__":
    check_consistency()
